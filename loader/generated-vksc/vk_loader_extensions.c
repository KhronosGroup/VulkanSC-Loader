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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"
#include "vk_loader_extensions.h"
#include <vulkan/vk_icd.h>
#include "wsi.h"
#include "debug_utils.h"
#include "extension_manual.h"

// Device extension error function
VKAPI_ATTR VkResult VKAPI_CALL vkDevExtError(VkDevice dev) {
    struct loader_device *found_dev;
    // The device going in is a trampoline device
    struct loader_icd_term *icd_term = loader_get_icd_and_device(dev, &found_dev);

    if (icd_term)
        loader_log(icd_term->this_instance, VULKAN_LOADER_ERROR_BIT, 0,
                   "Bad destination in loader trampoline dispatch,"
                   "Are layers and extensions that you are calling enabled?");
    return VK_ERROR_EXTENSION_NOT_PRESENT;
}

VKAPI_ATTR bool VKAPI_CALL loader_icd_init_entries(struct loader_instance* inst, struct loader_icd_term *icd_term) {
    const PFN_vkGetInstanceProcAddr fp_gipa = icd_term->scanned_icd->GetInstanceProcAddr;

#define LOOKUP_GIPA(func) icd_term->dispatch.func = (PFN_vk##func)fp_gipa(icd_term->instance, "vk" #func);

#define LOOKUP_REQUIRED_GIPA(func)                                                      \
    do {                                                                                \
        LOOKUP_GIPA(func);                                                              \
        if (!icd_term->dispatch.func) {                                                 \
            loader_log(inst, VULKAN_LOADER_WARN_BIT, 0, "Unable to load %s from ICD %s",\
                       "vk"#func, icd_term->scanned_icd->lib_name);                     \
            return false;                                                               \
        }                                                                               \
    } while (0)


    // ---- Core Vulkan SC 1.0
    LOOKUP_REQUIRED_GIPA(DestroyInstance);
    LOOKUP_REQUIRED_GIPA(EnumeratePhysicalDevices);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceFeatures);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceFormatProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceImageFormatProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceQueueFamilyProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceMemoryProperties);
    LOOKUP_REQUIRED_GIPA(GetDeviceProcAddr);
    LOOKUP_REQUIRED_GIPA(CreateDevice);
    LOOKUP_REQUIRED_GIPA(EnumerateDeviceExtensionProperties);
    LOOKUP_REQUIRED_GIPA(EnumeratePhysicalDeviceGroups);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceFeatures2);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceProperties2);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceFormatProperties2);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceImageFormatProperties2);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceQueueFamilyProperties2);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceMemoryProperties2);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceExternalBufferProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceExternalFenceProperties);
    LOOKUP_REQUIRED_GIPA(GetPhysicalDeviceExternalSemaphoreProperties);

    // ---- Core Vulkan 1.3
    LOOKUP_GIPA(GetPhysicalDeviceToolProperties);

    // ---- VK_KHR_surface extension commands
    LOOKUP_GIPA(DestroySurfaceKHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceSupportKHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceCapabilitiesKHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceFormatsKHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfacePresentModesKHR);

    // ---- VK_KHR_swapchain extension commands
    LOOKUP_GIPA(GetPhysicalDevicePresentRectanglesKHR);

    // ---- VK_KHR_display extension commands
    LOOKUP_GIPA(GetPhysicalDeviceDisplayPropertiesKHR);
    LOOKUP_GIPA(GetPhysicalDeviceDisplayPlanePropertiesKHR);
    LOOKUP_GIPA(GetDisplayPlaneSupportedDisplaysKHR);
    LOOKUP_GIPA(GetDisplayModePropertiesKHR);
    LOOKUP_GIPA(CreateDisplayModeKHR);
    LOOKUP_GIPA(GetDisplayPlaneCapabilitiesKHR);
    LOOKUP_GIPA(CreateDisplayPlaneSurfaceKHR);

    // ---- VK_KHR_performance_query extension commands
    LOOKUP_GIPA(EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR);
    LOOKUP_GIPA(GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR);

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceCapabilities2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceFormats2KHR);

    // ---- VK_KHR_get_display_properties2 extension commands
    LOOKUP_GIPA(GetPhysicalDeviceDisplayProperties2KHR);
    LOOKUP_GIPA(GetPhysicalDeviceDisplayPlaneProperties2KHR);
    LOOKUP_GIPA(GetDisplayModeProperties2KHR);
    LOOKUP_GIPA(GetDisplayPlaneCapabilities2KHR);

    // ---- VK_KHR_fragment_shading_rate extension commands
    LOOKUP_GIPA(GetPhysicalDeviceFragmentShadingRatesKHR);

    // ---- VK_KHR_object_refresh extension commands
    LOOKUP_GIPA(GetPhysicalDeviceRefreshableObjectTypesKHR);

    // ---- VK_KHR_calibrated_timestamps extension commands
    LOOKUP_GIPA(GetPhysicalDeviceCalibrateableTimeDomainsKHR);

    // ---- VK_EXT_direct_mode_display extension commands
    LOOKUP_GIPA(ReleaseDisplayEXT);

    // ---- VK_EXT_display_surface_counter extension commands
    LOOKUP_GIPA(GetPhysicalDeviceSurfaceCapabilities2EXT);

    // ---- VK_EXT_debug_utils extension commands
    LOOKUP_GIPA(CreateDebugUtilsMessengerEXT);
    LOOKUP_GIPA(DestroyDebugUtilsMessengerEXT);
    LOOKUP_GIPA(SubmitDebugUtilsMessageEXT);

    // ---- VK_EXT_sample_locations extension commands
    LOOKUP_GIPA(GetPhysicalDeviceMultisamplePropertiesEXT);

    // ---- VK_EXT_headless_surface extension commands
    LOOKUP_GIPA(CreateHeadlessSurfaceEXT);

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    LOOKUP_GIPA(AcquireWinrtDisplayNV);
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    LOOKUP_GIPA(GetWinrtDisplayNV);
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
    LOOKUP_GIPA(GetPhysicalDeviceSciSyncAttributesNV);
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
    LOOKUP_GIPA(GetPhysicalDeviceExternalMemorySciBufPropertiesNV);
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    LOOKUP_GIPA(GetPhysicalDeviceSciBufAttributesNV);
#endif // VK_USE_PLATFORM_SCI

#undef LOOKUP_REQUIRED_GIPA
#undef LOOKUP_GIPA

    return true;
};

// Init Device function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_device_dispatch_table(struct loader_dev_dispatch_table *dev_table, PFN_vkGetDeviceProcAddr gpa,
                                                             VkDevice dev) {
    VkLayerDispatchTable *table = &dev_table->core_dispatch;
    if (table->magic != DEVICE_DISP_TABLE_MAGIC_NUMBER) { abort(); }
    for (uint32_t i = 0; i < MAX_NUM_UNKNOWN_EXTS; i++) dev_table->ext_dispatch[i] = (PFN_vkDevExt)vkDevExtError;

    // ---- Core Vulkan SC 1.0 commands
    table->GetDeviceProcAddr = gpa;
    table->DestroyDevice = (PFN_vkDestroyDevice)gpa(dev, "vkDestroyDevice");
    table->GetDeviceQueue = (PFN_vkGetDeviceQueue)gpa(dev, "vkGetDeviceQueue");
    table->QueueSubmit = (PFN_vkQueueSubmit)gpa(dev, "vkQueueSubmit");
    table->QueueWaitIdle = (PFN_vkQueueWaitIdle)gpa(dev, "vkQueueWaitIdle");
    table->DeviceWaitIdle = (PFN_vkDeviceWaitIdle)gpa(dev, "vkDeviceWaitIdle");
    table->AllocateMemory = (PFN_vkAllocateMemory)gpa(dev, "vkAllocateMemory");
    table->MapMemory = (PFN_vkMapMemory)gpa(dev, "vkMapMemory");
    table->UnmapMemory = (PFN_vkUnmapMemory)gpa(dev, "vkUnmapMemory");
    table->FlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)gpa(dev, "vkFlushMappedMemoryRanges");
    table->InvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)gpa(dev, "vkInvalidateMappedMemoryRanges");
    table->GetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)gpa(dev, "vkGetDeviceMemoryCommitment");
    table->BindBufferMemory = (PFN_vkBindBufferMemory)gpa(dev, "vkBindBufferMemory");
    table->BindImageMemory = (PFN_vkBindImageMemory)gpa(dev, "vkBindImageMemory");
    table->GetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)gpa(dev, "vkGetBufferMemoryRequirements");
    table->GetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)gpa(dev, "vkGetImageMemoryRequirements");
    table->CreateFence = (PFN_vkCreateFence)gpa(dev, "vkCreateFence");
    table->DestroyFence = (PFN_vkDestroyFence)gpa(dev, "vkDestroyFence");
    table->ResetFences = (PFN_vkResetFences)gpa(dev, "vkResetFences");
    table->GetFenceStatus = (PFN_vkGetFenceStatus)gpa(dev, "vkGetFenceStatus");
    table->WaitForFences = (PFN_vkWaitForFences)gpa(dev, "vkWaitForFences");
    table->CreateSemaphore = (PFN_vkCreateSemaphore)gpa(dev, "vkCreateSemaphore");
    table->DestroySemaphore = (PFN_vkDestroySemaphore)gpa(dev, "vkDestroySemaphore");
    table->CreateQueryPool = (PFN_vkCreateQueryPool)gpa(dev, "vkCreateQueryPool");
    table->GetQueryPoolResults = (PFN_vkGetQueryPoolResults)gpa(dev, "vkGetQueryPoolResults");
    table->CreateBuffer = (PFN_vkCreateBuffer)gpa(dev, "vkCreateBuffer");
    table->DestroyBuffer = (PFN_vkDestroyBuffer)gpa(dev, "vkDestroyBuffer");
    table->CreateImage = (PFN_vkCreateImage)gpa(dev, "vkCreateImage");
    table->DestroyImage = (PFN_vkDestroyImage)gpa(dev, "vkDestroyImage");
    table->GetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)gpa(dev, "vkGetImageSubresourceLayout");
    table->CreateImageView = (PFN_vkCreateImageView)gpa(dev, "vkCreateImageView");
    table->DestroyImageView = (PFN_vkDestroyImageView)gpa(dev, "vkDestroyImageView");
    table->CreateCommandPool = (PFN_vkCreateCommandPool)gpa(dev, "vkCreateCommandPool");
    table->ResetCommandPool = (PFN_vkResetCommandPool)gpa(dev, "vkResetCommandPool");
    table->AllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)gpa(dev, "vkAllocateCommandBuffers");
    table->FreeCommandBuffers = (PFN_vkFreeCommandBuffers)gpa(dev, "vkFreeCommandBuffers");
    table->BeginCommandBuffer = (PFN_vkBeginCommandBuffer)gpa(dev, "vkBeginCommandBuffer");
    table->EndCommandBuffer = (PFN_vkEndCommandBuffer)gpa(dev, "vkEndCommandBuffer");
    table->ResetCommandBuffer = (PFN_vkResetCommandBuffer)gpa(dev, "vkResetCommandBuffer");
    table->CmdCopyBuffer = (PFN_vkCmdCopyBuffer)gpa(dev, "vkCmdCopyBuffer");
    table->CmdCopyImage = (PFN_vkCmdCopyImage)gpa(dev, "vkCmdCopyImage");
    table->CmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)gpa(dev, "vkCmdCopyBufferToImage");
    table->CmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)gpa(dev, "vkCmdCopyImageToBuffer");
    table->CmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)gpa(dev, "vkCmdUpdateBuffer");
    table->CmdFillBuffer = (PFN_vkCmdFillBuffer)gpa(dev, "vkCmdFillBuffer");
    table->CmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)gpa(dev, "vkCmdPipelineBarrier");
    table->CmdBeginQuery = (PFN_vkCmdBeginQuery)gpa(dev, "vkCmdBeginQuery");
    table->CmdEndQuery = (PFN_vkCmdEndQuery)gpa(dev, "vkCmdEndQuery");
    table->CmdResetQueryPool = (PFN_vkCmdResetQueryPool)gpa(dev, "vkCmdResetQueryPool");
    table->CmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)gpa(dev, "vkCmdWriteTimestamp");
    table->CmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)gpa(dev, "vkCmdCopyQueryPoolResults");
    table->CmdExecuteCommands = (PFN_vkCmdExecuteCommands)gpa(dev, "vkCmdExecuteCommands");
    table->CreateEvent = (PFN_vkCreateEvent)gpa(dev, "vkCreateEvent");
    table->DestroyEvent = (PFN_vkDestroyEvent)gpa(dev, "vkDestroyEvent");
    table->GetEventStatus = (PFN_vkGetEventStatus)gpa(dev, "vkGetEventStatus");
    table->SetEvent = (PFN_vkSetEvent)gpa(dev, "vkSetEvent");
    table->ResetEvent = (PFN_vkResetEvent)gpa(dev, "vkResetEvent");
    table->CreateBufferView = (PFN_vkCreateBufferView)gpa(dev, "vkCreateBufferView");
    table->DestroyBufferView = (PFN_vkDestroyBufferView)gpa(dev, "vkDestroyBufferView");
    table->CreatePipelineCache = (PFN_vkCreatePipelineCache)gpa(dev, "vkCreatePipelineCache");
    table->DestroyPipelineCache = (PFN_vkDestroyPipelineCache)gpa(dev, "vkDestroyPipelineCache");
    table->CreateComputePipelines = (PFN_vkCreateComputePipelines)gpa(dev, "vkCreateComputePipelines");
    table->DestroyPipeline = (PFN_vkDestroyPipeline)gpa(dev, "vkDestroyPipeline");
    table->CreatePipelineLayout = (PFN_vkCreatePipelineLayout)gpa(dev, "vkCreatePipelineLayout");
    table->DestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)gpa(dev, "vkDestroyPipelineLayout");
    table->CreateSampler = (PFN_vkCreateSampler)gpa(dev, "vkCreateSampler");
    table->DestroySampler = (PFN_vkDestroySampler)gpa(dev, "vkDestroySampler");
    table->CreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)gpa(dev, "vkCreateDescriptorSetLayout");
    table->DestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)gpa(dev, "vkDestroyDescriptorSetLayout");
    table->CreateDescriptorPool = (PFN_vkCreateDescriptorPool)gpa(dev, "vkCreateDescriptorPool");
    table->ResetDescriptorPool = (PFN_vkResetDescriptorPool)gpa(dev, "vkResetDescriptorPool");
    table->AllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)gpa(dev, "vkAllocateDescriptorSets");
    table->FreeDescriptorSets = (PFN_vkFreeDescriptorSets)gpa(dev, "vkFreeDescriptorSets");
    table->UpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)gpa(dev, "vkUpdateDescriptorSets");
    table->CmdBindPipeline = (PFN_vkCmdBindPipeline)gpa(dev, "vkCmdBindPipeline");
    table->CmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)gpa(dev, "vkCmdBindDescriptorSets");
    table->CmdClearColorImage = (PFN_vkCmdClearColorImage)gpa(dev, "vkCmdClearColorImage");
    table->CmdDispatch = (PFN_vkCmdDispatch)gpa(dev, "vkCmdDispatch");
    table->CmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)gpa(dev, "vkCmdDispatchIndirect");
    table->CmdSetEvent = (PFN_vkCmdSetEvent)gpa(dev, "vkCmdSetEvent");
    table->CmdResetEvent = (PFN_vkCmdResetEvent)gpa(dev, "vkCmdResetEvent");
    table->CmdWaitEvents = (PFN_vkCmdWaitEvents)gpa(dev, "vkCmdWaitEvents");
    table->CmdPushConstants = (PFN_vkCmdPushConstants)gpa(dev, "vkCmdPushConstants");
    table->CreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)gpa(dev, "vkCreateGraphicsPipelines");
    table->CreateFramebuffer = (PFN_vkCreateFramebuffer)gpa(dev, "vkCreateFramebuffer");
    table->DestroyFramebuffer = (PFN_vkDestroyFramebuffer)gpa(dev, "vkDestroyFramebuffer");
    table->CreateRenderPass = (PFN_vkCreateRenderPass)gpa(dev, "vkCreateRenderPass");
    table->DestroyRenderPass = (PFN_vkDestroyRenderPass)gpa(dev, "vkDestroyRenderPass");
    table->GetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)gpa(dev, "vkGetRenderAreaGranularity");
    table->CmdSetViewport = (PFN_vkCmdSetViewport)gpa(dev, "vkCmdSetViewport");
    table->CmdSetScissor = (PFN_vkCmdSetScissor)gpa(dev, "vkCmdSetScissor");
    table->CmdSetLineWidth = (PFN_vkCmdSetLineWidth)gpa(dev, "vkCmdSetLineWidth");
    table->CmdSetDepthBias = (PFN_vkCmdSetDepthBias)gpa(dev, "vkCmdSetDepthBias");
    table->CmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)gpa(dev, "vkCmdSetBlendConstants");
    table->CmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)gpa(dev, "vkCmdSetDepthBounds");
    table->CmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)gpa(dev, "vkCmdSetStencilCompareMask");
    table->CmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)gpa(dev, "vkCmdSetStencilWriteMask");
    table->CmdSetStencilReference = (PFN_vkCmdSetStencilReference)gpa(dev, "vkCmdSetStencilReference");
    table->CmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)gpa(dev, "vkCmdBindIndexBuffer");
    table->CmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)gpa(dev, "vkCmdBindVertexBuffers");
    table->CmdDraw = (PFN_vkCmdDraw)gpa(dev, "vkCmdDraw");
    table->CmdDrawIndexed = (PFN_vkCmdDrawIndexed)gpa(dev, "vkCmdDrawIndexed");
    table->CmdDrawIndirect = (PFN_vkCmdDrawIndirect)gpa(dev, "vkCmdDrawIndirect");
    table->CmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)gpa(dev, "vkCmdDrawIndexedIndirect");
    table->CmdBlitImage = (PFN_vkCmdBlitImage)gpa(dev, "vkCmdBlitImage");
    table->CmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)gpa(dev, "vkCmdClearDepthStencilImage");
    table->CmdClearAttachments = (PFN_vkCmdClearAttachments)gpa(dev, "vkCmdClearAttachments");
    table->CmdResolveImage = (PFN_vkCmdResolveImage)gpa(dev, "vkCmdResolveImage");
    table->CmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)gpa(dev, "vkCmdBeginRenderPass");
    table->CmdNextSubpass = (PFN_vkCmdNextSubpass)gpa(dev, "vkCmdNextSubpass");
    table->CmdEndRenderPass = (PFN_vkCmdEndRenderPass)gpa(dev, "vkCmdEndRenderPass");
    table->BindBufferMemory2 = (PFN_vkBindBufferMemory2)gpa(dev, "vkBindBufferMemory2");
    table->BindImageMemory2 = (PFN_vkBindImageMemory2)gpa(dev, "vkBindImageMemory2");
    table->GetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)gpa(dev, "vkGetDeviceGroupPeerMemoryFeatures");
    table->CmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)gpa(dev, "vkCmdSetDeviceMask");
    table->GetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)gpa(dev, "vkGetImageMemoryRequirements2");
    table->GetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)gpa(dev, "vkGetBufferMemoryRequirements2");
    table->GetDeviceQueue2 = (PFN_vkGetDeviceQueue2)gpa(dev, "vkGetDeviceQueue2");
    table->CmdDispatchBase = (PFN_vkCmdDispatchBase)gpa(dev, "vkCmdDispatchBase");
    table->GetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)gpa(dev, "vkGetDescriptorSetLayoutSupport");
    table->CreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)gpa(dev, "vkCreateSamplerYcbcrConversion");
    table->DestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)gpa(dev, "vkDestroySamplerYcbcrConversion");
    table->ResetQueryPool = (PFN_vkResetQueryPool)gpa(dev, "vkResetQueryPool");
    table->GetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)gpa(dev, "vkGetSemaphoreCounterValue");
    table->WaitSemaphores = (PFN_vkWaitSemaphores)gpa(dev, "vkWaitSemaphores");
    table->SignalSemaphore = (PFN_vkSignalSemaphore)gpa(dev, "vkSignalSemaphore");
    table->GetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)gpa(dev, "vkGetBufferDeviceAddress");
    table->GetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)gpa(dev, "vkGetBufferOpaqueCaptureAddress");
    table->GetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)gpa(dev, "vkGetDeviceMemoryOpaqueCaptureAddress");
    table->CmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)gpa(dev, "vkCmdDrawIndirectCount");
    table->CmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)gpa(dev, "vkCmdDrawIndexedIndirectCount");
    table->CreateRenderPass2 = (PFN_vkCreateRenderPass2)gpa(dev, "vkCreateRenderPass2");
    table->CmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)gpa(dev, "vkCmdBeginRenderPass2");
    table->CmdNextSubpass2 = (PFN_vkCmdNextSubpass2)gpa(dev, "vkCmdNextSubpass2");
    table->CmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)gpa(dev, "vkCmdEndRenderPass2");

    // ---- Core Vulkan 1.3 commands
    table->CreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)gpa(dev, "vkCreatePrivateDataSlot");
    table->DestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)gpa(dev, "vkDestroyPrivateDataSlot");
    table->SetPrivateData = (PFN_vkSetPrivateData)gpa(dev, "vkSetPrivateData");
    table->GetPrivateData = (PFN_vkGetPrivateData)gpa(dev, "vkGetPrivateData");
    table->CmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)gpa(dev, "vkCmdPipelineBarrier2");
    table->CmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)gpa(dev, "vkCmdWriteTimestamp2");
    table->QueueSubmit2 = (PFN_vkQueueSubmit2)gpa(dev, "vkQueueSubmit2");
    table->CmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)gpa(dev, "vkCmdCopyBuffer2");
    table->CmdCopyImage2 = (PFN_vkCmdCopyImage2)gpa(dev, "vkCmdCopyImage2");
    table->CmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)gpa(dev, "vkCmdCopyBufferToImage2");
    table->CmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)gpa(dev, "vkCmdCopyImageToBuffer2");
    table->GetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)gpa(dev, "vkGetDeviceBufferMemoryRequirements");
    table->GetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)gpa(dev, "vkGetDeviceImageMemoryRequirements");
    table->GetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)gpa(dev, "vkGetDeviceImageSparseMemoryRequirements");
    table->CmdSetEvent2 = (PFN_vkCmdSetEvent2)gpa(dev, "vkCmdSetEvent2");
    table->CmdResetEvent2 = (PFN_vkCmdResetEvent2)gpa(dev, "vkCmdResetEvent2");
    table->CmdWaitEvents2 = (PFN_vkCmdWaitEvents2)gpa(dev, "vkCmdWaitEvents2");
    table->CmdBlitImage2 = (PFN_vkCmdBlitImage2)gpa(dev, "vkCmdBlitImage2");
    table->CmdResolveImage2 = (PFN_vkCmdResolveImage2)gpa(dev, "vkCmdResolveImage2");
    table->CmdBeginRendering = (PFN_vkCmdBeginRendering)gpa(dev, "vkCmdBeginRendering");
    table->CmdEndRendering = (PFN_vkCmdEndRendering)gpa(dev, "vkCmdEndRendering");
    table->CmdSetCullMode = (PFN_vkCmdSetCullMode)gpa(dev, "vkCmdSetCullMode");
    table->CmdSetFrontFace = (PFN_vkCmdSetFrontFace)gpa(dev, "vkCmdSetFrontFace");
    table->CmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)gpa(dev, "vkCmdSetPrimitiveTopology");
    table->CmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)gpa(dev, "vkCmdSetViewportWithCount");
    table->CmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)gpa(dev, "vkCmdSetScissorWithCount");
    table->CmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)gpa(dev, "vkCmdBindVertexBuffers2");
    table->CmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)gpa(dev, "vkCmdSetDepthTestEnable");
    table->CmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)gpa(dev, "vkCmdSetDepthWriteEnable");
    table->CmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)gpa(dev, "vkCmdSetDepthCompareOp");
    table->CmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)gpa(dev, "vkCmdSetDepthBoundsTestEnable");
    table->CmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)gpa(dev, "vkCmdSetStencilTestEnable");
    table->CmdSetStencilOp = (PFN_vkCmdSetStencilOp)gpa(dev, "vkCmdSetStencilOp");
    table->CmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)gpa(dev, "vkCmdSetRasterizerDiscardEnable");
    table->CmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)gpa(dev, "vkCmdSetDepthBiasEnable");
    table->CmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)gpa(dev, "vkCmdSetPrimitiveRestartEnable");

    // ---- Core Vulkan 1.4 commands
    table->MapMemory2 = (PFN_vkMapMemory2)gpa(dev, "vkMapMemory2");
    table->UnmapMemory2 = (PFN_vkUnmapMemory2)gpa(dev, "vkUnmapMemory2");
    table->GetDeviceImageSubresourceLayout = (PFN_vkGetDeviceImageSubresourceLayout)gpa(dev, "vkGetDeviceImageSubresourceLayout");
    table->GetImageSubresourceLayout2 = (PFN_vkGetImageSubresourceLayout2)gpa(dev, "vkGetImageSubresourceLayout2");
    table->CopyMemoryToImage = (PFN_vkCopyMemoryToImage)gpa(dev, "vkCopyMemoryToImage");
    table->CopyImageToMemory = (PFN_vkCopyImageToMemory)gpa(dev, "vkCopyImageToMemory");
    table->CopyImageToImage = (PFN_vkCopyImageToImage)gpa(dev, "vkCopyImageToImage");
    table->TransitionImageLayout = (PFN_vkTransitionImageLayout)gpa(dev, "vkTransitionImageLayout");
    table->CmdPushDescriptorSet = (PFN_vkCmdPushDescriptorSet)gpa(dev, "vkCmdPushDescriptorSet");
    table->CmdBindDescriptorSets2 = (PFN_vkCmdBindDescriptorSets2)gpa(dev, "vkCmdBindDescriptorSets2");
    table->CmdPushConstants2 = (PFN_vkCmdPushConstants2)gpa(dev, "vkCmdPushConstants2");
    table->CmdPushDescriptorSet2 = (PFN_vkCmdPushDescriptorSet2)gpa(dev, "vkCmdPushDescriptorSet2");
    table->CmdSetLineStipple = (PFN_vkCmdSetLineStipple)gpa(dev, "vkCmdSetLineStipple");
    table->CmdBindIndexBuffer2 = (PFN_vkCmdBindIndexBuffer2)gpa(dev, "vkCmdBindIndexBuffer2");
    table->GetRenderingAreaGranularity = (PFN_vkGetRenderingAreaGranularity)gpa(dev, "vkGetRenderingAreaGranularity");
    table->CmdSetRenderingAttachmentLocations = (PFN_vkCmdSetRenderingAttachmentLocations)gpa(dev, "vkCmdSetRenderingAttachmentLocations");
    table->CmdSetRenderingInputAttachmentIndices = (PFN_vkCmdSetRenderingInputAttachmentIndices)gpa(dev, "vkCmdSetRenderingInputAttachmentIndices");

    // ---- Core Vulkan SC 1.0 commands
    table->GetCommandPoolMemoryConsumption = (PFN_vkGetCommandPoolMemoryConsumption)gpa(dev, "vkGetCommandPoolMemoryConsumption");
    table->GetFaultData = (PFN_vkGetFaultData)gpa(dev, "vkGetFaultData");
}

