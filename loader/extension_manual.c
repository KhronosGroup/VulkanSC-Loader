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
 * Author: Mark Young <marky@lunarg.com>
 * Author: Lenny Komow <lenny@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 */

#include "extension_manual.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocation.h"
#include "loader.h"
#include "log.h"
#include "wsi.h"

// ---- Manually added trampoline/terminator functions

// These functions, for whatever reason, require more complex changes than
// can easily be automatically generated.

#ifndef VULKANSC
// ---- VK_NV_external_memory_capabilities extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceExternalImageFormatPropertiesNV(
    VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage,
    VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType,
    VkExternalImageFormatPropertiesNV *pExternalImageFormatProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceExternalImageFormatPropertiesNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceExternalImageFormatPropertiesNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);

    return disp->GetPhysicalDeviceExternalImageFormatPropertiesNV(unwrapped_phys_dev, format, type, tiling, usage, flags,
                                                                  externalHandleType, pExternalImageFormatProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceExternalImageFormatPropertiesNV(
    VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage,
    VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType,
    VkExternalImageFormatPropertiesNV *pExternalImageFormatProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    if (!icd_term->dispatch.GetPhysicalDeviceExternalImageFormatPropertiesNV) {
        if (externalHandleType) {
            return VK_ERROR_FORMAT_NOT_SUPPORTED;
        }

        if (!icd_term->dispatch.GetPhysicalDeviceImageFormatProperties) {
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        pExternalImageFormatProperties->externalMemoryFeatures = 0;
        pExternalImageFormatProperties->exportFromImportedHandleTypes = 0;
        pExternalImageFormatProperties->compatibleHandleTypes = 0;

        return icd_term->dispatch.GetPhysicalDeviceImageFormatProperties(
            phys_dev_term->phys_dev, format, type, tiling, usage, flags, &pExternalImageFormatProperties->imageFormatProperties);
    }

    return icd_term->dispatch.GetPhysicalDeviceExternalImageFormatPropertiesNV(
        phys_dev_term->phys_dev, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties);
}
#endif  // VULKANSC

// ---- VK_EXT_display_surface_counter extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface,
                                                                        VkSurfaceCapabilities2EXT *pSurfaceCapabilities) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceExternalImageFormatPropertiesNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSurfaceCapabilities2EXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSurfaceCapabilities2EXT(unwrapped_phys_dev, surface, pSurfaceCapabilities);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSurfaceCapabilities2EXT(
    VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT *pSurfaceCapabilities) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    VkResult res = wsi_unwrap_icd_surface(icd_term, &surface);
    if (res != VK_SUCCESS) {
        return res;
    }

    if (NULL != icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilities2EXT) {
        // Pass the call to the driver
        return icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilities2EXT(phys_dev_term->phys_dev, surface, pSurfaceCapabilities);
    } else {
        // Emulate the call
        loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0,
                   "vkGetPhysicalDeviceSurfaceCapabilities2EXT: Emulating call in ICD \"%s\" using "
                   "vkGetPhysicalDeviceSurfaceCapabilitiesKHR",
                   icd_term->scanned_icd->lib_name);

        VkSurfaceCapabilitiesKHR surface_caps;
        res = icd_term->dispatch.GetPhysicalDeviceSurfaceCapabilitiesKHR(phys_dev_term->phys_dev, surface, &surface_caps);
        pSurfaceCapabilities->minImageCount = surface_caps.minImageCount;
        pSurfaceCapabilities->maxImageCount = surface_caps.maxImageCount;
        pSurfaceCapabilities->currentExtent = surface_caps.currentExtent;
        pSurfaceCapabilities->minImageExtent = surface_caps.minImageExtent;
        pSurfaceCapabilities->maxImageExtent = surface_caps.maxImageExtent;
        pSurfaceCapabilities->maxImageArrayLayers = surface_caps.maxImageArrayLayers;
        pSurfaceCapabilities->supportedTransforms = surface_caps.supportedTransforms;
        pSurfaceCapabilities->currentTransform = surface_caps.currentTransform;
        pSurfaceCapabilities->supportedCompositeAlpha = surface_caps.supportedCompositeAlpha;
        pSurfaceCapabilities->supportedUsageFlags = surface_caps.supportedUsageFlags;
        pSurfaceCapabilities->supportedSurfaceCounters = 0;

        if (pSurfaceCapabilities->pNext != NULL) {
            loader_log(icd_term->this_instance, VULKAN_LOADER_WARN_BIT, 0,
                       "vkGetPhysicalDeviceSurfaceCapabilities2EXT: Emulation found unrecognized structure type in "
                       "pSurfaceCapabilities->pNext - this struct will be ignored");
        }

        return res;
    }
}

