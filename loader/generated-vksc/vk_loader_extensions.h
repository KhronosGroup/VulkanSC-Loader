// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See loader_extension_generator.py for modifications

/*
 * Copyright (c) 2015-2025 The Khronos Group Inc.
 * Copyright (c) 2015-2025 Valve Corporation
 * Copyright (c) 2015-2025 LunarG, Inc.
 * Copyright (c) 2021-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Mark Young <marky@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 */

// clang-format off
#pragma once

#include <stdbool.h>
#include <vulkan/vulkan.h>
#include <vulkan/vk_layer.h>
#include "vk_layer_dispatch_table.h"


// Structures defined externally, but used here
struct loader_instance;
struct loader_device;
struct loader_icd_term;
struct loader_dev_dispatch_table;

// Device extension error function
VKAPI_ATTR VkResult VKAPI_CALL vkDevExtError(VkDevice dev);

// Extension interception for vkGetInstanceProcAddr function, so we can return
// the appropriate information for any instance extensions we know about.
bool extension_instance_gpa(struct loader_instance *ptr_instance, const char *name, void **addr);

struct loader_instance_extension_enable_list; // Forward declaration

// Extension interception for vkCreateInstance function, so we can properly
// detect and enable any instance extension information for extensions we know
// about.
void fill_out_enabled_instance_extensions(uint32_t extension_count, const char *const * extension_list, struct loader_instance_extension_enable_list* enables);

// Extension interception for vkGetDeviceProcAddr function, so we can return
// an appropriate terminator if this is one of those few device commands requiring
// a terminator.
PFN_vkVoidFunction get_extension_device_proc_terminator(struct loader_device *dev, const char *name, bool* found_name);

// Dispatch table properly filled in with appropriate terminators for the
// supported extensions.
extern const VkLayerInstanceDispatchTable instance_disp;

// Array of extension strings for instance extensions we support.
extern const char *const LOADER_INSTANCE_EXTENSIONS[];

VKAPI_ATTR bool VKAPI_CALL loader_icd_init_entries(struct loader_instance* inst, struct loader_icd_term *icd_term);

// Init Device function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_device_dispatch_table(struct loader_dev_dispatch_table *dev_table, PFN_vkGetDeviceProcAddr gpa,
                                                             VkDevice dev);

// Init Device function pointer dispatch table with extension commands
VKAPI_ATTR void VKAPI_CALL loader_init_device_extension_dispatch_table(struct loader_dev_dispatch_table *dev_table,
                                                                       PFN_vkGetInstanceProcAddr gipa,
                                                                       PFN_vkGetDeviceProcAddr gdpa,
                                                                       VkInstance inst,
                                                                       VkDevice dev);

// Init Instance function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_instance_core_dispatch_table(VkLayerInstanceDispatchTable *table, PFN_vkGetInstanceProcAddr gpa,
                                                                    VkInstance inst);

// Init Instance function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_instance_extension_dispatch_table(VkLayerInstanceDispatchTable *table, PFN_vkGetInstanceProcAddr gpa,
                                                                         VkInstance inst);

// Device command lookup function
VKAPI_ATTR void* VKAPI_CALL loader_lookup_device_dispatch_table(const VkLayerDispatchTable *table, const char *name, bool* name_found);

// Instance command lookup function
VKAPI_ATTR void* VKAPI_CALL loader_lookup_instance_dispatch_table(const VkLayerInstanceDispatchTable *table, const char *name,
                                                                  bool *found_name);

// Loader core instance terminators
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateInstance(
    const VkInstanceCreateInfo*                 pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkInstance*                                 pInstance);