// Init Device function pointer dispatch table with extension commands
VKAPI_ATTR void VKAPI_CALL loader_init_device_extension_dispatch_table(struct loader_dev_dispatch_table *dev_table,
                                                                       PFN_vkGetInstanceProcAddr gipa,
                                                                       PFN_vkGetDeviceProcAddr gdpa,
                                                                       VkInstance inst,
                                                                       VkDevice dev) {
    VkLayerDispatchTable *table = &dev_table->core_dispatch;
    table->magic = DEVICE_DISP_TABLE_MAGIC_NUMBER;

    // ---- VK_KHR_swapchain extension commands
    table->CreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)gdpa(dev, "vkCreateSwapchainKHR");
    table->GetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)gdpa(dev, "vkGetSwapchainImagesKHR");
    table->AcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)gdpa(dev, "vkAcquireNextImageKHR");
    table->QueuePresentKHR = (PFN_vkQueuePresentKHR)gdpa(dev, "vkQueuePresentKHR");
    table->GetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR)gdpa(dev, "vkGetDeviceGroupPresentCapabilitiesKHR");
    table->GetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR)gdpa(dev, "vkGetDeviceGroupSurfacePresentModesKHR");
    table->AcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR)gdpa(dev, "vkAcquireNextImage2KHR");

    // ---- VK_KHR_display_swapchain extension commands
    table->CreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)gdpa(dev, "vkCreateSharedSwapchainsKHR");

    // ---- VK_KHR_external_memory_fd extension commands
    table->GetMemoryFdKHR = (PFN_vkGetMemoryFdKHR)gdpa(dev, "vkGetMemoryFdKHR");
    table->GetMemoryFdPropertiesKHR = (PFN_vkGetMemoryFdPropertiesKHR)gdpa(dev, "vkGetMemoryFdPropertiesKHR");

    // ---- VK_KHR_external_semaphore_fd extension commands
    table->ImportSemaphoreFdKHR = (PFN_vkImportSemaphoreFdKHR)gdpa(dev, "vkImportSemaphoreFdKHR");
    table->GetSemaphoreFdKHR = (PFN_vkGetSemaphoreFdKHR)gdpa(dev, "vkGetSemaphoreFdKHR");

    // ---- VK_KHR_shared_presentable_image extension commands
    table->GetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR)gdpa(dev, "vkGetSwapchainStatusKHR");

    // ---- VK_KHR_external_fence_fd extension commands
    table->ImportFenceFdKHR = (PFN_vkImportFenceFdKHR)gdpa(dev, "vkImportFenceFdKHR");
    table->GetFenceFdKHR = (PFN_vkGetFenceFdKHR)gdpa(dev, "vkGetFenceFdKHR");

    // ---- VK_KHR_performance_query extension commands
    table->AcquireProfilingLockKHR = (PFN_vkAcquireProfilingLockKHR)gdpa(dev, "vkAcquireProfilingLockKHR");
    table->ReleaseProfilingLockKHR = (PFN_vkReleaseProfilingLockKHR)gdpa(dev, "vkReleaseProfilingLockKHR");

    // ---- VK_KHR_fragment_shading_rate extension commands
    table->CmdSetFragmentShadingRateKHR = (PFN_vkCmdSetFragmentShadingRateKHR)gdpa(dev, "vkCmdSetFragmentShadingRateKHR");

    // ---- VK_KHR_object_refresh extension commands
    table->CmdRefreshObjectsKHR = (PFN_vkCmdRefreshObjectsKHR)gdpa(dev, "vkCmdRefreshObjectsKHR");

    // ---- VK_KHR_synchronization2 extension commands
    table->CmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR)gdpa(dev, "vkCmdSetEvent2KHR");
    table->CmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR)gdpa(dev, "vkCmdResetEvent2KHR");
    table->CmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR)gdpa(dev, "vkCmdWaitEvents2KHR");
    table->CmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)gdpa(dev, "vkCmdPipelineBarrier2KHR");
    table->CmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR)gdpa(dev, "vkCmdWriteTimestamp2KHR");
    table->QueueSubmit2KHR = (PFN_vkQueueSubmit2KHR)gdpa(dev, "vkQueueSubmit2KHR");

    // ---- VK_KHR_copy_commands2 extension commands
    table->CmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)gdpa(dev, "vkCmdCopyBuffer2KHR");
    table->CmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)gdpa(dev, "vkCmdCopyImage2KHR");
    table->CmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)gdpa(dev, "vkCmdCopyBufferToImage2KHR");
    table->CmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)gdpa(dev, "vkCmdCopyImageToBuffer2KHR");
    table->CmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)gdpa(dev, "vkCmdBlitImage2KHR");
    table->CmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)gdpa(dev, "vkCmdResolveImage2KHR");

    // ---- VK_KHR_line_rasterization extension commands
    table->CmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)gdpa(dev, "vkCmdSetLineStippleKHR");

    // ---- VK_KHR_calibrated_timestamps extension commands
    table->GetCalibratedTimestampsKHR = (PFN_vkGetCalibratedTimestampsKHR)gdpa(dev, "vkGetCalibratedTimestampsKHR");

    // ---- VK_EXT_display_control extension commands
    table->DisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT)gdpa(dev, "vkDisplayPowerControlEXT");
    table->RegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT)gdpa(dev, "vkRegisterDeviceEventEXT");
    table->RegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT)gdpa(dev, "vkRegisterDisplayEventEXT");
    table->GetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT)gdpa(dev, "vkGetSwapchainCounterEXT");

    // ---- VK_EXT_discard_rectangles extension commands
    table->CmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT)gdpa(dev, "vkCmdSetDiscardRectangleEXT");
    table->CmdSetDiscardRectangleEnableEXT = (PFN_vkCmdSetDiscardRectangleEnableEXT)gdpa(dev, "vkCmdSetDiscardRectangleEnableEXT");
    table->CmdSetDiscardRectangleModeEXT = (PFN_vkCmdSetDiscardRectangleModeEXT)gdpa(dev, "vkCmdSetDiscardRectangleModeEXT");

    // ---- VK_EXT_hdr_metadata extension commands
    table->SetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT)gdpa(dev, "vkSetHdrMetadataEXT");

    // ---- VK_EXT_debug_utils extension commands
    table->SetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)gipa(inst, "vkSetDebugUtilsObjectNameEXT");
    table->SetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT)gipa(inst, "vkSetDebugUtilsObjectTagEXT");
    table->QueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)gipa(inst, "vkQueueBeginDebugUtilsLabelEXT");
    table->QueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)gipa(inst, "vkQueueEndDebugUtilsLabelEXT");
    table->QueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)gipa(inst, "vkQueueInsertDebugUtilsLabelEXT");
    table->CmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)gipa(inst, "vkCmdBeginDebugUtilsLabelEXT");
    table->CmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)gipa(inst, "vkCmdEndDebugUtilsLabelEXT");
    table->CmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)gipa(inst, "vkCmdInsertDebugUtilsLabelEXT");

    // ---- VK_EXT_sample_locations extension commands
    table->CmdSetSampleLocationsEXT = (PFN_vkCmdSetSampleLocationsEXT)gdpa(dev, "vkCmdSetSampleLocationsEXT");

    // ---- VK_EXT_image_drm_format_modifier extension commands
    table->GetImageDrmFormatModifierPropertiesEXT = (PFN_vkGetImageDrmFormatModifierPropertiesEXT)gdpa(dev, "vkGetImageDrmFormatModifierPropertiesEXT");

    // ---- VK_EXT_external_memory_host extension commands
    table->GetMemoryHostPointerPropertiesEXT = (PFN_vkGetMemoryHostPointerPropertiesEXT)gdpa(dev, "vkGetMemoryHostPointerPropertiesEXT");

    // ---- VK_EXT_line_rasterization extension commands
    table->CmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)gdpa(dev, "vkCmdSetLineStippleEXT");

    // ---- VK_EXT_extended_dynamic_state extension commands
    table->CmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT)gdpa(dev, "vkCmdSetCullModeEXT");
    table->CmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT)gdpa(dev, "vkCmdSetFrontFaceEXT");
    table->CmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT)gdpa(dev, "vkCmdSetPrimitiveTopologyEXT");
    table->CmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT)gdpa(dev, "vkCmdSetViewportWithCountEXT");
    table->CmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT)gdpa(dev, "vkCmdSetScissorWithCountEXT");
    table->CmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT)gdpa(dev, "vkCmdBindVertexBuffers2EXT");
    table->CmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT)gdpa(dev, "vkCmdSetDepthTestEnableEXT");
    table->CmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT)gdpa(dev, "vkCmdSetDepthWriteEnableEXT");
    table->CmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT)gdpa(dev, "vkCmdSetDepthCompareOpEXT");
    table->CmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT)gdpa(dev, "vkCmdSetDepthBoundsTestEnableEXT");
    table->CmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT)gdpa(dev, "vkCmdSetStencilTestEnableEXT");
    table->CmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT)gdpa(dev, "vkCmdSetStencilOpEXT");

    // ---- VK_EXT_vertex_input_dynamic_state extension commands
    table->CmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT)gdpa(dev, "vkCmdSetVertexInputEXT");

    // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
    table->GetFenceSciSyncFenceNV = (PFN_vkGetFenceSciSyncFenceNV)gdpa(dev, "vkGetFenceSciSyncFenceNV");
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->GetFenceSciSyncObjNV = (PFN_vkGetFenceSciSyncObjNV)gdpa(dev, "vkGetFenceSciSyncObjNV");
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->ImportFenceSciSyncFenceNV = (PFN_vkImportFenceSciSyncFenceNV)gdpa(dev, "vkImportFenceSciSyncFenceNV");
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->ImportFenceSciSyncObjNV = (PFN_vkImportFenceSciSyncObjNV)gdpa(dev, "vkImportFenceSciSyncObjNV");
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->GetSemaphoreSciSyncObjNV = (PFN_vkGetSemaphoreSciSyncObjNV)gdpa(dev, "vkGetSemaphoreSciSyncObjNV");
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->ImportSemaphoreSciSyncObjNV = (PFN_vkImportSemaphoreSciSyncObjNV)gdpa(dev, "vkImportSemaphoreSciSyncObjNV");
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
    table->GetMemorySciBufNV = (PFN_vkGetMemorySciBufNV)gdpa(dev, "vkGetMemorySciBufNV");
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_EXT_extended_dynamic_state2 extension commands
    table->CmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT)gdpa(dev, "vkCmdSetPatchControlPointsEXT");
    table->CmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT)gdpa(dev, "vkCmdSetRasterizerDiscardEnableEXT");
    table->CmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT)gdpa(dev, "vkCmdSetDepthBiasEnableEXT");
    table->CmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT)gdpa(dev, "vkCmdSetLogicOpEXT");
    table->CmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT)gdpa(dev, "vkCmdSetPrimitiveRestartEnableEXT");

    // ---- VK_EXT_color_write_enable extension commands
    table->CmdSetColorWriteEnableEXT = (PFN_vkCmdSetColorWriteEnableEXT)gdpa(dev, "vkCmdSetColorWriteEnableEXT");

    // ---- VK_NV_external_sci_sync2 extension commands
#if defined(VK_USE_PLATFORM_SCI)
    table->CreateSemaphoreSciSyncPoolNV = (PFN_vkCreateSemaphoreSciSyncPoolNV)gdpa(dev, "vkCreateSemaphoreSciSyncPoolNV");
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_QNX_external_memory_screen_buffer extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    table->GetScreenBufferPropertiesQNX = (PFN_vkGetScreenBufferPropertiesQNX)gdpa(dev, "vkGetScreenBufferPropertiesQNX");
#endif // VK_USE_PLATFORM_SCREEN_QNX
}

// Init Instance function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_instance_core_dispatch_table(VkLayerInstanceDispatchTable *table, PFN_vkGetInstanceProcAddr gpa,
                                                                    VkInstance inst) {

    // ---- Core Vulkan SC 1.0 commands
    table->DestroyInstance = (PFN_vkDestroyInstance)gpa(inst, "vkDestroyInstance");
    table->EnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)gpa(inst, "vkEnumeratePhysicalDevices");
    table->GetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)gpa(inst, "vkGetPhysicalDeviceFeatures");
    table->GetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)gpa(inst, "vkGetPhysicalDeviceFormatProperties");
    table->GetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties)gpa(inst, "vkGetPhysicalDeviceImageFormatProperties");
    table->GetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)gpa(inst, "vkGetPhysicalDeviceProperties");
    table->GetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)gpa(inst, "vkGetPhysicalDeviceQueueFamilyProperties");
    table->GetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)gpa(inst, "vkGetPhysicalDeviceMemoryProperties");
    table->GetInstanceProcAddr = gpa;
    table->EnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)gpa(inst, "vkEnumerateDeviceExtensionProperties");
    table->EnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)gpa(inst, "vkEnumerateDeviceLayerProperties");
    table->EnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)gpa(inst, "vkEnumeratePhysicalDeviceGroups");
    table->GetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)gpa(inst, "vkGetPhysicalDeviceFeatures2");
    table->GetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)gpa(inst, "vkGetPhysicalDeviceProperties2");
    table->GetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2)gpa(inst, "vkGetPhysicalDeviceFormatProperties2");
    table->GetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2)gpa(inst, "vkGetPhysicalDeviceImageFormatProperties2");
    table->GetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)gpa(inst, "vkGetPhysicalDeviceQueueFamilyProperties2");
    table->GetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2)gpa(inst, "vkGetPhysicalDeviceMemoryProperties2");
    table->GetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties)gpa(inst, "vkGetPhysicalDeviceExternalBufferProperties");
    table->GetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties)gpa(inst, "vkGetPhysicalDeviceExternalFenceProperties");
    table->GetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)gpa(inst, "vkGetPhysicalDeviceExternalSemaphoreProperties");

    // ---- Core Vulkan 1.3 commands
    table->GetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)gpa(inst, "vkGetPhysicalDeviceToolProperties");
}

