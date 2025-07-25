/*
 * Copyright (c) 2015-2022 The Khronos Group Inc.
 * Copyright (c) 2015-2022 Valve Corporation
 * Copyright (c) 2015-2022 LunarG, Inc.
 * Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * Copyright (c) 2023-2023 RasterGrid Kft.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Ian Elliott <ian@lunarg.com>
 * Author: Jon Ashburn <jon@lunarg.com>
 * Author: Ian Elliott <ianelliott@google.com>
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Lenny Komow <lenny@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 */

#include <stdio.h>
#include <stdlib.h>

#include <vulkan/vk_icd.h>

#include "allocation.h"
#include "loader.h"
#include "log.h"
#include "stack_allocation.h"
#include "vk_loader_platform.h"
#include "wsi.h"

// The first ICD/Loader interface that support querying the SurfaceKHR from
// the ICDs.
#define ICD_VER_SUPPORTS_ICD_SURFACE_KHR 3

struct loader_struct_type_info {
    VkStructureType stype;
    size_t size;
};

// This function unwraps the application-provided surface handle into the ICD-specific surface handle
// corresponding to the specified physical device. If the ICD-specific surface handle does not exist
// yet, then this function also creates of the ICD-specific surface object. This enables lazy creation
// of ICD-specific surface objects and therefore avoids creating surfaces for ICDs that may not be able
// to or should not create the specific type of surface (one example is the VK_KHR_display extension
// where the VkDisplayModeKHR handles the surfaces are created from are physical-device-specific
// non-dispatchable handles and therefore they should not be passed down to a foreign ICD).
VkResult wsi_unwrap_icd_surface(struct loader_icd_term *icd_term, VkSurfaceKHR *surface) {
    VkIcdSurface *icd_surface = (VkIcdSurface *)(uintptr_t)(*surface);

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
    if (icd_surface->base.platform == VK_ICD_WSI_PLATFORM_ANDROID) {
        // Android does not use ICD-created surfaces
        // NOTE: This may be incorrect and in fact the legacy code could result in out-of-bounds
        // accesses to VkIcdSurface::surface_index in case of Android, but we preserved the legacy
        // behavior (while also eliminating the chance for out-of-bounds accesses).
        return VK_SUCCESS;
    }
#endif  // VK_USE_PLATFORM_ANDROID_KHR
#if defined(VK_USE_PLATFORM_MACOS_MVK)
    if (icd_surface->base.platform == VK_ICD_WSI_PLATFORM_IOS) {
        // iOS does not use ICD-created surfaces (matching legacy behavior)
        // NOTE: This may be incorrect and in fact the legacy code could result in out-of-bounds
        // accesses to VkIcdSurface::surface_index in case of Android, but we preserved the legacy
        // behavior (while also eliminating the chance for out-of-bounds accesses).
        return VK_SUCCESS;
    }
#endif  // VK_USE_PLATFORM_MACOS_MVK

    if (NULL == icd_term->surface_list.list ||
        icd_term->surface_list.capacity <= icd_surface->surface_index * sizeof(VkSurfaceKHR)) {
        // This surface handle is not one that was created by the loader, therefore we simply return
        // the input surface handle unmodified. This matches legacy behavior.
        return VK_SUCCESS;
    }

    VkResult result = VK_SUCCESS;
    if (icd_term->scanned_icd->interface_version >= ICD_VER_SUPPORTS_ICD_SURFACE_KHR) {
        VkAllocationCallbacks *pAllocator = icd_surface->callbacks_valid ? &icd_surface->callbacks : NULL;
        if (VK_NULL_HANDLE == icd_term->surface_list.list[icd_surface->surface_index]) {
            // If the surface does not exist yet for the target ICD, then create it lazily
            switch (icd_surface->base.platform) {
#ifndef VULKANSC
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)
                case VK_ICD_WSI_PLATFORM_WAYLAND:
                    if (NULL != icd_term->dispatch.CreateWaylandSurfaceKHR &&
                        icd_term->enabled_instance_extensions.khr_wayland_surface) {
                        result = icd_term->dispatch.CreateWaylandSurfaceKHR(
                            icd_term->instance, (const VkWaylandSurfaceCreateInfoKHR *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_WAYLAND_KHR

#if defined(VK_USE_PLATFORM_WIN32_KHR)
                case VK_ICD_WSI_PLATFORM_WIN32:
                    if (NULL != icd_term->dispatch.CreateWin32SurfaceKHR &&
                        icd_term->enabled_instance_extensions.khr_win32_surface) {
                        result = icd_term->dispatch.CreateWin32SurfaceKHR(
                            icd_term->instance, (const VkWin32SurfaceCreateInfoKHR *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_WIN32_KHR

#if defined(VK_USE_PLATFORM_XCB_KHR)
                case VK_ICD_WSI_PLATFORM_XCB:
                    if (NULL != icd_term->dispatch.CreateXcbSurfaceKHR && icd_term->enabled_instance_extensions.khr_xcb_surface) {
                        result = icd_term->dispatch.CreateXcbSurfaceKHR(
                            icd_term->instance, (const VkXcbSurfaceCreateInfoKHR *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_XCB_KHR

#if defined(VK_USE_PLATFORM_XLIB_KHR)
                case VK_ICD_WSI_PLATFORM_XLIB:
                    if (NULL != icd_term->dispatch.CreateXlibSurfaceKHR && icd_term->enabled_instance_extensions.khr_xlib_surface) {
                        result = icd_term->dispatch.CreateXlibSurfaceKHR(
                            icd_term->instance, (const VkXlibSurfaceCreateInfoKHR *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_XLIB_KHR

#if defined(VK_USE_PLATFORM_MACOS_MVK)
                case VK_ICD_WSI_PLATFORM_MACOS:
                    if (NULL != icd_term->dispatch.CreateMacOSSurfaceMVK &&
                        icd_term->enabled_instance_extensions.mvk_macos_surface) {
                        result = icd_term->dispatch.CreateMacOSSurfaceMVK(
                            icd_term->instance, (const VkMacOSSurfaceCreateInfoMVK *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_MACOS_MVK
#endif  // VULKANSC

                case VK_ICD_WSI_PLATFORM_DISPLAY:
                    if (NULL != icd_term->dispatch.CreateDisplayPlaneSurfaceKHR &&
                        icd_term->enabled_instance_extensions.khr_display) {
                        result = icd_term->dispatch.CreateDisplayPlaneSurfaceKHR(
                            icd_term->instance, (const VkDisplaySurfaceCreateInfoKHR *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;

                case VK_ICD_WSI_PLATFORM_HEADLESS:
                    if (NULL != icd_term->dispatch.CreateHeadlessSurfaceEXT &&
                        icd_term->enabled_instance_extensions.ext_headless_surface) {
                        result = icd_term->dispatch.CreateHeadlessSurfaceEXT(
                            icd_term->instance, (const VkHeadlessSurfaceCreateInfoEXT *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;

#ifndef VULKANSC
#if defined(VK_USE_PLATFORM_METAL_EXT)
                case VK_ICD_WSI_PLATFORM_METAL:
                    if (NULL != icd_term->dispatch.CreateMetalSurfaceEXT &&
                        icd_term->enabled_instance_extensions.ext_metal_surface) {
                        result = icd_term->dispatch.CreateMetalSurfaceEXT(
                            icd_term->instance, (const VkMetalSurfaceCreateInfoEXT *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_METAL_EXT

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)
                case VK_ICD_WSI_PLATFORM_DIRECTFB:
                    if (NULL != icd_term->dispatch.CreateDirectFBSurfaceEXT &&
                        icd_term->enabled_instance_extensions.ext_directfb_surface) {
                        result = icd_term->dispatch.CreateDirectFBSurfaceEXT(
                            icd_term->instance, (const VkDirectFBSurfaceCreateInfoEXT *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_DIRECTFB_EXT

#if defined(VK_USE_PLATFORM_VI_NN)
                case VK_ICD_WSI_PLATFORM_VI:
                    if (NULL != icd_term->dispatch.CreateViSurfaceNN && icd_term->enabled_instance_extensions.nn_vi_surface) {
                        result = icd_term->dispatch.CreateViSurfaceNN(
                            icd_term->instance, (const VkViSurfaceCreateInfoNN *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_VI_NN

#if defined(VK_USE_PLATFORM_GGP)
                case VK_ICD_WSI_PLATFORM_GGP:
                    if (NULL != icd_term->dispatch.CreateStreamDescriptorSurfaceGGP &&
                        icd_term->enabled_instance_extensions.qnx_screen_surface) {
                        result = icd_term->dispatch.CreateStreamDescriptorSurfaceGGP(
                            icd_term->instance, (const VkStreamDescriptorSurfaceCreateInfoGGP *)icd_surface->create_info,
                            pAllocator, &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_GGP

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
                case VK_ICD_WSI_PLATFORM_SCREEN:
                    if (NULL != icd_term->dispatch.CreateScreenSurfaceQNX &&
                        icd_term->enabled_instance_extensions.qnx_screen_surface) {
                        result = icd_term->dispatch.CreateScreenSurfaceQNX(
                            icd_term->instance, (const VkScreenSurfaceCreateInfoQNX *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_SCREEN_QNX

#if defined(VK_USE_PLATFORM_FUCHSIA)
                case VK_ICD_WSI_PLATFORM_FUCHSIA:
                    if (NULL != icd_term->dispatch.CreateImagePipeSurfaceFUCHSIA &&
                        icd_term->enabled_instance_extensions.fuchsia_imagepipe_surface) {
                        result = icd_term->dispatch.CreateImagePipeSurfaceFUCHSIA(
                            icd_term->instance, (const VkImagePipeSurfaceCreateInfoFUCHSIA *)icd_surface->create_info, pAllocator,
                            &icd_term->surface_list.list[icd_surface->surface_index]);
                    } else {
                        result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    }
                    break;
#endif  // VK_USE_PLATFORM_FUCHSIA
#endif  // VULKANSC

                default:
                    // Not supported
                    result = VK_ERROR_EXTENSION_NOT_PRESENT;
                    break;
            }
        }

        *surface = icd_term->surface_list.list[icd_surface->surface_index];
    }

    return result;
}

// Linux WSI surface extensions are not always compiled into the loader. (Assume
// for Windows the KHR_win32_surface is always compiled into loader). A given
// Linux build environment might not have the headers required for building one
// of the three extensions  (Xlib, Xcb, Wayland).  Thus, need to check if
// the built loader actually supports the particular Linux surface extension.
// If not supported by the built loader it will not be included in the list of
// enumerated instance extensions.  This solves the issue where an ICD or layer
// advertises support for a given Linux surface extension but the loader was not
// built to support the extension.
bool wsi_unsupported_instance_extension(const VkExtensionProperties *ext_prop) {
#if !defined(VK_USE_PLATFORM_WAYLAND_KHR)
    if (!strcmp(ext_prop->extensionName, "VK_KHR_wayland_surface")) return true;
#endif  // VK_USE_PLATFORM_WAYLAND_KHR
#if !defined(VK_USE_PLATFORM_XCB_KHR)
    if (!strcmp(ext_prop->extensionName, "VK_KHR_xcb_surface")) return true;
#endif  // VK_USE_PLATFORM_XCB_KHR
#if !defined(VK_USE_PLATFORM_XLIB_KHR)
    if (!strcmp(ext_prop->extensionName, "VK_KHR_xlib_surface")) return true;
#endif  // VK_USE_PLATFORM_XLIB_KHR
#if !defined(VK_USE_PLATFORM_DIRECTFB_EXT)
    if (!strcmp(ext_prop->extensionName, "VK_EXT_directfb_surface")) return true;
#endif  // VK_USE_PLATFORM_DIRECTFB_EXT
#if !defined(VK_USE_PLATFORM_SCREEN_QNX)
    if (!strcmp(ext_prop->extensionName, "VK_QNX_screen_surface")) return true;
#endif  // VK_USE_PLATFORM_SCREEN_QNX

    return false;
}

// Functions for the VK_KHR_surface extension:

// This is the trampoline entrypoint for DestroySurfaceKHR
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface,
                                                             const VkAllocationCallbacks *pAllocator) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroySurfaceKHR: Invalid instance [VUID-vkDestroySurfaceKHR-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    loader_inst->disp->layer_inst_disp.DestroySurfaceKHR(loader_inst->instance, surface, pAllocator);
}

// This is the instance chain terminator function for DestroySurfaceKHR
VKAPI_ATTR void VKAPI_CALL terminator_DestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface,
                                                        const VkAllocationCallbacks *pAllocator) {
    struct loader_instance *loader_inst = loader_get_instance(instance);

    VkIcdSurface *icd_surface = (VkIcdSurface *)(uintptr_t)(surface);
    if (NULL != icd_surface) {
        for (struct loader_icd_term *icd_term = loader_inst->icd_terms; icd_term != NULL; icd_term = icd_term->next) {
            if (icd_term->enabled_instance_extensions.khr_surface &&
                icd_term->scanned_icd->interface_version >= ICD_VER_SUPPORTS_ICD_SURFACE_KHR &&
                NULL != icd_term->dispatch.DestroySurfaceKHR && icd_term->surface_list.list[icd_surface->surface_index]) {
                icd_term->dispatch.DestroySurfaceKHR(icd_term->instance, icd_term->surface_list.list[icd_surface->surface_index],
                                                     pAllocator);
                icd_term->surface_list.list[icd_surface->surface_index] = (VkSurfaceKHR)(uintptr_t)NULL;

            } else {
                // The real_icd_surface for any ICD not supporting the
                // proper interface version should be NULL.  If not, then
                // we have a problem.
                assert((VkSurfaceKHR)(uintptr_t)NULL == icd_term->surface_list.list[icd_surface->surface_index]);
            }
        }
        if (NULL != icd_surface->create_info) {
            loader_instance_heap_free(loader_inst, icd_surface->create_info);
        }
        loader_release_object_from_list(&loader_inst->surfaces_list, icd_surface->surface_index);
        loader_instance_heap_free(loader_inst, (void *)(uintptr_t)surface);
    }
}

// This is the trampoline entrypoint for GetPhysicalDeviceSurfaceSupportKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                  uint32_t queueFamilyIndex, VkSurfaceKHR surface,
                                                                                  VkBool32 *pSupported) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSurfaceSupportKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSurfaceSupportKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSurfaceSupportKHR(unwrapped_phys_dev, queueFamilyIndex, surface, pSupported);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceSurfaceSupportKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice,
                                                                             uint32_t queueFamilyIndex, VkSurfaceKHR surface,
                                                                             VkBool32 *pSupported) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_surface extension not enabled. vkGetPhysicalDeviceSurfaceSupportKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == pSupported) {
        loader_log(loader_inst, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "NULL pointer passed into vkGetPhysicalDeviceSurfaceSupportKHR for pSupported!");
        abort();
    }
    *pSupported = false;

    if (NULL == icd_term->dispatch.GetPhysicalDeviceSurfaceSupportKHR) {
        // set pSupported to false as this driver doesn't support WSI functionality
        *pSupported = false;
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceSurfaceSupportKHR!");
        return VK_SUCCESS;
    }

    VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
    if (res != VK_SUCCESS) {
        // set pSupported to false as this driver doesn't support WSI functionality
        *pSupported = false;
        return VK_SUCCESS;
    }

    return icd_term->dispatch.GetPhysicalDeviceSurfaceSupportKHR(phys_dev_term->phys_dev, queueFamilyIndex, surface, pSupported);
}

// This is the trampoline entrypoint for GetPhysicalDeviceSurfaceCapabilitiesKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR *pSurfaceCapabilities) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSurfaceCapabilitiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSurfaceCapabilitiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSurfaceCapabilitiesKHR(unwrapped_phys_dev, surface, pSurfaceCapabilities);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceSurfaceCapabilitiesKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice,
                                                                                  VkSurfaceKHR surface,
                                                                                  VkSurfaceCapabilitiesKHR *pSurfaceCapabilities) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_surface extension not enabled. vkGetPhysicalDeviceSurfaceCapabilitiesKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == pSurfaceCapabilities) {
        loader_log(loader_inst, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "NULL pointer passed into vkGetPhysicalDeviceSurfaceCapabilitiesKHR for pSurfaceCapabilities!");
        abort();
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilitiesKHR) {
        // Zero out the capabilities as this driver doesn't support WSI functionality
        memset(pSurfaceCapabilities, 0, sizeof(VkSurfaceCapabilitiesKHR));
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceSurfaceCapabilitiesKHR!");
        return VK_SUCCESS;
    }

    VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
    if (res != VK_SUCCESS) {
        return res;
    }

    return icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilitiesKHR(phys_dev_term->phys_dev, surface, pSurfaceCapabilities);
}

// This is the trampoline entrypoint for GetPhysicalDeviceSurfaceFormatsKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice,
                                                                                  VkSurfaceKHR surface,
                                                                                  uint32_t *pSurfaceFormatCount,
                                                                                  VkSurfaceFormatKHR *pSurfaceFormats) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSurfaceFormatsKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSurfaceFormatsKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSurfaceFormatsKHR(unwrapped_phys_dev, surface, pSurfaceFormatCount, pSurfaceFormats);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceSurfaceFormatsKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
                                                                             uint32_t *pSurfaceFormatCount,
                                                                             VkSurfaceFormatKHR *pSurfaceFormats) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_surface extension not enabled. vkGetPhysicalDeviceSurfaceFormatsKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == pSurfaceFormatCount) {
        loader_log(loader_inst, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "NULL pointer passed into vkGetPhysicalDeviceSurfaceFormatsKHR for pSurfaceFormatCount!");
        abort();
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceSurfaceFormatsKHR) {
        // Zero out the format count as this driver doesn't support WSI functionality
        *pSurfaceFormatCount = 0;
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceSurfaceFormatsKHR!");
        return VK_SUCCESS;
    }

    if (VK_NULL_HANDLE != surface) {
        VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
        if (res != VK_SUCCESS) {
            return res;
        }
    }

    return icd_term->dispatch.GetPhysicalDeviceSurfaceFormatsKHR(phys_dev_term->phys_dev, surface, pSurfaceFormatCount,
                                                                 pSurfaceFormats);
}

// This is the trampoline entrypoint for GetPhysicalDeviceSurfacePresentModesKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice,
                                                                                       VkSurfaceKHR surface,
                                                                                       uint32_t *pPresentModeCount,
                                                                                       VkPresentModeKHR *pPresentModes) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSurfacePresentModesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSurfacePresentModesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSurfacePresentModesKHR(unwrapped_phys_dev, surface, pPresentModeCount, pPresentModes);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceSurfacePresentModesKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice,
                                                                                  VkSurfaceKHR surface, uint32_t *pPresentModeCount,
                                                                                  VkPresentModeKHR *pPresentModes) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_surface extension not enabled. vkGetPhysicalDeviceSurfacePresentModesKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == pPresentModeCount) {
        loader_log(loader_inst, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "NULL pointer passed into vkGetPhysicalDeviceSurfacePresentModesKHR for pPresentModeCount!");
        abort();
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceSurfacePresentModesKHR) {
        // Zero out the present mode count as this driver doesn't support WSI functionality
        *pPresentModeCount = 0;
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceSurfacePresentModesKHR!");
        return VK_SUCCESS;
    }

    if (VK_NULL_HANDLE != surface) {
        VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
        if (res != VK_SUCCESS) {
            return res;
        }
    }

    return icd_term->dispatch.GetPhysicalDeviceSurfacePresentModesKHR(phys_dev_term->phys_dev, surface, pPresentModeCount,
                                                                      pPresentModes);
}

// Functions for the VK_KHR_swapchain extension:

// This is the trampoline entrypoint for CreateSwapchainKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR *pCreateInfo,
                                                                  const VkAllocationCallbacks *pAllocator,
                                                                  VkSwapchainKHR *pSwapchain) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSwapchainKHR: Invalid device [VUID-vkCreateSwapchainKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (NULL == disp->CreateSwapchainKHR) {
        struct loader_device *dev = *((struct loader_device **)device);
        loader_log(NULL != dev ? dev->phys_dev_term->this_icd_term->this_instance : NULL,
                   VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSwapchainKHR: Driver's function pointer was NULL, returning VK_SUCCESS. Was the VK_KHR_swapchain "
                   "extension enabled?");
        abort();
    }
    return disp->CreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR *pCreateInfo,
                                                             const VkAllocationCallbacks *pAllocator, VkSwapchainKHR *pSwapchain) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSwapchainKHR Terminator: device handle. This is likely the result of a "
                   "layer wrapping device handles and failing to unwrap them in all functions. "
                   "[VUID-vkCreateSwapchainKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (NULL == pCreateInfo) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSwapchainKHR: Invalid pCreateInfo pointer [VUID-vkCreateSwapchainKHR-pCreateInfo-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Need to gracefully handle the function pointer not being found.
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.CreateSwapchainKHR) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSwapchainKHR: Driver's function pointer was NULL, returning VK_SUCCESS. Was the VK_KHR_swapchain "
                   "extension enabled?");
        return VK_SUCCESS;
    }

    VkSwapchainCreateInfoKHR create_info_copy = *pCreateInfo;
    VkResult res = wsi_unwrap_icd_surface(icd_term, &create_info_copy.surface);
    if (res != VK_SUCCESS) {
        return res;
    }

    return dev->loader_dispatch.extension_terminator_dispatch.CreateSwapchainKHR(device, &create_info_copy, pAllocator, pSwapchain);
}

#ifndef VULKANSC
// This is the trampoline entrypoint for DestroySwapchainKHR
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain,
                                                               const VkAllocationCallbacks *pAllocator) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDestroySwapchainKHR: Invalid device [VUID-vkDestroySwapchainKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->DestroySwapchainKHR(device, swapchain, pAllocator);
}
#endif  // VULKANSC

// This is the trampoline entrypoint for GetSwapchainImagesKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain,
                                                                     uint32_t *pSwapchainImageCount, VkImage *pSwapchainImages) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSwapchainImagesKHR: Invalid device [VUID-vkGetSwapchainImagesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
}

// This is the trampoline entrypoint for AcquireNextImageKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout,
                                                                   VkSemaphore semaphore, VkFence fence, uint32_t *pImageIndex) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquireNextImageKHR: Invalid device [VUID-vkAcquireNextImageKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->AcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
}

// This is the trampoline entrypoint for QueuePresentKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR *pPresentInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueuePresentKHR: Invalid queue [VUID-vkQueuePresentKHR-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->QueuePresentKHR(queue, pPresentInfo);
}

VkResult allocate_icd_surface_struct(struct loader_instance *instance, size_t base_size, size_t platform_size,
                                     const VkAllocationCallbacks *pAllocator, VkIcdSurface **out_icd_surface) {
    uint32_t next_index = 0;
    VkIcdSurface *icd_surface = NULL;
    VkResult res = loader_get_next_available_entry(instance, &instance->surfaces_list, &next_index, pAllocator);
    if (res != VK_SUCCESS) {
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    icd_surface = loader_instance_heap_calloc(instance, sizeof(VkIcdSurface), VK_SYSTEM_ALLOCATION_SCOPE_OBJECT);
    if (icd_surface == NULL) {
        res = VK_ERROR_OUT_OF_HOST_MEMORY;
        goto out;
    }
    // Setup the new sizes and offsets so we can grow the structures in the
    // future without having problems
    icd_surface->base_size = (uint32_t)base_size;
    icd_surface->platform_size = (uint32_t)platform_size;
    icd_surface->non_platform_offset = (uint32_t)((uint8_t *)(&icd_surface->base_size) - (uint8_t *)icd_surface);
    icd_surface->entire_size = sizeof(VkIcdSurface);
    icd_surface->surface_index = next_index;
    icd_surface->create_info = NULL;

    for (struct loader_icd_term *icd_term = instance->icd_terms; icd_term != NULL; icd_term = icd_term->next) {
        if (icd_term->enabled_instance_extensions.khr_surface &&
            icd_term->scanned_icd->interface_version >= ICD_VER_SUPPORTS_ICD_SURFACE_KHR) {
            if (icd_term->surface_list.list == NULL) {
                res =
                    loader_init_generic_list(instance, (struct loader_generic_list *)&icd_term->surface_list, sizeof(VkSurfaceKHR));
                if (res != VK_SUCCESS) {
                    goto out;
                }
            } else if (icd_term->surface_list.capacity <= next_index * sizeof(VkSurfaceKHR)) {
                res = loader_resize_generic_list(instance, (struct loader_generic_list *)&icd_term->surface_list);
                if (res != VK_SUCCESS) {
                    goto out;
                }
            }
        }
    }

    *out_icd_surface = icd_surface;
out:
    if (res != VK_SUCCESS) {
        loader_instance_heap_free(instance, icd_surface);
        // cleanup of icd_term->surface_list is done during instance destruction
    }
    return res;
}

VkResult copy_surface_create_info(struct loader_instance *loader_inst, VkIcdSurface *icd_surface, const void *create_info,
                                  size_t struct_type_info_count, const struct loader_struct_type_info *struct_type_info,
                                  const char *base_struct_name, const VkAllocationCallbacks *pAllocator) {
    size_t create_info_total_size = 0;
    const void *pnext = create_info;
    while (NULL != pnext) {
        VkBaseInStructure base = {0};
        memcpy(&base, pnext, sizeof(VkBaseInStructure));
        bool known_struct = false;
        for (size_t i = 0; i < struct_type_info_count; ++i) {
            if (base.sType == struct_type_info[i].stype) {
                create_info_total_size += loader_aligned_size(struct_type_info[i].size);
                pnext = base.pNext;
                known_struct = true;
                break;
            }
        }
        if (!known_struct) {
            loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0, "Unsupported extension structure in %s pNext chain.",
                       base_struct_name);
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    icd_surface->create_info = loader_instance_heap_alloc(loader_inst, create_info_total_size, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT);
    if (NULL == icd_surface->create_info) {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    uint8_t *dst = (uint8_t *)icd_surface->create_info;
    VkBaseInStructure *prev_struct = NULL;
    pnext = create_info;
    while (NULL != pnext) {
        VkBaseInStructure base = {0};
        memcpy(&base, pnext, sizeof(VkBaseInStructure));
        for (size_t i = 0; i < struct_type_info_count; ++i) {
            if (base.sType == struct_type_info[i].stype) {
                memcpy(dst, pnext, struct_type_info[i].size);
                if (NULL != prev_struct) {
                    prev_struct->pNext = (const VkBaseInStructure *)dst;
                }
                prev_struct = (VkBaseInStructure *)dst;
                dst += loader_aligned_size(struct_type_info[i].size);
                pnext = base.pNext;
                break;
            }
        }
    }
    if (pAllocator) {
        icd_surface->callbacks_valid = true;
        icd_surface->callbacks = *pAllocator;
    }

    return VK_SUCCESS;
}

void cleanup_surface_creation(struct loader_instance *loader_inst, VkResult result, VkIcdSurface *icd_surface,
                              const VkAllocationCallbacks *pAllocator) {
    if (VK_SUCCESS != result && NULL != icd_surface) {
        for (struct loader_icd_term *icd_term = loader_inst->icd_terms; icd_term != NULL; icd_term = icd_term->next) {
            if (icd_term->enabled_instance_extensions.khr_surface && NULL != icd_term->surface_list.list &&
                icd_term->surface_list.capacity > icd_surface->surface_index * sizeof(VkSurfaceKHR) &&
                icd_term->surface_list.list[icd_surface->surface_index] && NULL != icd_term->dispatch.DestroySurfaceKHR) {
                icd_term->dispatch.DestroySurfaceKHR(icd_term->instance, icd_term->surface_list.list[icd_surface->surface_index],
                                                     pAllocator);
            }
        }
        if (loader_inst->surfaces_list.list &&
            loader_inst->surfaces_list.capacity > icd_surface->surface_index * sizeof(struct loader_used_object_status)) {
            loader_inst->surfaces_list.list[icd_surface->surface_index].status = VK_FALSE;
            if (NULL != pAllocator) {
                loader_inst->surfaces_list.list[icd_surface->surface_index].allocation_callbacks = *pAllocator;
            }
        }
        if (NULL != icd_surface->create_info) {
            loader_instance_heap_free(loader_inst, icd_surface->create_info);
        }
        loader_instance_heap_free(loader_inst, icd_surface);
    }
}

#ifndef VULKANSC
#if defined(VK_USE_PLATFORM_WIN32_KHR)

// Functions for the VK_KHR_win32_surface extension:

// This is the trampoline entrypoint for CreateWin32SurfaceKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(VkInstance instance,
                                                                     const VkWin32SurfaceCreateInfoKHR *pCreateInfo,
                                                                     const VkAllocationCallbacks *pAllocator,
                                                                     VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateWin32SurfaceKHR: Invalid instance [VUID-vkCreateWin32SurfaceKHR-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateWin32SurfaceKHR(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateWin32SurfaceKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR *pCreateInfo,
                                                                const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // Initialize pSurface to NULL just to be safe.
    *pSurface = VK_NULL_HANDLE;
    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.khr_win32_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_win32_surface extension not enabled. vkCreateWin32SurfaceKHR not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->win_surf.base), sizeof(icd_surface->win_surf), pAllocator,
                                         &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->win_surf.base.platform = VK_ICD_WSI_PLATFORM_WIN32;
    icd_surface->win_surf.hinstance = pCreateInfo->hinstance;
    icd_surface->win_surf.hwnd = pCreateInfo->hwnd;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, sizeof(VkWin32SurfaceCreateInfoKHR)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkWin32SurfaceCreateInfoKHR", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);
    return result;
}

// This is the trampoline entrypoint for
// GetPhysicalDeviceWin32PresentationSupportKHR
LOADER_EXPORT VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                            uint32_t queueFamilyIndex) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceWin32PresentationSupportKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceWin32PresentationSupportKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceWin32PresentationSupportKHR(unwrapped_phys_dev, queueFamilyIndex);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceWin32PresentationSupportKHR
VKAPI_ATTR VkBool32 VKAPI_CALL terminator_GetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                       uint32_t queueFamilyIndex) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_win32_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_win32_surface extension not enabled. vkGetPhysicalDeviceWin32PresentationSupportKHR not executed!");
        return VK_FALSE;
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceWin32PresentationSupportKHR) {
        // return VK_FALSE as this driver doesn't support WSI functionality
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceWin32PresentationSupportKHR!");
        return VK_FALSE;
    }

    return icd_term->dispatch.GetPhysicalDeviceWin32PresentationSupportKHR(phys_dev_term->phys_dev, queueFamilyIndex);
}
#endif  // VK_USE_PLATFORM_WIN32_KHR

#if defined(VK_USE_PLATFORM_WAYLAND_KHR)

// This is the trampoline entrypoint for CreateWaylandSurfaceKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateWaylandSurfaceKHR(VkInstance instance,
                                                                       const VkWaylandSurfaceCreateInfoKHR *pCreateInfo,
                                                                       const VkAllocationCallbacks *pAllocator,
                                                                       VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateWaylandSurfaceKHR: Invalid instance [VUID-vkCreateWaylandSurfaceKHR-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateWaylandSurfaceKHR(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateWaylandSurfaceKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateWaylandSurfaceKHR(VkInstance instance,
                                                                  const VkWaylandSurfaceCreateInfoKHR *pCreateInfo,
                                                                  const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.khr_wayland_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_wayland_surface extension not enabled. vkCreateWaylandSurfaceKHR not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->wayland_surf.base), sizeof(icd_surface->wayland_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->wayland_surf.base.platform = VK_ICD_WSI_PLATFORM_WAYLAND;
    icd_surface->wayland_surf.display = pCreateInfo->display;
    icd_surface->wayland_surf.surface = pCreateInfo->surface;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR, sizeof(VkWaylandSurfaceCreateInfoKHR)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkWaylandSurfaceCreateInfoKHR", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

// This is the trampoline entrypoint for
// GetPhysicalDeviceWaylandPresentationSupportKHR
LOADER_EXPORT VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                              uint32_t queueFamilyIndex,
                                                                                              struct wl_display *display) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceWaylandPresentationSupportKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceWaylandPresentationSupportKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceWaylandPresentationSupportKHR(unwrapped_phys_dev, queueFamilyIndex, display);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceWaylandPresentationSupportKHR
VKAPI_ATTR VkBool32 VKAPI_CALL terminator_GetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                         uint32_t queueFamilyIndex,
                                                                                         struct wl_display *display) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_wayland_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_wayland_surface extension not enabled. vkGetPhysicalDeviceWaylandPresentationSupportKHR not executed!");
        return VK_FALSE;
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceWaylandPresentationSupportKHR) {
        // return VK_FALSE as this driver doesn't support WSI functionality
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceWaylandPresentationSupportKHR!");
        return VK_FALSE;
    }

    return icd_term->dispatch.GetPhysicalDeviceWaylandPresentationSupportKHR(phys_dev_term->phys_dev, queueFamilyIndex, display);
}
#endif  // VK_USE_PLATFORM_WAYLAND_KHR

#if defined(VK_USE_PLATFORM_XCB_KHR)

// Functions for the VK_KHR_xcb_surface extension:

// This is the trampoline entrypoint for CreateXcbSurfaceKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateXcbSurfaceKHR(VkInstance instance,
                                                                   const VkXcbSurfaceCreateInfoKHR *pCreateInfo,
                                                                   const VkAllocationCallbacks *pAllocator,
                                                                   VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateXcbSurfaceKHR: Invalid instance [VUID-vkCreateXcbSurfaceKHR-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateXcbSurfaceKHR(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateXcbSurfaceKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR *pCreateInfo,
                                                              const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.khr_xcb_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_xcb_surface extension not enabled. vkCreateXcbSurfaceKHR not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->xcb_surf.base), sizeof(icd_surface->xcb_surf), pAllocator,
                                         &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->xcb_surf.base.platform = VK_ICD_WSI_PLATFORM_XCB;
    icd_surface->xcb_surf.connection = pCreateInfo->connection;
    icd_surface->xcb_surf.window = pCreateInfo->window;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR, sizeof(VkXcbSurfaceCreateInfoKHR)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkXcbSurfaceCreateInfoKHR", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

// This is the trampoline entrypoint for
// GetPhysicalDeviceXcbPresentationSupportKHR
LOADER_EXPORT VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                          uint32_t queueFamilyIndex,
                                                                                          xcb_connection_t *connection,
                                                                                          xcb_visualid_t visual_id) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceXcbPresentationSupportKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceXcbPresentationSupportKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceXcbPresentationSupportKHR(unwrapped_phys_dev, queueFamilyIndex, connection, visual_id);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceXcbPresentationSupportKHR
VKAPI_ATTR VkBool32 VKAPI_CALL terminator_GetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                     uint32_t queueFamilyIndex,
                                                                                     xcb_connection_t *connection,
                                                                                     xcb_visualid_t visual_id) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_xcb_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_xcb_surface extension not enabled. vkGetPhysicalDeviceXcbPresentationSupportKHR not executed!");
        return VK_FALSE;
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceXcbPresentationSupportKHR) {
        // return VK_FALSE as this driver doesn't support WSI functionality
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceXcbPresentationSupportKHR!");
        return VK_FALSE;
    }

    return icd_term->dispatch.GetPhysicalDeviceXcbPresentationSupportKHR(phys_dev_term->phys_dev, queueFamilyIndex, connection,
                                                                         visual_id);
}
#endif  // VK_USE_PLATFORM_XCB_KHR

#if defined(VK_USE_PLATFORM_XLIB_KHR)

// Functions for the VK_KHR_xlib_surface extension:

// This is the trampoline entrypoint for CreateXlibSurfaceKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateXlibSurfaceKHR(VkInstance instance,
                                                                    const VkXlibSurfaceCreateInfoKHR *pCreateInfo,
                                                                    const VkAllocationCallbacks *pAllocator,
                                                                    VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateXlibSurfaceKHR: Invalid instance [VUID-vkCreateXlibSurfaceKHR-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateXlibSurfaceKHR(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateXlibSurfaceKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR *pCreateInfo,
                                                               const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.khr_xlib_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_xlib_surface extension not enabled. vkCreateXlibSurfaceKHR not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->xlib_surf.base), sizeof(icd_surface->xlib_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->xlib_surf.base.platform = VK_ICD_WSI_PLATFORM_XLIB;
    icd_surface->xlib_surf.dpy = pCreateInfo->dpy;
    icd_surface->xlib_surf.window = pCreateInfo->window;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR, sizeof(VkXlibSurfaceCreateInfoKHR)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkXlibSurfaceCreateInfoKHR", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

// This is the trampoline entrypoint for
// GetPhysicalDeviceXlibPresentationSupportKHR
LOADER_EXPORT VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                           uint32_t queueFamilyIndex, Display *dpy,
                                                                                           VisualID visualID) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceXlibPresentationSupportKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceXlibPresentationSupportKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceXlibPresentationSupportKHR(unwrapped_phys_dev, queueFamilyIndex, dpy, visualID);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceXlibPresentationSupportKHR
VKAPI_ATTR VkBool32 VKAPI_CALL terminator_GetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice,
                                                                                      uint32_t queueFamilyIndex, Display *dpy,
                                                                                      VisualID visualID) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_xlib_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_xlib_surface extension not enabled. vkGetPhysicalDeviceXlibPresentationSupportKHR not executed!");
        return VK_FALSE;
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceXlibPresentationSupportKHR) {
        // return VK_FALSE as this driver doesn't support WSI functionality
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceXlibPresentationSupportKHR!");
        return VK_FALSE;
    }

    return icd_term->dispatch.GetPhysicalDeviceXlibPresentationSupportKHR(phys_dev_term->phys_dev, queueFamilyIndex, dpy, visualID);
}
#endif  // VK_USE_PLATFORM_XLIB_KHR
#endif  // VULKANSC

