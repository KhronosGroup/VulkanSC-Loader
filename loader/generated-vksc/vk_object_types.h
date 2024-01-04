// clang-format off
// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See helper_file_generator.py for modifications


/***************************************************************************
 *
 * Copyright (c) 2015-2017 The Khronos Group Inc.
 * Copyright (c) 2015-2017 Valve Corporation
 * Copyright (c) 2015-2017 LunarG, Inc.
 * Copyright (c) 2015-2017 Google Inc.
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
 * Author: Courtney Goeltzenleuchter <courtneygo@google.com>
 * Author: Tobin Ehlis <tobine@google.com>
 * Author: Chris Forbes <chrisforbes@google.com>
 * Author: John Zulauf<jzulauf@lunarg.com>
 *
 ****************************************************************************/


#pragma once

#include <vulkan/vulkan.h>

// Object Type enum for validation layer internal object handling
typedef enum VulkanObjectType {
    kVulkanObjectTypeUnknown = 0,
    kVulkanObjectTypeBuffer = 1,
    kVulkanObjectTypeImage = 2,
    kVulkanObjectTypeInstance = 3,
    kVulkanObjectTypePhysicalDevice = 4,
    kVulkanObjectTypeDevice = 5,
    kVulkanObjectTypeQueue = 6,
    kVulkanObjectTypeSemaphore = 7,
    kVulkanObjectTypeCommandBuffer = 8,
    kVulkanObjectTypeFence = 9,
    kVulkanObjectTypeDeviceMemory = 10,
    kVulkanObjectTypeEvent = 11,
    kVulkanObjectTypeQueryPool = 12,
    kVulkanObjectTypeBufferView = 13,
    kVulkanObjectTypeImageView = 14,
    kVulkanObjectTypeShaderModule = 15,
    kVulkanObjectTypePipelineCache = 16,
    kVulkanObjectTypePipelineLayout = 17,
    kVulkanObjectTypePipeline = 18,
    kVulkanObjectTypeRenderPass = 19,
    kVulkanObjectTypeDescriptorSetLayout = 20,
    kVulkanObjectTypeSampler = 21,
    kVulkanObjectTypeDescriptorSet = 22,
    kVulkanObjectTypeDescriptorPool = 23,
    kVulkanObjectTypeFramebuffer = 24,
    kVulkanObjectTypeCommandPool = 25,
    kVulkanObjectTypeSamplerYcbcrConversion = 26,
    kVulkanObjectTypePrivateDataSlot = 27,
    kVulkanObjectTypeSurfaceKHR = 28,
    kVulkanObjectTypeSwapchainKHR = 29,
    kVulkanObjectTypeDisplayKHR = 30,
    kVulkanObjectTypeDisplayModeKHR = 31,
    kVulkanObjectTypeDebugUtilsMessengerEXT = 32,
    kVulkanObjectTypeSemaphoreSciSyncPoolNV = 33,
    kVulkanObjectTypeMax = 34,
    // Aliases for backwards compatibilty of "promoted" types
} VulkanObjectType;

// Array of object name strings for OBJECT_TYPE enum conversion
static const char * const object_string[kVulkanObjectTypeMax] = {
    "Unknown",
    "Buffer",
    "Image",
    "Instance",
    "PhysicalDevice",
    "Device",
    "Queue",
    "Semaphore",
    "CommandBuffer",
    "Fence",
    "DeviceMemory",
    "Event",
    "QueryPool",
    "BufferView",
    "ImageView",
    "ShaderModule",
    "PipelineCache",
    "PipelineLayout",
    "Pipeline",
    "RenderPass",
    "DescriptorSetLayout",
    "Sampler",
    "DescriptorSet",
    "DescriptorPool",
    "Framebuffer",
    "CommandPool",
    "SamplerYcbcrConversion",
    "PrivateDataSlot",
    "SurfaceKHR",
    "SwapchainKHR",
    "DisplayKHR",
    "DisplayModeKHR",
    "DebugUtilsMessengerEXT",
    "SemaphoreSciSyncPoolNV",
};

// Helper array to get Vulkan VK_EXT_debug_report object type enum from the internal layers version
const VkDebugReportObjectTypeEXT get_debug_report_enum[] = {
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT, // kVulkanObjectTypeUnknown
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeBuffer
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeImage
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeInstance
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypePhysicalDevice
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeDevice
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeQueue
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeSemaphore
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeCommandBuffer
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeFence
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeDeviceMemory
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeEvent
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeQueryPool
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeBufferView
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeImageView
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeShaderModule
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypePipelineCache
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypePipelineLayout
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypePipeline
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeRenderPass
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeDescriptorSetLayout
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeSampler
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeDescriptorSet
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeDescriptorPool
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeFramebuffer
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeCommandPool
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeSamplerYcbcrConversion
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypePrivateDataSlot
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeSurfaceKHR
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeSwapchainKHR
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeDisplayKHR
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeDisplayModeKHR
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeDebugUtilsMessengerEXT
    VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT,   // kVulkanObjectTypeSemaphoreSciSyncPoolNV
};