// Init Instance function pointer dispatch table with core commands
VKAPI_ATTR void VKAPI_CALL loader_init_instance_extension_dispatch_table(VkLayerInstanceDispatchTable *table, PFN_vkGetInstanceProcAddr gpa,
                                                                        VkInstance inst) {

    // ---- VK_KHR_surface extension commands
    table->DestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)gpa(inst, "vkDestroySurfaceKHR");
    table->GetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)gpa(inst, "vkGetPhysicalDeviceSurfaceSupportKHR");
    table->GetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)gpa(inst, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    table->GetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)gpa(inst, "vkGetPhysicalDeviceSurfaceFormatsKHR");
    table->GetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)gpa(inst, "vkGetPhysicalDeviceSurfacePresentModesKHR");

    // ---- VK_KHR_swapchain extension commands
    table->GetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR)gpa(inst, "vkGetPhysicalDevicePresentRectanglesKHR");

    // ---- VK_KHR_display extension commands
    table->GetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR)gpa(inst, "vkGetPhysicalDeviceDisplayPropertiesKHR");
    table->GetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR)gpa(inst, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
    table->GetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR)gpa(inst, "vkGetDisplayPlaneSupportedDisplaysKHR");
    table->GetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR)gpa(inst, "vkGetDisplayModePropertiesKHR");
    table->CreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR)gpa(inst, "vkCreateDisplayModeKHR");
    table->GetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR)gpa(inst, "vkGetDisplayPlaneCapabilitiesKHR");
    table->CreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR)gpa(inst, "vkCreateDisplayPlaneSurfaceKHR");

    // ---- VK_KHR_performance_query extension commands
    table->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR)gpa(inst, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
    table->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = (PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR)gpa(inst, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    table->GetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR)gpa(inst, "vkGetPhysicalDeviceSurfaceCapabilities2KHR");
    table->GetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR)gpa(inst, "vkGetPhysicalDeviceSurfaceFormats2KHR");

    // ---- VK_KHR_get_display_properties2 extension commands
    table->GetPhysicalDeviceDisplayProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayProperties2KHR)gpa(inst, "vkGetPhysicalDeviceDisplayProperties2KHR");
    table->GetPhysicalDeviceDisplayPlaneProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR)gpa(inst, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR");
    table->GetDisplayModeProperties2KHR = (PFN_vkGetDisplayModeProperties2KHR)gpa(inst, "vkGetDisplayModeProperties2KHR");
    table->GetDisplayPlaneCapabilities2KHR = (PFN_vkGetDisplayPlaneCapabilities2KHR)gpa(inst, "vkGetDisplayPlaneCapabilities2KHR");

    // ---- VK_KHR_fragment_shading_rate extension commands
    table->GetPhysicalDeviceFragmentShadingRatesKHR = (PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR)gpa(inst, "vkGetPhysicalDeviceFragmentShadingRatesKHR");

    // ---- VK_KHR_object_refresh extension commands
    table->GetPhysicalDeviceRefreshableObjectTypesKHR = (PFN_vkGetPhysicalDeviceRefreshableObjectTypesKHR)gpa(inst, "vkGetPhysicalDeviceRefreshableObjectTypesKHR");

    // ---- VK_KHR_calibrated_timestamps extension commands
    table->GetPhysicalDeviceCalibrateableTimeDomainsKHR = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR)gpa(inst, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");

    // ---- VK_EXT_direct_mode_display extension commands
    table->ReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT)gpa(inst, "vkReleaseDisplayEXT");

    // ---- VK_EXT_display_surface_counter extension commands
    table->GetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT)gpa(inst, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");

    // ---- VK_EXT_debug_utils extension commands
    table->CreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)gpa(inst, "vkCreateDebugUtilsMessengerEXT");
    table->DestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)gpa(inst, "vkDestroyDebugUtilsMessengerEXT");
    table->SubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT)gpa(inst, "vkSubmitDebugUtilsMessageEXT");

    // ---- VK_EXT_sample_locations extension commands
    table->GetPhysicalDeviceMultisamplePropertiesEXT = (PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT)gpa(inst, "vkGetPhysicalDeviceMultisamplePropertiesEXT");

    // ---- VK_EXT_headless_surface extension commands
    table->CreateHeadlessSurfaceEXT = (PFN_vkCreateHeadlessSurfaceEXT)gpa(inst, "vkCreateHeadlessSurfaceEXT");

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->AcquireWinrtDisplayNV = (PFN_vkAcquireWinrtDisplayNV)gpa(inst, "vkAcquireWinrtDisplayNV");
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetWinrtDisplayNV = (PFN_vkGetWinrtDisplayNV)gpa(inst, "vkGetWinrtDisplayNV");
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
    table->GetPhysicalDeviceSciSyncAttributesNV = (PFN_vkGetPhysicalDeviceSciSyncAttributesNV)gpa(inst, "vkGetPhysicalDeviceSciSyncAttributesNV");
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
    table->GetPhysicalDeviceExternalMemorySciBufPropertiesNV = (PFN_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV)gpa(inst, "vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV");
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->GetPhysicalDeviceSciBufAttributesNV = (PFN_vkGetPhysicalDeviceSciBufAttributesNV)gpa(inst, "vkGetPhysicalDeviceSciBufAttributesNV");
#endif // VK_USE_PLATFORM_SCI
}

// Functions that required a terminator need to have a separate dispatch table which contains their corresponding
// device function. This is used in the terminators themselves.
void init_extension_device_proc_terminator_dispatch(struct loader_device *dev) {
    struct loader_device_terminator_dispatch* dispatch = &dev->loader_dispatch.extension_terminator_dispatch;
    PFN_vkGetDeviceProcAddr gpda = (PFN_vkGetDeviceProcAddr)dev->phys_dev_term->this_icd_term->dispatch.GetDeviceProcAddr;

    // ---- VK_KHR_swapchain extension commands
    if (dev->driver_extensions.khr_swapchain_enabled)
       dispatch->CreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)gpda(dev->icd_device, "vkCreateSwapchainKHR");
    if (dev->driver_extensions.khr_swapchain_enabled)
       dispatch->GetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR)gpda(dev->icd_device, "vkGetDeviceGroupSurfacePresentModesKHR");

    // ---- VK_KHR_display_swapchain extension commands
    if (dev->driver_extensions.khr_display_swapchain_enabled)
       dispatch->CreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)gpda(dev->icd_device, "vkCreateSharedSwapchainsKHR");

    // ---- VK_EXT_debug_utils extension commands
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->SetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)gpda(dev->icd_device, "vkSetDebugUtilsObjectNameEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->SetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT)gpda(dev->icd_device, "vkSetDebugUtilsObjectTagEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->QueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)gpda(dev->icd_device, "vkQueueBeginDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->QueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)gpda(dev->icd_device, "vkQueueEndDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->QueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)gpda(dev->icd_device, "vkQueueInsertDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->CmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)gpda(dev->icd_device, "vkCmdBeginDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->CmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)gpda(dev->icd_device, "vkCmdEndDebugUtilsLabelEXT");
    if (dev->driver_extensions.ext_debug_utils_enabled)
       dispatch->CmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)gpda(dev->icd_device, "vkCmdInsertDebugUtilsLabelEXT");
}

// These are prototypes for functions that need their trampoline called in all circumstances.
// They are used in loader_lookup_device_dispatch_table but are defined afterwards.

    // ---- VK_EXT_debug_utils extension commands
VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectNameEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo);
VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectTagEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectTagInfoEXT*         pTagInfo);