#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)

// Functions for the VK_EXT_directfb_surface extension:

// This is the trampoline entrypoint for CreateDirectFBSurfaceEXT
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDirectFBSurfaceEXT(VkInstance instance,
                                                                        const VkDirectFBSurfaceCreateInfoEXT *pCreateInfo,
                                                                        const VkAllocationCallbacks *pAllocator,
                                                                        VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateDirectFBSurfaceEXT: Invalid instance [VUID-vkCreateDirectFBSurfaceEXT-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateDirectFBSurfaceEXT(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateDirectFBSurfaceEXT
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateDirectFBSurfaceEXT(VkInstance instance,
                                                                   const VkDirectFBSurfaceCreateInfoEXT *pCreateInfo,
                                                                   const VkAllocationCallbacks *pAllocator,
                                                                   VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.ext_directfb_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_EXT_directfb_surface extension not enabled. vkCreateDirectFBSurfaceEXT not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->directfb_surf.base), sizeof(icd_surface->directfb_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->directfb_surf.base.platform = VK_ICD_WSI_PLATFORM_DIRECTFB;
    icd_surface->directfb_surf.dfb = pCreateInfo->dfb;
    icd_surface->directfb_surf.surface = pCreateInfo->surface;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_DIRECTFB_SURFACE_CREATE_INFO_EXT, sizeof(VkDirectFBSurfaceCreateInfoEXT)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkDirectFBSurfaceCreateInfoEXT", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

// This is the trampoline entrypoint for
// GetPhysicalDeviceDirectFBPresentationSupportEXT
LOADER_EXPORT VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceDirectFBPresentationSupportEXT(VkPhysicalDevice physicalDevice,
                                                                                               uint32_t queueFamilyIndex,
                                                                                               IDirectFB *dfb) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceDirectFBPresentationSupportEXT: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceDirectFBPresentationSupportEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceDirectFBPresentationSupportEXT(unwrapped_phys_dev, queueFamilyIndex, dfb);
}

// This is the instance chain terminator function for
// GetPhysicalDeviceDirectFBPresentationSupportEXT
VKAPI_ATTR VkBool32 VKAPI_CALL terminator_GetPhysicalDeviceDirectFBPresentationSupportEXT(VkPhysicalDevice physicalDevice,
                                                                                          uint32_t queueFamilyIndex,
                                                                                          IDirectFB *dfb) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.ext_directfb_surface) {
        loader_log(
            loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
            "VK_EXT_directfb_surface extension not enabled. vkGetPhysicalDeviceDirectFBPresentationSupportKHR not executed!");
        return VK_FALSE;
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceDirectFBPresentationSupportEXT) {
        // return VK_FALSE as this driver doesn't support WSI functionality
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceDirectFBPresentationSupportEXT!");
        return VK_FALSE;
    }

    return icd_term->dispatch.GetPhysicalDeviceDirectFBPresentationSupportEXT(phys_dev_term->phys_dev, queueFamilyIndex, dfb);
}

#endif  // VK_USE_PLATFORM_DIRECTFB_EXT

#if defined(VK_USE_PLATFORM_ANDROID_KHR)

// Functions for the VK_KHR_android_surface extension:

// This is the trampoline entrypoint for CreateAndroidSurfaceKHR
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateAndroidSurfaceKHR(VkInstance instance,
                                                                       const VkAndroidSurfaceCreateInfoKHR *pCreateInfo,
                                                                       const VkAllocationCallbacks *pAllocator,
                                                                       VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateAndroidSurfaceKHR: Invalid instance [VUID-vkCreateAndroidSurfaceKHR-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateAndroidSurfaceKHR(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateAndroidSurfaceKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateAndroidSurfaceKHR(VkInstance instance,
                                                                  const VkAndroidSurfaceCreateInfoKHR *pCreateInfo,
                                                                  const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.khr_display) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_display extension not enabled. vkCreateAndroidSurfaceKHR not executed!");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    // Next, if so, proceed with the implementation of this function:
    VkIcdSurfaceAndroid *icd_surface =
        loader_instance_heap_alloc(loader_inst, sizeof(VkIcdSurfaceAndroid), VK_SYSTEM_ALLOCATION_SCOPE_OBJECT);
    if (icd_surface == NULL) {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    icd_surface->base.platform = VK_ICD_WSI_PLATFORM_ANDROID;
    icd_surface->window = pCreateInfo->window;

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

    return VK_SUCCESS;
}

#endif  // VK_USE_PLATFORM_ANDROID_KHR

// Functions for the VK_EXT_headless_surface extension:

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateHeadlessSurfaceEXT(VkInstance instance,
                                                                        const VkHeadlessSurfaceCreateInfoEXT *pCreateInfo,
                                                                        const VkAllocationCallbacks *pAllocator,
                                                                        VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateHeadlessSurfaceEXT: Invalid instance [VUID-vkCreateHeadlessSurfaceEXT-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateHeadlessSurfaceEXT(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateHeadlessSurfaceEXT(VkInstance instance,
                                                                   const VkHeadlessSurfaceCreateInfoEXT *pCreateInfo,
                                                                   const VkAllocationCallbacks *pAllocator,
                                                                   VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.ext_headless_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_EXT_headless_surface extension not enabled.  "
                   "vkCreateHeadlessSurfaceEXT not executed!");
        return VK_SUCCESS;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->headless_surf.base), sizeof(icd_surface->headless_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->headless_surf.base.platform = VK_ICD_WSI_PLATFORM_HEADLESS;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_HEADLESS_SURFACE_CREATE_INFO_EXT, sizeof(VkHeadlessSurfaceCreateInfoEXT)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkHeadlessSurfaceCreateInfoEXT", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

// Ensure we are properly setting VK_USE_PLATFORM_METAL_EXT, VK_USE_PLATFORM_IOS_MVK, and VK_USE_PLATFORM_MACOS_MVK.
#if __APPLE__

#ifndef VK_USE_PLATFORM_METAL_EXT
#error "VK_USE_PLATFORM_METAL_EXT not defined!"
#endif

#include <TargetConditionals.h>

#if TARGET_OS_IOS

#ifndef VK_USE_PLATFORM_IOS_MVK
#error "VK_USE_PLATFORM_IOS_MVK not defined!"
#endif

#endif  //  TARGET_OS_IOS

#if TARGET_OS_OSX

#ifndef VK_USE_PLATFORM_MACOS_MVK
#error "VK_USE_PLATFORM_MACOS_MVK not defined!"
#endif

#endif  // TARGET_OS_OSX

#endif  // __APPLE__

#if defined(VK_USE_PLATFORM_MACOS_MVK)

// Functions for the VK_MVK_macos_surface extension:

// This is the trampoline entrypoint for CreateMacOSSurfaceMVK
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateMacOSSurfaceMVK(VkInstance instance,
                                                                     const VkMacOSSurfaceCreateInfoMVK *pCreateInfo,
                                                                     const VkAllocationCallbacks *pAllocator,
                                                                     VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateMacOSSurfaceMVK: Invalid instance [VUID-vkCreateMacOSSurfaceMVK-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateMacOSSurfaceMVK(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateMacOSSurfaceKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateMacOSSurfaceMVK(VkInstance instance, const VkMacOSSurfaceCreateInfoMVK *pCreateInfo,
                                                                const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.mvk_macos_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_MVK_macos_surface extension not enabled. vkCreateMacOSSurfaceMVK not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->macos_surf.base), sizeof(icd_surface->macos_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->macos_surf.base.platform = VK_ICD_WSI_PLATFORM_MACOS;
    icd_surface->macos_surf.pView = pCreateInfo->pView;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK, sizeof(VkMacOSSurfaceCreateInfoMVK)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkMacOSSurfaceCreateInfoMVK", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

#endif  // VK_USE_PLATFORM_MACOS_MVK

#if defined(VK_USE_PLATFORM_IOS_MVK)

// Functions for the VK_MVK_ios_surface extension:

// This is the trampoline entrypoint for CreateIOSSurfaceMVK
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateIOSSurfaceMVK(VkInstance instance,
                                                                   const VkIOSSurfaceCreateInfoMVK *pCreateInfo,
                                                                   const VkAllocationCallbacks *pAllocator,
                                                                   VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateIOSSurfaceMVK: Invalid instance [VUID-vkCreateIOSSurfaceMVK-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateIOSSurfaceMVK(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateIOSSurfaceKHR
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateIOSSurfaceMVK(VkInstance instance, const VkIOSSurfaceCreateInfoMVK *pCreateInfo,
                                                              const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    (void)pAllocator;

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.mvk_ios_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_MVK_ios_surface extension not enabled. vkCreateIOSSurfaceMVK not executed!");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    // Next, if so, proceed with the implementation of this function:
    VkIcdSurfaceIOS *icd_surface =
        loader_instance_heap_alloc(loader_inst, sizeof(VkIcdSurfaceIOS), VK_SYSTEM_ALLOCATION_SCOPE_OBJECT);
    if (icd_surface == NULL) {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }

    icd_surface->base.platform = VK_ICD_WSI_PLATFORM_IOS;
    icd_surface->pView = pCreateInfo->pView;

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

    return VK_SUCCESS;
}

#endif  // VK_USE_PLATFORM_IOS_MVK

#if defined(VK_USE_PLATFORM_GGP)

// Functions for the VK_GGP_stream_descriptor_surface extension:

// This is the trampoline entrypoint for CreateStreamDescriptorSurfaceGGP
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL
vkCreateStreamDescriptorSurfaceGGP(VkInstance instance, const VkStreamDescriptorSurfaceCreateInfoGGP *pCreateInfo,
                                   const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(
            NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
            "vkCreateStreamDescriptorSurfaceGGP: Invalid instance [VUID-vkCreateStreamDescriptorSurfaceGGP-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateStreamDescriptorSurfaceGGP(loader_inst->instance, pCreateInfo, pAllocator,
                                                                               pSurface);
}

// This is the instance chain terminator function for CreateStreamDescriptorSurfaceGGP
VKAPI_ATTR VkResult VKAPI_CALL
terminator_CreateStreamDescriptorSurfaceGGP(VkInstance instance, const VkStreamDescriptorSurfaceCreateInfoGGP *pCreateInfo,
                                            const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.wsi_ggp_surface_enabled) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_GGP_stream_descriptor_surface extension not enabled. vkCreateStreamDescriptorSurfaceGGP not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->ggp_surf.base), sizeof(icd_surface->ggp_surf), pAllocator,
                                         &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->ggp_surf.base.platform = VK_ICD_WSI_PLATFORM_GGP;
    icd_surface->ggp_surf.streamDescriptor = pCreateInfo->streamDescriptor;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_STREAM_DESCRIPTOR_SURFACE_CREATE_INFO_GGP, sizeof(VkStreamDescriptorSurfaceCreateInfoGGP)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkStreamDescriptorSurfaceCreateInfoGGP", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

#endif  // VK_USE_PLATFORM_GGP

#if defined(VK_USE_PLATFORM_METAL_EXT)

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateMetalSurfaceEXT(VkInstance instance,
                                                                     const VkMetalSurfaceCreateInfoEXT *pCreateInfo,
                                                                     const VkAllocationCallbacks *pAllocator,
                                                                     VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateMetalSurfaceEXT: Invalid instance [VUID-vkCreateMetalSurfaceEXT-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateMetalSurfaceEXT(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateMetalSurfaceEXT(VkInstance instance, const VkMetalSurfaceCreateInfoEXT *pCreateInfo,
                                                                const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.ext_metal_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_EXT_metal_surface extension not enabled. vkCreateMetalSurfaceEXT will not be executed.");
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->metal_surf.base), sizeof(icd_surface->metal_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->metal_surf.base.platform = VK_ICD_WSI_PLATFORM_METAL;
    icd_surface->metal_surf.pLayer = pCreateInfo->pLayer;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT, sizeof(VkMetalSurfaceCreateInfoEXT)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkMetalSurfaceCreateInfoEXT", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

#endif  // VK_USE_PLATFORM_METAL_EXT

#ifndef VULKANSC
#if defined(VK_USE_PLATFORM_SCREEN_QNX)

// This is the trampoline entrypoint for CreateScreenSurfaceQNX
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateScreenSurfaceQNX(VkInstance instance,
                                                                      const VkScreenSurfaceCreateInfoQNX *pCreateInfo,
                                                                      const VkAllocationCallbacks *pAllocator,
                                                                      VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateScreenSurfaceQNX: Invalid instance [VUID-vkCreateScreenSurfaceQNX-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateScreenSurfaceQNX(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateScreenSurfaceQNX
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateScreenSurfaceQNX(VkInstance instance,
                                                                 const VkScreenSurfaceCreateInfoQNX *pCreateInfo,
                                                                 const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.qnx_screen_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_QNX_screen_surface extension not enabled. vkCreateScreenSurfaceQNX not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->screen_surf.base), sizeof(icd_surface->screen_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->screen_surf.base.platform = VK_ICD_WSI_PLATFORM_SCREEN;
    icd_surface->screen_surf.context = pCreateInfo->context;
    icd_surface->screen_surf.window = pCreateInfo->window;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX, sizeof(VkScreenSurfaceCreateInfoQNX)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkScreenSurfaceCreateInfoQNX", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

// This is the trampoline entrypoint for
// GetPhysicalDeviceScreenPresentationSupportQNX
LOADER_EXPORT VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceScreenPresentationSupportQNX(VkPhysicalDevice physicalDevice,
                                                                                             uint32_t queueFamilyIndex,
                                                                                             struct _screen_window *window) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceScreenPresentationSupportQNX: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceScreenPresentationSupportQNX-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    const VkLayerInstanceDispatchTable *disp = loader_get_instance_layer_dispatch(physicalDevice);
    VkBool32 res = disp->GetPhysicalDeviceScreenPresentationSupportQNX(unwrapped_phys_dev, queueFamilyIndex, window);
    return res;
}

// This is the instance chain terminator function for
// GetPhysicalDeviceScreenPresentationSupportQNX
VKAPI_ATTR VkBool32 VKAPI_CALL terminator_GetPhysicalDeviceScreenPresentationSupportQNX(VkPhysicalDevice physicalDevice,
                                                                                        uint32_t queueFamilyIndex,
                                                                                        struct _screen_window *window) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.qnx_screen_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_QNX_screen_surface extension not enabled. vkGetPhysicalDeviceScreenPresentationSupportQNX not executed!");
        return VK_FALSE;
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceScreenPresentationSupportQNX) {
        // return VK_FALSE as this driver doesn't support WSI functionality
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceScreenPresentationSupportQNX!");
        return VK_FALSE;
    }

    return icd_term->dispatch.GetPhysicalDeviceScreenPresentationSupportQNX(phys_dev_term->phys_dev, queueFamilyIndex, window);
}
#endif  // VK_USE_PLATFORM_SCREEN_QNX
#endif  // VULKANSC

#if defined(VK_USE_PLATFORM_VI_NN)

// Functions for the VK_NN_vi_surface extension:

// This is the trampoline entrypoint for CreateViSurfaceNN
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateViSurfaceNN(VkInstance instance, const VkViSurfaceCreateInfoNN *pCreateInfo,
                                                                 const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateViSurfaceNN: Invalid instance [VUID-vkCreateViSurfaceNN-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateViSurfaceNN(loader_inst->instance, pCreateInfo, pAllocator, pSurface);
}

// This is the instance chain terminator function for CreateViSurfaceNN
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateViSurfaceNN(VkInstance instance, const VkViSurfaceCreateInfoNN *pCreateInfo,
                                                            const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.nn_vi_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_NN_vi_surface extension not enabled. vkCreateViSurfaceNN not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->vi_surf.base), sizeof(icd_surface->vi_surf), pAllocator,
                                         &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->vi_surf.base.platform = VK_ICD_WSI_PLATFORM_VI;
    icd_surface->vi_surf.window = pCreateInfo->window;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_VI_SURFACE_CREATE_INFO_NN, sizeof(VkViSurfaceCreateInfoNN)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkViSurfaceCreateInfoNN", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

#endif  // VK_USE_PLATFORM_VI_NN

// Functions for the VK_KHR_display instance extension:
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice,
                                                                                     uint32_t *pPropertyCount,
                                                                                     VkDisplayPropertiesKHR *pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceDisplayPropertiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceDisplayPropertiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    VkResult res = disp->GetPhysicalDeviceDisplayPropertiesKHR(unwrapped_phys_dev, pPropertyCount, pProperties);
    return res;
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice,
                                                                                uint32_t *pPropertyCount,
                                                                                VkDisplayPropertiesKHR *pProperties) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_display) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_display extension not enabled. vkGetPhysicalDeviceDisplayPropertiesKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceDisplayPropertiesKHR) {
        loader_log(loader_inst, VULKAN_LOADER_WARN_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceDisplayPropertiesKHR!");
        // return 0 for property count as this driver doesn't support WSI functionality
        if (pPropertyCount) {
            *pPropertyCount = 0;
        }
        return VK_SUCCESS;
    }

    return icd_term->dispatch.GetPhysicalDeviceDisplayPropertiesKHR(phys_dev_term->phys_dev, pPropertyCount, pProperties);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPlanePropertiesKHR(
    VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkDisplayPlanePropertiesKHR *pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceDisplayPlanePropertiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceDisplayPlanePropertiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    VkResult res = disp->GetPhysicalDeviceDisplayPlanePropertiesKHR(unwrapped_phys_dev, pPropertyCount, pProperties);
    return res;
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice,
                                                                                     uint32_t *pPropertyCount,
                                                                                     VkDisplayPlanePropertiesKHR *pProperties) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_display) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_display extension not enabled. vkGetPhysicalDeviceDisplayPlanePropertiesKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == icd_term->dispatch.GetPhysicalDeviceDisplayPlanePropertiesKHR) {
        loader_log(loader_inst, VULKAN_LOADER_WARN_BIT, 0,
                   "ICD for selected physical device does not export vkGetPhysicalDeviceDisplayPlanePropertiesKHR!");
        // return 0 for property count as this driver doesn't support WSI functionality
        if (pPropertyCount) {
            *pPropertyCount = 0;
        }
        return VK_SUCCESS;
    }

    return icd_term->dispatch.GetPhysicalDeviceDisplayPlanePropertiesKHR(phys_dev_term->phys_dev, pPropertyCount, pProperties);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice,
                                                                                   uint32_t planeIndex, uint32_t *pDisplayCount,
                                                                                   VkDisplayKHR *pDisplays) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDisplayPlaneSupportedDisplaysKHR: Invalid physicalDevice "
                   "[VUID-vkGetDisplayPlaneSupportedDisplaysKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    VkResult res = disp->GetDisplayPlaneSupportedDisplaysKHR(unwrapped_phys_dev, planeIndex, pDisplayCount, pDisplays);
    return res;
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex,
                                                                              uint32_t *pDisplayCount, VkDisplayKHR *pDisplays) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_display) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_display extension not enabled. vkGetDisplayPlaneSupportedDisplaysKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == icd_term->dispatch.GetDisplayPlaneSupportedDisplaysKHR) {
        loader_log(loader_inst, VULKAN_LOADER_WARN_BIT, 0,
                   "ICD for selected physical device does not export vkGetDisplayPlaneSupportedDisplaysKHR!");
        // return 0 for property count as this driver doesn't support WSI functionality
        if (pDisplayCount) {
            *pDisplayCount = 0;
        }
        return VK_SUCCESS;
    }

    return icd_term->dispatch.GetDisplayPlaneSupportedDisplaysKHR(phys_dev_term->phys_dev, planeIndex, pDisplayCount, pDisplays);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display,
                                                                           uint32_t *pPropertyCount,
                                                                           VkDisplayModePropertiesKHR *pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDisplayModePropertiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetDisplayModePropertiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    VkResult res = disp->GetDisplayModePropertiesKHR(unwrapped_phys_dev, display, pPropertyCount, pProperties);
    return res;
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display,
                                                                      uint32_t *pPropertyCount,
                                                                      VkDisplayModePropertiesKHR *pProperties) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_display) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_display extension not enabled. vkGetDisplayModePropertiesKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == icd_term->dispatch.GetDisplayModePropertiesKHR) {
        loader_log(loader_inst, VULKAN_LOADER_WARN_BIT, 0,
                   "ICD for selected physical device does not export vkGetDisplayModePropertiesKHR!");
        // return 0 for property count as this driver doesn't support WSI functionality
        if (pPropertyCount) {
            *pPropertyCount = 0;
        }
        return VK_SUCCESS;
    }

    return icd_term->dispatch.GetDisplayModePropertiesKHR(phys_dev_term->phys_dev, display, pPropertyCount, pProperties);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display,
                                                                    const VkDisplayModeCreateInfoKHR *pCreateInfo,
                                                                    const VkAllocationCallbacks *pAllocator,
                                                                    VkDisplayModeKHR *pMode) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateDisplayModeKHR: Invalid physicalDevice "
                   "[VUID-vkCreateDisplayModeKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    VkResult res = disp->CreateDisplayModeKHR(unwrapped_phys_dev, display, pCreateInfo, pAllocator, pMode);
    return res;
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display,
                                                               const VkDisplayModeCreateInfoKHR *pCreateInfo,
                                                               const VkAllocationCallbacks *pAllocator, VkDisplayModeKHR *pMode) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_display) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_display extension not enabled. vkCreateDisplayModeKHR not executed!");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    if (NULL == icd_term->dispatch.CreateDisplayModeKHR) {
        // Can't emulate, so return an appropriate error
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD for selected physical device does not export vkCreateDisplayModeKHR!");
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    return icd_term->dispatch.CreateDisplayModeKHR(phys_dev_term->phys_dev, display, pCreateInfo, pAllocator, pMode);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice,
                                                                              VkDisplayModeKHR mode, uint32_t planeIndex,
                                                                              VkDisplayPlaneCapabilitiesKHR *pCapabilities) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDisplayPlaneCapabilitiesKHR: Invalid physicalDevice "
                   "[VUID-vkGetDisplayPlaneCapabilitiesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    VkResult res = disp->GetDisplayPlaneCapabilitiesKHR(unwrapped_phys_dev, mode, planeIndex, pCapabilities);
    return res;
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode,
                                                                         uint32_t planeIndex,
                                                                         VkDisplayPlaneCapabilitiesKHR *pCapabilities) {
    // First, check to ensure the appropriate extension was enabled:
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;
    if (!loader_inst->enabled_extensions.khr_display) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_display extension not enabled. vkGetDisplayPlaneCapabilitiesKHR not executed!");
        return VK_SUCCESS;
    }

    if (NULL == icd_term->dispatch.GetDisplayPlaneCapabilitiesKHR) {
        // Emulate support
        loader_log(loader_inst, VULKAN_LOADER_WARN_BIT, 0,
                   "ICD for selected physical device does not export vkGetDisplayPlaneCapabilitiesKHR!");
        if (pCapabilities) {
            memset(pCapabilities, 0, sizeof(VkDisplayPlaneCapabilitiesKHR));
        }
        return VK_SUCCESS;
    }

    return icd_term->dispatch.GetDisplayPlaneCapabilitiesKHR(phys_dev_term->phys_dev, mode, planeIndex, pCapabilities);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDisplayPlaneSurfaceKHR(VkInstance instance,
                                                                            const VkDisplaySurfaceCreateInfoKHR *pCreateInfo,
                                                                            const VkAllocationCallbacks *pAllocator,
                                                                            VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateDisplayPlaneSurfaceKHR: Invalid instance [VUID-vkCreateDisplayPlaneSurfaceKHR-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateDisplayPlaneSurfaceKHR(loader_inst->instance, pCreateInfo, pAllocator,
                                                                           pSurface);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateDisplayPlaneSurfaceKHR(VkInstance instance,
                                                                       const VkDisplaySurfaceCreateInfoKHR *pCreateInfo,
                                                                       const VkAllocationCallbacks *pAllocator,
                                                                       VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;
    loader_platform_thread_lock_mutex(&loader_lock);

    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.khr_display) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_display extension not enabled. vkCreateDisplayPlaneSurfaceKHR not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->display_surf.base), sizeof(icd_surface->display_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->display_surf.base.platform = VK_ICD_WSI_PLATFORM_DISPLAY;
    icd_surface->display_surf.displayMode = pCreateInfo->displayMode;
    icd_surface->display_surf.planeIndex = pCreateInfo->planeIndex;
    icd_surface->display_surf.planeStackIndex = pCreateInfo->planeStackIndex;
    icd_surface->display_surf.transform = pCreateInfo->transform;
    icd_surface->display_surf.globalAlpha = pCreateInfo->globalAlpha;
    icd_surface->display_surf.alphaMode = pCreateInfo->alphaMode;
    icd_surface->display_surf.imageExtent = pCreateInfo->imageExtent;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR, sizeof(VkDisplaySurfaceCreateInfoKHR)},
        {VK_STRUCTURE_TYPE_DISPLAY_SURFACE_STEREO_CREATE_INFO_NV, sizeof(VkDisplaySurfaceStereoCreateInfoNV)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkDisplaySurfaceCreateInfoKHR", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);
    loader_platform_thread_unlock_mutex(&loader_lock);

    return result;
}

// EXT_display_swapchain Extension command

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount,
                                                                         const VkSwapchainCreateInfoKHR *pCreateInfos,
                                                                         const VkAllocationCallbacks *pAllocator,
                                                                         VkSwapchainKHR *pSwapchains) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSharedSwapchainsKHR: Invalid device [VUID-vkCreateSharedSwapchainsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateSharedSwapchainsKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount,
                                                                    const VkSwapchainCreateInfoKHR *pCreateInfos,
                                                                    const VkAllocationCallbacks *pAllocator,
                                                                    VkSwapchainKHR *pSwapchains) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSharedSwapchainsKHR Terminator: Invalid device handle. This is likely the result of a "
                   "layer wrapping device handles and failing to unwrap them in all functions. "
                   "[VUID-vkCreateSharedSwapchainsKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (NULL != icd_term->surface_list.list) {
        loader_log(NULL, VULKAN_LOADER_ERROR_BIT, 0,
                   "vkCreateSharedSwapchainsKHR Terminator: No VkSurfaceKHR objects were created, indicating an application "
                   "bug. Returning VK_SUCCESS. ");
        return VK_SUCCESS;
    }
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.CreateSharedSwapchainsKHR) {
        loader_log(NULL, VULKAN_LOADER_ERROR_BIT, 0,
                   "vkCreateSharedSwapchainsKHR Terminator: Driver's function pointer was NULL, returning VK_SUCCESS. Was the "
                   "VK_KHR_display_swapchain extension enabled?");
        return VK_SUCCESS;
    }

    VkSwapchainCreateInfoKHR *pCreateCopy = loader_stack_alloc(sizeof(VkSwapchainCreateInfoKHR) * swapchainCount);
    if (NULL == pCreateCopy) {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    memcpy(pCreateCopy, pCreateInfos, sizeof(VkSwapchainCreateInfoKHR) * swapchainCount);
    for (uint32_t sc = 0; sc < swapchainCount; sc++) {
        VkResult res = wsi_unwrap_icd_surface(icd_term, &pCreateCopy[sc].surface);
        if (res != VK_SUCCESS) {
            return res;
        }
    }
    return dev->loader_dispatch.extension_terminator_dispatch.CreateSharedSwapchainsKHR(device, swapchainCount, pCreateCopy,
                                                                                        pAllocator, pSwapchains);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL
vkGetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR *pDeviceGroupPresentCapabilities) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceGroupPresentCapabilitiesKHR: Invalid device "
                   "[VUID-vkGetDeviceGroupPresentCapabilitiesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface,
                                                                                    VkDeviceGroupPresentModeFlagsKHR *pModes) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceGroupSurfacePresentModesKHR: Invalid device "
                   "[VUID-vkGetDeviceGroupSurfacePresentModesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceGroupSurfacePresentModesKHR(device, surface, pModes);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface,
                                                                               VkDeviceGroupPresentModeFlagsKHR *pModes) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceGroupSurfacePresentModesKHR: Invalid device "
                   "[VUID-vkGetDeviceGroupSurfacePresentModesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.GetDeviceGroupSurfacePresentModesKHR) {
        loader_log(NULL, VULKAN_LOADER_ERROR_BIT, 0,
                   "vkGetDeviceGroupSurfacePresentModesKHR: Driver's function pointer was NULL, returning VK_SUCCESS. Was either "
                   "Vulkan 1.1 and VK_KHR_swapchain enabled or both the VK_KHR_device_group and VK_KHR_surface "
                   "extensions enabled when using Vulkan 1.0?");
        return VK_SUCCESS;
    }

    VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
    if (res != VK_SUCCESS) {
        return res;
    }

    return dev->loader_dispatch.extension_terminator_dispatch.GetDeviceGroupSurfacePresentModesKHR(device, surface, pModes);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice,
                                                                                     VkSurfaceKHR surface, uint32_t *pRectCount,
                                                                                     VkRect2D *pRects) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDevicePresentRectanglesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDevicePresentRectanglesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDevicePresentRectanglesKHR(unwrapped_phys_dev, surface, pRectCount, pRects);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice,
                                                                                VkSurfaceKHR surface, uint32_t *pRectCount,
                                                                                VkRect2D *pRects) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDevicePresentRectanglesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDevicePresentRectanglesKHX");
        // return as this driver doesn't support WSI functionality
        if (pRectCount) {
            *pRectCount = 0;
        }
        return VK_SUCCESS;
    }

    VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
    if (res != VK_SUCCESS) {
        return res;
    }

    return icd_term->dispatch.GetPhysicalDevicePresentRectanglesKHR(phys_dev_term->phys_dev, surface, pRectCount, pRects);
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR *pAcquireInfo,
                                                                    uint32_t *pImageIndex) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquireNextImage2KHR: Invalid device [VUID-vkAcquireNextImage2KHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->AcquireNextImage2KHR(device, pAcquireInfo, pImageIndex);
}