// Helper array to get Official Vulkan VkObjectType enum from the internal layers version
const VkObjectType get_object_type_enum[] = {
    VK_OBJECT_TYPE_UNKNOWN, // kVulkanObjectTypeUnknown
    VK_OBJECT_TYPE_BUFFER,   // kVulkanObjectTypeBuffer
    VK_OBJECT_TYPE_IMAGE,   // kVulkanObjectTypeImage
    VK_OBJECT_TYPE_INSTANCE,   // kVulkanObjectTypeInstance
    VK_OBJECT_TYPE_PHYSICAL_DEVICE,   // kVulkanObjectTypePhysicalDevice
    VK_OBJECT_TYPE_DEVICE,   // kVulkanObjectTypeDevice
    VK_OBJECT_TYPE_QUEUE,   // kVulkanObjectTypeQueue
    VK_OBJECT_TYPE_SEMAPHORE,   // kVulkanObjectTypeSemaphore
    VK_OBJECT_TYPE_COMMAND_BUFFER,   // kVulkanObjectTypeCommandBuffer
    VK_OBJECT_TYPE_FENCE,   // kVulkanObjectTypeFence
    VK_OBJECT_TYPE_DEVICE_MEMORY,   // kVulkanObjectTypeDeviceMemory
    VK_OBJECT_TYPE_EVENT,   // kVulkanObjectTypeEvent
    VK_OBJECT_TYPE_QUERY_POOL,   // kVulkanObjectTypeQueryPool
    VK_OBJECT_TYPE_BUFFER_VIEW,   // kVulkanObjectTypeBufferView
    VK_OBJECT_TYPE_IMAGE_VIEW,   // kVulkanObjectTypeImageView
    VK_OBJECT_TYPE_SHADER_MODULE,   // kVulkanObjectTypeShaderModule
    VK_OBJECT_TYPE_PIPELINE_CACHE,   // kVulkanObjectTypePipelineCache
    VK_OBJECT_TYPE_PIPELINE_LAYOUT,   // kVulkanObjectTypePipelineLayout
    VK_OBJECT_TYPE_PIPELINE,   // kVulkanObjectTypePipeline
    VK_OBJECT_TYPE_RENDER_PASS,   // kVulkanObjectTypeRenderPass
    VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT,   // kVulkanObjectTypeDescriptorSetLayout
    VK_OBJECT_TYPE_SAMPLER,   // kVulkanObjectTypeSampler
    VK_OBJECT_TYPE_DESCRIPTOR_SET,   // kVulkanObjectTypeDescriptorSet
    VK_OBJECT_TYPE_DESCRIPTOR_POOL,   // kVulkanObjectTypeDescriptorPool
    VK_OBJECT_TYPE_FRAMEBUFFER,   // kVulkanObjectTypeFramebuffer
    VK_OBJECT_TYPE_COMMAND_POOL,   // kVulkanObjectTypeCommandPool
    VK_OBJECT_TYPE_SAMPLER_YCBCR_CONVERSION,   // kVulkanObjectTypeSamplerYcbcrConversion
    VK_OBJECT_TYPE_PRIVATE_DATA_SLOT,   // kVulkanObjectTypePrivateDataSlot
    VK_OBJECT_TYPE_SURFACE_KHR,   // kVulkanObjectTypeSurfaceKHR
    VK_OBJECT_TYPE_SWAPCHAIN_KHR,   // kVulkanObjectTypeSwapchainKHR
    VK_OBJECT_TYPE_DISPLAY_KHR,   // kVulkanObjectTypeDisplayKHR
    VK_OBJECT_TYPE_DISPLAY_MODE_KHR,   // kVulkanObjectTypeDisplayModeKHR
    VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT,   // kVulkanObjectTypeDebugUtilsMessengerEXT
    VK_OBJECT_TYPE_SEMAPHORE_SCI_SYNC_POOL_NV,   // kVulkanObjectTypeSemaphoreSciSyncPoolNV
};

// Helper function to convert from VkDebugReportObjectTypeEXT to VkObjectType
static inline VkObjectType convertDebugReportObjectToCoreObject(VkDebugReportObjectTypeEXT debug_report_obj){
    if (debug_report_obj == VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT) {
        return VK_OBJECT_TYPE_UNKNOWN;
    }
    return VK_OBJECT_TYPE_UNKNOWN;
}

// Helper function to convert from VkDebugReportObjectTypeEXT to VkObjectType
static inline VkDebugReportObjectTypeEXT convertCoreObjectToDebugReportObject(VkObjectType core_report_obj){
    if (core_report_obj == VK_OBJECT_TYPE_UNKNOWN) {
        return VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT;
    }
    return VK_DEBUG_REPORT_OBJECT_TYPE_UNKNOWN_EXT;
}
// clang-format on