// Device command lookup function
VKAPI_ATTR void* VKAPI_CALL loader_lookup_device_dispatch_table(const VkLayerDispatchTable *table, const char *name, bool* found_name) {
    if (!name || name[0] != 'v' || name[1] != 'k') {
        *found_name = false;
        return NULL;
    }

    name += 2;
    *found_name = true;
    struct loader_device* dev = (struct loader_device *)table;
    const struct loader_instance* inst = dev->phys_dev_term->this_icd_term->this_instance;
    uint32_t api_version = VK_MAKE_API_VERSION(0, inst->app_api_version.major, inst->app_api_version.minor, inst->app_api_version.patch);
    const uint32_t name_hash = loader_hash_string(name);

    switch (name_hash) {

        // ---- Core Vulkan SC 1.0 commands
        case 0x556f3e66u:
            if (!strcmp(name, "GetDeviceProcAddr")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetDeviceProcAddr;
            }
            break;
        case 0xc3c245f3u:
            if (!strcmp(name, "DestroyDevice")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyDevice;
            }
            break;
        case 0xe828e700u:
            if (!strcmp(name, "GetDeviceQueue")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetDeviceQueue;
            }
            break;
        case 0xf634aeb0u:
            if (!strcmp(name, "QueueSubmit")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->QueueSubmit;
            }
            break;
        case 0x30e5a4dfu:
            if (!strcmp(name, "QueueWaitIdle")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->QueueWaitIdle;
            }
            break;
        case 0x97ad82bcu:
            if (!strcmp(name, "DeviceWaitIdle")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DeviceWaitIdle;
            }
            break;
        case 0x1a48a22du:
            if (!strcmp(name, "AllocateMemory")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->AllocateMemory;
            }
            break;
        case 0x2b4a440au:
            if (!strcmp(name, "MapMemory")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->MapMemory;
            }
            break;
        case 0xdd78dd07u:
            if (!strcmp(name, "UnmapMemory")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->UnmapMemory;
            }
            break;
        case 0x04c06873u:
            if (!strcmp(name, "FlushMappedMemoryRanges")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->FlushMappedMemoryRanges;
            }
            break;
        case 0x42e40ec6u:
            if (!strcmp(name, "InvalidateMappedMemoryRanges")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->InvalidateMappedMemoryRanges;
            }
            break;
        case 0xb58c2237u:
            if (!strcmp(name, "GetDeviceMemoryCommitment")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetDeviceMemoryCommitment;
            }
            break;
        case 0xf9d3e8bbu:
            if (!strcmp(name, "BindBufferMemory")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->BindBufferMemory;
            }
            break;
        case 0xa6ad4e7cu:
            if (!strcmp(name, "BindImageMemory")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->BindImageMemory;
            }
            break;
        case 0xdbd8f14eu:
            if (!strcmp(name, "GetBufferMemoryRequirements")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetBufferMemoryRequirements;
            }
            break;
        case 0xadd404fbu:
            if (!strcmp(name, "GetImageMemoryRequirements")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetImageMemoryRequirements;
            }
            break;
        case 0xb85cb06eu:
            if (!strcmp(name, "CreateFence")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateFence;
            }
            break;
        case 0xee059b16u:
            if (!strcmp(name, "DestroyFence")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyFence;
            }
            break;
        case 0x49e2bbfeu:
            if (!strcmp(name, "ResetFences")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->ResetFences;
            }
            break;
        case 0x27219372u:
            if (!strcmp(name, "GetFenceStatus")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetFenceStatus;
            }
            break;
        case 0x2701d8c1u:
            if (!strcmp(name, "WaitForFences")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->WaitForFences;
            }
            break;
        case 0x72a17f35u:
            if (!strcmp(name, "CreateSemaphore")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateSemaphore;
            }
            break;
        case 0x7a900dbdu:
            if (!strcmp(name, "DestroySemaphore")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroySemaphore;
            }
            break;
        case 0x1d052b99u:
            if (!strcmp(name, "CreateQueryPool")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateQueryPool;
            }
            break;
        case 0x2acc2043u:
            if (!strcmp(name, "GetQueryPoolResults")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetQueryPoolResults;
            }
            break;
        case 0x594c57f3u:
            if (!strcmp(name, "CreateBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateBuffer;
            }
            break;
        case 0x74b0eb7bu:
            if (!strcmp(name, "DestroyBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyBuffer;
            }
            break;
        case 0x1052ae42u:
            if (!strcmp(name, "CreateImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateImage;
            }
            break;
        case 0xe4d58afau:
            if (!strcmp(name, "DestroyImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyImage;
            }
            break;
        case 0x5bec9c60u:
            if (!strcmp(name, "GetImageSubresourceLayout")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetImageSubresourceLayout;
            }
            break;
        case 0x98d3880bu:
            if (!strcmp(name, "CreateImageView")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateImageView;
            }
            break;
        case 0x3ac8cdd3u:
            if (!strcmp(name, "DestroyImageView")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyImageView;
            }
            break;
        case 0x5b4c1778u:
            if (!strcmp(name, "CreateCommandPool")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateCommandPool;
            }
            break;
        case 0xd1984e7fu:
            if (!strcmp(name, "ResetCommandPool")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->ResetCommandPool;
            }
            break;
        case 0x46e1a59eu:
            if (!strcmp(name, "AllocateCommandBuffers")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->AllocateCommandBuffers;
            }
            break;
        case 0x92a01f53u:
            if (!strcmp(name, "FreeCommandBuffers")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->FreeCommandBuffers;
            }
            break;
        case 0xd6878265u:
            if (!strcmp(name, "BeginCommandBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->BeginCommandBuffer;
            }
            break;
        case 0x00b4c891u:
            if (!strcmp(name, "EndCommandBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->EndCommandBuffer;
            }
            break;
        case 0xb4c6737fu:
            if (!strcmp(name, "ResetCommandBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->ResetCommandBuffer;
            }
            break;
        case 0x0c36d35cu:
            if (!strcmp(name, "CmdCopyBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdCopyBuffer;
            }
            break;
        case 0xc56ce137u:
            if (!strcmp(name, "CmdCopyImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdCopyImage;
            }
            break;
        case 0x37f8b1cau:
            if (!strcmp(name, "CmdCopyBufferToImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdCopyBufferToImage;
            }
            break;
        case 0xdd6c206cu:
            if (!strcmp(name, "CmdCopyImageToBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdCopyImageToBuffer;
            }
            break;
        case 0x004dd694u:
            if (!strcmp(name, "CmdUpdateBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdUpdateBuffer;
            }
            break;
        case 0x9c272074u:
            if (!strcmp(name, "CmdFillBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdFillBuffer;
            }
            break;
        case 0x99bb3b50u:
            if (!strcmp(name, "CmdPipelineBarrier")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdPipelineBarrier;
            }
            break;
        case 0x847b49f8u:
            if (!strcmp(name, "CmdBeginQuery")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdBeginQuery;
            }
            break;
        case 0xa38ee8bcu:
            if (!strcmp(name, "CmdEndQuery")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdEndQuery;
            }
            break;
        case 0x4cd9424cu:
            if (!strcmp(name, "CmdResetQueryPool")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdResetQueryPool;
            }
            break;
        case 0x36056986u:
            if (!strcmp(name, "CmdWriteTimestamp")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdWriteTimestamp;
            }
            break;
        case 0x03cfd77au:
            if (!strcmp(name, "CmdCopyQueryPoolResults")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdCopyQueryPoolResults;
            }
            break;
        case 0xfc3b9de4u:
            if (!strcmp(name, "CmdExecuteCommands")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdExecuteCommands;
            }
            break;
        case 0x45545f97u:
            if (!strcmp(name, "CreateEvent")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateEvent;
            }
            break;
        case 0x2fb5259fu:
            if (!strcmp(name, "DestroyEvent")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyEvent;
            }
            break;
        case 0x30fcfaffu:
            if (!strcmp(name, "GetEventStatus")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetEventStatus;
            }
            break;
        case 0x519d96f1u:
            if (!strcmp(name, "SetEvent")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->SetEvent;
            }
            break;
        case 0x068fe748u:
            if (!strcmp(name, "ResetEvent")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->ResetEvent;
            }
            break;
        case 0xe8d8b0f6u:
            if (!strcmp(name, "CreateBufferView")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateBufferView;
            }
            break;
        case 0x4ccdf76eu:
            if (!strcmp(name, "DestroyBufferView")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyBufferView;
            }
            break;
        case 0x192270cfu:
            if (!strcmp(name, "CreatePipelineCache")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreatePipelineCache;
            }
            break;
        case 0x902ac897u:
            if (!strcmp(name, "DestroyPipelineCache")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyPipelineCache;
            }
            break;
        case 0xd2393b0du:
            if (!strcmp(name, "CreateComputePipelines")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateComputePipelines;
            }
            break;
        case 0x3a781083u:
            if (!strcmp(name, "DestroyPipeline")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyPipeline;
            }
            break;
        case 0x386cb351u:
            if (!strcmp(name, "CreatePipelineLayout")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreatePipelineLayout;
            }
            break;
        case 0x24a65109u:
            if (!strcmp(name, "DestroyPipelineLayout")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyPipelineLayout;
            }
            break;
        case 0x22611e57u:
            if (!strcmp(name, "CreateSampler")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateSampler;
            }
            break;
        case 0x66efd24fu:
            if (!strcmp(name, "DestroySampler")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroySampler;
            }
            break;
        case 0x0c59900eu:
            if (!strcmp(name, "CreateDescriptorSetLayout")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateDescriptorSetLayout;
            }
            break;
        case 0xcdc1f4b6u:
            if (!strcmp(name, "DestroyDescriptorSetLayout")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyDescriptorSetLayout;
            }
            break;
        case 0xe154a866u:
            if (!strcmp(name, "CreateDescriptorPool")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateDescriptorPool;
            }
            break;
        case 0xbd10cdc7u:
            if (!strcmp(name, "ResetDescriptorPool")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->ResetDescriptorPool;
            }
            break;
        case 0x8783e9eau:
            if (!strcmp(name, "AllocateDescriptorSets")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->AllocateDescriptorSets;
            }
            break;
        case 0xf6ab6a4bu:
            if (!strcmp(name, "FreeDescriptorSets")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->FreeDescriptorSets;
            }
            break;
        case 0x796a4db0u:
            if (!strcmp(name, "UpdateDescriptorSets")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->UpdateDescriptorSets;
            }
            break;
        case 0x0fea12b2u:
            if (!strcmp(name, "CmdBindPipeline")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdBindPipeline;
            }
            break;
        case 0xbdecba10u:
            if (!strcmp(name, "CmdBindDescriptorSets")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdBindDescriptorSets;
            }
            break;
        case 0x68e97180u:
            if (!strcmp(name, "CmdClearColorImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdClearColorImage;
            }
            break;
        case 0x0b58a221u:
            if (!strcmp(name, "CmdDispatch")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDispatch;
            }
            break;
        case 0x023cf383u:
            if (!strcmp(name, "CmdDispatchIndirect")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDispatchIndirect;
            }
            break;
        case 0xe0c49af3u:
            if (!strcmp(name, "CmdSetEvent")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetEvent;
            }
            break;
        case 0xab60a1d6u:
            if (!strcmp(name, "CmdResetEvent")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdResetEvent;
            }
            break;
        case 0x41fbe8a7u:
            if (!strcmp(name, "CmdWaitEvents")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdWaitEvents;
            }
            break;
        case 0xef4f8998u:
            if (!strcmp(name, "CmdPushConstants")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdPushConstants;
            }
            break;
        case 0x49120077u:
            if (!strcmp(name, "CreateGraphicsPipelines")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateGraphicsPipelines;
            }
            break;
        case 0xee253c88u:
            if (!strcmp(name, "CreateFramebuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateFramebuffer;
            }
            break;
        case 0x4edbdb50u:
            if (!strcmp(name, "DestroyFramebuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyFramebuffer;
            }
            break;
        case 0xc3352a08u:
            if (!strcmp(name, "CreateRenderPass")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateRenderPass;
            }
            break;
        case 0xea8843a0u:
            if (!strcmp(name, "DestroyRenderPass")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroyRenderPass;
            }
            break;
        case 0xbd702976u:
            if (!strcmp(name, "GetRenderAreaGranularity")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetRenderAreaGranularity;
            }
            break;
        case 0x60223eafu:
            if (!strcmp(name, "CmdSetViewport")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetViewport;
            }
            break;
        case 0x06645d65u:
            if (!strcmp(name, "CmdSetScissor")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetScissor;
            }
            break;
        case 0x028ebdd5u:
            if (!strcmp(name, "CmdSetLineWidth")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetLineWidth;
            }
            break;
        case 0x84edaf93u:
            if (!strcmp(name, "CmdSetDepthBias")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetDepthBias;
            }
            break;
        case 0x12c65e99u:
            if (!strcmp(name, "CmdSetBlendConstants")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetBlendConstants;
            }
            break;
        case 0xa6c6ccffu:
            if (!strcmp(name, "CmdSetDepthBounds")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetDepthBounds;
            }
            break;
        case 0xed6fff6eu:
            if (!strcmp(name, "CmdSetStencilCompareMask")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetStencilCompareMask;
            }
            break;
        case 0x1b99fe4au:
            if (!strcmp(name, "CmdSetStencilWriteMask")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetStencilWriteMask;
            }
            break;
        case 0x43a8794cu:
            if (!strcmp(name, "CmdSetStencilReference")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetStencilReference;
            }
            break;
        case 0x6113c7aau:
            if (!strcmp(name, "CmdBindIndexBuffer")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdBindIndexBuffer;
            }
            break;
        case 0x8480280du:
            if (!strcmp(name, "CmdBindVertexBuffers")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdBindVertexBuffers;
            }
            break;
        case 0x8c1fc0d9u:
            if (!strcmp(name, "CmdDraw")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDraw;
            }
            break;
        case 0xb1da916eu:
            if (!strcmp(name, "CmdDrawIndexed")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDrawIndexed;
            }
            break;
        case 0x44bd488bu:
            if (!strcmp(name, "CmdDrawIndirect")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDrawIndirect;
            }
            break;
        case 0xf026b8a0u:
            if (!strcmp(name, "CmdDrawIndexedIndirect")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDrawIndexedIndirect;
            }
            break;
        case 0x203c55edu:
            if (!strcmp(name, "CmdBlitImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdBlitImage;
            }
            break;
        case 0x0a1abe14u:
            if (!strcmp(name, "CmdClearDepthStencilImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdClearDepthStencilImage;
            }
            break;
        case 0xf8912576u:
            if (!strcmp(name, "CmdClearAttachments")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdClearAttachments;
            }
            break;
        case 0x7d6ce9fau:
            if (!strcmp(name, "CmdResolveImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdResolveImage;
            }
            break;
        case 0x97aa36c5u:
            if (!strcmp(name, "CmdBeginRenderPass")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdBeginRenderPass;
            }
            break;
        case 0x65711319u:
            if (!strcmp(name, "CmdNextSubpass")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdNextSubpass;
            }
            break;
        case 0x21535791u:
            if (!strcmp(name, "CmdEndRenderPass")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdEndRenderPass;
            }
            break;
        case 0xd1970fabu:
            if (!strcmp(name, "BindBufferMemory2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->BindBufferMemory2;
            }
            break;
        case 0xb0d244cau:
            if (!strcmp(name, "BindImageMemory2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->BindImageMemory2;
            }
            break;
        case 0x76cc3b34u:
            if (!strcmp(name, "GetDeviceGroupPeerMemoryFeatures")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetDeviceGroupPeerMemoryFeatures;
            }
            break;
        case 0x7ce530b3u:
            if (!strcmp(name, "CmdSetDeviceMask")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdSetDeviceMask;
            }
            break;
        case 0x6dc3886bu:
            if (!strcmp(name, "GetImageMemoryRequirements2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetImageMemoryRequirements2;
            }
            break;
        case 0x92842634u:
            if (!strcmp(name, "GetBufferMemoryRequirements2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetBufferMemoryRequirements2;
            }
            break;
        case 0xaa63f3b6u:
            if (!strcmp(name, "GetDeviceQueue2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetDeviceQueue2;
            }
            break;
        case 0xc39e3e2cu:
            if (!strcmp(name, "CmdDispatchBase")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDispatchBase;
            }
            break;
        case 0x74e1f8cfu:
            if (!strcmp(name, "GetDescriptorSetLayoutSupport")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetDescriptorSetLayoutSupport;
            }
            break;
        case 0x452314aeu:
            if (!strcmp(name, "CreateSamplerYcbcrConversion")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateSamplerYcbcrConversion;
            }
            break;
        case 0xa5a844d6u:
            if (!strcmp(name, "DestroySamplerYcbcrConversion")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->DestroySamplerYcbcrConversion;
            }
            break;
        case 0xb0cc2abau:
            if (!strcmp(name, "ResetQueryPool")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->ResetQueryPool;
            }
            break;
        case 0x5a94735eu:
            if (!strcmp(name, "GetSemaphoreCounterValue")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetSemaphoreCounterValue;
            }
            break;
        case 0xec14fdebu:
            if (!strcmp(name, "WaitSemaphores")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->WaitSemaphores;
            }
            break;
        case 0x53897c39u:
            if (!strcmp(name, "SignalSemaphore")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->SignalSemaphore;
            }
            break;
        case 0x58b83869u:
            if (!strcmp(name, "GetBufferDeviceAddress")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetBufferDeviceAddress;
            }
            break;
        case 0x7878eaa4u:
            if (!strcmp(name, "GetBufferOpaqueCaptureAddress")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetBufferOpaqueCaptureAddress;
            }
            break;
        case 0x9a0eb25fu:
            if (!strcmp(name, "GetDeviceMemoryOpaqueCaptureAddress")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetDeviceMemoryOpaqueCaptureAddress;
            }
            break;
        case 0xe62a3a1au:
            if (!strcmp(name, "CmdDrawIndirectCount")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDrawIndirectCount;
            }
            break;
        case 0xf9fd358fu:
            if (!strcmp(name, "CmdDrawIndexedIndirectCount")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdDrawIndexedIndirectCount;
            }
            break;
        case 0x86b1794eu:
            if (!strcmp(name, "CreateRenderPass2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CreateRenderPass2;
            }
            break;
        case 0xb7f486d5u:
            if (!strcmp(name, "CmdBeginRenderPass2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdBeginRenderPass2;
            }
            break;
        case 0xdc012cb1u:
            if (!strcmp(name, "CmdNextSubpass2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdNextSubpass2;
            }
            break;
        case 0x1932f599u:
            if (!strcmp(name, "CmdEndRenderPass2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->CmdEndRenderPass2;
            }
            break;

        // ---- Core Vulkan 1.3 commands
        case 0x177d5920u:
            if (!strcmp(name, "CreatePrivateDataSlot")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CreatePrivateDataSlot;
            }
            break;
        case 0x7f21ff68u:
            if (!strcmp(name, "DestroyPrivateDataSlot")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->DestroyPrivateDataSlot;
            }
            break;
        case 0xe7f3b50eu:
            if (!strcmp(name, "SetPrivateData")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->SetPrivateData;
            }
            break;
        case 0xe2ac6662u:
            if (!strcmp(name, "GetPrivateData")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->GetPrivateData;
            }
            break;
        case 0x63be7b46u:
            if (!strcmp(name, "CmdPipelineBarrier2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdPipelineBarrier2;
            }
            break;
        case 0xbe85665cu:
            if (!strcmp(name, "CmdWriteTimestamp2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdWriteTimestamp2;
            }
            break;
        case 0x16eeb6a6u:
            if (!strcmp(name, "QueueSubmit2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->QueueSubmit2;
            }
            break;
        case 0xa84ed62au:
            if (!strcmp(name, "CmdCopyBuffer2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdCopyBuffer2;
            }
            break;
        case 0xcf663adfu:
            if (!strcmp(name, "CmdCopyImage2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdCopyImage2;
            }
            break;
        case 0x14802968u:
            if (!strcmp(name, "CmdCopyBufferToImage2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdCopyBufferToImage2;
            }
            break;
        case 0xef36f3fau:
            if (!strcmp(name, "CmdCopyImageToBuffer2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdCopyImageToBuffer2;
            }
            break;
        case 0xb708741cu:
            if (!strcmp(name, "GetDeviceBufferMemoryRequirements")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->GetDeviceBufferMemoryRequirements;
            }
            break;
        case 0xca328b99u:
            if (!strcmp(name, "GetDeviceImageMemoryRequirements")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->GetDeviceImageMemoryRequirements;
            }
            break;
        case 0x3fe21ac5u:
            if (!strcmp(name, "GetDeviceImageSparseMemoryRequirements")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->GetDeviceImageSparseMemoryRequirements;
            }
            break;
        case 0x967f9dd3u:
            if (!strcmp(name, "CmdSetEvent2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetEvent2;
            }
            break;
        case 0xad1ed9ecu:
            if (!strcmp(name, "CmdResetEvent2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdResetEvent2;
            }
            break;
        case 0x748f228fu:
            if (!strcmp(name, "CmdWaitEvents2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdWaitEvents2;
            }
            break;
        case 0x9dfb2e0du:
            if (!strcmp(name, "CmdBlitImage2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdBlitImage2;
            }
            break;
        case 0x3a7405d8u:
            if (!strcmp(name, "CmdResolveImage2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdResolveImage2;
            }
            break;
        case 0xaa8fee8cu:
            if (!strcmp(name, "CmdBeginRendering")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdBeginRendering;
            }
            break;
        case 0xee0f67d0u:
            if (!strcmp(name, "CmdEndRendering")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdEndRendering;
            }
            break;
        case 0x20a446deu:
            if (!strcmp(name, "CmdSetCullMode")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetCullMode;
            }
            break;
        case 0x414443d5u:
            if (!strcmp(name, "CmdSetFrontFace")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetFrontFace;
            }
            break;
        case 0x1a103db7u:
            if (!strcmp(name, "CmdSetPrimitiveTopology")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetPrimitiveTopology;
            }
            break;
        case 0xcba6442eu:
            if (!strcmp(name, "CmdSetViewportWithCount")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetViewportWithCount;
            }
            break;
        case 0x9d1ae5f0u:
            if (!strcmp(name, "CmdSetScissorWithCount")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetScissorWithCount;
            }
            break;
        case 0xd4bf5b2du:
            if (!strcmp(name, "CmdBindVertexBuffers2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdBindVertexBuffers2;
            }
            break;
        case 0xfdeb3f45u:
            if (!strcmp(name, "CmdSetDepthTestEnable")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetDepthTestEnable;
            }
            break;
        case 0xeedd9e22u:
            if (!strcmp(name, "CmdSetDepthWriteEnable")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetDepthWriteEnable;
            }
            break;
        case 0x56561e4au:
            if (!strcmp(name, "CmdSetDepthCompareOp")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetDepthCompareOp;
            }
            break;
        case 0x7948f434u:
            if (!strcmp(name, "CmdSetDepthBoundsTestEnable")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetDepthBoundsTestEnable;
            }
            break;
        case 0xad756094u:
            if (!strcmp(name, "CmdSetStencilTestEnable")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetStencilTestEnable;
            }
            break;
        case 0x1d9ffdc0u:
            if (!strcmp(name, "CmdSetStencilOp")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetStencilOp;
            }
            break;
        case 0xc64b8095u:
            if (!strcmp(name, "CmdSetRasterizerDiscardEnable")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetRasterizerDiscardEnable;
            }
            break;
        case 0x4e9b6cfcu:
            if (!strcmp(name, "CmdSetDepthBiasEnable")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetDepthBiasEnable;
            }
            break;
        case 0xd45e7f8eu:
            if (!strcmp(name, "CmdSetPrimitiveRestartEnable")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_3) return NULL;
                return (void *)table->CmdSetPrimitiveRestartEnable;
            }
            break;

        // ---- Core Vulkan 1.4 commands
        case 0x5de96428u:
            if (!strcmp(name, "MapMemory2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->MapMemory2;
            }
            break;
        case 0xda443a6fu:
            if (!strcmp(name, "UnmapMemory2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->UnmapMemory2;
            }
            break;
        case 0x31e492fau:
            if (!strcmp(name, "GetDeviceImageSubresourceLayout")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->GetDeviceImageSubresourceLayout;
            }
            break;
        case 0x077a1516u:
            if (!strcmp(name, "GetImageSubresourceLayout2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->GetImageSubresourceLayout2;
            }
            break;
        case 0xa305dfb7u:
            if (!strcmp(name, "CopyMemoryToImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CopyMemoryToImage;
            }
            break;
        case 0xc7c58193u:
            if (!strcmp(name, "CopyImageToMemory")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CopyImageToMemory;
            }
            break;
        case 0x07cb5f2du:
            if (!strcmp(name, "CopyImageToImage")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CopyImageToImage;
            }
            break;
        case 0x311876ddu:
            if (!strcmp(name, "TransitionImageLayout")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->TransitionImageLayout;
            }
            break;
        case 0xe6f62546u:
            if (!strcmp(name, "CmdPushDescriptorSet")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CmdPushDescriptorSet;
            }
            break;
        case 0x1da90386u:
            if (!strcmp(name, "CmdBindDescriptorSets2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CmdBindDescriptorSets2;
            }
            break;
        case 0x6435b69eu:
            if (!strcmp(name, "CmdPushConstants2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CmdPushConstants2;
            }
            break;
        case 0x097cf59cu:
            if (!strcmp(name, "CmdPushDescriptorSet2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CmdPushDescriptorSet2;
            }
            break;
        case 0x3e320cccu:
            if (!strcmp(name, "CmdSetLineStipple")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CmdSetLineStipple;
            }
            break;
        case 0x6a233448u:
            if (!strcmp(name, "CmdBindIndexBuffer2")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CmdBindIndexBuffer2;
            }
            break;
        case 0xe26f5990u:
            if (!strcmp(name, "GetRenderingAreaGranularity")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->GetRenderingAreaGranularity;
            }
            break;
        case 0xa1d575eeu:
            if (!strcmp(name, "CmdSetRenderingAttachmentLocations")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CmdSetRenderingAttachmentLocations;
            }
            break;
        case 0xf6408f2du:
            if (!strcmp(name, "CmdSetRenderingInputAttachmentIndices")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_4) return NULL;
                return (void *)table->CmdSetRenderingInputAttachmentIndices;
            }
            break;

        // ---- Core Vulkan SC 1.0 commands
        case 0xa69b8094u:
            if (!strcmp(name, "GetCommandPoolMemoryConsumption")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetCommandPoolMemoryConsumption;
            }
            break;
        case 0x217e8321u:
            if (!strcmp(name, "GetFaultData")) {
                if (dev->should_ignore_device_commands_from_newer_version && api_version < VKSC_API_VERSION_1_0) return NULL;
                return (void *)table->GetFaultData;
            }
            break;

        // ---- VK_KHR_swapchain extension commands
        case 0xe67ad416u:
            if (!strcmp(name, "CreateSwapchainKHR")) return (void *)table->CreateSwapchainKHR;
            break;
        case 0x1beb0af2u:
            if (!strcmp(name, "GetSwapchainImagesKHR")) return (void *)table->GetSwapchainImagesKHR;
            break;
        case 0x3cfee58au:
            if (!strcmp(name, "AcquireNextImageKHR")) return (void *)table->AcquireNextImageKHR;
            break;
        case 0xe1fb6286u:
            if (!strcmp(name, "QueuePresentKHR")) return (void *)table->QueuePresentKHR;
            break;
        case 0x50feefb4u:
            if (!strcmp(name, "GetDeviceGroupPresentCapabilitiesKHR")) return (void *)table->GetDeviceGroupPresentCapabilitiesKHR;
            break;
        case 0x75cc4ee9u:
            if (!strcmp(name, "GetDeviceGroupSurfacePresentModesKHR")) return (void *)table->GetDeviceGroupSurfacePresentModesKHR;
            break;
        case 0x89ecd932u:
            if (!strcmp(name, "AcquireNextImage2KHR")) return (void *)table->AcquireNextImage2KHR;
            break;

        // ---- VK_KHR_display_swapchain extension commands
        case 0x65d55da4u:
            if (!strcmp(name, "CreateSharedSwapchainsKHR")) return (void *)table->CreateSharedSwapchainsKHR;
            break;

        // ---- VK_KHR_external_memory_fd extension commands
        case 0xf40b9fe1u:
            if (!strcmp(name, "GetMemoryFdKHR")) return (void *)table->GetMemoryFdKHR;
            break;
        case 0x56495eaau:
            if (!strcmp(name, "GetMemoryFdPropertiesKHR")) return (void *)table->GetMemoryFdPropertiesKHR;
            break;

        // ---- VK_KHR_external_semaphore_fd extension commands
        case 0x63f7079fu:
            if (!strcmp(name, "ImportSemaphoreFdKHR")) return (void *)table->ImportSemaphoreFdKHR;
            break;
        case 0x68dc7f34u:
            if (!strcmp(name, "GetSemaphoreFdKHR")) return (void *)table->GetSemaphoreFdKHR;
            break;

        // ---- VK_KHR_shared_presentable_image extension commands
        case 0x7204d3eeu:
            if (!strcmp(name, "GetSwapchainStatusKHR")) return (void *)table->GetSwapchainStatusKHR;
            break;

        // ---- VK_KHR_external_fence_fd extension commands
        case 0x8cdebc12u:
            if (!strcmp(name, "ImportFenceFdKHR")) return (void *)table->ImportFenceFdKHR;
            break;
        case 0x5a3a2481u:
            if (!strcmp(name, "GetFenceFdKHR")) return (void *)table->GetFenceFdKHR;
            break;

        // ---- VK_KHR_performance_query extension commands
        case 0xf1c9f763u:
            if (!strcmp(name, "AcquireProfilingLockKHR")) return (void *)table->AcquireProfilingLockKHR;
            break;
        case 0xebe8785eu:
            if (!strcmp(name, "ReleaseProfilingLockKHR")) return (void *)table->ReleaseProfilingLockKHR;
            break;

        // ---- VK_KHR_fragment_shading_rate extension commands
        case 0x3fb07adeu:
            if (!strcmp(name, "CmdSetFragmentShadingRateKHR")) return (void *)table->CmdSetFragmentShadingRateKHR;
            break;

        // ---- VK_KHR_object_refresh extension commands
        case 0x00d754b9u:
            if (!strcmp(name, "CmdRefreshObjectsKHR")) return (void *)table->CmdRefreshObjectsKHR;
            break;

        // ---- VK_KHR_synchronization2 extension commands
        case 0x5a728716u:
            if (!strcmp(name, "CmdSetEvent2KHR")) return (void *)table->CmdSetEvent2KHR;
            break;
        case 0xa5b840dfu:
            if (!strcmp(name, "CmdResetEvent2KHR")) return (void *)table->CmdResetEvent2KHR;
            break;
        case 0x91e1837au:
            if (!strcmp(name, "CmdWaitEvents2KHR")) return (void *)table->CmdWaitEvents2KHR;
            break;
        case 0x1dfbddedu:
            if (!strcmp(name, "CmdPipelineBarrier2KHR")) return (void *)table->CmdPipelineBarrier2KHR;
            break;
        case 0xe0d31c8fu:
            if (!strcmp(name, "CmdWriteTimestamp2KHR")) return (void *)table->CmdWriteTimestamp2KHR;
            break;
        case 0x63783d0du:
            if (!strcmp(name, "QueueSubmit2KHR")) return (void *)table->QueueSubmit2KHR;
            break;

        // ---- VK_KHR_copy_commands2 extension commands
        case 0x8ad79009u:
            if (!strcmp(name, "CmdCopyBuffer2KHR")) return (void *)table->CmdCopyBuffer2KHR;
            break;
        case 0xb82dbd0au:
            if (!strcmp(name, "CmdCopyImage2KHR")) return (void *)table->CmdCopyImage2KHR;
            break;
        case 0xac4cc803u:
            if (!strcmp(name, "CmdCopyBufferToImage2KHR")) return (void *)table->CmdCopyBufferToImage2KHR;
            break;
        case 0xb3361a99u:
            if (!strcmp(name, "CmdCopyImageToBuffer2KHR")) return (void *)table->CmdCopyImageToBuffer2KHR;
            break;
        case 0x6f8868d4u:
            if (!strcmp(name, "CmdBlitImage2KHR")) return (void *)table->CmdBlitImage2KHR;
            break;
        case 0xd9427c73u:
            if (!strcmp(name, "CmdResolveImage2KHR")) return (void *)table->CmdResolveImage2KHR;
            break;

        // ---- VK_KHR_line_rasterization extension commands
        case 0x0968c67fu:
            if (!strcmp(name, "CmdSetLineStippleKHR")) return (void *)table->CmdSetLineStippleKHR;
            break;

        // ---- VK_KHR_calibrated_timestamps extension commands
        case 0x6b882920u:
            if (!strcmp(name, "GetCalibratedTimestampsKHR")) return (void *)table->GetCalibratedTimestampsKHR;
            break;

        // ---- VK_EXT_display_control extension commands
        case 0xcd3d83d6u:
            if (!strcmp(name, "DisplayPowerControlEXT")) return (void *)table->DisplayPowerControlEXT;
            break;
        case 0x89eb83c5u:
            if (!strcmp(name, "RegisterDeviceEventEXT")) return (void *)table->RegisterDeviceEventEXT;
            break;
        case 0x308cb801u:
            if (!strcmp(name, "RegisterDisplayEventEXT")) return (void *)table->RegisterDisplayEventEXT;
            break;
        case 0x422be39au:
            if (!strcmp(name, "GetSwapchainCounterEXT")) return (void *)table->GetSwapchainCounterEXT;
            break;

        // ---- VK_EXT_discard_rectangles extension commands
        case 0x494be225u:
            if (!strcmp(name, "CmdSetDiscardRectangleEXT")) return (void *)table->CmdSetDiscardRectangleEXT;
            break;
        case 0xde952114u:
            if (!strcmp(name, "CmdSetDiscardRectangleEnableEXT")) return (void *)table->CmdSetDiscardRectangleEnableEXT;
            break;
        case 0x0229a59cu:
            if (!strcmp(name, "CmdSetDiscardRectangleModeEXT")) return (void *)table->CmdSetDiscardRectangleModeEXT;
            break;

        // ---- VK_EXT_hdr_metadata extension commands
        case 0x4c4c9e61u:
            if (!strcmp(name, "SetHdrMetadataEXT")) return (void *)table->SetHdrMetadataEXT;
            break;

        // ---- VK_EXT_debug_utils extension commands
        case 0x773b4682u:
            if (!strcmp(name, "SetDebugUtilsObjectNameEXT")) return dev->layer_extensions.ext_debug_utils_enabled ? (void *)SetDebugUtilsObjectNameEXT : NULL;
            break;
        case 0x357569a7u:
            if (!strcmp(name, "SetDebugUtilsObjectTagEXT")) return dev->layer_extensions.ext_debug_utils_enabled ? (void *)SetDebugUtilsObjectTagEXT : NULL;
            break;
        case 0x17c2ff64u:
            if (!strcmp(name, "QueueBeginDebugUtilsLabelEXT")) return (void *)table->QueueBeginDebugUtilsLabelEXT;
            break;
        case 0xdf00ddb4u:
            if (!strcmp(name, "QueueEndDebugUtilsLabelEXT")) return (void *)table->QueueEndDebugUtilsLabelEXT;
            break;
        case 0x4e04da94u:
            if (!strcmp(name, "QueueInsertDebugUtilsLabelEXT")) return (void *)table->QueueInsertDebugUtilsLabelEXT;
            break;
        case 0xc0ad7af9u:
            if (!strcmp(name, "CmdBeginDebugUtilsLabelEXT")) return (void *)table->CmdBeginDebugUtilsLabelEXT;
            break;
        case 0x54548a95u:
            if (!strcmp(name, "CmdEndDebugUtilsLabelEXT")) return (void *)table->CmdEndDebugUtilsLabelEXT;
            break;
        case 0x08691667u:
            if (!strcmp(name, "CmdInsertDebugUtilsLabelEXT")) return (void *)table->CmdInsertDebugUtilsLabelEXT;
            break;

        // ---- VK_EXT_sample_locations extension commands
        case 0xd0bfab14u:
            if (!strcmp(name, "CmdSetSampleLocationsEXT")) return (void *)table->CmdSetSampleLocationsEXT;
            break;

        // ---- VK_EXT_image_drm_format_modifier extension commands
        case 0x0f35fea9u:
            if (!strcmp(name, "GetImageDrmFormatModifierPropertiesEXT")) return (void *)table->GetImageDrmFormatModifierPropertiesEXT;
            break;

        // ---- VK_EXT_external_memory_host extension commands
        case 0x969c0921u:
            if (!strcmp(name, "GetMemoryHostPointerPropertiesEXT")) return (void *)table->GetMemoryHostPointerPropertiesEXT;
            break;

        // ---- VK_EXT_line_rasterization extension commands
        case 0xad3668e7u:
            if (!strcmp(name, "CmdSetLineStippleEXT")) return (void *)table->CmdSetLineStippleEXT;
            break;

        // ---- VK_EXT_extended_dynamic_state extension commands
        case 0xab9b765du:
            if (!strcmp(name, "CmdSetCullModeEXT")) return (void *)table->CmdSetCullModeEXT;
            break;
        case 0xf2289404u:
            if (!strcmp(name, "CmdSetFrontFaceEXT")) return (void *)table->CmdSetFrontFaceEXT;
            break;
        case 0x64cba91au:
            if (!strcmp(name, "CmdSetPrimitiveTopologyEXT")) return (void *)table->CmdSetPrimitiveTopologyEXT;
            break;
        case 0xf0fcf30du:
            if (!strcmp(name, "CmdSetViewportWithCountEXT")) return (void *)table->CmdSetViewportWithCountEXT;
            break;
        case 0xe7925953u:
            if (!strcmp(name, "CmdSetScissorWithCountEXT")) return (void *)table->CmdSetScissorWithCountEXT;
            break;
        case 0xb4cd241cu:
            if (!strcmp(name, "CmdBindVertexBuffers2EXT")) return (void *)table->CmdBindVertexBuffers2EXT;
            break;
        case 0xdfd30d54u:
            if (!strcmp(name, "CmdSetDepthTestEnableEXT")) return (void *)table->CmdSetDepthTestEnableEXT;
            break;
        case 0x10132f69u:
            if (!strcmp(name, "CmdSetDepthWriteEnableEXT")) return (void *)table->CmdSetDepthWriteEnableEXT;
            break;
        case 0x421cb111u:
            if (!strcmp(name, "CmdSetDepthCompareOpEXT")) return (void *)table->CmdSetDepthCompareOpEXT;
            break;
        case 0x6a6d3a6fu:
            if (!strcmp(name, "CmdSetDepthBoundsTestEnableEXT")) return (void *)table->CmdSetDepthBoundsTestEnableEXT;
            break;
        case 0x62b54f0fu:
            if (!strcmp(name, "CmdSetStencilTestEnableEXT")) return (void *)table->CmdSetStencilTestEnableEXT;
            break;
        case 0xc2c7a883u:
            if (!strcmp(name, "CmdSetStencilOpEXT")) return (void *)table->CmdSetStencilOpEXT;
            break;

        // ---- VK_EXT_vertex_input_dynamic_state extension commands
        case 0x8005af30u:
            if (!strcmp(name, "CmdSetVertexInputEXT")) return (void *)table->CmdSetVertexInputEXT;
            break;

        // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
        case 0x48abd33bu:
            if (!strcmp(name, "GetFenceSciSyncFenceNV")) return (void *)table->GetFenceSciSyncFenceNV;
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0x00d4b6e7u:
            if (!strcmp(name, "GetFenceSciSyncObjNV")) return (void *)table->GetFenceSciSyncObjNV;
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0xc2a49162u:
            if (!strcmp(name, "ImportFenceSciSyncFenceNV")) return (void *)table->ImportFenceSciSyncFenceNV;
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0x0a315cb6u:
            if (!strcmp(name, "ImportFenceSciSyncObjNV")) return (void *)table->ImportFenceSciSyncObjNV;
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0xb5c53a50u:
            if (!strcmp(name, "GetSemaphoreSciSyncObjNV")) return (void *)table->GetSemaphoreSciSyncObjNV;
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0xe9c047d5u:
            if (!strcmp(name, "ImportSemaphoreSciSyncObjNV")) return (void *)table->ImportSemaphoreSciSyncObjNV;
            break;
#endif // VK_USE_PLATFORM_SCI

        // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
        case 0xa0ad2156u:
            if (!strcmp(name, "GetMemorySciBufNV")) return (void *)table->GetMemorySciBufNV;
            break;
#endif // VK_USE_PLATFORM_SCI

        // ---- VK_EXT_extended_dynamic_state2 extension commands
        case 0xe3cf69c8u:
            if (!strcmp(name, "CmdSetPatchControlPointsEXT")) return (void *)table->CmdSetPatchControlPointsEXT;
            break;
        case 0x015d47c4u:
            if (!strcmp(name, "CmdSetRasterizerDiscardEnableEXT")) return (void *)table->CmdSetRasterizerDiscardEnableEXT;
            break;
        case 0xd526ddf7u:
            if (!strcmp(name, "CmdSetDepthBiasEnableEXT")) return (void *)table->CmdSetDepthBiasEnableEXT;
            break;
        case 0xe76c2231u:
            if (!strcmp(name, "CmdSetLogicOpEXT")) return (void *)table->CmdSetLogicOpEXT;
            break;
        case 0x69f6e32du:
            if (!strcmp(name, "CmdSetPrimitiveRestartEnableEXT")) return (void *)table->CmdSetPrimitiveRestartEnableEXT;
            break;

        // ---- VK_EXT_color_write_enable extension commands
        case 0x88b42aefu:
            if (!strcmp(name, "CmdSetColorWriteEnableEXT")) return (void *)table->CmdSetColorWriteEnableEXT;
            break;

        // ---- VK_NV_external_sci_sync2 extension commands
#if defined(VK_USE_PLATFORM_SCI)
        case 0xb880962bu:
            if (!strcmp(name, "CreateSemaphoreSciSyncPoolNV")) return (void *)table->CreateSemaphoreSciSyncPoolNV;
            break;
#endif // VK_USE_PLATFORM_SCI

        // ---- VK_QNX_external_memory_screen_buffer extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
        case 0xb6bc3d65u:
            if (!strcmp(name, "GetScreenBufferPropertiesQNX")) return (void *)table->GetScreenBufferPropertiesQNX;
            break;
#endif // VK_USE_PLATFORM_SCREEN_QNX
        default:
            break;
    }

    *found_name = false;
    return NULL;
}

// Instance command lookup function
VKAPI_ATTR void* VKAPI_CALL loader_lookup_instance_dispatch_table(const VkLayerInstanceDispatchTable *table, const char *name,
                                                                 bool *found_name) {
    if (!name || name[0] != 'v' || name[1] != 'k') {
        *found_name = false;
        return NULL;
    }

    *found_name = true;
    name += 2;
    const uint32_t name_hash = loader_hash_string(name);
    switch (name_hash) {

        // ---- Core Vulkan SC 1.0 commands
        case 0x72bac092u:
            if (!strcmp(name, "DestroyInstance")) return (void *)table->DestroyInstance;
            break;
        case 0x47707f5bu:
            if (!strcmp(name, "EnumeratePhysicalDevices")) return (void *)table->EnumeratePhysicalDevices;
            break;
        case 0x1f85ee93u:
            if (!strcmp(name, "GetPhysicalDeviceFeatures")) return (void *)table->GetPhysicalDeviceFeatures;
            break;
        case 0x74a5d8deu:
            if (!strcmp(name, "GetPhysicalDeviceFormatProperties")) return (void *)table->GetPhysicalDeviceFormatProperties;
            break;
        case 0x8451aa6bu:
            if (!strcmp(name, "GetPhysicalDeviceImageFormatProperties")) return (void *)table->GetPhysicalDeviceImageFormatProperties;
            break;
        case 0x1de4f4b9u:
            if (!strcmp(name, "GetPhysicalDeviceProperties")) return (void *)table->GetPhysicalDeviceProperties;
            break;
        case 0x027f4f12u:
            if (!strcmp(name, "GetPhysicalDeviceQueueFamilyProperties")) return (void *)table->GetPhysicalDeviceQueueFamilyProperties;
            break;
        case 0x1c0f4f2eu:
            if (!strcmp(name, "GetPhysicalDeviceMemoryProperties")) return (void *)table->GetPhysicalDeviceMemoryProperties;
            break;
        case 0x2d3c8c27u:
            if (!strcmp(name, "GetInstanceProcAddr")) return (void *)table->GetInstanceProcAddr;
            break;
        case 0xd83dfc59u:
            if (!strcmp(name, "EnumerateDeviceExtensionProperties")) return (void *)table->EnumerateDeviceExtensionProperties;
            break;
        case 0x74122e01u:
            if (!strcmp(name, "EnumerateDeviceLayerProperties")) return (void *)table->EnumerateDeviceLayerProperties;
            break;
        case 0xf777380au:
            if (!strcmp(name, "EnumeratePhysicalDeviceGroups")) return (void *)table->EnumeratePhysicalDeviceGroups;
            break;
        case 0x40d6a773u:
            if (!strcmp(name, "GetPhysicalDeviceFeatures2")) return (void *)table->GetPhysicalDeviceFeatures2;
            break;
        case 0x9a6cf6d1u:
            if (!strcmp(name, "GetPhysicalDeviceProperties2")) return (void *)table->GetPhysicalDeviceProperties2;
            break;
        case 0x8d147b84u:
            if (!strcmp(name, "GetPhysicalDeviceFormatProperties2")) return (void *)table->GetPhysicalDeviceFormatProperties2;
            break;
        case 0xa58f2a1bu:
            if (!strcmp(name, "GetPhysicalDeviceImageFormatProperties2")) return (void *)table->GetPhysicalDeviceImageFormatProperties2;
            break;
        case 0x0e698f60u:
            if (!strcmp(name, "GetPhysicalDeviceQueueFamilyProperties2")) return (void *)table->GetPhysicalDeviceQueueFamilyProperties2;
            break;
        case 0x48198914u:
            if (!strcmp(name, "GetPhysicalDeviceMemoryProperties2")) return (void *)table->GetPhysicalDeviceMemoryProperties2;
            break;
        case 0x457cf6d0u:
            if (!strcmp(name, "GetPhysicalDeviceExternalBufferProperties")) return (void *)table->GetPhysicalDeviceExternalBufferProperties;
            break;
        case 0xae7670e9u:
            if (!strcmp(name, "GetPhysicalDeviceExternalFenceProperties")) return (void *)table->GetPhysicalDeviceExternalFenceProperties;
            break;
        case 0xc95e77dau:
            if (!strcmp(name, "GetPhysicalDeviceExternalSemaphoreProperties")) return (void *)table->GetPhysicalDeviceExternalSemaphoreProperties;
            break;

        // ---- Core Vulkan 1.3 commands
        case 0xbf928f7bu:
            if (!strcmp(name, "GetPhysicalDeviceToolProperties")) return (void *)table->GetPhysicalDeviceToolProperties;
            break;

        // ---- VK_KHR_surface extension commands
        case 0xa055626fu:
            if (!strcmp(name, "DestroySurfaceKHR")) return (void *)table->DestroySurfaceKHR;
            break;
        case 0xeddb22e9u:
            if (!strcmp(name, "GetPhysicalDeviceSurfaceSupportKHR")) return (void *)table->GetPhysicalDeviceSurfaceSupportKHR;
            break;
        case 0x35be348cu:
            if (!strcmp(name, "GetPhysicalDeviceSurfaceCapabilitiesKHR")) return (void *)table->GetPhysicalDeviceSurfaceCapabilitiesKHR;
            break;
        case 0xcbc23c60u:
            if (!strcmp(name, "GetPhysicalDeviceSurfaceFormatsKHR")) return (void *)table->GetPhysicalDeviceSurfaceFormatsKHR;
            break;
        case 0xc3bb5079u:
            if (!strcmp(name, "GetPhysicalDeviceSurfacePresentModesKHR")) return (void *)table->GetPhysicalDeviceSurfacePresentModesKHR;
            break;

        // ---- VK_KHR_swapchain extension commands
        case 0x7f1cbd5cu:
            if (!strcmp(name, "GetPhysicalDevicePresentRectanglesKHR")) return (void *)table->GetPhysicalDevicePresentRectanglesKHR;
            break;

        // ---- VK_KHR_display extension commands
        case 0x6ae00b02u:
            if (!strcmp(name, "GetPhysicalDeviceDisplayPropertiesKHR")) return (void *)table->GetPhysicalDeviceDisplayPropertiesKHR;
            break;
        case 0x74256fc0u:
            if (!strcmp(name, "GetPhysicalDeviceDisplayPlanePropertiesKHR")) return (void *)table->GetPhysicalDeviceDisplayPlanePropertiesKHR;
            break;
        case 0x069c6c3bu:
            if (!strcmp(name, "GetDisplayPlaneSupportedDisplaysKHR")) return (void *)table->GetDisplayPlaneSupportedDisplaysKHR;
            break;
        case 0x7fb98644u:
            if (!strcmp(name, "GetDisplayModePropertiesKHR")) return (void *)table->GetDisplayModePropertiesKHR;
            break;
        case 0x9565f3f9u:
            if (!strcmp(name, "CreateDisplayModeKHR")) return (void *)table->CreateDisplayModeKHR;
            break;
        case 0x1ff22654u:
            if (!strcmp(name, "GetDisplayPlaneCapabilitiesKHR")) return (void *)table->GetDisplayPlaneCapabilitiesKHR;
            break;
        case 0xdd4f3c17u:
            if (!strcmp(name, "CreateDisplayPlaneSurfaceKHR")) return (void *)table->CreateDisplayPlaneSurfaceKHR;
            break;

        // ---- VK_KHR_performance_query extension commands
        case 0xdd2c038du:
            if (!strcmp(name, "EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR")) return (void *)table->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
            break;
        case 0x204022a7u:
            if (!strcmp(name, "GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR")) return (void *)table->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
            break;

        // ---- VK_KHR_get_surface_capabilities2 extension commands
        case 0xfc0babdcu:
            if (!strcmp(name, "GetPhysicalDeviceSurfaceCapabilities2KHR")) return (void *)table->GetPhysicalDeviceSurfaceCapabilities2KHR;
            break;
        case 0xbeb71818u:
            if (!strcmp(name, "GetPhysicalDeviceSurfaceFormats2KHR")) return (void *)table->GetPhysicalDeviceSurfaceFormats2KHR;
            break;

        // ---- VK_KHR_get_display_properties2 extension commands
        case 0x6267683au:
            if (!strcmp(name, "GetPhysicalDeviceDisplayProperties2KHR")) return (void *)table->GetPhysicalDeviceDisplayProperties2KHR;
            break;
        case 0x2693ff78u:
            if (!strcmp(name, "GetPhysicalDeviceDisplayPlaneProperties2KHR")) return (void *)table->GetPhysicalDeviceDisplayPlaneProperties2KHR;
            break;
        case 0x91ff80e4u:
            if (!strcmp(name, "GetDisplayModeProperties2KHR")) return (void *)table->GetDisplayModeProperties2KHR;
            break;
        case 0x2769b7b4u:
            if (!strcmp(name, "GetDisplayPlaneCapabilities2KHR")) return (void *)table->GetDisplayPlaneCapabilities2KHR;
            break;

        // ---- VK_KHR_fragment_shading_rate extension commands
        case 0x5c375044u:
            if (!strcmp(name, "GetPhysicalDeviceFragmentShadingRatesKHR")) return (void *)table->GetPhysicalDeviceFragmentShadingRatesKHR;
            break;

        // ---- VK_KHR_object_refresh extension commands
        case 0x6fe481d0u:
            if (!strcmp(name, "GetPhysicalDeviceRefreshableObjectTypesKHR")) return (void *)table->GetPhysicalDeviceRefreshableObjectTypesKHR;
            break;

        // ---- VK_KHR_calibrated_timestamps extension commands
        case 0x5e5a476cu:
            if (!strcmp(name, "GetPhysicalDeviceCalibrateableTimeDomainsKHR")) return (void *)table->GetPhysicalDeviceCalibrateableTimeDomainsKHR;
            break;

        // ---- VK_EXT_direct_mode_display extension commands
        case 0x8981a5c7u:
            if (!strcmp(name, "ReleaseDisplayEXT")) return (void *)table->ReleaseDisplayEXT;
            break;

        // ---- VK_EXT_display_surface_counter extension commands
        case 0xd1bdfdd4u:
            if (!strcmp(name, "GetPhysicalDeviceSurfaceCapabilities2EXT")) return (void *)table->GetPhysicalDeviceSurfaceCapabilities2EXT;
            break;

        // ---- VK_EXT_debug_utils extension commands
        case 0xda987a67u:
            if (!strcmp(name, "CreateDebugUtilsMessengerEXT")) return (void *)table->CreateDebugUtilsMessengerEXT;
            break;
        case 0xc22d235fu:
            if (!strcmp(name, "DestroyDebugUtilsMessengerEXT")) return (void *)table->DestroyDebugUtilsMessengerEXT;
            break;
        case 0xa4e5a25fu:
            if (!strcmp(name, "SubmitDebugUtilsMessageEXT")) return (void *)table->SubmitDebugUtilsMessageEXT;
            break;

        // ---- VK_EXT_sample_locations extension commands
        case 0x91fd6da9u:
            if (!strcmp(name, "GetPhysicalDeviceMultisamplePropertiesEXT")) return (void *)table->GetPhysicalDeviceMultisamplePropertiesEXT;
            break;

        // ---- VK_EXT_headless_surface extension commands
        case 0xd35abb2cu:
            if (!strcmp(name, "CreateHeadlessSurfaceEXT")) return (void *)table->CreateHeadlessSurfaceEXT;
            break;

        // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        case 0xcef6a005u:
            if (!strcmp(name, "AcquireWinrtDisplayNV")) return (void *)table->AcquireWinrtDisplayNV;
            break;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        case 0xd5127861u:
            if (!strcmp(name, "GetWinrtDisplayNV")) return (void *)table->GetWinrtDisplayNV;
            break;
#endif // VK_USE_PLATFORM_WIN32_KHR

        // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
        case 0x3f042c9bu:
            if (!strcmp(name, "GetPhysicalDeviceSciSyncAttributesNV")) return (void *)table->GetPhysicalDeviceSciSyncAttributesNV;
            break;
#endif // VK_USE_PLATFORM_SCI

        // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
        case 0x2fda62dbu:
            if (!strcmp(name, "GetPhysicalDeviceExternalMemorySciBufPropertiesNV")) return (void *)table->GetPhysicalDeviceExternalMemorySciBufPropertiesNV;
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0xad036203u:
            if (!strcmp(name, "GetPhysicalDeviceSciBufAttributesNV")) return (void *)table->GetPhysicalDeviceSciBufAttributesNV;
            break;
#endif // VK_USE_PLATFORM_SCI
        default:
            break;
    }

    *found_name = false;
    return NULL;
}


// ---- VK_KHR_external_memory_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryFdKHR(
    VkDevice                                    device,
    const VkMemoryGetFdInfoKHR*                 pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetMemoryFdKHR");
    return disp->GetMemoryFdKHR(device, pGetFdInfo, pFd);
}

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryFdPropertiesKHR(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    int                                         fd,
    VkMemoryFdPropertiesKHR*                    pMemoryFdProperties) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetMemoryFdPropertiesKHR");
    return disp->GetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties);
}


// ---- VK_KHR_external_semaphore_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ImportSemaphoreFdKHR(
    VkDevice                                    device,
    const VkImportSemaphoreFdInfoKHR*           pImportSemaphoreFdInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkImportSemaphoreFdKHR");
    return disp->ImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSemaphoreFdKHR(
    VkDevice                                    device,
    const VkSemaphoreGetFdInfoKHR*              pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetSemaphoreFdKHR");
    return disp->GetSemaphoreFdKHR(device, pGetFdInfo, pFd);
}


// ---- VK_KHR_shared_presentable_image extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainStatusKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetSwapchainStatusKHR");
    return disp->GetSwapchainStatusKHR(device, swapchain);
}


// ---- VK_KHR_external_fence_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ImportFenceFdKHR(
    VkDevice                                    device,
    const VkImportFenceFdInfoKHR*               pImportFenceFdInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkImportFenceFdKHR");
    return disp->ImportFenceFdKHR(device, pImportFenceFdInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetFenceFdKHR(
    VkDevice                                    device,
    const VkFenceGetFdInfoKHR*                  pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetFenceFdKHR");
    return disp->GetFenceFdKHR(device, pGetFdInfo, pFd);
}


// ---- VK_KHR_performance_query extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pCounterCount,
    VkPerformanceCounterKHR*                    pCounters,
    VkPerformanceCounterDescriptionKHR*         pCounterDescriptions) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(unwrapped_phys_dev, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    uint32_t*                                   pCounterCount,
    VkPerformanceCounterKHR*                    pCounters,
    VkPerformanceCounterDescriptionKHR*         pCounterDescriptions) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(phys_dev_term->phys_dev, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR*  pPerformanceQueryCreateInfo,
    uint32_t*                                   pNumPasses) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(unwrapped_phys_dev, pPerformanceQueryCreateInfo, pNumPasses);
}

VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkQueryPoolPerformanceCreateInfoKHR*  pPerformanceQueryCreateInfo,
    uint32_t*                                   pNumPasses) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    icd_term->dispatch.GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(phys_dev_term->phys_dev, pPerformanceQueryCreateInfo, pNumPasses);
}

VKAPI_ATTR VkResult VKAPI_CALL AcquireProfilingLockKHR(
    VkDevice                                    device,
    const VkAcquireProfilingLockInfoKHR*        pInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkAcquireProfilingLockKHR");
    return disp->AcquireProfilingLockKHR(device, pInfo);
}

VKAPI_ATTR void VKAPI_CALL ReleaseProfilingLockKHR(
    VkDevice                                    device) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkReleaseProfilingLockKHR");
    disp->ReleaseProfilingLockKHR(device);
}


// ---- VK_KHR_fragment_shading_rate extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFragmentShadingRatesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR*     pFragmentShadingRates) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetPhysicalDeviceFragmentShadingRatesKHR");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceFragmentShadingRatesKHR(unwrapped_phys_dev, pFragmentShadingRateCount, pFragmentShadingRates);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceFragmentShadingRatesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR*     pFragmentShadingRates) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceFragmentShadingRatesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceFragmentShadingRatesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceFragmentShadingRatesKHR(phys_dev_term->phys_dev, pFragmentShadingRateCount, pFragmentShadingRates);
}

VKAPI_ATTR void VKAPI_CALL CmdSetFragmentShadingRateKHR(
    VkCommandBuffer                             commandBuffer,
    const VkExtent2D*                           pFragmentSize,
    const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetFragmentShadingRateKHR");
    disp->CmdSetFragmentShadingRateKHR(commandBuffer, pFragmentSize, combinerOps);
}


// ---- VK_KHR_object_refresh extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdRefreshObjectsKHR(
    VkCommandBuffer                             commandBuffer,
    const VkRefreshObjectListKHR*               pRefreshObjects) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdRefreshObjectsKHR");
    disp->CmdRefreshObjectsKHR(commandBuffer, pRefreshObjects);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceRefreshableObjectTypesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pRefreshableObjectTypeCount,
    VkObjectType*                               pRefreshableObjectTypes) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetPhysicalDeviceRefreshableObjectTypesKHR");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceRefreshableObjectTypesKHR(unwrapped_phys_dev, pRefreshableObjectTypeCount, pRefreshableObjectTypes);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceRefreshableObjectTypesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pRefreshableObjectTypeCount,
    VkObjectType*                               pRefreshableObjectTypes) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceRefreshableObjectTypesKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceRefreshableObjectTypesKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceRefreshableObjectTypesKHR(phys_dev_term->phys_dev, pRefreshableObjectTypeCount, pRefreshableObjectTypes);
}


// ---- VK_KHR_synchronization2 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetEvent2KHR(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    const VkDependencyInfo*                     pDependencyInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetEvent2KHR");
    disp->CmdSetEvent2KHR(commandBuffer, event, pDependencyInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdResetEvent2KHR(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags2                       stageMask) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdResetEvent2KHR");
    disp->CmdResetEvent2KHR(commandBuffer, event, stageMask);
}

VKAPI_ATTR void VKAPI_CALL CmdWaitEvents2KHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    eventCount,
    const VkEvent*                              pEvents,
    const VkDependencyInfo*                     pDependencyInfos) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdWaitEvents2KHR");
    disp->CmdWaitEvents2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdPipelineBarrier2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkDependencyInfo*                     pDependencyInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdPipelineBarrier2KHR");
    disp->CmdPipelineBarrier2KHR(commandBuffer, pDependencyInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteTimestamp2KHR(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags2                       stage,
    VkQueryPool                                 queryPool,
    uint32_t                                    query) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdWriteTimestamp2KHR");
    disp->CmdWriteTimestamp2KHR(commandBuffer, stage, queryPool, query);
}

VKAPI_ATTR VkResult VKAPI_CALL QueueSubmit2KHR(
    VkQueue                                     queue,
    uint32_t                                    submitCount,
    const VkSubmitInfo2*                        pSubmits,
    VkFence                                     fence) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_queue_dispatch(queue, "vkQueueSubmit2KHR");
    return disp->QueueSubmit2KHR(queue, submitCount, pSubmits, fence);
}


// ---- VK_KHR_copy_commands2 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdCopyBuffer2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferInfo2*                    pCopyBufferInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdCopyBuffer2KHR");
    disp->CmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageInfo2*                     pCopyImageInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdCopyImage2KHR");
    disp->CmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyBufferToImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferToImageInfo2*             pCopyBufferToImageInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdCopyBufferToImage2KHR");
    disp->CmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImageToBuffer2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageToBufferInfo2*             pCopyImageToBufferInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdCopyImageToBuffer2KHR");
    disp->CmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBlitImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkBlitImageInfo2*                     pBlitImageInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdBlitImage2KHR");
    disp->CmdBlitImage2KHR(commandBuffer, pBlitImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdResolveImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkResolveImageInfo2*                  pResolveImageInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdResolveImage2KHR");
    disp->CmdResolveImage2KHR(commandBuffer, pResolveImageInfo);
}


// ---- VK_KHR_line_rasterization extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetLineStippleKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetLineStippleKHR");
    disp->CmdSetLineStippleKHR(commandBuffer, lineStippleFactor, lineStipplePattern);
}


// ---- VK_KHR_calibrated_timestamps extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceCalibrateableTimeDomainsKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainKHR*                            pTimeDomains) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceCalibrateableTimeDomainsKHR(unwrapped_phys_dev, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceCalibrateableTimeDomainsKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainKHR*                            pTimeDomains) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceCalibrateableTimeDomainsKHR) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceCalibrateableTimeDomainsKHR");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceCalibrateableTimeDomainsKHR(phys_dev_term->phys_dev, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL GetCalibratedTimestampsKHR(
    VkDevice                                    device,
    uint32_t                                    timestampCount,
    const VkCalibratedTimestampInfoKHR*         pTimestampInfos,
    uint64_t*                                   pTimestamps,
    uint64_t*                                   pMaxDeviation) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetCalibratedTimestampsKHR");
    return disp->GetCalibratedTimestampsKHR(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}


// ---- VK_EXT_display_control extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL DisplayPowerControlEXT(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayPowerInfoEXT*                pDisplayPowerInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkDisplayPowerControlEXT");
    return disp->DisplayPowerControlEXT(device, display, pDisplayPowerInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL RegisterDeviceEventEXT(
    VkDevice                                    device,
    const VkDeviceEventInfoEXT*                 pDeviceEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkRegisterDeviceEventEXT");
    return disp->RegisterDeviceEventEXT(device, pDeviceEventInfo, pAllocator, pFence);
}

VKAPI_ATTR VkResult VKAPI_CALL RegisterDisplayEventEXT(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayEventInfoEXT*                pDisplayEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkRegisterDisplayEventEXT");
    return disp->RegisterDisplayEventEXT(device, display, pDisplayEventInfo, pAllocator, pFence);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainCounterEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkSurfaceCounterFlagBitsEXT                 counter,
    uint64_t*                                   pCounterValue) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetSwapchainCounterEXT");
    return disp->GetSwapchainCounterEXT(device, swapchain, counter, pCounterValue);
}


// ---- VK_EXT_discard_rectangles extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstDiscardRectangle,
    uint32_t                                    discardRectangleCount,
    const VkRect2D*                             pDiscardRectangles) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetDiscardRectangleEXT");
    disp->CmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    discardRectangleEnable) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetDiscardRectangleEnableEXT");
    disp->CmdSetDiscardRectangleEnableEXT(commandBuffer, discardRectangleEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkDiscardRectangleModeEXT                   discardRectangleMode) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetDiscardRectangleModeEXT");
    disp->CmdSetDiscardRectangleModeEXT(commandBuffer, discardRectangleMode);
}


// ---- VK_EXT_hdr_metadata extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL SetHdrMetadataEXT(
    VkDevice                                    device,
    uint32_t                                    swapchainCount,
    const VkSwapchainKHR*                       pSwapchains,
    const VkHdrMetadataEXT*                     pMetadata) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkSetHdrMetadataEXT");
    disp->SetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata);
}


// ---- VK_EXT_debug_utils extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectNameEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkSetDebugUtilsObjectNameEXT");
    VkDebugUtilsObjectNameInfoEXT local_name_info;
    memcpy(&local_name_info, pNameInfo, sizeof(VkDebugUtilsObjectNameInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pNameInfo->objectType == VK_OBJECT_TYPE_PHYSICAL_DEVICE) {
        struct loader_physical_device_tramp *phys_dev_tramp = (struct loader_physical_device_tramp *)(uintptr_t)pNameInfo->objectHandle;
        local_name_info.objectHandle = (uint64_t)(uintptr_t)phys_dev_tramp->phys_dev;
    }
    if (pNameInfo->objectType == VK_OBJECT_TYPE_INSTANCE) {
        struct loader_instance* instance = (struct loader_instance *)(uintptr_t)pNameInfo->objectHandle;
        local_name_info.objectHandle = (uint64_t)(uintptr_t)instance->instance;
    }
    if (disp->SetDebugUtilsObjectNameEXT != NULL) {
        return disp->SetDebugUtilsObjectNameEXT(device, &local_name_info);
    } else {
        return VK_SUCCESS;
    }
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_SetDebugUtilsObjectNameEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "SetDebugUtilsObjectNameEXT: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugUtilsObjectNameInfoEXT local_name_info;
    memcpy(&local_name_info, pNameInfo, sizeof(VkDebugUtilsObjectNameInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pNameInfo->objectType == VK_OBJECT_TYPE_PHYSICAL_DEVICE) {
        struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)(uintptr_t)pNameInfo->objectHandle;
        local_name_info.objectHandle = (uint64_t)(uintptr_t)phys_dev_term->phys_dev;
    // If this is a KHR_surface, and the ICD has created its own, we have to replace it with the proper one for the next call.
    } else if (pNameInfo->objectType == VK_OBJECT_TYPE_SURFACE_KHR) {
        if (NULL != dev && NULL != dev->loader_dispatch.core_dispatch.CreateSwapchainKHR) {
            VkSurfaceKHR surface = (VkSurfaceKHR)(uintptr_t)pNameInfo->objectHandle;
            if (wsi_unwrap_icd_surface(icd_term, &surface) == VK_SUCCESS) {
                local_name_info.objectHandle = (uint64_t)surface;
            }
        }
    // If this is an instance we have to replace it with the proper one for the next call.
    } else if (pNameInfo->objectType == VK_OBJECT_TYPE_INSTANCE) {
        local_name_info.objectHandle = (uint64_t)(uintptr_t)icd_term->instance;
    }
    // Exit early if the driver does not support the function - this can happen as a layer or the loader itself supports
    // debug utils but the driver does not.
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.SetDebugUtilsObjectNameEXT)
        return VK_SUCCESS;
    return dev->loader_dispatch.extension_terminator_dispatch.SetDebugUtilsObjectNameEXT(device, &local_name_info);
}

VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectTagEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectTagInfoEXT*         pTagInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkSetDebugUtilsObjectTagEXT");
    VkDebugUtilsObjectTagInfoEXT local_tag_info;
    memcpy(&local_tag_info, pTagInfo, sizeof(VkDebugUtilsObjectTagInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pTagInfo->objectType == VK_OBJECT_TYPE_PHYSICAL_DEVICE) {
        struct loader_physical_device_tramp *phys_dev_tramp = (struct loader_physical_device_tramp *)(uintptr_t)pTagInfo->objectHandle;
        local_tag_info.objectHandle = (uint64_t)(uintptr_t)phys_dev_tramp->phys_dev;
    }
    if (pTagInfo->objectType == VK_OBJECT_TYPE_INSTANCE) {
        struct loader_instance* instance = (struct loader_instance *)(uintptr_t)pTagInfo->objectHandle;
        local_tag_info.objectHandle = (uint64_t)(uintptr_t)instance->instance;
    }
    if (disp->SetDebugUtilsObjectTagEXT != NULL) {
        return disp->SetDebugUtilsObjectTagEXT(device, &local_tag_info);
    } else {
        return VK_SUCCESS;
    }
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_SetDebugUtilsObjectTagEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectTagInfoEXT*         pTagInfo) {
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev);
    if (NULL == icd_term || NULL == dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "SetDebugUtilsObjectTagEXT: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    VkDebugUtilsObjectTagInfoEXT local_tag_info;
    memcpy(&local_tag_info, pTagInfo, sizeof(VkDebugUtilsObjectTagInfoEXT));
    // If this is a physical device, we have to replace it with the proper one for the next call.
    if (pTagInfo->objectType == VK_OBJECT_TYPE_PHYSICAL_DEVICE) {
        struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)(uintptr_t)pTagInfo->objectHandle;
        local_tag_info.objectHandle = (uint64_t)(uintptr_t)phys_dev_term->phys_dev;
    // If this is a KHR_surface, and the ICD has created its own, we have to replace it with the proper one for the next call.
    } else if (pTagInfo->objectType == VK_OBJECT_TYPE_SURFACE_KHR) {
        if (NULL != dev && NULL != dev->loader_dispatch.core_dispatch.CreateSwapchainKHR) {
            VkSurfaceKHR surface = (VkSurfaceKHR)(uintptr_t)pTagInfo->objectHandle;
            if (wsi_unwrap_icd_surface(icd_term, &surface) == VK_SUCCESS) {
                local_tag_info.objectHandle = (uint64_t)surface;
            }
        }
    // If this is an instance we have to replace it with the proper one for the next call.
    } else if (pTagInfo->objectType == VK_OBJECT_TYPE_INSTANCE) {
        local_tag_info.objectHandle = (uint64_t)(uintptr_t)icd_term->instance;
    }
    // Exit early if the driver does not support the function - this can happen as a layer or the loader itself supports
    // debug utils but the driver does not.
    if (NULL == dev->loader_dispatch.extension_terminator_dispatch.SetDebugUtilsObjectTagEXT)
        return VK_SUCCESS;
    return dev->loader_dispatch.extension_terminator_dispatch.SetDebugUtilsObjectTagEXT(device, &local_tag_info);
}

VKAPI_ATTR void VKAPI_CALL QueueBeginDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_queue_dispatch(queue, "vkQueueBeginDebugUtilsLabelEXT");
    if (disp->QueueBeginDebugUtilsLabelEXT != NULL) {
        disp->QueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_QueueBeginDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(queue);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.QueueBeginDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.QueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL QueueEndDebugUtilsLabelEXT(
    VkQueue                                     queue) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_queue_dispatch(queue, "vkQueueEndDebugUtilsLabelEXT");
    if (disp->QueueEndDebugUtilsLabelEXT != NULL) {
        disp->QueueEndDebugUtilsLabelEXT(queue);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_QueueEndDebugUtilsLabelEXT(
    VkQueue                                     queue) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(queue);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.QueueEndDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.QueueEndDebugUtilsLabelEXT(queue);
}

VKAPI_ATTR void VKAPI_CALL QueueInsertDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_queue_dispatch(queue, "vkQueueInsertDebugUtilsLabelEXT");
    if (disp->QueueInsertDebugUtilsLabelEXT != NULL) {
        disp->QueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_QueueInsertDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(queue);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.QueueInsertDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.QueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBeginDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdBeginDebugUtilsLabelEXT");
    if (disp->CmdBeginDebugUtilsLabelEXT != NULL) {
        disp->CmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_CmdBeginDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(commandBuffer);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.CmdBeginDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.CmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdEndDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdEndDebugUtilsLabelEXT");
    if (disp->CmdEndDebugUtilsLabelEXT != NULL) {
        disp->CmdEndDebugUtilsLabelEXT(commandBuffer);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_CmdEndDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(commandBuffer);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.CmdEndDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.CmdEndDebugUtilsLabelEXT(commandBuffer);
}

VKAPI_ATTR void VKAPI_CALL CmdInsertDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdInsertDebugUtilsLabelEXT");
    if (disp->CmdInsertDebugUtilsLabelEXT != NULL) {
        disp->CmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
    }
}

VKAPI_ATTR void VKAPI_CALL terminator_CmdInsertDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo) {
    struct loader_dev_dispatch_table *dispatch_table = loader_get_dev_dispatch(commandBuffer);
    if (NULL == dispatch_table) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0, "VK_EXT_debug_utils: Invalid device handle");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    // Only call down if the device supports the function
    if (NULL != dispatch_table->extension_terminator_dispatch.CmdInsertDebugUtilsLabelEXT)
        dispatch_table->extension_terminator_dispatch.CmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}


// ---- VK_EXT_sample_locations extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetSampleLocationsEXT(
    VkCommandBuffer                             commandBuffer,
    const VkSampleLocationsInfoEXT*             pSampleLocationsInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetSampleLocationsEXT");
    disp->CmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMultisamplePropertiesEXT(
    VkPhysicalDevice                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    VkMultisamplePropertiesEXT*                 pMultisampleProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetPhysicalDeviceMultisamplePropertiesEXT");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceMultisamplePropertiesEXT(unwrapped_phys_dev, samples, pMultisampleProperties);
}

VKAPI_ATTR void VKAPI_CALL terminator_GetPhysicalDeviceMultisamplePropertiesEXT(
    VkPhysicalDevice                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    VkMultisamplePropertiesEXT*                 pMultisampleProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceMultisamplePropertiesEXT) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceMultisamplePropertiesEXT");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    icd_term->dispatch.GetPhysicalDeviceMultisamplePropertiesEXT(phys_dev_term->phys_dev, samples, pMultisampleProperties);
}


// ---- VK_EXT_image_drm_format_modifier extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetImageDrmFormatModifierPropertiesEXT(
    VkDevice                                    device,
    VkImage                                     image,
    VkImageDrmFormatModifierPropertiesEXT*      pProperties) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetImageDrmFormatModifierPropertiesEXT");
    return disp->GetImageDrmFormatModifierPropertiesEXT(device, image, pProperties);
}


// ---- VK_EXT_external_memory_host extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryHostPointerPropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    const void*                                 pHostPointer,
    VkMemoryHostPointerPropertiesEXT*           pMemoryHostPointerProperties) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetMemoryHostPointerPropertiesEXT");
    return disp->GetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties);
}


// ---- VK_EXT_line_rasterization extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetLineStippleEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetLineStippleEXT");
    disp->CmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern);
}


// ---- VK_EXT_extended_dynamic_state extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetCullModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkCullModeFlags                             cullMode) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetCullModeEXT");
    disp->CmdSetCullModeEXT(commandBuffer, cullMode);
}

VKAPI_ATTR void VKAPI_CALL CmdSetFrontFaceEXT(
    VkCommandBuffer                             commandBuffer,
    VkFrontFace                                 frontFace) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetFrontFaceEXT");
    disp->CmdSetFrontFaceEXT(commandBuffer, frontFace);
}

VKAPI_ATTR void VKAPI_CALL CmdSetPrimitiveTopologyEXT(
    VkCommandBuffer                             commandBuffer,
    VkPrimitiveTopology                         primitiveTopology) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetPrimitiveTopologyEXT");
    disp->CmdSetPrimitiveTopologyEXT(commandBuffer, primitiveTopology);
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewportWithCountEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetViewportWithCountEXT");
    disp->CmdSetViewportWithCountEXT(commandBuffer, viewportCount, pViewports);
}

VKAPI_ATTR void VKAPI_CALL CmdSetScissorWithCountEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetScissorWithCountEXT");
    disp->CmdSetScissorWithCountEXT(commandBuffer, scissorCount, pScissors);
}

VKAPI_ATTR void VKAPI_CALL CmdBindVertexBuffers2EXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets,
    const VkDeviceSize*                         pSizes,
    const VkDeviceSize*                         pStrides) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdBindVertexBuffers2EXT");
    disp->CmdBindVertexBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthTestEnable) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetDepthTestEnableEXT");
    disp->CmdSetDepthTestEnableEXT(commandBuffer, depthTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthWriteEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthWriteEnable) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetDepthWriteEnableEXT");
    disp->CmdSetDepthWriteEnableEXT(commandBuffer, depthWriteEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthCompareOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkCompareOp                                 depthCompareOp) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetDepthCompareOpEXT");
    disp->CmdSetDepthCompareOpEXT(commandBuffer, depthCompareOp);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthBoundsTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBoundsTestEnable) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetDepthBoundsTestEnableEXT");
    disp->CmdSetDepthBoundsTestEnableEXT(commandBuffer, depthBoundsTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetStencilTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    stencilTestEnable) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetStencilTestEnableEXT");
    disp->CmdSetStencilTestEnableEXT(commandBuffer, stencilTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetStencilOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    VkStencilOp                                 failOp,
    VkStencilOp                                 passOp,
    VkStencilOp                                 depthFailOp,
    VkCompareOp                                 compareOp) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetStencilOpEXT");
    disp->CmdSetStencilOpEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}


// ---- VK_NV_acquire_winrt_display extension trampoline/terminators

#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL AcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkAcquireWinrtDisplayNV");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->AcquireWinrtDisplayNV(unwrapped_phys_dev, display);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_AcquireWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.AcquireWinrtDisplayNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support AcquireWinrtDisplayNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.AcquireWinrtDisplayNV(phys_dev_term->phys_dev, display);
}

#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
VKAPI_ATTR VkResult VKAPI_CALL GetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetWinrtDisplayNV");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetWinrtDisplayNV(unwrapped_phys_dev, deviceRelativeId, pDisplay);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetWinrtDisplayNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    deviceRelativeId,
    VkDisplayKHR*                               pDisplay) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetWinrtDisplayNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetWinrtDisplayNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetWinrtDisplayNV(phys_dev_term->phys_dev, deviceRelativeId, pDisplay);
}

#endif // VK_USE_PLATFORM_WIN32_KHR

// ---- VK_EXT_vertex_input_dynamic_state extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetVertexInputEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT*  pVertexBindingDescriptions,
    uint32_t                                    vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetVertexInputEXT");
    disp->CmdSetVertexInputEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
}


// ---- VK_NV_external_sci_sync extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetFenceSciSyncFenceNV(
    VkDevice                                    device,
    const VkFenceGetSciSyncInfoNV*              pGetSciSyncHandleInfo,
    void*                                       pHandle) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetFenceSciSyncFenceNV");
    return disp->GetFenceSciSyncFenceNV(device, pGetSciSyncHandleInfo, pHandle);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetFenceSciSyncObjNV(
    VkDevice                                    device,
    const VkFenceGetSciSyncInfoNV*              pGetSciSyncHandleInfo,
    void*                                       pHandle) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetFenceSciSyncObjNV");
    return disp->GetFenceSciSyncObjNV(device, pGetSciSyncHandleInfo, pHandle);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL ImportFenceSciSyncFenceNV(
    VkDevice                                    device,
    const VkImportFenceSciSyncInfoNV*           pImportFenceSciSyncInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkImportFenceSciSyncFenceNV");
    return disp->ImportFenceSciSyncFenceNV(device, pImportFenceSciSyncInfo);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL ImportFenceSciSyncObjNV(
    VkDevice                                    device,
    const VkImportFenceSciSyncInfoNV*           pImportFenceSciSyncInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkImportFenceSciSyncObjNV");
    return disp->ImportFenceSciSyncObjNV(device, pImportFenceSciSyncInfo);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSciSyncAttributesNV(
    VkPhysicalDevice                            physicalDevice,
    const VkSciSyncAttributesInfoNV*            pSciSyncAttributesInfo,
    NvSciSyncAttrList                           pAttributes) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetPhysicalDeviceSciSyncAttributesNV");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSciSyncAttributesNV(unwrapped_phys_dev, pSciSyncAttributesInfo, pAttributes);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSciSyncAttributesNV(
    VkPhysicalDevice                            physicalDevice,
    const VkSciSyncAttributesInfoNV*            pSciSyncAttributesInfo,
    NvSciSyncAttrList                           pAttributes) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceSciSyncAttributesNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceSciSyncAttributesNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceSciSyncAttributesNV(phys_dev_term->phys_dev, pSciSyncAttributesInfo, pAttributes);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetSemaphoreSciSyncObjNV(
    VkDevice                                    device,
    const VkSemaphoreGetSciSyncInfoNV*          pGetSciSyncInfo,
    void*                                       pHandle) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetSemaphoreSciSyncObjNV");
    return disp->GetSemaphoreSciSyncObjNV(device, pGetSciSyncInfo, pHandle);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL ImportSemaphoreSciSyncObjNV(
    VkDevice                                    device,
    const VkImportSemaphoreSciSyncInfoNV*       pImportSemaphoreSciSyncInfo) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkImportSemaphoreSciSyncObjNV");
    return disp->ImportSemaphoreSciSyncObjNV(device, pImportSemaphoreSciSyncInfo);
}