// ---- VK_KHR_get_display_properties2 extension trampoline/terminators

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice,
                                                                                      uint32_t *pPropertyCount,
                                                                                      VkDisplayProperties2KHR *pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceDisplayProperties2KHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceDisplayProperties2KHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceDisplayProperties2KHR(unwrapped_phys_dev, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice,
                                                                                 uint32_t *pPropertyCount,
                                                                                 VkDisplayProperties2KHR *pProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    // If the function is available in the driver, just call into it
    if (icd_term->dispatch.GetPhysicalDeviceDisplayProperties2KHR != NULL) {
        return icd_term->dispatch.GetPhysicalDeviceDisplayProperties2KHR(phys_dev_term->phys_dev, pPropertyCount, pProperties);
    }

    // We have to emulate the function.
    loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0,
               "vkGetPhysicalDeviceDisplayProperties2KHR: Emulating call in ICD \"%s\"", icd_term->scanned_icd->lib_name);

    // If the icd doesn't support VK_KHR_display, then no properties are available
    if (icd_term->dispatch.GetPhysicalDeviceDisplayPropertiesKHR == NULL) {
        *pPropertyCount = 0;
        return VK_SUCCESS;
    }

    // If we aren't writing to pProperties, then emulation is straightforward
    if (pProperties == NULL || *pPropertyCount == 0) {
        return icd_term->dispatch.GetPhysicalDeviceDisplayPropertiesKHR(phys_dev_term->phys_dev, pPropertyCount, NULL);
    }

    // If we do have to write to pProperties, then we need to write to a temporary array of VkDisplayPropertiesKHR and copy it
    VkDisplayPropertiesKHR *properties = loader_stack_alloc(*pPropertyCount * sizeof(VkDisplayPropertiesKHR));
    if (properties == NULL) {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    VkResult res = icd_term->dispatch.GetPhysicalDeviceDisplayPropertiesKHR(phys_dev_term->phys_dev, pPropertyCount, properties);
    if (res < 0) {
        return res;
    }
    for (uint32_t i = 0; i < *pPropertyCount; ++i) {
        memcpy(&pProperties[i].displayProperties, &properties[i], sizeof(VkDisplayPropertiesKHR));
    }
    return res;
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPlaneProperties2KHR(
    VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkDisplayPlaneProperties2KHR *pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceDisplayPlaneProperties2KHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceDisplayPlaneProperties2KHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceDisplayPlaneProperties2KHR(unwrapped_phys_dev, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice,
                                                                                      uint32_t *pPropertyCount,
                                                                                      VkDisplayPlaneProperties2KHR *pProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    // If the function is available in the driver, just call into it
    if (icd_term->dispatch.GetPhysicalDeviceDisplayPlaneProperties2KHR != NULL) {
        return icd_term->dispatch.GetPhysicalDeviceDisplayPlaneProperties2KHR(phys_dev_term->phys_dev, pPropertyCount, pProperties);
    }

    // We have to emulate the function.
    loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0,
               "vkGetPhysicalDeviceDisplayPlaneProperties2KHR: Emulating call in ICD \"%s\"", icd_term->scanned_icd->lib_name);

    // If the icd doesn't support VK_KHR_display, then no properties are available
    if (icd_term->dispatch.GetPhysicalDeviceDisplayPlanePropertiesKHR == NULL) {
        *pPropertyCount = 0;
        return VK_SUCCESS;
    }

    // If we aren't writing to pProperties, then emulation is straightforward
    if (pProperties == NULL || *pPropertyCount == 0) {
        return icd_term->dispatch.GetPhysicalDeviceDisplayPlanePropertiesKHR(phys_dev_term->phys_dev, pPropertyCount, NULL);
    }

    // If we do have to write to pProperties, then we need to write to a temporary array of VkDisplayPlanePropertiesKHR and copy it
    VkDisplayPlanePropertiesKHR *properties = loader_stack_alloc(*pPropertyCount * sizeof(VkDisplayPlanePropertiesKHR));
    if (properties == NULL) {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    VkResult res =
        icd_term->dispatch.GetPhysicalDeviceDisplayPlanePropertiesKHR(phys_dev_term->phys_dev, pPropertyCount, properties);
    if (res < 0) {
        return res;
    }
    for (uint32_t i = 0; i < *pPropertyCount; ++i) {
        memcpy(&pProperties[i].displayPlaneProperties, &properties[i], sizeof(VkDisplayPlanePropertiesKHR));
    }
    return res;
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display,
                                                                            uint32_t *pPropertyCount,
                                                                            VkDisplayModeProperties2KHR *pProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDisplayModeProperties2KHR: Invalid physicalDevice "
                   "[VUID-vkGetDisplayModeProperties2KHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetDisplayModeProperties2KHR(unwrapped_phys_dev, display, pPropertyCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display,
                                                                       uint32_t *pPropertyCount,
                                                                       VkDisplayModeProperties2KHR *pProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    // If the function is available in the driver, just call into it
    if (icd_term->dispatch.GetDisplayModeProperties2KHR != NULL) {
        return icd_term->dispatch.GetDisplayModeProperties2KHR(phys_dev_term->phys_dev, display, pPropertyCount, pProperties);
    }

    // We have to emulate the function.
    loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0, "vkGetDisplayModeProperties2KHR: Emulating call in ICD \"%s\"",
               icd_term->scanned_icd->lib_name);

    // If the icd doesn't support VK_KHR_display, then no properties are available
    if (icd_term->dispatch.GetDisplayModePropertiesKHR == NULL) {
        *pPropertyCount = 0;
        return VK_SUCCESS;
    }

    // If we aren't writing to pProperties, then emulation is straightforward
    if (pProperties == NULL || *pPropertyCount == 0) {
        return icd_term->dispatch.GetDisplayModePropertiesKHR(phys_dev_term->phys_dev, display, pPropertyCount, NULL);
    }

    // If we do have to write to pProperties, then we need to write to a temporary array of VkDisplayModePropertiesKHR and copy it
    VkDisplayModePropertiesKHR *properties = loader_stack_alloc(*pPropertyCount * sizeof(VkDisplayModePropertiesKHR));
    if (properties == NULL) {
        return VK_ERROR_OUT_OF_HOST_MEMORY;
    }
    VkResult res = icd_term->dispatch.GetDisplayModePropertiesKHR(phys_dev_term->phys_dev, display, pPropertyCount, properties);
    if (res < 0) {
        return res;
    }
    for (uint32_t i = 0; i < *pPropertyCount; ++i) {
        memcpy(&pProperties[i].displayModeProperties, &properties[i], sizeof(VkDisplayModePropertiesKHR));
    }
    return res;
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice,
                                                                               const VkDisplayPlaneInfo2KHR *pDisplayPlaneInfo,
                                                                               VkDisplayPlaneCapabilities2KHR *pCapabilities) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDisplayPlaneCapabilities2KHR: Invalid physicalDevice "
                   "[VUID-vkGetDisplayPlaneCapabilities2KHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetDisplayPlaneCapabilities2KHR(unwrapped_phys_dev, pDisplayPlaneInfo, pCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice,
                                                                          const VkDisplayPlaneInfo2KHR *pDisplayPlaneInfo,
                                                                          VkDisplayPlaneCapabilities2KHR *pCapabilities) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    // If the function is available in the driver, just call into it
    if (icd_term->dispatch.GetDisplayPlaneCapabilities2KHR != NULL) {
        return icd_term->dispatch.GetDisplayPlaneCapabilities2KHR(phys_dev_term->phys_dev, pDisplayPlaneInfo, pCapabilities);
    }

    // We have to emulate the function.
    loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0,
               "vkGetDisplayPlaneCapabilities2KHR: Emulating call in ICD \"%s\"", icd_term->scanned_icd->lib_name);

    // If the icd doesn't support VK_KHR_display, then there are no capabilities
    if (NULL == icd_term->dispatch.GetDisplayPlaneCapabilitiesKHR) {
        if (pCapabilities) {
            memset(&pCapabilities->capabilities, 0, sizeof(VkDisplayPlaneCapabilitiesKHR));
        }
        return VK_SUCCESS;
    }

    // Just call into the old version of the function.
    return icd_term->dispatch.GetDisplayPlaneCapabilitiesKHR(phys_dev_term->phys_dev, pDisplayPlaneInfo->mode,
                                                             pDisplayPlaneInfo->planeIndex, &pCapabilities->capabilities);
}