// ---- VK_EXT_direct_mode_display extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkReleaseDisplayEXT: Invalid physicalDevice [VUID-vkReleaseDisplayEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->ReleaseDisplayEXT(unwrapped_phys_dev, display);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_ReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    if (icd_term->dispatch.ReleaseDisplayEXT == NULL) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD \"%s\" associated with VkPhysicalDevice does not support vkReleaseDisplayEXT - Consequently, the call is "
                   "invalid because it should not be possible to acquire a display on this device",
                   icd_term->scanned_icd->lib_name);
        abort();
    }
    return icd_term->dispatch.ReleaseDisplayEXT(phys_dev_term->phys_dev, display);
}

#ifndef VULKANSC
// ---- VK_EXT_acquire_xlib_display extension trampoline/terminators

#if defined(VK_USE_PLATFORM_XLIB_XRANDR_EXT)
VKAPI_ATTR VkResult VKAPI_CALL AcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display *dpy, VkDisplayKHR display) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquireXlibDisplayEXT: Invalid physicalDevice [VUID-vkAcquireXlibDisplayEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->AcquireXlibDisplayEXT(unwrapped_phys_dev, dpy, display);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_AcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display *dpy,
                                                                VkDisplayKHR display) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    if (icd_term->dispatch.AcquireXlibDisplayEXT != NULL) {
        // Pass the call to the driver
        return icd_term->dispatch.AcquireXlibDisplayEXT(phys_dev_term->phys_dev, dpy, display);
    } else {
        // Emulate the call
        loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0,
                   "vkAcquireXLibDisplayEXT: Emulating call in ICD \"%s\" by returning error", icd_term->scanned_icd->lib_name);

        // Fail for the unsupported command
        return VK_ERROR_INITIALIZATION_FAILED;
    }
}

VKAPI_ATTR VkResult VKAPI_CALL GetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display *dpy, RROutput rrOutput,
                                                        VkDisplayKHR *pDisplay) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetRandROutputDisplayEXT: Invalid physicalDevice [VUID-vkGetRandROutputDisplayEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetRandROutputDisplayEXT(unwrapped_phys_dev, dpy, rrOutput, pDisplay);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display *dpy, RROutput rrOutput,
                                                                   VkDisplayKHR *pDisplay) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    if (icd_term->dispatch.GetRandROutputDisplayEXT != NULL) {
        // Pass the call to the driver
        return icd_term->dispatch.GetRandROutputDisplayEXT(phys_dev_term->phys_dev, dpy, rrOutput, pDisplay);
    } else {
        // Emulate the call
        loader_log(icd_term->this_instance, VULKAN_LOADER_INFO_BIT, 0,
                   "vkGetRandROutputDisplayEXT: Emulating call in ICD \"%s\" by returning null display",
                   icd_term->scanned_icd->lib_name);

        // Return a null handle to indicate this can't be done
        *pDisplay = VK_NULL_HANDLE;
        return VK_SUCCESS;
    }
}

#endif  // VK_USE_PLATFORM_XLIB_XRANDR_EXT

#ifndef VULKANSC  // VK_EXT_full_screen_exclusive is unsupported in Vulkan SC
#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfacePresentModes2EXT(VkPhysicalDevice physicalDevice,
                                                                        const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
                                                                        uint32_t *pPresentModeCount,
                                                                        VkPresentModeKHR *pPresentModes) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSurfacePresentModes2EXT: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSurfacePresentModes2EXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSurfacePresentModes2EXT(unwrapped_phys_dev, pSurfaceInfo, pPresentModeCount, pPresentModes);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSurfacePresentModes2EXT(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo, uint32_t *pPresentModeCount,
    VkPresentModeKHR *pPresentModes) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceSurfacePresentModes2EXT) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceSurfacePresentModes2EXT");
        abort();
    }

    VkPhysicalDeviceSurfaceInfo2KHR surface_info_copy = *pSurfaceInfo;
    if (VK_NULL_HANDLE != pSurfaceInfo->surface) {
        VkResult res = wsi_unwrap_icd_surface(icd_term, &surface_info_copy.surface);
        if (res != VK_SUCCESS) {
            return res;
        }
    }

    return icd_term->dispatch.GetPhysicalDeviceSurfacePresentModes2EXT(phys_dev_term->phys_dev, &surface_info_copy,
                                                                       pPresentModeCount, pPresentModes);
}