#endif // VK_USE_PLATFORM_SCI

// ---- VK_NV_external_memory_sci_buf extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetMemorySciBufNV(
    VkDevice                                    device,
    const VkMemoryGetSciBufInfoNV*              pGetSciBufInfo,
    NvSciBufObj*                                pHandle) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetMemorySciBufNV");
    return disp->GetMemorySciBufNV(device, pGetSciBufInfo, pHandle);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceExternalMemorySciBufPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    NvSciBufObj                                 handle,
    VkMemorySciBufPropertiesNV*                 pMemorySciBufProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceExternalMemorySciBufPropertiesNV(unwrapped_phys_dev, handleType, handle, pMemorySciBufProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceExternalMemorySciBufPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    NvSciBufObj                                 handle,
    VkMemorySciBufPropertiesNV*                 pMemorySciBufProperties) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceExternalMemorySciBufPropertiesNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceExternalMemorySciBufPropertiesNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceExternalMemorySciBufPropertiesNV(phys_dev_term->phys_dev, handleType, handle, pMemorySciBufProperties);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSciBufAttributesNV(
    VkPhysicalDevice                            physicalDevice,
    NvSciBufAttrList                            pAttributes) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, "vkGetPhysicalDeviceSciBufAttributesNV");
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceSciBufAttributesNV(unwrapped_phys_dev, pAttributes);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceSciBufAttributesNV(
    VkPhysicalDevice                            physicalDevice,
    NvSciBufAttrList                            pAttributes) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceSciBufAttributesNV) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceSciBufAttributesNV");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceSciBufAttributesNV(phys_dev_term->phys_dev, pAttributes);
}

