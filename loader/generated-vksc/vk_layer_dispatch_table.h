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

#include <vulkan/vulkan.h>

#if !defined(PFN_GetPhysicalDeviceProcAddr)
typedef PFN_vkVoidFunction (VKAPI_PTR *PFN_GetPhysicalDeviceProcAddr)(VkInstance instance, const char* pName);
#endif

// Instance function pointer dispatch table
typedef struct VkLayerInstanceDispatchTable_ {
    // Manually add in GetPhysicalDeviceProcAddr entry
    PFN_GetPhysicalDeviceProcAddr GetPhysicalDeviceProcAddr;

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
    PFN_vkGetInstanceProcAddr GetInstanceProcAddr;
    PFN_vkCreateDevice CreateDevice;
    PFN_vkEnumerateInstanceExtensionProperties EnumerateInstanceExtensionProperties;
    PFN_vkEnumerateDeviceExtensionProperties EnumerateDeviceExtensionProperties;
    PFN_vkEnumerateInstanceLayerProperties EnumerateInstanceLayerProperties;
    PFN_vkEnumerateDeviceLayerProperties EnumerateDeviceLayerProperties;
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
} VkLayerInstanceDispatchTable;

// Device function pointer dispatch table
#define DEVICE_DISP_TABLE_MAGIC_NUMBER 0x10ADED040410ADEDUL
typedef struct VkLayerDispatchTable_ {
    uint64_t magic; // Should be DEVICE_DISP_TABLE_MAGIC_NUMBER

    // ---- Core Vulkan SC 1.0 commands
    PFN_vkGetDeviceProcAddr GetDeviceProcAddr;
    PFN_vkDestroyDevice DestroyDevice;
    PFN_vkGetDeviceQueue GetDeviceQueue;
    PFN_vkQueueSubmit QueueSubmit;
    PFN_vkQueueWaitIdle QueueWaitIdle;
    PFN_vkDeviceWaitIdle DeviceWaitIdle;
    PFN_vkAllocateMemory AllocateMemory;
    PFN_vkMapMemory MapMemory;
    PFN_vkUnmapMemory UnmapMemory;
    PFN_vkFlushMappedMemoryRanges FlushMappedMemoryRanges;
    PFN_vkInvalidateMappedMemoryRanges InvalidateMappedMemoryRanges;
    PFN_vkGetDeviceMemoryCommitment GetDeviceMemoryCommitment;
    PFN_vkBindBufferMemory BindBufferMemory;
    PFN_vkBindImageMemory BindImageMemory;
    PFN_vkGetBufferMemoryRequirements GetBufferMemoryRequirements;
    PFN_vkGetImageMemoryRequirements GetImageMemoryRequirements;
    PFN_vkCreateFence CreateFence;
    PFN_vkDestroyFence DestroyFence;
    PFN_vkResetFences ResetFences;
    PFN_vkGetFenceStatus GetFenceStatus;
    PFN_vkWaitForFences WaitForFences;
    PFN_vkCreateSemaphore CreateSemaphore;
    PFN_vkDestroySemaphore DestroySemaphore;
    PFN_vkCreateEvent CreateEvent;
    PFN_vkDestroyEvent DestroyEvent;
    PFN_vkGetEventStatus GetEventStatus;
    PFN_vkSetEvent SetEvent;
    PFN_vkResetEvent ResetEvent;
    PFN_vkCreateQueryPool CreateQueryPool;
    PFN_vkGetQueryPoolResults GetQueryPoolResults;
    PFN_vkCreateBuffer CreateBuffer;
    PFN_vkDestroyBuffer DestroyBuffer;
    PFN_vkCreateBufferView CreateBufferView;
    PFN_vkDestroyBufferView DestroyBufferView;
    PFN_vkCreateImage CreateImage;
    PFN_vkDestroyImage DestroyImage;
    PFN_vkGetImageSubresourceLayout GetImageSubresourceLayout;
    PFN_vkCreateImageView CreateImageView;
    PFN_vkDestroyImageView DestroyImageView;
    PFN_vkCreatePipelineCache CreatePipelineCache;
    PFN_vkDestroyPipelineCache DestroyPipelineCache;
    PFN_vkCreateGraphicsPipelines CreateGraphicsPipelines;
    PFN_vkCreateComputePipelines CreateComputePipelines;
    PFN_vkDestroyPipeline DestroyPipeline;
    PFN_vkCreatePipelineLayout CreatePipelineLayout;
    PFN_vkDestroyPipelineLayout DestroyPipelineLayout;
    PFN_vkCreateSampler CreateSampler;
    PFN_vkDestroySampler DestroySampler;
    PFN_vkCreateDescriptorSetLayout CreateDescriptorSetLayout;
    PFN_vkDestroyDescriptorSetLayout DestroyDescriptorSetLayout;
    PFN_vkCreateDescriptorPool CreateDescriptorPool;
    PFN_vkResetDescriptorPool ResetDescriptorPool;
    PFN_vkAllocateDescriptorSets AllocateDescriptorSets;
    PFN_vkFreeDescriptorSets FreeDescriptorSets;
    PFN_vkUpdateDescriptorSets UpdateDescriptorSets;
    PFN_vkCreateFramebuffer CreateFramebuffer;
    PFN_vkDestroyFramebuffer DestroyFramebuffer;
    PFN_vkCreateRenderPass CreateRenderPass;
    PFN_vkDestroyRenderPass DestroyRenderPass;
    PFN_vkGetRenderAreaGranularity GetRenderAreaGranularity;
    PFN_vkCreateCommandPool CreateCommandPool;
    PFN_vkResetCommandPool ResetCommandPool;
    PFN_vkAllocateCommandBuffers AllocateCommandBuffers;
    PFN_vkFreeCommandBuffers FreeCommandBuffers;
    PFN_vkBeginCommandBuffer BeginCommandBuffer;
    PFN_vkEndCommandBuffer EndCommandBuffer;
    PFN_vkResetCommandBuffer ResetCommandBuffer;
    PFN_vkCmdBindPipeline CmdBindPipeline;
    PFN_vkCmdSetViewport CmdSetViewport;
    PFN_vkCmdSetScissor CmdSetScissor;
    PFN_vkCmdSetLineWidth CmdSetLineWidth;
    PFN_vkCmdSetDepthBias CmdSetDepthBias;
    PFN_vkCmdSetBlendConstants CmdSetBlendConstants;
    PFN_vkCmdSetDepthBounds CmdSetDepthBounds;
    PFN_vkCmdSetStencilCompareMask CmdSetStencilCompareMask;
    PFN_vkCmdSetStencilWriteMask CmdSetStencilWriteMask;
    PFN_vkCmdSetStencilReference CmdSetStencilReference;
    PFN_vkCmdBindDescriptorSets CmdBindDescriptorSets;
    PFN_vkCmdBindIndexBuffer CmdBindIndexBuffer;
    PFN_vkCmdBindVertexBuffers CmdBindVertexBuffers;
    PFN_vkCmdDraw CmdDraw;
    PFN_vkCmdDrawIndexed CmdDrawIndexed;
    PFN_vkCmdDrawIndirect CmdDrawIndirect;
    PFN_vkCmdDrawIndexedIndirect CmdDrawIndexedIndirect;
    PFN_vkCmdDispatch CmdDispatch;
    PFN_vkCmdDispatchIndirect CmdDispatchIndirect;
    PFN_vkCmdCopyBuffer CmdCopyBuffer;
    PFN_vkCmdCopyImage CmdCopyImage;
    PFN_vkCmdBlitImage CmdBlitImage;
    PFN_vkCmdCopyBufferToImage CmdCopyBufferToImage;
    PFN_vkCmdCopyImageToBuffer CmdCopyImageToBuffer;
    PFN_vkCmdUpdateBuffer CmdUpdateBuffer;
    PFN_vkCmdFillBuffer CmdFillBuffer;
    PFN_vkCmdClearColorImage CmdClearColorImage;
    PFN_vkCmdClearDepthStencilImage CmdClearDepthStencilImage;
    PFN_vkCmdClearAttachments CmdClearAttachments;
    PFN_vkCmdResolveImage CmdResolveImage;
    PFN_vkCmdSetEvent CmdSetEvent;
    PFN_vkCmdResetEvent CmdResetEvent;
    PFN_vkCmdWaitEvents CmdWaitEvents;
    PFN_vkCmdPipelineBarrier CmdPipelineBarrier;
    PFN_vkCmdBeginQuery CmdBeginQuery;
    PFN_vkCmdEndQuery CmdEndQuery;
    PFN_vkCmdResetQueryPool CmdResetQueryPool;
    PFN_vkCmdWriteTimestamp CmdWriteTimestamp;
    PFN_vkCmdCopyQueryPoolResults CmdCopyQueryPoolResults;
    PFN_vkCmdPushConstants CmdPushConstants;
    PFN_vkCmdBeginRenderPass CmdBeginRenderPass;
    PFN_vkCmdNextSubpass CmdNextSubpass;
    PFN_vkCmdEndRenderPass CmdEndRenderPass;
    PFN_vkCmdExecuteCommands CmdExecuteCommands;
    PFN_vkBindBufferMemory2 BindBufferMemory2;
    PFN_vkBindImageMemory2 BindImageMemory2;
    PFN_vkGetDeviceGroupPeerMemoryFeatures GetDeviceGroupPeerMemoryFeatures;
    PFN_vkCmdSetDeviceMask CmdSetDeviceMask;
    PFN_vkCmdDispatchBase CmdDispatchBase;
    PFN_vkGetImageMemoryRequirements2 GetImageMemoryRequirements2;
    PFN_vkGetBufferMemoryRequirements2 GetBufferMemoryRequirements2;
    PFN_vkGetDeviceQueue2 GetDeviceQueue2;
    PFN_vkCreateSamplerYcbcrConversion CreateSamplerYcbcrConversion;
    PFN_vkDestroySamplerYcbcrConversion DestroySamplerYcbcrConversion;
    PFN_vkGetDescriptorSetLayoutSupport GetDescriptorSetLayoutSupport;
    PFN_vkCmdDrawIndirectCount CmdDrawIndirectCount;
    PFN_vkCmdDrawIndexedIndirectCount CmdDrawIndexedIndirectCount;
    PFN_vkCreateRenderPass2 CreateRenderPass2;
    PFN_vkCmdBeginRenderPass2 CmdBeginRenderPass2;
    PFN_vkCmdNextSubpass2 CmdNextSubpass2;
    PFN_vkCmdEndRenderPass2 CmdEndRenderPass2;
    PFN_vkResetQueryPool ResetQueryPool;
    PFN_vkGetSemaphoreCounterValue GetSemaphoreCounterValue;
    PFN_vkWaitSemaphores WaitSemaphores;
    PFN_vkSignalSemaphore SignalSemaphore;
    PFN_vkGetBufferDeviceAddress GetBufferDeviceAddress;
    PFN_vkGetBufferOpaqueCaptureAddress GetBufferOpaqueCaptureAddress;
    PFN_vkGetDeviceMemoryOpaqueCaptureAddress GetDeviceMemoryOpaqueCaptureAddress;

    // ---- Core Vulkan 1.3 commands
    PFN_vkCreatePrivateDataSlot CreatePrivateDataSlot;
    PFN_vkDestroyPrivateDataSlot DestroyPrivateDataSlot;
    PFN_vkSetPrivateData SetPrivateData;
    PFN_vkGetPrivateData GetPrivateData;
    PFN_vkCmdSetEvent2 CmdSetEvent2;
    PFN_vkCmdResetEvent2 CmdResetEvent2;
    PFN_vkCmdWaitEvents2 CmdWaitEvents2;
    PFN_vkCmdPipelineBarrier2 CmdPipelineBarrier2;
    PFN_vkCmdWriteTimestamp2 CmdWriteTimestamp2;
    PFN_vkQueueSubmit2 QueueSubmit2;
    PFN_vkCmdCopyBuffer2 CmdCopyBuffer2;
    PFN_vkCmdCopyImage2 CmdCopyImage2;
    PFN_vkCmdCopyBufferToImage2 CmdCopyBufferToImage2;
    PFN_vkCmdCopyImageToBuffer2 CmdCopyImageToBuffer2;
    PFN_vkCmdBlitImage2 CmdBlitImage2;
    PFN_vkCmdResolveImage2 CmdResolveImage2;
    PFN_vkCmdBeginRendering CmdBeginRendering;
    PFN_vkCmdEndRendering CmdEndRendering;
    PFN_vkCmdSetCullMode CmdSetCullMode;
    PFN_vkCmdSetFrontFace CmdSetFrontFace;
    PFN_vkCmdSetPrimitiveTopology CmdSetPrimitiveTopology;
    PFN_vkCmdSetViewportWithCount CmdSetViewportWithCount;
    PFN_vkCmdSetScissorWithCount CmdSetScissorWithCount;
    PFN_vkCmdBindVertexBuffers2 CmdBindVertexBuffers2;
    PFN_vkCmdSetDepthTestEnable CmdSetDepthTestEnable;
    PFN_vkCmdSetDepthWriteEnable CmdSetDepthWriteEnable;
    PFN_vkCmdSetDepthCompareOp CmdSetDepthCompareOp;
    PFN_vkCmdSetDepthBoundsTestEnable CmdSetDepthBoundsTestEnable;
    PFN_vkCmdSetStencilTestEnable CmdSetStencilTestEnable;
    PFN_vkCmdSetStencilOp CmdSetStencilOp;
    PFN_vkCmdSetRasterizerDiscardEnable CmdSetRasterizerDiscardEnable;
    PFN_vkCmdSetDepthBiasEnable CmdSetDepthBiasEnable;
    PFN_vkCmdSetPrimitiveRestartEnable CmdSetPrimitiveRestartEnable;
    PFN_vkGetDeviceBufferMemoryRequirements GetDeviceBufferMemoryRequirements;
    PFN_vkGetDeviceImageMemoryRequirements GetDeviceImageMemoryRequirements;
    PFN_vkGetDeviceImageSparseMemoryRequirements GetDeviceImageSparseMemoryRequirements;

    // ---- Core Vulkan 1.4 commands
    PFN_vkCmdSetLineStipple CmdSetLineStipple;
    PFN_vkMapMemory2 MapMemory2;
    PFN_vkUnmapMemory2 UnmapMemory2;
    PFN_vkCmdBindIndexBuffer2 CmdBindIndexBuffer2;
    PFN_vkGetRenderingAreaGranularity GetRenderingAreaGranularity;
    PFN_vkGetDeviceImageSubresourceLayout GetDeviceImageSubresourceLayout;
    PFN_vkGetImageSubresourceLayout2 GetImageSubresourceLayout2;
    PFN_vkCmdPushDescriptorSet CmdPushDescriptorSet;
    PFN_vkCmdSetRenderingAttachmentLocations CmdSetRenderingAttachmentLocations;
    PFN_vkCmdSetRenderingInputAttachmentIndices CmdSetRenderingInputAttachmentIndices;
    PFN_vkCmdBindDescriptorSets2 CmdBindDescriptorSets2;
    PFN_vkCmdPushConstants2 CmdPushConstants2;
    PFN_vkCmdPushDescriptorSet2 CmdPushDescriptorSet2;
    PFN_vkCopyMemoryToImage CopyMemoryToImage;
    PFN_vkCopyImageToMemory CopyImageToMemory;
    PFN_vkCopyImageToImage CopyImageToImage;
    PFN_vkTransitionImageLayout TransitionImageLayout;

    // ---- Core Vulkan SC 1.0 commands
    PFN_vkGetCommandPoolMemoryConsumption GetCommandPoolMemoryConsumption;
    PFN_vkGetFaultData GetFaultData;
    PFN_vkCreateSwapchainKHR CreateSwapchainKHR;
    PFN_vkGetSwapchainImagesKHR GetSwapchainImagesKHR;
    PFN_vkAcquireNextImageKHR AcquireNextImageKHR;
    PFN_vkQueuePresentKHR QueuePresentKHR;
    PFN_vkGetDeviceGroupPresentCapabilitiesKHR GetDeviceGroupPresentCapabilitiesKHR;
    PFN_vkGetDeviceGroupSurfacePresentModesKHR GetDeviceGroupSurfacePresentModesKHR;
    PFN_vkAcquireNextImage2KHR AcquireNextImage2KHR;
    PFN_vkCreateSharedSwapchainsKHR CreateSharedSwapchainsKHR;
    PFN_vkGetMemoryFdKHR GetMemoryFdKHR;
    PFN_vkGetMemoryFdPropertiesKHR GetMemoryFdPropertiesKHR;
    PFN_vkImportSemaphoreFdKHR ImportSemaphoreFdKHR;
    PFN_vkGetSemaphoreFdKHR GetSemaphoreFdKHR;
    PFN_vkGetSwapchainStatusKHR GetSwapchainStatusKHR;
    PFN_vkImportFenceFdKHR ImportFenceFdKHR;
    PFN_vkGetFenceFdKHR GetFenceFdKHR;
    PFN_vkAcquireProfilingLockKHR AcquireProfilingLockKHR;
    PFN_vkReleaseProfilingLockKHR ReleaseProfilingLockKHR;
    PFN_vkCmdSetFragmentShadingRateKHR CmdSetFragmentShadingRateKHR;
    PFN_vkCmdRefreshObjectsKHR CmdRefreshObjectsKHR;
    PFN_vkCmdSetEvent2KHR CmdSetEvent2KHR;
    PFN_vkCmdResetEvent2KHR CmdResetEvent2KHR;
    PFN_vkCmdWaitEvents2KHR CmdWaitEvents2KHR;
    PFN_vkCmdPipelineBarrier2KHR CmdPipelineBarrier2KHR;
    PFN_vkCmdWriteTimestamp2KHR CmdWriteTimestamp2KHR;
    PFN_vkQueueSubmit2KHR QueueSubmit2KHR;
    PFN_vkCmdCopyBuffer2KHR CmdCopyBuffer2KHR;
    PFN_vkCmdCopyImage2KHR CmdCopyImage2KHR;
    PFN_vkCmdCopyBufferToImage2KHR CmdCopyBufferToImage2KHR;
    PFN_vkCmdCopyImageToBuffer2KHR CmdCopyImageToBuffer2KHR;
    PFN_vkCmdBlitImage2KHR CmdBlitImage2KHR;
    PFN_vkCmdResolveImage2KHR CmdResolveImage2KHR;
    PFN_vkCmdSetLineStippleKHR CmdSetLineStippleKHR;
    PFN_vkGetCalibratedTimestampsKHR GetCalibratedTimestampsKHR;
    PFN_vkDisplayPowerControlEXT DisplayPowerControlEXT;
    PFN_vkRegisterDeviceEventEXT RegisterDeviceEventEXT;
    PFN_vkRegisterDisplayEventEXT RegisterDisplayEventEXT;
    PFN_vkGetSwapchainCounterEXT GetSwapchainCounterEXT;
    PFN_vkCmdSetDiscardRectangleEXT CmdSetDiscardRectangleEXT;
    PFN_vkCmdSetDiscardRectangleEnableEXT CmdSetDiscardRectangleEnableEXT;
    PFN_vkCmdSetDiscardRectangleModeEXT CmdSetDiscardRectangleModeEXT;
    PFN_vkSetHdrMetadataEXT SetHdrMetadataEXT;
    PFN_vkSetDebugUtilsObjectNameEXT SetDebugUtilsObjectNameEXT;
    PFN_vkSetDebugUtilsObjectTagEXT SetDebugUtilsObjectTagEXT;
    PFN_vkQueueBeginDebugUtilsLabelEXT QueueBeginDebugUtilsLabelEXT;
    PFN_vkQueueEndDebugUtilsLabelEXT QueueEndDebugUtilsLabelEXT;
    PFN_vkQueueInsertDebugUtilsLabelEXT QueueInsertDebugUtilsLabelEXT;
    PFN_vkCmdBeginDebugUtilsLabelEXT CmdBeginDebugUtilsLabelEXT;
    PFN_vkCmdEndDebugUtilsLabelEXT CmdEndDebugUtilsLabelEXT;
    PFN_vkCmdInsertDebugUtilsLabelEXT CmdInsertDebugUtilsLabelEXT;
    PFN_vkCmdSetSampleLocationsEXT CmdSetSampleLocationsEXT;
    PFN_vkGetImageDrmFormatModifierPropertiesEXT GetImageDrmFormatModifierPropertiesEXT;
    PFN_vkGetMemoryHostPointerPropertiesEXT GetMemoryHostPointerPropertiesEXT;
    PFN_vkCmdSetLineStippleEXT CmdSetLineStippleEXT;
    PFN_vkCmdSetCullModeEXT CmdSetCullModeEXT;
    PFN_vkCmdSetFrontFaceEXT CmdSetFrontFaceEXT;
    PFN_vkCmdSetPrimitiveTopologyEXT CmdSetPrimitiveTopologyEXT;
    PFN_vkCmdSetViewportWithCountEXT CmdSetViewportWithCountEXT;
    PFN_vkCmdSetScissorWithCountEXT CmdSetScissorWithCountEXT;
    PFN_vkCmdBindVertexBuffers2EXT CmdBindVertexBuffers2EXT;
    PFN_vkCmdSetDepthTestEnableEXT CmdSetDepthTestEnableEXT;
    PFN_vkCmdSetDepthWriteEnableEXT CmdSetDepthWriteEnableEXT;
    PFN_vkCmdSetDepthCompareOpEXT CmdSetDepthCompareOpEXT;
    PFN_vkCmdSetDepthBoundsTestEnableEXT CmdSetDepthBoundsTestEnableEXT;
    PFN_vkCmdSetStencilTestEnableEXT CmdSetStencilTestEnableEXT;
    PFN_vkCmdSetStencilOpEXT CmdSetStencilOpEXT;
    PFN_vkCmdSetVertexInputEXT CmdSetVertexInputEXT;
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkGetFenceSciSyncFenceNV GetFenceSciSyncFenceNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkGetFenceSciSyncObjNV GetFenceSciSyncObjNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkImportFenceSciSyncFenceNV ImportFenceSciSyncFenceNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkImportFenceSciSyncObjNV ImportFenceSciSyncObjNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkGetSemaphoreSciSyncObjNV GetSemaphoreSciSyncObjNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkImportSemaphoreSciSyncObjNV ImportSemaphoreSciSyncObjNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkGetMemorySciBufNV GetMemorySciBufNV;
#endif // VK_USE_PLATFORM_SCI
    PFN_vkCmdSetPatchControlPointsEXT CmdSetPatchControlPointsEXT;
    PFN_vkCmdSetRasterizerDiscardEnableEXT CmdSetRasterizerDiscardEnableEXT;
    PFN_vkCmdSetDepthBiasEnableEXT CmdSetDepthBiasEnableEXT;
    PFN_vkCmdSetLogicOpEXT CmdSetLogicOpEXT;
    PFN_vkCmdSetPrimitiveRestartEnableEXT CmdSetPrimitiveRestartEnableEXT;
    PFN_vkCmdSetColorWriteEnableEXT CmdSetColorWriteEnableEXT;
#if defined(VK_USE_PLATFORM_SCI)
    PFN_vkCreateSemaphoreSciSyncPoolNV CreateSemaphoreSciSyncPoolNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    PFN_vkGetScreenBufferPropertiesQNX GetScreenBufferPropertiesQNX;
#endif // VK_USE_PLATFORM_SCREEN_QNX
} VkLayerDispatchTable;

// clang-format on