#if defined(VK_USE_PLATFORM_FUCHSIA)

// This is the trampoline entrypoint for CreateImagePipeSurfaceFUCHSIA
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateImagePipeSurfaceFUCHSIA(VkInstance instance,
                                                                             const VkImagePipeSurfaceCreateInfoFUCHSIA *pCreateInfo,
                                                                             const VkAllocationCallbacks *pAllocator,
                                                                             VkSurfaceKHR *pSurface) {
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (NULL == loader_inst) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateImagePipeSurfaceFUCHSIA: Invalid instance [VUID-vkCreateImagePipeSurfaceFUCHSIA-instance-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return loader_inst->disp->layer_inst_disp.CreateImagePipeSurfaceFUCHSIA(loader_inst->instance, pCreateInfo, pAllocator,
                                                                            pSurface);
}

// This is the instance chain terminator function for CreateImagePipeSurfaceFUCHSIA
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateImagePipeSurfaceFUCHSIA(VkInstance instance,
                                                                        const VkImagePipeSurfaceCreateInfoFUCHSIA *pCreateInfo,
                                                                        const VkAllocationCallbacks *pAllocator,
                                                                        VkSurfaceKHR *pSurface) {
    VkResult result = VK_SUCCESS;
    VkIcdSurface *icd_surface = NULL;

    // Initialize pSurface to NULL just to be safe.
    *pSurface = VK_NULL_HANDLE;
    // First, check to ensure the appropriate extension was enabled:
    struct loader_instance *loader_inst = loader_get_instance(instance);
    if (!loader_inst->enabled_extensions.fuchsia_imagepipe_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_FUCHSIA_imagepipe_surface extension not enabled.  "
                   "vkCreateImagePipeSurfaceFUCHSIA not executed!");
        result = VK_ERROR_EXTENSION_NOT_PRESENT;
        goto out;
    }

    // Next, if so, proceed with the implementation of this function:
    result = allocate_icd_surface_struct(loader_inst, sizeof(icd_surface->imagepipe_surf.base), sizeof(icd_surface->imagepipe_surf),
                                         pAllocator, &icd_surface);
    if (VK_SUCCESS != result) {
        goto out;
    }

    icd_surface->imagepipe_surf.base.platform = VK_ICD_WSI_PLATFORM_FUCHSIA;

    const struct loader_struct_type_info ci_types[] = {
        {VK_STRUCTURE_TYPE_IMAGEPIPE_SURFACE_CREATE_INFO_FUCHSIA, sizeof(VkImagePipeSurfaceCreateInfoFUCHSIA)},
    };
    copy_surface_create_info(loader_inst, icd_surface, pCreateInfo, sizeof(ci_types) / sizeof(ci_types[0]), ci_types,
                             "VkImagePipeSurfaceCreateInfoFUCHSIA", pAllocator);

    *pSurface = (VkSurfaceKHR)(uintptr_t)icd_surface;

out:
    cleanup_surface_creation(loader_inst, result, icd_surface, pAllocator);

    return result;
}
#endif  // VK_USE_PLATFORM_FUCHSIA

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL
vkGetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
                                           VkSurfaceCapabilities2KHR *pSurfaceCapabilities) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSurfaceCapabilities2KHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSurfaceCapabilities2KHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSurfaceCapabilities2KHR(unwrapped_phys_dev, pSurfaceInfo, pSurfaceCapabilities);
}