VKAPI_ATTR void VKAPI_CALL terminator_DestroyInstance(
    VkInstance                                  instance,
    const VkAllocationCallbacks*                pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumeratePhysicalDevices(
    VkInstance                                  instance,
    uint32_t*                                   pPhysicalDeviceCount,
    VkPhysicalDevice*                           pPhysicalDevices);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceFeatures(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures*                   pFeatures);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceFormatProperties(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties*                         pFormatProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceImageFormatProperties(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkImageTiling                               tiling,
    VkImageUsageFlags                           usage,
    VkImageCreateFlags                          flags,
    VkImageFormatProperties*                    pImageFormatProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceProperties(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties*                 pProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties*                    pQueueFamilyProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceMemoryProperties(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties*           pMemoryProperties);
VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL terminator_GetInstanceProcAddr(
    VkInstance                                  instance,
    const char*                                 pName);
VKAPI_ATTR VkResult VKAPI_CALL terminator_CreateDevice(
    VkPhysicalDevice                            physicalDevice,
    const VkDeviceCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDevice*                                   pDevice);
VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumerateInstanceExtensionProperties(
    const char*                                 pLayerName,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_pre_instance_EnumerateInstanceExtensionProperties(
    const VkEnumerateInstanceExtensionPropertiesChain* chain,
    const char*                                 pLayerName,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumerateDeviceExtensionProperties(
    VkPhysicalDevice                            physicalDevice,
    const char*                                 pLayerName,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumerateInstanceLayerProperties(
    uint32_t*                                   pPropertyCount,
    VkLayerProperties*                          pProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_pre_instance_EnumerateInstanceLayerProperties(
    const VkEnumerateInstanceLayerPropertiesChain* chain,
    uint32_t*                                   pPropertyCount,
    VkLayerProperties*                          pProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumerateDeviceLayerProperties(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkLayerProperties*                          pProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumerateInstanceVersion(
    uint32_t*                                   pApiVersion);
VKAPI_ATTR VkResult VKAPI_CALL terminator_pre_instance_EnumerateInstanceVersion(
    const VkEnumerateInstanceVersionChain* chain,
    uint32_t*                                   pApiVersion);
VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumeratePhysicalDeviceGroups(
    VkInstance                                  instance,
    uint32_t*                                   pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties*            pPhysicalDeviceGroupProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceFeatures2(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures2*                  pFeatures);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceProperties2(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties2*                pProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceFormatProperties2(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties2*                        pFormatProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceImageFormatProperties2(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2*     pImageFormatInfo,
    VkImageFormatProperties2*                   pImageFormatProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2*                   pQueueFamilyProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceMemoryProperties2(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties2*          pMemoryProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceExternalBufferProperties(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo*   pExternalBufferInfo,
    VkExternalBufferProperties*                 pExternalBufferProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceExternalFenceProperties(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo*    pExternalFenceInfo,
    VkExternalFenceProperties*                  pExternalFenceProperties);
VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceExternalSemaphoreProperties(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties*              pExternalSemaphoreProperties);
VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceToolProperties(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pToolCount,
    VkPhysicalDeviceToolProperties*             pToolProperties);

// ICD function pointer dispatch table
struct loader_icd_term_dispatch {

    // ---- Core Vulkan SC 1.0 commands
    PFN_vkCreateInstance CreateInstance;
    PFN_vkDestroyInstance DestroyInstance;
    PFN_vkEnumeratePhysicalDevices EnumeratePhysicalDevices;
    PFN_vkGetPhysicalDeviceFeatures GetPhysicalDeviceFeatures;
    PFN_vkGetPhysicalDeviceFormatProperties GetPhysicalDeviceFormatProperties;
    PFN_vkGetPhysicalDeviceImageFormatProperties GetPhysicalDeviceImageFormatProperties;
    PFN_vkGetPhysicalDeviceProperties GetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties GetPhysicalDeviceQueueFamilyProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties;
    PFN_vkGetDeviceProcAddr GetDeviceProcAddr;
    PFN_vkCreateDevice CreateDevice;
    PFN_vkEnumerateInstanceExtensionProperties EnumerateInstanceExtensionProperties;
    PFN_vkEnumerateDeviceExtensionProperties EnumerateDeviceExtensionProperties;
    PFN_vkEnumerateInstanceLayerProperties EnumerateInstanceLayerProperties;
    PFN_vkEnumerateInstanceVersion EnumerateInstanceVersion;
    PFN_vkEnumeratePhysicalDeviceGroups EnumeratePhysicalDeviceGroups;
    PFN_vkGetPhysicalDeviceFeatures2 GetPhysicalDeviceFeatures2;
    PFN_vkGetPhysicalDeviceProperties2 GetPhysicalDeviceProperties2;
    PFN_vkGetPhysicalDeviceFormatProperties2 GetPhysicalDeviceFormatProperties2;
    PFN_vkGetPhysicalDeviceImageFormatProperties2 GetPhysicalDeviceImageFormatProperties2;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties2 GetPhysicalDeviceQueueFamilyProperties2;
    PFN_vkGetPhysicalDeviceMemoryProperties2 GetPhysicalDeviceMemoryProperties2;
    PFN_vkGetPhysicalDeviceExternalBufferProperties GetPhysicalDeviceExternalBufferProperties;
    PFN_vkGetPhysicalDeviceExternalFenceProperties GetPhysicalDeviceExternalFenceProperties;
    PFN_vkGetPhysicalDeviceExternalSemaphoreProperties GetPhysicalDeviceExternalSemaphoreProperties;

    // ---- Core Vulkan 1.3 commands
    PFN_vkGetPhysicalDeviceToolProperties GetPhysicalDeviceToolProperties;

    // ---- VK_KHR_surface extension commands
    PFN_vkDestroySurfaceKHR DestroySurfaceKHR;
    PFN_vkGetPhysicalDeviceSurfaceSupportKHR GetPhysicalDeviceSurfaceSupportKHR;
    PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR GetPhysicalDeviceSurfaceCapabilitiesKHR;
    PFN_vkGetPhysicalDeviceSurfaceFormatsKHR GetPhysicalDeviceSurfaceFormatsKHR;
    PFN_vkGetPhysicalDeviceSurfacePresentModesKHR GetPhysicalDeviceSurfacePresentModesKHR;

    // ---- VK_KHR_swapchain extension commands
    PFN_vkGetPhysicalDevicePresentRectanglesKHR GetPhysicalDevicePresentRectanglesKHR;

    // ---- VK_KHR_display extension commands
    PFN_vkGetPhysicalDeviceDisplayPropertiesKHR GetPhysicalDeviceDisplayPropertiesKHR;
    PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR GetPhysicalDeviceDisplayPlanePropertiesKHR;
    PFN_vkGetDisplayPlaneSupportedDisplaysKHR GetDisplayPlaneSupportedDisplaysKHR;
    PFN_vkGetDisplayModePropertiesKHR GetDisplayModePropertiesKHR;
    PFN_vkCreateDisplayModeKHR CreateDisplayModeKHR;
    PFN_vkGetDisplayPlaneCapabilitiesKHR GetDisplayPlaneCapabilitiesKHR;
    PFN_vkCreateDisplayPlaneSurfaceKHR CreateDisplayPlaneSurfaceKHR;

    // ---- VK_KHR_performance_query extension commands
    PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
    PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR GetPhysicalDeviceSurfaceCapabilities2KHR;
    PFN_vkGetPhysicalDeviceSurfaceFormats2KHR GetPhysicalDeviceSurfaceFormats2KHR;

    // ---- VK_KHR_get_display_properties2 extension commands
    PFN_vkGetPhysicalDeviceDisplayProperties2KHR GetPhysicalDeviceDisplayProperties2KHR;
    PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR GetPhysicalDeviceDisplayPlaneProperties2KHR;
    PFN_vkGetDisplayModeProperties2KHR GetDisplayModeProperties2KHR;
    PFN_vkGetDisplayPlaneCapabilities2KHR GetDisplayPlaneCapabilities2KHR;

    // ---- VK_KHR_fragment_shading_rate extension commands
    PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR GetPhysicalDeviceFragmentShadingRatesKHR;

    // ---- VK_KHR_object_refresh extension commands
    PFN_vkGetPhysicalDeviceRefreshableObjectTypesKHR GetPhysicalDeviceRefreshableObjectTypesKHR;

    // ---- VK_KHR_calibrated_timestamps extension commands
    PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR GetPhysicalDeviceCalibrateableTimeDomainsKHR;

    // ---- VK_EXT_direct_mode_display extension commands
    PFN_vkReleaseDisplayEXT ReleaseDisplayEXT;

    // ---- VK_EXT_display_surface_counter extension commands
    PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT GetPhysicalDeviceSurfaceCapabilities2EXT;

    // ---- VK_EXT_debug_utils extension commands
    PFN_vkCreateDebugUtilsMessengerEXT CreateDebugUtilsMessengerEXT;
    PFN_vkDestroyDebugUtilsMessengerEXT DestroyDebugUtilsMessengerEXT;
    PFN_vkSubmitDebugUtilsMessageEXT SubmitDebugUtilsMessageEXT;

    // ---- VK_EXT_sample_locations extension commands
    PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT GetPhysicalDeviceMultisamplePropertiesEXT;

    // ---- VK_EXT_headless_surface extension commands
    PFN_vkCreateHeadlessSurfaceEXT CreateHeadlessSurfaceEXT;

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkAcquireWinrtDisplayNV AcquireWinrtDisplayNV;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    PFN_vkGetWinrtDisplayNV GetWinrtDisplayNV;
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkGetPhysicalDeviceSciSyncAttributesNV GetPhysicalDeviceSciSyncAttributesNV;
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV GetPhysicalDeviceExternalMemorySciBufPropertiesNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkGetPhysicalDeviceSciBufAttributesNV GetPhysicalDeviceSciBufAttributesNV;
#endif // VK_USE_PLATFORM_SCI
};

struct loader_instance_extension_enable_list {
    uint8_t khr_surface;
    uint8_t khr_display;
    uint8_t khr_get_surface_capabilities2;
    uint8_t khr_get_display_properties2;
    uint8_t ext_direct_mode_display;
    uint8_t ext_display_surface_counter;
    uint8_t ext_swapchain_colorspace;
    uint8_t ext_debug_utils;
    uint8_t ext_validation_features;
    uint8_t ext_headless_surface;
    uint8_t ext_application_parameters;
    uint8_t ext_layer_settings;
};

// Functions that required a terminator need to have a separate dispatch table which contains their corresponding
// device function. This is used in the terminators themselves.
struct loader_device_terminator_dispatch {

    // ---- VK_KHR_swapchain extension commands
    PFN_vkCreateSwapchainKHR CreateSwapchainKHR;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR GetDeviceGroupSurfacePresentModesKHR;

    // ---- VK_KHR_display_swapchain extension commands
    PFN_vkCreateSharedSwapchainsKHR CreateSharedSwapchainsKHR;

    // ---- VK_EXT_debug_utils extension commands
    PFN_vkSetDebugUtilsObjectNameEXT SetDebugUtilsObjectNameEXT;
    PFN_vkSetDebugUtilsObjectTagEXT SetDebugUtilsObjectTagEXT;
    PFN_vkQueueBeginDebugUtilsLabelEXT QueueBeginDebugUtilsLabelEXT;
    PFN_vkQueueEndDebugUtilsLabelEXT QueueEndDebugUtilsLabelEXT;
    PFN_vkQueueInsertDebugUtilsLabelEXT QueueInsertDebugUtilsLabelEXT;
    PFN_vkCmdBeginDebugUtilsLabelEXT CmdBeginDebugUtilsLabelEXT;
    PFN_vkCmdEndDebugUtilsLabelEXT CmdEndDebugUtilsLabelEXT;
    PFN_vkCmdInsertDebugUtilsLabelEXT CmdInsertDebugUtilsLabelEXT;
};

// clang-format on