#endif // VK_USE_PLATFORM_SCI

// ---- VK_EXT_extended_dynamic_state2 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetPatchControlPointsEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    patchControlPoints) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetPatchControlPointsEXT");
    disp->CmdSetPatchControlPointsEXT(commandBuffer, patchControlPoints);
}

VKAPI_ATTR void VKAPI_CALL CmdSetRasterizerDiscardEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    rasterizerDiscardEnable) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetRasterizerDiscardEnableEXT");
    disp->CmdSetRasterizerDiscardEnableEXT(commandBuffer, rasterizerDiscardEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthBiasEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBiasEnable) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetDepthBiasEnableEXT");
    disp->CmdSetDepthBiasEnableEXT(commandBuffer, depthBiasEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetLogicOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkLogicOp                                   logicOp) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetLogicOpEXT");
    disp->CmdSetLogicOpEXT(commandBuffer, logicOp);
}

VKAPI_ATTR void VKAPI_CALL CmdSetPrimitiveRestartEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    primitiveRestartEnable) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetPrimitiveRestartEnableEXT");
    disp->CmdSetPrimitiveRestartEnableEXT(commandBuffer, primitiveRestartEnable);
}


// ---- VK_EXT_color_write_enable extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetColorWriteEnableEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    attachmentCount,
    const VkBool32*                             pColorWriteEnables) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, "vkCmdSetColorWriteEnableEXT");
    disp->CmdSetColorWriteEnableEXT(commandBuffer, attachmentCount, pColorWriteEnables);
}