#ifndef VULKANSC  // Vulkan SC does not support VK_EXT_surface_maintenance1 yet
void emulate_VK_EXT_surface_maintenance1(struct loader_icd_term *icd_term, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
                                         VkSurfaceCapabilities2KHR *pSurfaceCapabilities) {
    // Because VK_EXT_surface_maintenance1 is an instance extension, applications will use it to query info on drivers which do
    // not support the extension. Thus we need to emulate the driver filling out the structs in that case.
    if (!icd_term->enabled_instance_extensions.ext_surface_maintenance1) {
        VkPresentModeKHR present_mode = VK_PRESENT_MODE_MAX_ENUM_KHR;
        const void *void_pNext = pSurfaceInfo->pNext;
        while (void_pNext) {
            VkBaseOutStructure out_structure = {0};
            memcpy(&out_structure, void_pNext, sizeof(VkBaseOutStructure));
            if (out_structure.sType == VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_EXT) {
                VkSurfacePresentModeEXT *surface_present_mode = (VkSurfacePresentModeEXT *)void_pNext;
                present_mode = surface_present_mode->presentMode;
            }
            void_pNext = out_structure.pNext;
        }
        // If no VkSurfacePresentModeEXT was present, return
        if (present_mode == VK_PRESENT_MODE_MAX_ENUM_KHR) {
            return;
        }

        void_pNext = pSurfaceCapabilities->pNext;
        while (void_pNext) {
            VkBaseOutStructure out_structure = {0};
            memcpy(&out_structure, void_pNext, sizeof(VkBaseOutStructure));
            if (out_structure.sType == VK_STRUCTURE_TYPE_SURFACE_PRESENT_MODE_COMPATIBILITY_EXT) {
                VkSurfacePresentModeCompatibilityEXT *surface_present_mode_compatibility =
                    (VkSurfacePresentModeCompatibilityEXT *)void_pNext;
                if (surface_present_mode_compatibility->pPresentModes) {
                    if (surface_present_mode_compatibility->presentModeCount != 0) {
                        surface_present_mode_compatibility->pPresentModes[0] = present_mode;
                        surface_present_mode_compatibility->presentModeCount = 1;
                    }
                } else {
                    surface_present_mode_compatibility->presentModeCount = 1;
                }

            } else if (out_structure.sType == VK_STRUCTURE_TYPE_SURFACE_PRESENT_SCALING_CAPABILITIES_EXT) {
                // Because there is no way to fill out the information faithfully, set scaled max/min image extent to the
                // surface capabilities max/min extent and the rest to zero.
                VkSurfacePresentScalingCapabilitiesEXT *surface_present_scaling_capabilities =
                    (VkSurfacePresentScalingCapabilitiesEXT *)void_pNext;
                surface_present_scaling_capabilities->supportedPresentScaling = 0;
                surface_present_scaling_capabilities->supportedPresentGravityX = 0;
                surface_present_scaling_capabilities->supportedPresentGravityY = 0;
                surface_present_scaling_capabilities->maxScaledImageExtent =
                    pSurfaceCapabilities->surfaceCapabilities.maxImageExtent;
                surface_present_scaling_capabilities->minScaledImageExtent =
                    pSurfaceCapabilities->surfaceCapabilities.minImageExtent;
            }
            void_pNext = out_structure.pNext;
        }
    }
}
#endif  // VULKANSC

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSurfaceCapabilities2KHR(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
    VkSurfaceCapabilities2KHR *pSurfaceCapabilities) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;

    if (!loader_inst->enabled_extensions.khr_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_surface extension not enabled. vkGetPhysicalDeviceSurfaceCapabilities2KHR not executed!");
        return VK_SUCCESS;
    }

    VkSurfaceKHR surface = pSurfaceInfo->surface;
    if (VK_NULL_HANDLE != pSurfaceInfo->surface) {
        VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
        if (res != VK_SUCCESS) {
            return res;
        }
    }

    if (icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilities2KHR != NULL) {
        void *pNext = pSurfaceCapabilities->pNext;
        while (pNext != NULL) {
            VkBaseOutStructure pNext_out_structure = {0};
            memcpy(&pNext_out_structure, pNext, sizeof(VkBaseOutStructure));
#ifndef VULKANSC
            if (pNext_out_structure.sType == VK_STRUCTURE_TYPE_SURFACE_PROTECTED_CAPABILITIES_KHR) {
                // Not all ICDs may be supporting VK_KHR_surface_protected_capabilities
                // Initialize VkSurfaceProtectedCapabilitiesKHR.supportsProtected to false and
                // if an ICD supports protected surfaces, it will reset it to true accordingly.
                ((VkSurfaceProtectedCapabilitiesKHR *)pNext)->supportsProtected = VK_FALSE;
            }
#endif  // VULKANSC
            pNext = pNext_out_structure.pNext;
        }

        // Pass the call to the driver, possibly unwrapping the ICD surface
        VkPhysicalDeviceSurfaceInfo2KHR info_copy = *pSurfaceInfo;
        info_copy.surface = surface;

        VkResult res =
            icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilities2KHR(phys_dev_term->phys_dev, &info_copy, pSurfaceCapabilities);

#ifndef VULKANSC  // Vulkan SC does not support VK_EXT_surface_maintenance1 yet
        // Because VK_EXT_surface_maintenance1 is an instance extension, applications will use it to query info on drivers which do
        // not support the extension. Thus we need to emulate the driver filling out the structs in that case.
        if (!icd_term->enabled_instance_extensions.ext_surface_maintenance1) {
            emulate_VK_EXT_surface_maintenance1(icd_term, pSurfaceInfo, pSurfaceCapabilities);
        }
#endif  // VULKANSC

        return res;
    } else {
        // Emulate the call
        loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0,
                   "vkGetPhysicalDeviceSurfaceCapabilities2KHR: Emulating call in ICD \"%s\" using "
                   "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
                   icd_term->scanned_icd->lib_name);

        // Write to the VkSurfaceCapabilities2KHR struct

        // If the icd doesn't support VK_KHR_surface, then there are no capabilities
        if (NULL == icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilitiesKHR) {
            if (pSurfaceCapabilities) {
                memset(&pSurfaceCapabilities->surfaceCapabilities, 0, sizeof(VkSurfaceCapabilitiesKHR));
            }
            return VK_SUCCESS;
        }
        VkResult res = icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilitiesKHR(phys_dev_term->phys_dev, surface,
                                                                                  &pSurfaceCapabilities->surfaceCapabilities);