VKAPI_ATTR VkResult VKAPI_CALL GetDeviceGroupSurfacePresentModes2EXT(VkDevice device,
                                                                     const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
                                                                     VkDeviceGroupPresentModeFlagsKHR *pModes) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceGroupSurfacePresentModes2EXT: Invalid device "
                   "[VUID-vkGetDeviceGroupSurfacePresentModes2EXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetDeviceGroupSurfacePresentModes2EXT(device, pSurfaceInfo, pModes);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device,
                                                                                const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo,
                                                                                VkDeviceGroupPresentModeFlagsKHR *pModes) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev ||
        NULL == dev->loader_dispatch.extension_terminator_dispatch.GetDeviceGroupSurfacePresentModes2EXT) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceGroupSurfacePresentModes2EXT Terminator: Invalid device handle. This is likely the result of a "
                   "layer wrapping device handles and failing to unwrap them in all functions. "
                   "[VUID-vkGetDeviceGroupSurfacePresentModes2EXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    if (NULL == pSurfaceInfo) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetDeviceGroupSurfacePresentModes2EXT: Invalid pSurfaceInfo pointer "
                   "[VUID-vkGetDeviceGroupSurfacePresentModes2EXT-pSurfaceInfo-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }

    VkPhysicalDeviceSurfaceInfo2KHR surface_info_copy = *pSurfaceInfo;
    if (VK_NULL_HANDLE != pSurfaceInfo->surface) {
        VkResult res = wsi_unwrap_icd_surface(icd_term, &surface_info_copy.surface);
        if (res != VK_SUCCESS) {
            return res;
        }
    }

    return dev->loader_dispatch.extension_terminator_dispatch.GetDeviceGroupSurfacePresentModes2EXT(device, &surface_info_copy,
                                                                                                    pModes);
}

#endif  // VK_USE_PLATFORM_WIN32_KHR
#endif  // VULKANSC

// ---- VK_EXT_tooling_info extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t *pToolCount,
                                                                  VkPhysicalDeviceToolPropertiesEXT *pToolProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceToolPropertiesEXT: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceToolPropertiesEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceToolPropertiesEXT(unwrapped_phys_dev, pToolCount, pToolProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t *pToolCount,
                                                                             VkPhysicalDeviceToolPropertiesEXT *pToolProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;

    bool tooling_info_supported = false;
    uint32_t ext_count = 0;
    VkExtensionProperties *ext_props = NULL;
    VkResult res = VK_SUCCESS;
    VkResult enumerate_res = VK_SUCCESS;

    enumerate_res = icd_term->dispatch.EnumerateDeviceExtensionProperties(phys_dev_term->phys_dev, NULL, &ext_count, NULL);
    if (enumerate_res != VK_SUCCESS) {
        goto out;
    }

    ext_props = loader_instance_heap_alloc(icd_term->this_instance, sizeof(VkExtensionProperties) * ext_count,
                                           VK_SYSTEM_ALLOCATION_SCOPE_COMMAND);
    if (!ext_props) {
        res = VK_ERROR_OUT_OF_HOST_MEMORY;
        goto out;
    }

    enumerate_res = icd_term->dispatch.EnumerateDeviceExtensionProperties(phys_dev_term->phys_dev, NULL, &ext_count, ext_props);
    if (enumerate_res != VK_SUCCESS) {
        goto out;
    }

    for (uint32_t i = 0; i < ext_count; i++) {
        if (strncmp(ext_props[i].extensionName, VK_EXT_TOOLING_INFO_EXTENSION_NAME, VK_MAX_EXTENSION_NAME_SIZE) == 0) {
            tooling_info_supported = true;
            break;
        }
    }

    if (tooling_info_supported && icd_term->dispatch.GetPhysicalDeviceToolPropertiesEXT) {
        res = icd_term->dispatch.GetPhysicalDeviceToolPropertiesEXT(phys_dev_term->phys_dev, pToolCount, pToolProperties);
    }

out:
    // In the case the driver didn't support the extension, make sure that the first layer doesn't find the count uninitialized
    if (!tooling_info_supported || !icd_term->dispatch.GetPhysicalDeviceToolPropertiesEXT) {
        *pToolCount = 0;
    }

    loader_instance_heap_free(icd_term->this_instance, ext_props);

    return res;
}
#endif  // VULKANSC