// ---- VK_NV_external_sci_sync2 extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphoreSciSyncPoolNV(
    VkDevice                                    device,
    const VkSemaphoreSciSyncPoolCreateInfoNV*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSemaphoreSciSyncPoolNV*                   pSemaphorePool) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkCreateSemaphoreSciSyncPoolNV");
    return disp->CreateSemaphoreSciSyncPoolNV(device, pCreateInfo, pAllocator, pSemaphorePool);
}

#endif // VK_USE_PLATFORM_SCI

// ---- VK_QNX_external_memory_screen_buffer extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
VKAPI_ATTR VkResult VKAPI_CALL GetScreenBufferPropertiesQNX(
    VkDevice                                    device,
    const struct _screen_buffer*                buffer,
    VkScreenBufferPropertiesQNX*                pProperties) {
    const VkLayerDispatchTable *disp = loader_validate_and_get_device_dispatch(device, "vkGetScreenBufferPropertiesQNX");
    return disp->GetScreenBufferPropertiesQNX(device, buffer, pProperties);
}

#endif // VK_USE_PLATFORM_SCREEN_QNX
// GPA helpers for extensions
// name_hash must be loader_hash_string(name) - passed in by the caller so it is only computed once per lookup.
bool extension_instance_gpa(struct loader_instance *ptr_instance, const char *name, uint32_t name_hash, void **addr) {
    *addr = NULL;
    switch (name_hash) {

        // ---- VK_KHR_external_memory_fd extension commands
        case 0xdad4337au:
            if (!strcmp("vkGetMemoryFdKHR", name)) {
                *addr = (void *)GetMemoryFdKHR;
                return true;
            }
            break;
        case 0x040c9cadu:
            if (!strcmp("vkGetMemoryFdPropertiesKHR", name)) {
                *addr = (void *)GetMemoryFdPropertiesKHR;
                return true;
            }
            break;

        // ---- VK_KHR_external_semaphore_fd extension commands
        case 0xc07a1bd8u:
            if (!strcmp("vkImportSemaphoreFdKHR", name)) {
                *addr = (void *)ImportSemaphoreFdKHR;
                return true;
            }
            break;
        case 0x119d3c25u:
            if (!strcmp("vkGetSemaphoreFdKHR", name)) {
                *addr = (void *)GetSemaphoreFdKHR;
                return true;
            }
            break;

        // ---- VK_KHR_shared_presentable_image extension commands
        case 0x5596f083u:
            if (!strcmp("vkGetSwapchainStatusKHR", name)) {
                *addr = (void *)GetSwapchainStatusKHR;
                return true;
            }
            break;

        // ---- VK_KHR_external_fence_fd extension commands
        case 0xdc1dfab5u:
            if (!strcmp("vkImportFenceFdKHR", name)) {
                *addr = (void *)ImportFenceFdKHR;
                return true;
            }
            break;
        case 0xbfa75230u:
            if (!strcmp("vkGetFenceFdKHR", name)) {
                *addr = (void *)GetFenceFdKHR;
                return true;
            }
            break;

        // ---- VK_KHR_performance_query extension commands
        case 0x426d36bcu:
            if (!strcmp("vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR", name)) {
                *addr = (void *)EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
                return true;
            }
            break;
        case 0x479085d6u:
            if (!strcmp("vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR", name)) {
                *addr = (void *)GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
                return true;
            }
            break;
        case 0xbf49690eu:
            if (!strcmp("vkAcquireProfilingLockKHR", name)) {
                *addr = (void *)AcquireProfilingLockKHR;
                return true;
            }
            break;
        case 0xf4fdd0b7u:
            if (!strcmp("vkReleaseProfilingLockKHR", name)) {
                *addr = (void *)ReleaseProfilingLockKHR;
                return true;
            }
            break;

        // ---- VK_KHR_fragment_shading_rate extension commands
        case 0x9e1664efu:
            if (!strcmp("vkGetPhysicalDeviceFragmentShadingRatesKHR", name)) {
                *addr = (void *)GetPhysicalDeviceFragmentShadingRatesKHR;
                return true;
            }
            break;
        case 0xe95260c9u:
            if (!strcmp("vkCmdSetFragmentShadingRateKHR", name)) {
                *addr = (void *)CmdSetFragmentShadingRateKHR;
                return true;
            }
            break;

        // ---- VK_KHR_object_refresh extension commands
        case 0x74779216u:
            if (!strcmp("vkCmdRefreshObjectsKHR", name)) {
                *addr = (void *)CmdRefreshObjectsKHR;
                return true;
            }
            break;
        case 0xf942b41bu:
            if (!strcmp("vkGetPhysicalDeviceRefreshableObjectTypesKHR", name)) {
                *addr = (void *)GetPhysicalDeviceRefreshableObjectTypesKHR;
                return true;
            }
            break;

        // ---- VK_KHR_synchronization2 extension commands
        case 0x92a07673u:
            if (!strcmp("vkCmdSetEvent2KHR", name)) {
                *addr = (void *)CmdSetEvent2KHR;
                return true;
            }
            break;
        case 0xa1fb0bf6u:
            if (!strcmp("vkCmdResetEvent2KHR", name)) {
                *addr = (void *)CmdResetEvent2KHR;
                return true;
            }
            break;
        case 0x8f02f937u:
            if (!strcmp("vkCmdWaitEvents2KHR", name)) {
                *addr = (void *)CmdWaitEvents2KHR;
                return true;
            }
            break;
        case 0x76af21b6u:
            if (!strcmp("vkCmdPipelineBarrier2KHR", name)) {
                *addr = (void *)CmdPipelineBarrier2KHR;
                return true;
            }
            break;
        case 0xb4125402u:
            if (!strcmp("vkCmdWriteTimestamp2KHR", name)) {
                *addr = (void *)CmdWriteTimestamp2KHR;
                return true;
            }
            break;
        case 0x60afde40u:
            if (!strcmp("vkQueueSubmit2KHR", name)) {
                *addr = (void *)QueueSubmit2KHR;
                return true;
            }
            break;

        // ---- VK_KHR_copy_commands2 extension commands
        case 0xa0c8b948u:
            if (!strcmp("vkCmdCopyBuffer2KHR", name)) {
                *addr = (void *)CmdCopyBuffer2KHR;
                return true;
            }
            break;
        case 0x589da3cdu:
            if (!strcmp("vkCmdCopyImage2KHR", name)) {
                *addr = (void *)CmdCopyImage2KHR;
                return true;
            }
            break;
        case 0x866f8fe4u:
            if (!strcmp("vkCmdCopyBufferToImage2KHR", name)) {
                *addr = (void *)CmdCopyBufferToImage2KHR;
                return true;
            }
            break;
        case 0x03ac3d82u:
            if (!strcmp("vkCmdCopyImageToBuffer2KHR", name)) {
                *addr = (void *)CmdCopyImageToBuffer2KHR;
                return true;
            }
            break;
        case 0x9c4f6ffbu:
            if (!strcmp("vkCmdBlitImage2KHR", name)) {
                *addr = (void *)CmdBlitImage2KHR;
                return true;
            }
            break;
        case 0xefa437aeu:
            if (!strcmp("vkCmdResolveImage2KHR", name)) {
                *addr = (void *)CmdResolveImage2KHR;
                return true;
            }
            break;

        // ---- VK_KHR_line_rasterization extension commands
        case 0x4819f988u:
            if (!strcmp("vkCmdSetLineStippleKHR", name)) {
                *addr = (void *)CmdSetLineStippleKHR;
                return true;
            }
            break;

        // ---- VK_KHR_calibrated_timestamps extension commands
        case 0xda63f0cbu:
            if (!strcmp("vkGetPhysicalDeviceCalibrateableTimeDomainsKHR", name)) {
                *addr = (void *)GetPhysicalDeviceCalibrateableTimeDomainsKHR;
                return true;
            }
            break;
        case 0x4a8edbdfu:
            if (!strcmp("vkGetCalibratedTimestampsKHR", name)) {
                *addr = (void *)GetCalibratedTimestampsKHR;
                return true;
            }
            break;

        // ---- VK_EXT_direct_mode_display extension commands
        case 0x8a28db5au:
            if (!strcmp("vkReleaseDisplayEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_direct_mode_display == 1)
                             ? (void *)ReleaseDisplayEXT
                             : NULL;
                return true;
            }
            break;

        // ---- VK_EXT_display_surface_counter extension commands
        case 0xb811cc3bu:
            if (!strcmp("vkGetPhysicalDeviceSurfaceCapabilities2EXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_display_surface_counter == 1)
                             ? (void *)GetPhysicalDeviceSurfaceCapabilities2EXT
                             : NULL;
                return true;
            }
            break;

        // ---- VK_EXT_display_control extension commands
        case 0xf97f8b25u:
            if (!strcmp("vkDisplayPowerControlEXT", name)) {
                *addr = (void *)DisplayPowerControlEXT;
                return true;
            }
            break;
        case 0x2effdcc2u:
            if (!strcmp("vkRegisterDeviceEventEXT", name)) {
                *addr = (void *)RegisterDeviceEventEXT;
                return true;
            }
            break;
        case 0xadc421e4u:
            if (!strcmp("vkRegisterDisplayEventEXT", name)) {
                *addr = (void *)RegisterDisplayEventEXT;
                return true;
            }
            break;
        case 0x302569e5u:
            if (!strcmp("vkGetSwapchainCounterEXT", name)) {
                *addr = (void *)GetSwapchainCounterEXT;
                return true;
            }
            break;

        // ---- VK_EXT_discard_rectangles extension commands
        case 0x746a9b6cu:
            if (!strcmp("vkCmdSetDiscardRectangleEXT", name)) {
                *addr = (void *)CmdSetDiscardRectangleEXT;
                return true;
            }
            break;
        case 0x228ac2c5u:
            if (!strcmp("vkCmdSetDiscardRectangleEnableEXT", name)) {
                *addr = (void *)CmdSetDiscardRectangleEnableEXT;
                return true;
            }
            break;
        case 0xe2eab3f1u:
            if (!strcmp("vkCmdSetDiscardRectangleModeEXT", name)) {
                *addr = (void *)CmdSetDiscardRectangleModeEXT;
                return true;
            }
            break;

        // ---- VK_EXT_hdr_metadata extension commands
        case 0x04d97c94u:
            if (!strcmp("vkSetHdrMetadataEXT", name)) {
                *addr = (void *)SetHdrMetadataEXT;
                return true;
            }
            break;

        // ---- VK_EXT_debug_utils extension commands
        case 0xd89ff139u:
            if (!strcmp("vkSetDebugUtilsObjectNameEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                             ? (void *)SetDebugUtilsObjectNameEXT
                             : NULL;
                return true;
            }
            break;
        case 0x5e0dab22u:
            if (!strcmp("vkSetDebugUtilsObjectTagEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                             ? (void *)SetDebugUtilsObjectTagEXT
                             : NULL;
                return true;
            }
            break;
        case 0x46b78797u:
            if (!strcmp("vkQueueBeginDebugUtilsLabelEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                             ? (void *)QueueBeginDebugUtilsLabelEXT
                             : NULL;
                return true;
            }
            break;
        case 0x6aea05b3u:
            if (!strcmp("vkQueueEndDebugUtilsLabelEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                             ? (void *)QueueEndDebugUtilsLabelEXT
                             : NULL;
                return true;
            }
            break;
        case 0x963e0d79u:
            if (!strcmp("vkQueueInsertDebugUtilsLabelEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                             ? (void *)QueueInsertDebugUtilsLabelEXT
                             : NULL;
                return true;
            }
            break;
        case 0x26ebe05au:
            if (!strcmp("vkCmdBeginDebugUtilsLabelEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                             ? (void *)CmdBeginDebugUtilsLabelEXT
                             : NULL;
                return true;
            }
            break;
        case 0x8cc22c12u:
            if (!strcmp("vkCmdEndDebugUtilsLabelEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                             ? (void *)CmdEndDebugUtilsLabelEXT
                             : NULL;
                return true;
            }
            break;
        case 0x95502ba6u:
            if (!strcmp("vkCmdInsertDebugUtilsLabelEXT", name)) {
                *addr = (ptr_instance->enabled_extensions.ext_debug_utils == 1)
                             ? (void *)CmdInsertDebugUtilsLabelEXT
                             : NULL;
                return true;
            }
            break;

        // ---- VK_EXT_sample_locations extension commands
        case 0x893ad3bbu:
            if (!strcmp("vkCmdSetSampleLocationsEXT", name)) {
                *addr = (void *)CmdSetSampleLocationsEXT;
                return true;
            }
            break;
        case 0x84f1eedcu:
            if (!strcmp("vkGetPhysicalDeviceMultisamplePropertiesEXT", name)) {
                *addr = (void *)GetPhysicalDeviceMultisamplePropertiesEXT;
                return true;
            }
            break;

        // ---- VK_EXT_image_drm_format_modifier extension commands
        case 0xe442e9b6u:
            if (!strcmp("vkGetImageDrmFormatModifierPropertiesEXT", name)) {
                *addr = (void *)GetImageDrmFormatModifierPropertiesEXT;
                return true;
            }
            break;

        // ---- VK_EXT_external_memory_host extension commands
        case 0x21c55ba0u:
            if (!strcmp("vkGetMemoryHostPointerPropertiesEXT", name)) {
                *addr = (void *)GetMemoryHostPointerPropertiesEXT;
                return true;
            }
            break;

        // ---- VK_EXT_line_rasterization extension commands
        case 0x7c80d680u:
            if (!strcmp("vkCmdSetLineStippleEXT", name)) {
                *addr = (void *)CmdSetLineStippleEXT;
                return true;
            }
            break;

        // ---- VK_EXT_extended_dynamic_state extension commands
        case 0x74f8fcccu:
            if (!strcmp("vkCmdSetCullModeEXT", name)) {
                *addr = (void *)CmdSetCullModeEXT;
                return true;
            }
            break;
        case 0xeb32bae3u:
            if (!strcmp("vkCmdSetFrontFaceEXT", name)) {
                *addr = (void *)CmdSetFrontFaceEXT;
                return true;
            }
            break;
        case 0x5965de89u:
            if (!strcmp("vkCmdSetPrimitiveTopologyEXT", name)) {
                *addr = (void *)CmdSetPrimitiveTopologyEXT;
                return true;
            }
            break;
        case 0x3574db42u:
            if (!strcmp("vkCmdSetViewportWithCountEXT", name)) {
                *addr = (void *)CmdSetViewportWithCountEXT;
                return true;
            }
            break;
        case 0x0e3b094eu:
            if (!strcmp("vkCmdSetScissorWithCountEXT", name)) {
                *addr = (void *)CmdSetScissorWithCountEXT;
                return true;
            }
            break;
        case 0x481f705bu:
            if (!strcmp("vkCmdBindVertexBuffers2EXT", name)) {
                *addr = (void *)CmdBindVertexBuffers2EXT;
                return true;
            }
            break;
        case 0xa9d85657u:
            if (!strcmp("vkCmdSetDepthTestEnableEXT", name)) {
                *addr = (void *)CmdSetDepthTestEnableEXT;
                return true;
            }
            break;
        case 0x612d1f30u:
            if (!strcmp("vkCmdSetDepthWriteEnableEXT", name)) {
                *addr = (void *)CmdSetDepthWriteEnableEXT;
                return true;
            }
            break;
        case 0x5d725d28u:
            if (!strcmp("vkCmdSetDepthCompareOpEXT", name)) {
                *addr = (void *)CmdSetDepthCompareOpEXT;
                return true;
            }
            break;
        case 0x02593548u:
            if (!strcmp("vkCmdSetDepthBoundsTestEnableEXT", name)) {
                *addr = (void *)CmdSetDepthBoundsTestEnableEXT;
                return true;
            }
            break;
        case 0xf481ae18u:
            if (!strcmp("vkCmdSetStencilTestEnableEXT", name)) {
                *addr = (void *)CmdSetStencilTestEnableEXT;
                return true;
            }
            break;
        case 0xdc736664u:
            if (!strcmp("vkCmdSetStencilOpEXT", name)) {
                *addr = (void *)CmdSetStencilOpEXT;
                return true;
            }
            break;

        // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        case 0x6a89f660u:
            if (!strcmp("vkAcquireWinrtDisplayNV", name)) {
                *addr = (void *)AcquireWinrtDisplayNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
        case 0x6f0cbf1cu:
            if (!strcmp("vkGetWinrtDisplayNV", name)) {
                *addr = (void *)GetWinrtDisplayNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_WIN32_KHR

        // ---- VK_EXT_vertex_input_dynamic_state extension commands
        case 0x3298ff83u:
            if (!strcmp("vkCmdSetVertexInputEXT", name)) {
                *addr = (void *)CmdSetVertexInputEXT;
                return true;
            }
            break;

        // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
        case 0x6f0eae70u:
            if (!strcmp("vkGetFenceSciSyncFenceNV", name)) {
                *addr = (void *)GetFenceSciSyncFenceNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0x73236404u:
            if (!strcmp("vkGetFenceSciSyncObjNV", name)) {
                *addr = (void *)GetFenceSciSyncObjNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0xe7f9bd6fu:
            if (!strcmp("vkImportFenceSciSyncFenceNV", name)) {
                *addr = (void *)ImportFenceSciSyncFenceNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0xe6743703u:
            if (!strcmp("vkImportFenceSciSyncObjNV", name)) {
                *addr = (void *)ImportFenceSciSyncObjNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0x2dac6910u:
            if (!strcmp("vkGetPhysicalDeviceSciSyncAttributesNV", name)) {
                *addr = (void *)GetPhysicalDeviceSciSyncAttributesNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0x5982b4f3u:
            if (!strcmp("vkGetSemaphoreSciSyncObjNV", name)) {
                *addr = (void *)GetSemaphoreSciSyncObjNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0x160dc67cu:
            if (!strcmp("vkImportSemaphoreSciSyncObjNV", name)) {
                *addr = (void *)ImportSemaphoreSciSyncObjNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI

        // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
        case 0xa4485397u:
            if (!strcmp("vkGetMemorySciBufNV", name)) {
                *addr = (void *)GetMemorySciBufNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0x3429362au:
            if (!strcmp("vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV", name)) {
                *addr = (void *)GetPhysicalDeviceExternalMemorySciBufPropertiesNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
        case 0x2b3e7766u:
            if (!strcmp("vkGetPhysicalDeviceSciBufAttributesNV", name)) {
                *addr = (void *)GetPhysicalDeviceSciBufAttributesNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI

        // ---- VK_EXT_extended_dynamic_state2 extension commands
        case 0x2c78d559u:
            if (!strcmp("vkCmdSetPatchControlPointsEXT", name)) {
                *addr = (void *)CmdSetPatchControlPointsEXT;
                return true;
            }
            break;
        case 0x711bc26fu:
            if (!strcmp("vkCmdSetRasterizerDiscardEnableEXT", name)) {
                *addr = (void *)CmdSetRasterizerDiscardEnableEXT;
                return true;
            }
            break;
        case 0xad4bca4cu:
            if (!strcmp("vkCmdSetDepthBiasEnableEXT", name)) {
                *addr = (void *)CmdSetDepthBiasEnableEXT;
                return true;
            }
            break;
        case 0x0eefc5f6u:
            if (!strcmp("vkCmdSetLogicOpEXT", name)) {
                *addr = (void *)CmdSetLogicOpEXT;
                return true;
            }
            break;
        case 0x29891200u:
            if (!strcmp("vkCmdSetPrimitiveRestartEnableEXT", name)) {
                *addr = (void *)CmdSetPrimitiveRestartEnableEXT;
                return true;
            }
            break;

        // ---- VK_EXT_color_write_enable extension commands
        case 0x2151479au:
            if (!strcmp("vkCmdSetColorWriteEnableEXT", name)) {
                *addr = (void *)CmdSetColorWriteEnableEXT;
                return true;
            }
            break;

        // ---- VK_NV_external_sci_sync2 extension commands
#if defined(VK_USE_PLATFORM_SCI)
        case 0xbff08f80u:
            if (!strcmp("vkCreateSemaphoreSciSyncPoolNV", name)) {
                *addr = (void *)CreateSemaphoreSciSyncPoolNV;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCI

        // ---- VK_QNX_external_memory_screen_buffer extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
        case 0xfed75262u:
            if (!strcmp("vkGetScreenBufferPropertiesQNX", name)) {
                *addr = (void *)GetScreenBufferPropertiesQNX;
                return true;
            }
            break;
#endif // VK_USE_PLATFORM_SCREEN_QNX
        default:
            break;
    }
    return false;
}

// Used to keep track of all enabled instance extensions
void fill_out_enabled_instance_extensions(uint32_t extension_count, const char *const * extension_list, struct loader_instance_extension_enable_list* enables) {
    for (uint32_t i = 0; i < extension_count; i++) {

    // ---- VK_KHR_surface extension commands
        if (0 == strcmp(extension_list[i], VK_KHR_SURFACE_EXTENSION_NAME)) { enables->khr_surface = 1; }

    // ---- VK_KHR_display extension commands
        else if (0 == strcmp(extension_list[i], VK_KHR_DISPLAY_EXTENSION_NAME)) { enables->khr_display = 1; }

    // ---- VK_KHR_get_surface_capabilities2 extension commands
        else if (0 == strcmp(extension_list[i], VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME)) { enables->khr_get_surface_capabilities2 = 1; }

    // ---- VK_KHR_get_display_properties2 extension commands
        else if (0 == strcmp(extension_list[i], VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME)) { enables->khr_get_display_properties2 = 1; }

    // ---- VK_EXT_direct_mode_display extension commands
        else if (0 == strcmp(extension_list[i], VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME)) { enables->ext_direct_mode_display = 1; }

    // ---- VK_EXT_display_surface_counter extension commands
        else if (0 == strcmp(extension_list[i], VK_EXT_DISPLAY_SURFACE_COUNTER_EXTENSION_NAME)) { enables->ext_display_surface_counter = 1; }

    // ---- VK_EXT_swapchain_colorspace extension commands
        else if (0 == strcmp(extension_list[i], VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME)) { enables->ext_swapchain_colorspace = 1; }

    // ---- VK_EXT_debug_utils extension commands
        else if (0 == strcmp(extension_list[i], VK_EXT_DEBUG_UTILS_EXTENSION_NAME)) { enables->ext_debug_utils = 1; }

    // ---- VK_EXT_validation_features extension commands
        else if (0 == strcmp(extension_list[i], VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME)) { enables->ext_validation_features = 1; }

    // ---- VK_EXT_headless_surface extension commands
        else if (0 == strcmp(extension_list[i], VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME)) { enables->ext_headless_surface = 1; }

    // ---- VK_EXT_application_parameters extension commands
        else if (0 == strcmp(extension_list[i], VK_EXT_APPLICATION_PARAMETERS_EXTENSION_NAME)) { enables->ext_application_parameters = 1; }

    // ---- VK_EXT_layer_settings extension commands
        else if (0 == strcmp(extension_list[i], VK_EXT_LAYER_SETTINGS_EXTENSION_NAME)) { enables->ext_layer_settings = 1; }
    }
}

// Some device commands still need a terminator because the loader needs to unwrap something about them.
// In many cases, the item needing unwrapping is a VkPhysicalDevice or VkSurfaceKHR object.  But there may be other items
// in the future.
PFN_vkVoidFunction get_extension_device_proc_terminator(struct loader_device *dev, const char *name, bool* found_name) {
    *found_name = false;
    if (!name || name[0] != 'v' || name[1] != 'k') {
        return NULL;
    }
    name += 2;
    // ---- VK_KHR_swapchain extension commands
    if (!strcmp(name, "CreateSwapchainKHR")) {
        *found_name = true;
        return dev->driver_extensions.khr_swapchain_enabled ?
            (PFN_vkVoidFunction)terminator_CreateSwapchainKHR : NULL;
    }
    if (!strcmp(name, "GetDeviceGroupSurfacePresentModesKHR")) {
        *found_name = true;
        return dev->driver_extensions.khr_swapchain_enabled ?
            (PFN_vkVoidFunction)terminator_GetDeviceGroupSurfacePresentModesKHR : NULL;
    }
    // ---- VK_KHR_display_swapchain extension commands
    if (!strcmp(name, "CreateSharedSwapchainsKHR")) {
        *found_name = true;
        return dev->driver_extensions.khr_display_swapchain_enabled ?
            (PFN_vkVoidFunction)terminator_CreateSharedSwapchainsKHR : NULL;
    }
    // ---- VK_EXT_debug_utils extension commands
    if (!strcmp(name, "SetDebugUtilsObjectNameEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_SetDebugUtilsObjectNameEXT : NULL;
    }
    if (!strcmp(name, "SetDebugUtilsObjectTagEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_SetDebugUtilsObjectTagEXT : NULL;
    }
    if (!strcmp(name, "QueueBeginDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_QueueBeginDebugUtilsLabelEXT : NULL;
    }
    if (!strcmp(name, "QueueEndDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_QueueEndDebugUtilsLabelEXT : NULL;
    }
    if (!strcmp(name, "QueueInsertDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_QueueInsertDebugUtilsLabelEXT : NULL;
    }
    if (!strcmp(name, "CmdBeginDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_CmdBeginDebugUtilsLabelEXT : NULL;
    }
    if (!strcmp(name, "CmdEndDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_CmdEndDebugUtilsLabelEXT : NULL;
    }
    if (!strcmp(name, "CmdInsertDebugUtilsLabelEXT")) {
        *found_name = true;
        return dev->driver_extensions.ext_debug_utils_enabled ?
            (PFN_vkVoidFunction)terminator_CmdInsertDebugUtilsLabelEXT : NULL;
    }
    return NULL;
}

// This table contains the loader's instance dispatch table, which contains
// default functions if no instance layers are activated.  This contains
// pointers to "terminator functions".
const VkLayerInstanceDispatchTable instance_disp = {

    // ---- Core Vulkan SC 1.0 commands
    .DestroyInstance = terminator_DestroyInstance,
    .EnumeratePhysicalDevices = terminator_EnumeratePhysicalDevices,
    .GetPhysicalDeviceFeatures = terminator_GetPhysicalDeviceFeatures,
    .GetPhysicalDeviceFormatProperties = terminator_GetPhysicalDeviceFormatProperties,
    .GetPhysicalDeviceImageFormatProperties = terminator_GetPhysicalDeviceImageFormatProperties,
    .GetPhysicalDeviceProperties = terminator_GetPhysicalDeviceProperties,
    .GetPhysicalDeviceQueueFamilyProperties = terminator_GetPhysicalDeviceQueueFamilyProperties,
    .GetPhysicalDeviceMemoryProperties = terminator_GetPhysicalDeviceMemoryProperties,
    .GetInstanceProcAddr = vkGetInstanceProcAddr,
    .EnumerateDeviceExtensionProperties = terminator_EnumerateDeviceExtensionProperties,
    .EnumerateDeviceLayerProperties = terminator_EnumerateDeviceLayerProperties,
    .EnumeratePhysicalDeviceGroups = terminator_EnumeratePhysicalDeviceGroups,
    .GetPhysicalDeviceFeatures2 = terminator_GetPhysicalDeviceFeatures2,
    .GetPhysicalDeviceProperties2 = terminator_GetPhysicalDeviceProperties2,
    .GetPhysicalDeviceFormatProperties2 = terminator_GetPhysicalDeviceFormatProperties2,
    .GetPhysicalDeviceImageFormatProperties2 = terminator_GetPhysicalDeviceImageFormatProperties2,
    .GetPhysicalDeviceQueueFamilyProperties2 = terminator_GetPhysicalDeviceQueueFamilyProperties2,
    .GetPhysicalDeviceMemoryProperties2 = terminator_GetPhysicalDeviceMemoryProperties2,
    .GetPhysicalDeviceExternalBufferProperties = terminator_GetPhysicalDeviceExternalBufferProperties,
    .GetPhysicalDeviceExternalFenceProperties = terminator_GetPhysicalDeviceExternalFenceProperties,
    .GetPhysicalDeviceExternalSemaphoreProperties = terminator_GetPhysicalDeviceExternalSemaphoreProperties,

    // ---- Core Vulkan 1.3 commands
    .GetPhysicalDeviceToolProperties = terminator_GetPhysicalDeviceToolProperties,

    // ---- VK_KHR_surface extension commands
    .DestroySurfaceKHR = terminator_DestroySurfaceKHR,
    .GetPhysicalDeviceSurfaceSupportKHR = terminator_GetPhysicalDeviceSurfaceSupportKHR,
    .GetPhysicalDeviceSurfaceCapabilitiesKHR = terminator_GetPhysicalDeviceSurfaceCapabilitiesKHR,
    .GetPhysicalDeviceSurfaceFormatsKHR = terminator_GetPhysicalDeviceSurfaceFormatsKHR,
    .GetPhysicalDeviceSurfacePresentModesKHR = terminator_GetPhysicalDeviceSurfacePresentModesKHR,

    // ---- VK_KHR_swapchain extension commands
    .GetPhysicalDevicePresentRectanglesKHR = terminator_GetPhysicalDevicePresentRectanglesKHR,

    // ---- VK_KHR_display extension commands
    .GetPhysicalDeviceDisplayPropertiesKHR = terminator_GetPhysicalDeviceDisplayPropertiesKHR,
    .GetPhysicalDeviceDisplayPlanePropertiesKHR = terminator_GetPhysicalDeviceDisplayPlanePropertiesKHR,
    .GetDisplayPlaneSupportedDisplaysKHR = terminator_GetDisplayPlaneSupportedDisplaysKHR,
    .GetDisplayModePropertiesKHR = terminator_GetDisplayModePropertiesKHR,
    .CreateDisplayModeKHR = terminator_CreateDisplayModeKHR,
    .GetDisplayPlaneCapabilitiesKHR = terminator_GetDisplayPlaneCapabilitiesKHR,
    .CreateDisplayPlaneSurfaceKHR = terminator_CreateDisplayPlaneSurfaceKHR,

    // ---- VK_KHR_performance_query extension commands
    .EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = terminator_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR,
    .GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = terminator_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR,

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    .GetPhysicalDeviceSurfaceCapabilities2KHR = terminator_GetPhysicalDeviceSurfaceCapabilities2KHR,
    .GetPhysicalDeviceSurfaceFormats2KHR = terminator_GetPhysicalDeviceSurfaceFormats2KHR,

    // ---- VK_KHR_get_display_properties2 extension commands
    .GetPhysicalDeviceDisplayProperties2KHR = terminator_GetPhysicalDeviceDisplayProperties2KHR,
    .GetPhysicalDeviceDisplayPlaneProperties2KHR = terminator_GetPhysicalDeviceDisplayPlaneProperties2KHR,
    .GetDisplayModeProperties2KHR = terminator_GetDisplayModeProperties2KHR,
    .GetDisplayPlaneCapabilities2KHR = terminator_GetDisplayPlaneCapabilities2KHR,

    // ---- VK_KHR_fragment_shading_rate extension commands
    .GetPhysicalDeviceFragmentShadingRatesKHR = terminator_GetPhysicalDeviceFragmentShadingRatesKHR,

    // ---- VK_KHR_object_refresh extension commands
    .GetPhysicalDeviceRefreshableObjectTypesKHR = terminator_GetPhysicalDeviceRefreshableObjectTypesKHR,

    // ---- VK_KHR_calibrated_timestamps extension commands
    .GetPhysicalDeviceCalibrateableTimeDomainsKHR = terminator_GetPhysicalDeviceCalibrateableTimeDomainsKHR,

    // ---- VK_EXT_direct_mode_display extension commands
    .ReleaseDisplayEXT = terminator_ReleaseDisplayEXT,

    // ---- VK_EXT_display_surface_counter extension commands
    .GetPhysicalDeviceSurfaceCapabilities2EXT = terminator_GetPhysicalDeviceSurfaceCapabilities2EXT,

    // ---- VK_EXT_debug_utils extension commands
    .CreateDebugUtilsMessengerEXT = terminator_CreateDebugUtilsMessengerEXT,
    .DestroyDebugUtilsMessengerEXT = terminator_DestroyDebugUtilsMessengerEXT,
    .SubmitDebugUtilsMessageEXT = terminator_SubmitDebugUtilsMessageEXT,

    // ---- VK_EXT_sample_locations extension commands
    .GetPhysicalDeviceMultisamplePropertiesEXT = terminator_GetPhysicalDeviceMultisamplePropertiesEXT,

    // ---- VK_EXT_headless_surface extension commands
    .CreateHeadlessSurfaceEXT = terminator_CreateHeadlessSurfaceEXT,

    // ---- VK_NV_acquire_winrt_display extension commands
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    .AcquireWinrtDisplayNV = terminator_AcquireWinrtDisplayNV,
#endif // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    .GetWinrtDisplayNV = terminator_GetWinrtDisplayNV,
#endif // VK_USE_PLATFORM_WIN32_KHR

    // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
    .GetPhysicalDeviceSciSyncAttributesNV = terminator_GetPhysicalDeviceSciSyncAttributesNV,
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
    .GetPhysicalDeviceExternalMemorySciBufPropertiesNV = terminator_GetPhysicalDeviceExternalMemorySciBufPropertiesNV,
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    .GetPhysicalDeviceSciBufAttributesNV = terminator_GetPhysicalDeviceSciBufAttributesNV,
#endif // VK_USE_PLATFORM_SCI
};

// A null-terminated list of all of the instance extensions supported by the loader.
// If an instance extension name is not in this list, but it is exported by one or more of the
// ICDs detected by the loader, then the extension name not in the list will be filtered out
// before passing the list of extensions to the application.
const char *const LOADER_INSTANCE_EXTENSIONS[] = {
                                                  VK_KHR_SURFACE_EXTENSION_NAME,
                                                  VK_KHR_DISPLAY_EXTENSION_NAME,
                                                  VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME,
                                                  VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME,
                                                  VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME,
                                                  VK_EXT_DISPLAY_SURFACE_COUNTER_EXTENSION_NAME,
                                                  VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME,
                                                  VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
                                                  VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME,
                                                  VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME,
                                                  VK_EXT_APPLICATION_PARAMETERS_EXTENSION_NAME,
                                                  VK_EXT_LAYER_SETTINGS_EXTENSION_NAME,
                                                  NULL };
// clang-format on