#ifndef VULKANSC  // Vulkan SC does not support VK_EXT_surface_maintenance1 yet
        emulate_VK_EXT_surface_maintenance1(icd_term, pSurfaceInfo, pSurfaceCapabilities);
#endif  // VULKANSC
        return res;
    }
}

LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL
vkGetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
                                      uint32_t *pSurfaceFormatCount, VkSurfaceFormat2KHR *pSurfaceFormats) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSurfaceFormats2KHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSurfaceFormats2KHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSurfaceFormats2KHR(unwrapped_phys_dev, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice,
                                                                              const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
                                                                              uint32_t *pSurfaceFormatCount,
                                                                              VkSurfaceFormat2KHR *pSurfaceFormats) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    struct loader_instance *loader_inst = (struct loader_instance *)icd_term->this_instance;

    if (!loader_inst->enabled_extensions.khr_surface) {
        loader_log(loader_inst, VULKAN_LOADER_ERROR_BIT, 0,
                   "VK_KHR_surface extension not enabled. vkGetPhysicalDeviceSurfaceFormats2KHR not executed!");
        return VK_SUCCESS;
    }

    VkSurfaceKHR surface = pSurfaceInfo->surface;
    if (VK_NULL_HANDLE != pSurfaceInfo->surface) {
        VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
        if (res != VK_SUCCESS) {
            return res;
        }
    }

    if (icd_term->dispatch.GetPhysicalDeviceSurfaceFormats2KHR != NULL) {
        // Pass the call to the driver, possibly unwrapping the ICD surface
        VkPhysicalDeviceSurfaceInfo2KHR info_copy = *pSurfaceInfo;
        info_copy.surface = surface;

        return icd_term->dispatch.GetPhysicalDeviceSurfaceFormats2KHR(phys_dev_term->phys_dev, &info_copy, pSurfaceFormatCount,
                                                                      pSurfaceFormats);
    } else {
        // Emulate the call
        loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0,
                   "vkGetPhysicalDeviceSurfaceFormats2KHR: Emulating call in ICD \"%s\" using vkGetPhysicalDeviceSurfaceFormatsKHR",
                   icd_term->scanned_icd->lib_name);

        if (pSurfaceInfo->pNext != NULL) {
            loader_log(icd_term->this_instance, VULKAN_LOADER_WARN_BIT, 0,
                       "vkGetPhysicalDeviceSurfaceFormats2KHR: Emulation found unrecognized structure type in pSurfaceInfo->pNext "
                       "- this struct will be ignored");
        }

        // If the icd doesn't support VK_KHR_surface, then there are no formats
        if (NULL == icd_term->dispatch.GetPhysicalDeviceSurfaceFormatsKHR) {
            if (pSurfaceFormatCount) {
                *pSurfaceFormatCount = 0;
            }
            return VK_SUCCESS;
        }

        if (*pSurfaceFormatCount == 0 || pSurfaceFormats == NULL) {
            // Write to pSurfaceFormatCount
            return icd_term->dispatch.GetPhysicalDeviceSurfaceFormatsKHR(phys_dev_term->phys_dev, surface, pSurfaceFormatCount,
                                                                         NULL);
        } else {
            // Allocate a temporary array for the output of the old function
            VkSurfaceFormatKHR *formats = loader_stack_alloc(*pSurfaceFormatCount * sizeof(VkSurfaceFormatKHR));
            if (formats == NULL) {
                return VK_ERROR_OUT_OF_HOST_MEMORY;
            }

            VkResult res = icd_term->dispatch.GetPhysicalDeviceSurfaceFormatsKHR(phys_dev_term->phys_dev, surface,
                                                                                 pSurfaceFormatCount, formats);
            for (uint32_t i = 0; i < *pSurfaceFormatCount; ++i) {
                pSurfaceFormats[i].surfaceFormat = formats[i];
                if (pSurfaceFormats[i].pNext != NULL) {
                    loader_log(icd_term->this_instance, VULKAN_LOADER_WARN_BIT, 0,
                               "vkGetPhysicalDeviceSurfaceFormats2KHR: Emulation found unrecognized structure type in "
                               "pSurfaceFormats[%d].pNext - this struct will be ignored",
                               i);
                }
            }
            return res;
        }
    }
}

bool wsi_swapchain_instance_gpa(struct loader_instance *loader_inst, const char *name, void **addr) {
    *addr = NULL;

    // Functions for the VK_KHR_surface extension:
    if (!strcmp("vkDestroySurfaceKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkDestroySurfaceKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceSurfaceSupportKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetPhysicalDeviceSurfaceSupportKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceSurfaceCapabilitiesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetPhysicalDeviceSurfaceCapabilitiesKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceSurfaceFormatsKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetPhysicalDeviceSurfaceFormatsKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceSurfacePresentModesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetPhysicalDeviceSurfacePresentModesKHR : NULL;
        return true;
    }

    if (!strcmp("vkGetDeviceGroupPresentCapabilitiesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetDeviceGroupPresentCapabilitiesKHR : NULL;
        return true;
    }

    if (!strcmp("vkGetDeviceGroupSurfacePresentModesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetDeviceGroupSurfacePresentModesKHR : NULL;
        return true;
    }

    if (!strcmp("vkGetPhysicalDevicePresentRectanglesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetPhysicalDevicePresentRectanglesKHR : NULL;
        return true;
    }

    // Functions for VK_KHR_get_surface_capabilities2 extension:
    if (!strcmp("vkGetPhysicalDeviceSurfaceCapabilities2KHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetPhysicalDeviceSurfaceCapabilities2KHR : NULL;
        return true;
    }

    if (!strcmp("vkGetPhysicalDeviceSurfaceFormats2KHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_surface ? (void *)vkGetPhysicalDeviceSurfaceFormats2KHR : NULL;
        return true;
    }

    // Functions for the VK_KHR_swapchain extension:

    // Note: This is a device extension, and its functions are statically
    // exported from the loader.  Per Khronos decisions, the loader's GIPA
    // function will return the trampoline function for such device-extension
    // functions, regardless of whether the extension has been enabled.
    if (!strcmp("vkCreateSwapchainKHR", name)) {
        *addr = (void *)vkCreateSwapchainKHR;
        return true;
    }
#ifndef VULKANSC
    if (!strcmp("vkDestroySwapchainKHR", name)) {
        *addr = (void *)vkDestroySwapchainKHR;
        return true;
    }
#endif  // VULKANSC
    if (!strcmp("vkGetSwapchainImagesKHR", name)) {
        *addr = (void *)vkGetSwapchainImagesKHR;
        return true;
    }
    if (!strcmp("vkAcquireNextImageKHR", name)) {
        *addr = (void *)vkAcquireNextImageKHR;
        return true;
    }
    if (!strcmp("vkQueuePresentKHR", name)) {
        *addr = (void *)vkQueuePresentKHR;
        return true;
    }
    if (!strcmp("vkAcquireNextImage2KHR", name)) {
        *addr = (void *)vkAcquireNextImage2KHR;
        return true;
    }

#ifndef VULKANSC
#if defined(VK_USE_PLATFORM_WIN32_KHR)

    // Functions for the VK_KHR_win32_surface extension:
    if (!strcmp("vkCreateWin32SurfaceKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_win32_surface ? (void *)vkCreateWin32SurfaceKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceWin32PresentationSupportKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_win32_surface ? (void *)vkGetPhysicalDeviceWin32PresentationSupportKHR : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WAYLAND_KHR)

    // Functions for the VK_KHR_wayland_surface extension:
    if (!strcmp("vkCreateWaylandSurfaceKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_wayland_surface ? (void *)vkCreateWaylandSurfaceKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceWaylandPresentationSupportKHR", name)) {
        *addr =
            loader_inst->enabled_extensions.khr_wayland_surface ? (void *)vkGetPhysicalDeviceWaylandPresentationSupportKHR : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_WAYLAND_KHR
#if defined(VK_USE_PLATFORM_XCB_KHR)

    // Functions for the VK_KHR_xcb_surface extension:
    if (!strcmp("vkCreateXcbSurfaceKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_xcb_surface ? (void *)vkCreateXcbSurfaceKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceXcbPresentationSupportKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_xcb_surface ? (void *)vkGetPhysicalDeviceXcbPresentationSupportKHR : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_XCB_KHR
#if defined(VK_USE_PLATFORM_XLIB_KHR)

    // Functions for the VK_KHR_xlib_surface extension:
    if (!strcmp("vkCreateXlibSurfaceKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_xlib_surface ? (void *)vkCreateXlibSurfaceKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceXlibPresentationSupportKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_xlib_surface ? (void *)vkGetPhysicalDeviceXlibPresentationSupportKHR : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_XLIB_KHR
#endif  // VULKANSC
#if defined(VK_USE_PLATFORM_DIRECTFB_EXT)

    // Functions for the VK_EXT_directfb_surface extension:
    if (!strcmp("vkCreateDirectFBSurfaceEXT", name)) {
        *addr = loader_inst->enabled_extensions.ext_directfb_surface ? (void *)vkCreateDirectFBSurfaceEXT : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceDirectFBPresentationSupportEXT", name)) {
        *addr =
            loader_inst->enabled_extensions.ext_directfb_surface ? (void *)vkGetPhysicalDeviceDirectFBPresentationSupportEXT : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_DIRECTFB_EXT
#if defined(VK_USE_PLATFORM_ANDROID_KHR)

    // Functions for the VK_KHR_android_surface extension:
    if (!strcmp("vkCreateAndroidSurfaceKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_android_surface ? (void *)vkCreateAndroidSurfaceKHR : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_ANDROID_KHR

#if defined(VK_USE_PLATFORM_MACOS_MVK)

    // Functions for the VK_MVK_macos_surface extension:
    if (!strcmp("vkCreateMacOSSurfaceMVK", name)) {
        *addr = loader_inst->enabled_extensions.mvk_macos_surface ? (void *)vkCreateMacOSSurfaceMVK : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_MACOS_MVK
#if defined(VK_USE_PLATFORM_IOS_MVK)

    // Functions for the VK_MVK_ios_surface extension:
    if (!strcmp("vkCreateIOSSurfaceMVK", name)) {
        *addr = loader_inst->enabled_extensions.mvk_ios_surface ? (void *)vkCreateIOSSurfaceMVK : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_IOS_MVK
#if defined(VK_USE_PLATFORM_GGP)

    // Functions for the VK_GGP_stream_descriptor_surface extension:
    if (!strcmp("vkCreateStreamDescriptorSurfaceGGP", name)) {
        *addr = loader_inst->enabled_extensions.wsi_ggp_surface_enabled ? (void *)vkCreateStreamDescriptorSurfaceGGP : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_GGP
#if defined(VK_USE_PLATFORM_FUCHSIA)

    // Functions for the VK_FUCHSIA_imagepipe_surface extension:
    if (!strcmp("vkCreateImagePipeSurfaceFUCHSIA", name)) {
        *addr = loader_inst->enabled_extensions.fuchsia_imagepipe_surface ? (void *)vkCreateImagePipeSurfaceFUCHSIA : NULL;
        return true;
    }

#endif  // VK_USE_PLATFORM_FUCHSIA

    // Functions for the VK_EXT_headless_surface extension:
    if (!strcmp("vkCreateHeadlessSurfaceEXT", name)) {
        *addr = loader_inst->enabled_extensions.ext_headless_surface ? (void *)vkCreateHeadlessSurfaceEXT : NULL;
        return true;
    }

#if defined(VK_USE_PLATFORM_METAL_EXT)
    // Functions for the VK_MVK_macos_surface extension:
    if (!strcmp("vkCreateMetalSurfaceEXT", name)) {
        *addr = loader_inst->enabled_extensions.ext_metal_surface ? (void *)vkCreateMetalSurfaceEXT : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_METAL_EXT

#ifndef VULKANSC
#if defined(VK_USE_PLATFORM_SCREEN_QNX)

    // Functions for the VK_QNX_screen_surface extension:
    if (!strcmp("vkCreateScreenSurfaceQNX", name)) {
        *addr = loader_inst->enabled_extensions.qnx_screen_surface ? (void *)vkCreateScreenSurfaceQNX : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceScreenPresentationSupportQNX", name)) {
        *addr = loader_inst->enabled_extensions.qnx_screen_surface ? (void *)vkGetPhysicalDeviceScreenPresentationSupportQNX : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_SCREEN_QNX
#endif  // VULKANSC

#if defined(VK_USE_PLATFORM_VI_NN)

    // Functions for the VK_NN_vi_surface extension:
    if (!strcmp("vkCreateViSurfaceNN", name)) {
        *addr = loader_inst->enabled_extensions.nn_vi_surface ? (void *)vkCreateViSurfaceNN : NULL;
        return true;
    }
#endif  // VK_USE_PLATFORM_VI_NN

    // Functions for VK_KHR_display extension:
    if (!strcmp("vkGetPhysicalDeviceDisplayPropertiesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_display ? (void *)vkGetPhysicalDeviceDisplayPropertiesKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceDisplayPlanePropertiesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_display ? (void *)vkGetPhysicalDeviceDisplayPlanePropertiesKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetDisplayPlaneSupportedDisplaysKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_display ? (void *)vkGetDisplayPlaneSupportedDisplaysKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetDisplayModePropertiesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_display ? (void *)vkGetDisplayModePropertiesKHR : NULL;
        return true;
    }
    if (!strcmp("vkCreateDisplayModeKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_display ? (void *)vkCreateDisplayModeKHR : NULL;
        return true;
    }
    if (!strcmp("vkGetDisplayPlaneCapabilitiesKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_display ? (void *)vkGetDisplayPlaneCapabilitiesKHR : NULL;
        return true;
    }
    if (!strcmp("vkCreateDisplayPlaneSurfaceKHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_display ? (void *)vkCreateDisplayPlaneSurfaceKHR : NULL;
        return true;
    }

    // Functions for KHR_display_swapchain extension:
    if (!strcmp("vkCreateSharedSwapchainsKHR", name)) {
        *addr = (void *)vkCreateSharedSwapchainsKHR;
        return true;
    }

    // Functions for KHR_get_display_properties2
    if (!strcmp("vkGetPhysicalDeviceDisplayProperties2KHR", name)) {
        *addr =
            loader_inst->enabled_extensions.khr_get_display_properties2 ? (void *)vkGetPhysicalDeviceDisplayProperties2KHR : NULL;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceDisplayPlaneProperties2KHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_get_display_properties2 ? (void *)vkGetPhysicalDeviceDisplayPlaneProperties2KHR
                                                                            : NULL;
        return true;
    }
    if (!strcmp("vkGetDisplayModeProperties2KHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_get_display_properties2 ? (void *)vkGetDisplayModeProperties2KHR : NULL;
        return true;
    }
    if (!strcmp("vkGetDisplayPlaneCapabilities2KHR", name)) {
        *addr = loader_inst->enabled_extensions.khr_get_display_properties2 ? (void *)vkGetDisplayPlaneCapabilities2KHR : NULL;
        return true;
    }

    return false;
}
