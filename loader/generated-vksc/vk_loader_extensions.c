// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See loader_extension_generator.py for modifications

/*
 * Copyright (c) 2015-2022 The Khronos Group Inc.
 * Copyright (c) 2015-2022 Valve Corporation
 * Copyright (c) 2015-2022 LunarG, Inc.
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vk_loader_platform.h"
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
    struct loader_icd_term *icd_term = loader_get_icd_and_device(dev, &found_dev, NULL);

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


    // ---- Core SC 1_0
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

    // ---- VK_EXT_calibrated_timestamps extension commands
    LOOKUP_GIPA(GetPhysicalDeviceCalibrateableTimeDomainsEXT);

    // ---- VK_EXT_headless_surface extension commands
    LOOKUP_GIPA(CreateHeadlessSurfaceEXT);

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

    // ---- Core SC 1_0 commands
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
    table->CreateEvent = (PFN_vkCreateEvent)gpa(dev, "vkCreateEvent");
    table->DestroyEvent = (PFN_vkDestroyEvent)gpa(dev, "vkDestroyEvent");
    table->GetEventStatus = (PFN_vkGetEventStatus)gpa(dev, "vkGetEventStatus");
    table->SetEvent = (PFN_vkSetEvent)gpa(dev, "vkSetEvent");
    table->ResetEvent = (PFN_vkResetEvent)gpa(dev, "vkResetEvent");
    table->CreateQueryPool = (PFN_vkCreateQueryPool)gpa(dev, "vkCreateQueryPool");
    table->GetQueryPoolResults = (PFN_vkGetQueryPoolResults)gpa(dev, "vkGetQueryPoolResults");
    table->CreateBuffer = (PFN_vkCreateBuffer)gpa(dev, "vkCreateBuffer");
    table->DestroyBuffer = (PFN_vkDestroyBuffer)gpa(dev, "vkDestroyBuffer");
    table->CreateBufferView = (PFN_vkCreateBufferView)gpa(dev, "vkCreateBufferView");
    table->DestroyBufferView = (PFN_vkDestroyBufferView)gpa(dev, "vkDestroyBufferView");
    table->CreateImage = (PFN_vkCreateImage)gpa(dev, "vkCreateImage");
    table->DestroyImage = (PFN_vkDestroyImage)gpa(dev, "vkDestroyImage");
    table->GetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)gpa(dev, "vkGetImageSubresourceLayout");
    table->CreateImageView = (PFN_vkCreateImageView)gpa(dev, "vkCreateImageView");
    table->DestroyImageView = (PFN_vkDestroyImageView)gpa(dev, "vkDestroyImageView");
    table->CreatePipelineCache = (PFN_vkCreatePipelineCache)gpa(dev, "vkCreatePipelineCache");
    table->DestroyPipelineCache = (PFN_vkDestroyPipelineCache)gpa(dev, "vkDestroyPipelineCache");
    table->CreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)gpa(dev, "vkCreateGraphicsPipelines");
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
    table->CreateFramebuffer = (PFN_vkCreateFramebuffer)gpa(dev, "vkCreateFramebuffer");
    table->DestroyFramebuffer = (PFN_vkDestroyFramebuffer)gpa(dev, "vkDestroyFramebuffer");
    table->CreateRenderPass = (PFN_vkCreateRenderPass)gpa(dev, "vkCreateRenderPass");
    table->DestroyRenderPass = (PFN_vkDestroyRenderPass)gpa(dev, "vkDestroyRenderPass");
    table->GetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)gpa(dev, "vkGetRenderAreaGranularity");
    table->CreateCommandPool = (PFN_vkCreateCommandPool)gpa(dev, "vkCreateCommandPool");
    table->ResetCommandPool = (PFN_vkResetCommandPool)gpa(dev, "vkResetCommandPool");
    table->AllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)gpa(dev, "vkAllocateCommandBuffers");
    table->FreeCommandBuffers = (PFN_vkFreeCommandBuffers)gpa(dev, "vkFreeCommandBuffers");
    table->BeginCommandBuffer = (PFN_vkBeginCommandBuffer)gpa(dev, "vkBeginCommandBuffer");
    table->EndCommandBuffer = (PFN_vkEndCommandBuffer)gpa(dev, "vkEndCommandBuffer");
    table->ResetCommandBuffer = (PFN_vkResetCommandBuffer)gpa(dev, "vkResetCommandBuffer");
    table->CmdBindPipeline = (PFN_vkCmdBindPipeline)gpa(dev, "vkCmdBindPipeline");
    table->CmdSetViewport = (PFN_vkCmdSetViewport)gpa(dev, "vkCmdSetViewport");
    table->CmdSetScissor = (PFN_vkCmdSetScissor)gpa(dev, "vkCmdSetScissor");
    table->CmdSetLineWidth = (PFN_vkCmdSetLineWidth)gpa(dev, "vkCmdSetLineWidth");
    table->CmdSetDepthBias = (PFN_vkCmdSetDepthBias)gpa(dev, "vkCmdSetDepthBias");
    table->CmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)gpa(dev, "vkCmdSetBlendConstants");
    table->CmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)gpa(dev, "vkCmdSetDepthBounds");
    table->CmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)gpa(dev, "vkCmdSetStencilCompareMask");
    table->CmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)gpa(dev, "vkCmdSetStencilWriteMask");
    table->CmdSetStencilReference = (PFN_vkCmdSetStencilReference)gpa(dev, "vkCmdSetStencilReference");
    table->CmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)gpa(dev, "vkCmdBindDescriptorSets");
    table->CmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)gpa(dev, "vkCmdBindIndexBuffer");
    table->CmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)gpa(dev, "vkCmdBindVertexBuffers");
    table->CmdDraw = (PFN_vkCmdDraw)gpa(dev, "vkCmdDraw");
    table->CmdDrawIndexed = (PFN_vkCmdDrawIndexed)gpa(dev, "vkCmdDrawIndexed");
    table->CmdDrawIndirect = (PFN_vkCmdDrawIndirect)gpa(dev, "vkCmdDrawIndirect");
    table->CmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)gpa(dev, "vkCmdDrawIndexedIndirect");
    table->CmdDispatch = (PFN_vkCmdDispatch)gpa(dev, "vkCmdDispatch");
    table->CmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)gpa(dev, "vkCmdDispatchIndirect");
    table->CmdCopyBuffer = (PFN_vkCmdCopyBuffer)gpa(dev, "vkCmdCopyBuffer");
    table->CmdCopyImage = (PFN_vkCmdCopyImage)gpa(dev, "vkCmdCopyImage");
    table->CmdBlitImage = (PFN_vkCmdBlitImage)gpa(dev, "vkCmdBlitImage");
    table->CmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)gpa(dev, "vkCmdCopyBufferToImage");
    table->CmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)gpa(dev, "vkCmdCopyImageToBuffer");
    table->CmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)gpa(dev, "vkCmdUpdateBuffer");
    table->CmdFillBuffer = (PFN_vkCmdFillBuffer)gpa(dev, "vkCmdFillBuffer");
    table->CmdClearColorImage = (PFN_vkCmdClearColorImage)gpa(dev, "vkCmdClearColorImage");
    table->CmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)gpa(dev, "vkCmdClearDepthStencilImage");
    table->CmdClearAttachments = (PFN_vkCmdClearAttachments)gpa(dev, "vkCmdClearAttachments");
    table->CmdResolveImage = (PFN_vkCmdResolveImage)gpa(dev, "vkCmdResolveImage");
    table->CmdSetEvent = (PFN_vkCmdSetEvent)gpa(dev, "vkCmdSetEvent");
    table->CmdResetEvent = (PFN_vkCmdResetEvent)gpa(dev, "vkCmdResetEvent");
    table->CmdWaitEvents = (PFN_vkCmdWaitEvents)gpa(dev, "vkCmdWaitEvents");
    table->CmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)gpa(dev, "vkCmdPipelineBarrier");
    table->CmdBeginQuery = (PFN_vkCmdBeginQuery)gpa(dev, "vkCmdBeginQuery");
    table->CmdEndQuery = (PFN_vkCmdEndQuery)gpa(dev, "vkCmdEndQuery");
    table->CmdResetQueryPool = (PFN_vkCmdResetQueryPool)gpa(dev, "vkCmdResetQueryPool");
    table->CmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)gpa(dev, "vkCmdWriteTimestamp");
    table->CmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)gpa(dev, "vkCmdCopyQueryPoolResults");
    table->CmdPushConstants = (PFN_vkCmdPushConstants)gpa(dev, "vkCmdPushConstants");
    table->CmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)gpa(dev, "vkCmdBeginRenderPass");
    table->CmdNextSubpass = (PFN_vkCmdNextSubpass)gpa(dev, "vkCmdNextSubpass");
    table->CmdEndRenderPass = (PFN_vkCmdEndRenderPass)gpa(dev, "vkCmdEndRenderPass");
    table->CmdExecuteCommands = (PFN_vkCmdExecuteCommands)gpa(dev, "vkCmdExecuteCommands");
    table->BindBufferMemory2 = (PFN_vkBindBufferMemory2)gpa(dev, "vkBindBufferMemory2");
    table->BindImageMemory2 = (PFN_vkBindImageMemory2)gpa(dev, "vkBindImageMemory2");
    table->GetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)gpa(dev, "vkGetDeviceGroupPeerMemoryFeatures");
    table->CmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)gpa(dev, "vkCmdSetDeviceMask");
    table->CmdDispatchBase = (PFN_vkCmdDispatchBase)gpa(dev, "vkCmdDispatchBase");
    table->GetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)gpa(dev, "vkGetImageMemoryRequirements2");
    table->GetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)gpa(dev, "vkGetBufferMemoryRequirements2");
    table->GetDeviceQueue2 = (PFN_vkGetDeviceQueue2)gpa(dev, "vkGetDeviceQueue2");
    table->CreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)gpa(dev, "vkCreateSamplerYcbcrConversion");
    table->DestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)gpa(dev, "vkDestroySamplerYcbcrConversion");
    table->GetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)gpa(dev, "vkGetDescriptorSetLayoutSupport");
    table->CmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)gpa(dev, "vkCmdDrawIndirectCount");
    table->CmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)gpa(dev, "vkCmdDrawIndexedIndirectCount");
    table->CreateRenderPass2 = (PFN_vkCreateRenderPass2)gpa(dev, "vkCreateRenderPass2");
    table->CmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)gpa(dev, "vkCmdBeginRenderPass2");
    table->CmdNextSubpass2 = (PFN_vkCmdNextSubpass2)gpa(dev, "vkCmdNextSubpass2");
    table->CmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)gpa(dev, "vkCmdEndRenderPass2");
    table->ResetQueryPool = (PFN_vkResetQueryPool)gpa(dev, "vkResetQueryPool");
    table->GetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)gpa(dev, "vkGetSemaphoreCounterValue");
    table->WaitSemaphores = (PFN_vkWaitSemaphores)gpa(dev, "vkWaitSemaphores");
    table->SignalSemaphore = (PFN_vkSignalSemaphore)gpa(dev, "vkSignalSemaphore");
    table->GetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)gpa(dev, "vkGetBufferDeviceAddress");
    table->GetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)gpa(dev, "vkGetBufferOpaqueCaptureAddress");
    table->GetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)gpa(dev, "vkGetDeviceMemoryOpaqueCaptureAddress");
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
    table->CmdWriteBufferMarker2AMD = (PFN_vkCmdWriteBufferMarker2AMD)gdpa(dev, "vkCmdWriteBufferMarker2AMD");
    table->GetQueueCheckpointData2NV = (PFN_vkGetQueueCheckpointData2NV)gdpa(dev, "vkGetQueueCheckpointData2NV");

    // ---- VK_KHR_copy_commands2 extension commands
    table->CmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)gdpa(dev, "vkCmdCopyBuffer2KHR");
    table->CmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)gdpa(dev, "vkCmdCopyImage2KHR");
    table->CmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)gdpa(dev, "vkCmdCopyBufferToImage2KHR");
    table->CmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)gdpa(dev, "vkCmdCopyImageToBuffer2KHR");
    table->CmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)gdpa(dev, "vkCmdBlitImage2KHR");
    table->CmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)gdpa(dev, "vkCmdResolveImage2KHR");

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

    // ---- VK_EXT_calibrated_timestamps extension commands
    table->GetCalibratedTimestampsEXT = (PFN_vkGetCalibratedTimestampsEXT)gdpa(dev, "vkGetCalibratedTimestampsEXT");

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

    // ---- Core SC 1_0 commands
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

    // ---- VK_EXT_calibrated_timestamps extension commands
    table->GetPhysicalDeviceCalibrateableTimeDomainsEXT = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT)gpa(inst, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT");

    // ---- VK_EXT_headless_surface extension commands
    table->CreateHeadlessSurfaceEXT = (PFN_vkCreateHeadlessSurfaceEXT)gpa(inst, "vkCreateHeadlessSurfaceEXT");

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


    // ---- Core SC 1_0 commands
    if (!strcmp(name, "GetDeviceProcAddr")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceProcAddr;
    }
    if (!strcmp(name, "DestroyDevice")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyDevice;
    }
    if (!strcmp(name, "GetDeviceQueue")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceQueue;
    }
    if (!strcmp(name, "QueueSubmit")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->QueueSubmit;
    }
    if (!strcmp(name, "QueueWaitIdle")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->QueueWaitIdle;
    }
    if (!strcmp(name, "DeviceWaitIdle")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DeviceWaitIdle;
    }
    if (!strcmp(name, "AllocateMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->AllocateMemory;
    }
    if (!strcmp(name, "MapMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->MapMemory;
    }
    if (!strcmp(name, "UnmapMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->UnmapMemory;
    }
    if (!strcmp(name, "FlushMappedMemoryRanges")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->FlushMappedMemoryRanges;
    }
    if (!strcmp(name, "InvalidateMappedMemoryRanges")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->InvalidateMappedMemoryRanges;
    }
    if (!strcmp(name, "GetDeviceMemoryCommitment")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceMemoryCommitment;
    }
    if (!strcmp(name, "BindBufferMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->BindBufferMemory;
    }
    if (!strcmp(name, "BindImageMemory")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->BindImageMemory;
    }
    if (!strcmp(name, "GetBufferMemoryRequirements")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetBufferMemoryRequirements;
    }
    if (!strcmp(name, "GetImageMemoryRequirements")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetImageMemoryRequirements;
    }
    if (!strcmp(name, "CreateFence")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateFence;
    }
    if (!strcmp(name, "DestroyFence")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyFence;
    }
    if (!strcmp(name, "ResetFences")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetFences;
    }
    if (!strcmp(name, "GetFenceStatus")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetFenceStatus;
    }
    if (!strcmp(name, "WaitForFences")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->WaitForFences;
    }
    if (!strcmp(name, "CreateSemaphore")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateSemaphore;
    }
    if (!strcmp(name, "DestroySemaphore")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroySemaphore;
    }
    if (!strcmp(name, "CreateEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateEvent;
    }
    if (!strcmp(name, "DestroyEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyEvent;
    }
    if (!strcmp(name, "GetEventStatus")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetEventStatus;
    }
    if (!strcmp(name, "SetEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->SetEvent;
    }
    if (!strcmp(name, "ResetEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetEvent;
    }
    if (!strcmp(name, "CreateQueryPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateQueryPool;
    }
    if (!strcmp(name, "GetQueryPoolResults")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetQueryPoolResults;
    }
    if (!strcmp(name, "CreateBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateBuffer;
    }
    if (!strcmp(name, "DestroyBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyBuffer;
    }
    if (!strcmp(name, "CreateBufferView")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateBufferView;
    }
    if (!strcmp(name, "DestroyBufferView")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyBufferView;
    }
    if (!strcmp(name, "CreateImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateImage;
    }
    if (!strcmp(name, "DestroyImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyImage;
    }
    if (!strcmp(name, "GetImageSubresourceLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetImageSubresourceLayout;
    }
    if (!strcmp(name, "CreateImageView")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateImageView;
    }
    if (!strcmp(name, "DestroyImageView")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyImageView;
    }
    if (!strcmp(name, "CreatePipelineCache")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreatePipelineCache;
    }
    if (!strcmp(name, "DestroyPipelineCache")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyPipelineCache;
    }
    if (!strcmp(name, "CreateGraphicsPipelines")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateGraphicsPipelines;
    }
    if (!strcmp(name, "CreateComputePipelines")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateComputePipelines;
    }
    if (!strcmp(name, "DestroyPipeline")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyPipeline;
    }
    if (!strcmp(name, "CreatePipelineLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreatePipelineLayout;
    }
    if (!strcmp(name, "DestroyPipelineLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyPipelineLayout;
    }
    if (!strcmp(name, "CreateSampler")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateSampler;
    }
    if (!strcmp(name, "DestroySampler")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroySampler;
    }
    if (!strcmp(name, "CreateDescriptorSetLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateDescriptorSetLayout;
    }
    if (!strcmp(name, "DestroyDescriptorSetLayout")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyDescriptorSetLayout;
    }
    if (!strcmp(name, "CreateDescriptorPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateDescriptorPool;
    }
    if (!strcmp(name, "ResetDescriptorPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetDescriptorPool;
    }
    if (!strcmp(name, "AllocateDescriptorSets")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->AllocateDescriptorSets;
    }
    if (!strcmp(name, "FreeDescriptorSets")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->FreeDescriptorSets;
    }
    if (!strcmp(name, "UpdateDescriptorSets")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->UpdateDescriptorSets;
    }
    if (!strcmp(name, "CreateFramebuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateFramebuffer;
    }
    if (!strcmp(name, "DestroyFramebuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyFramebuffer;
    }
    if (!strcmp(name, "CreateRenderPass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateRenderPass;
    }
    if (!strcmp(name, "DestroyRenderPass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroyRenderPass;
    }
    if (!strcmp(name, "GetRenderAreaGranularity")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetRenderAreaGranularity;
    }
    if (!strcmp(name, "CreateCommandPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateCommandPool;
    }
    if (!strcmp(name, "ResetCommandPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetCommandPool;
    }
    if (!strcmp(name, "AllocateCommandBuffers")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->AllocateCommandBuffers;
    }
    if (!strcmp(name, "FreeCommandBuffers")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->FreeCommandBuffers;
    }
    if (!strcmp(name, "BeginCommandBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->BeginCommandBuffer;
    }
    if (!strcmp(name, "EndCommandBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->EndCommandBuffer;
    }
    if (!strcmp(name, "ResetCommandBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetCommandBuffer;
    }
    if (!strcmp(name, "CmdBindPipeline")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBindPipeline;
    }
    if (!strcmp(name, "CmdSetViewport")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetViewport;
    }
    if (!strcmp(name, "CmdSetScissor")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetScissor;
    }
    if (!strcmp(name, "CmdSetLineWidth")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetLineWidth;
    }
    if (!strcmp(name, "CmdSetDepthBias")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetDepthBias;
    }
    if (!strcmp(name, "CmdSetBlendConstants")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetBlendConstants;
    }
    if (!strcmp(name, "CmdSetDepthBounds")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetDepthBounds;
    }
    if (!strcmp(name, "CmdSetStencilCompareMask")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetStencilCompareMask;
    }
    if (!strcmp(name, "CmdSetStencilWriteMask")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetStencilWriteMask;
    }
    if (!strcmp(name, "CmdSetStencilReference")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetStencilReference;
    }
    if (!strcmp(name, "CmdBindDescriptorSets")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBindDescriptorSets;
    }
    if (!strcmp(name, "CmdBindIndexBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBindIndexBuffer;
    }
    if (!strcmp(name, "CmdBindVertexBuffers")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBindVertexBuffers;
    }
    if (!strcmp(name, "CmdDraw")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDraw;
    }
    if (!strcmp(name, "CmdDrawIndexed")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDrawIndexed;
    }
    if (!strcmp(name, "CmdDrawIndirect")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDrawIndirect;
    }
    if (!strcmp(name, "CmdDrawIndexedIndirect")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDrawIndexedIndirect;
    }
    if (!strcmp(name, "CmdDispatch")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDispatch;
    }
    if (!strcmp(name, "CmdDispatchIndirect")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDispatchIndirect;
    }
    if (!strcmp(name, "CmdCopyBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyBuffer;
    }
    if (!strcmp(name, "CmdCopyImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyImage;
    }
    if (!strcmp(name, "CmdBlitImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBlitImage;
    }
    if (!strcmp(name, "CmdCopyBufferToImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyBufferToImage;
    }
    if (!strcmp(name, "CmdCopyImageToBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyImageToBuffer;
    }
    if (!strcmp(name, "CmdUpdateBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdUpdateBuffer;
    }
    if (!strcmp(name, "CmdFillBuffer")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdFillBuffer;
    }
    if (!strcmp(name, "CmdClearColorImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdClearColorImage;
    }
    if (!strcmp(name, "CmdClearDepthStencilImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdClearDepthStencilImage;
    }
    if (!strcmp(name, "CmdClearAttachments")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdClearAttachments;
    }
    if (!strcmp(name, "CmdResolveImage")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdResolveImage;
    }
    if (!strcmp(name, "CmdSetEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetEvent;
    }
    if (!strcmp(name, "CmdResetEvent")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdResetEvent;
    }
    if (!strcmp(name, "CmdWaitEvents")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdWaitEvents;
    }
    if (!strcmp(name, "CmdPipelineBarrier")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdPipelineBarrier;
    }
    if (!strcmp(name, "CmdBeginQuery")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBeginQuery;
    }
    if (!strcmp(name, "CmdEndQuery")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdEndQuery;
    }
    if (!strcmp(name, "CmdResetQueryPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdResetQueryPool;
    }
    if (!strcmp(name, "CmdWriteTimestamp")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdWriteTimestamp;
    }
    if (!strcmp(name, "CmdCopyQueryPoolResults")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdCopyQueryPoolResults;
    }
    if (!strcmp(name, "CmdPushConstants")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdPushConstants;
    }
    if (!strcmp(name, "CmdBeginRenderPass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBeginRenderPass;
    }
    if (!strcmp(name, "CmdNextSubpass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdNextSubpass;
    }
    if (!strcmp(name, "CmdEndRenderPass")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdEndRenderPass;
    }
    if (!strcmp(name, "CmdExecuteCommands")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdExecuteCommands;
    }
    if (!strcmp(name, "BindBufferMemory2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->BindBufferMemory2;
    }
    if (!strcmp(name, "BindImageMemory2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->BindImageMemory2;
    }
    if (!strcmp(name, "GetDeviceGroupPeerMemoryFeatures")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceGroupPeerMemoryFeatures;
    }
    if (!strcmp(name, "CmdSetDeviceMask")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdSetDeviceMask;
    }
    if (!strcmp(name, "CmdDispatchBase")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDispatchBase;
    }
    if (!strcmp(name, "GetImageMemoryRequirements2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetImageMemoryRequirements2;
    }
    if (!strcmp(name, "GetBufferMemoryRequirements2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetBufferMemoryRequirements2;
    }
    if (!strcmp(name, "GetDeviceQueue2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceQueue2;
    }
    if (!strcmp(name, "CreateSamplerYcbcrConversion")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateSamplerYcbcrConversion;
    }
    if (!strcmp(name, "DestroySamplerYcbcrConversion")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->DestroySamplerYcbcrConversion;
    }
    if (!strcmp(name, "GetDescriptorSetLayoutSupport")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDescriptorSetLayoutSupport;
    }
    if (!strcmp(name, "CmdDrawIndirectCount")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDrawIndirectCount;
    }
    if (!strcmp(name, "CmdDrawIndexedIndirectCount")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdDrawIndexedIndirectCount;
    }
    if (!strcmp(name, "CreateRenderPass2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CreateRenderPass2;
    }
    if (!strcmp(name, "CmdBeginRenderPass2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdBeginRenderPass2;
    }
    if (!strcmp(name, "CmdNextSubpass2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdNextSubpass2;
    }
    if (!strcmp(name, "CmdEndRenderPass2")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->CmdEndRenderPass2;
    }
    if (!strcmp(name, "ResetQueryPool")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->ResetQueryPool;
    }
    if (!strcmp(name, "GetSemaphoreCounterValue")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetSemaphoreCounterValue;
    }
    if (!strcmp(name, "WaitSemaphores")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->WaitSemaphores;
    }
    if (!strcmp(name, "SignalSemaphore")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->SignalSemaphore;
    }
    if (!strcmp(name, "GetBufferDeviceAddress")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetBufferDeviceAddress;
    }
    if (!strcmp(name, "GetBufferOpaqueCaptureAddress")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetBufferOpaqueCaptureAddress;
    }
    if (!strcmp(name, "GetDeviceMemoryOpaqueCaptureAddress")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetDeviceMemoryOpaqueCaptureAddress;
    }
    if (!strcmp(name, "GetCommandPoolMemoryConsumption")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetCommandPoolMemoryConsumption;
    }
    if (!strcmp(name, "GetFaultData")) {
        if (dev->should_ignore_device_commands_from_newer_version && api_version < VK_API_VERSION_1_0) return NULL;
        return (void *)table->GetFaultData;
    }

    // ---- VK_KHR_swapchain extension commands
    if (!strcmp(name, "CreateSwapchainKHR")) return (void *)table->CreateSwapchainKHR;
    if (!strcmp(name, "GetSwapchainImagesKHR")) return (void *)table->GetSwapchainImagesKHR;
    if (!strcmp(name, "AcquireNextImageKHR")) return (void *)table->AcquireNextImageKHR;
    if (!strcmp(name, "QueuePresentKHR")) return (void *)table->QueuePresentKHR;
    if (!strcmp(name, "GetDeviceGroupPresentCapabilitiesKHR")) return (void *)table->GetDeviceGroupPresentCapabilitiesKHR;
    if (!strcmp(name, "GetDeviceGroupSurfacePresentModesKHR")) return (void *)table->GetDeviceGroupSurfacePresentModesKHR;
    if (!strcmp(name, "AcquireNextImage2KHR")) return (void *)table->AcquireNextImage2KHR;

    // ---- VK_KHR_display_swapchain extension commands
    if (!strcmp(name, "CreateSharedSwapchainsKHR")) return (void *)table->CreateSharedSwapchainsKHR;

    // ---- VK_KHR_external_memory_fd extension commands
    if (!strcmp(name, "GetMemoryFdKHR")) return (void *)table->GetMemoryFdKHR;
    if (!strcmp(name, "GetMemoryFdPropertiesKHR")) return (void *)table->GetMemoryFdPropertiesKHR;

    // ---- VK_KHR_external_semaphore_fd extension commands
    if (!strcmp(name, "ImportSemaphoreFdKHR")) return (void *)table->ImportSemaphoreFdKHR;
    if (!strcmp(name, "GetSemaphoreFdKHR")) return (void *)table->GetSemaphoreFdKHR;

    // ---- VK_KHR_shared_presentable_image extension commands
    if (!strcmp(name, "GetSwapchainStatusKHR")) return (void *)table->GetSwapchainStatusKHR;

    // ---- VK_KHR_external_fence_fd extension commands
    if (!strcmp(name, "ImportFenceFdKHR")) return (void *)table->ImportFenceFdKHR;
    if (!strcmp(name, "GetFenceFdKHR")) return (void *)table->GetFenceFdKHR;

    // ---- VK_KHR_performance_query extension commands
    if (!strcmp(name, "AcquireProfilingLockKHR")) return (void *)table->AcquireProfilingLockKHR;
    if (!strcmp(name, "ReleaseProfilingLockKHR")) return (void *)table->ReleaseProfilingLockKHR;

    // ---- VK_KHR_fragment_shading_rate extension commands
    if (!strcmp(name, "CmdSetFragmentShadingRateKHR")) return (void *)table->CmdSetFragmentShadingRateKHR;

    // ---- VK_KHR_object_refresh extension commands
    if (!strcmp(name, "CmdRefreshObjectsKHR")) return (void *)table->CmdRefreshObjectsKHR;

    // ---- VK_KHR_synchronization2 extension commands
    if (!strcmp(name, "CmdSetEvent2KHR")) return (void *)table->CmdSetEvent2KHR;
    if (!strcmp(name, "CmdResetEvent2KHR")) return (void *)table->CmdResetEvent2KHR;
    if (!strcmp(name, "CmdWaitEvents2KHR")) return (void *)table->CmdWaitEvents2KHR;
    if (!strcmp(name, "CmdPipelineBarrier2KHR")) return (void *)table->CmdPipelineBarrier2KHR;
    if (!strcmp(name, "CmdWriteTimestamp2KHR")) return (void *)table->CmdWriteTimestamp2KHR;
    if (!strcmp(name, "QueueSubmit2KHR")) return (void *)table->QueueSubmit2KHR;
    if (!strcmp(name, "CmdWriteBufferMarker2AMD")) return (void *)table->CmdWriteBufferMarker2AMD;
    if (!strcmp(name, "GetQueueCheckpointData2NV")) return (void *)table->GetQueueCheckpointData2NV;

    // ---- VK_KHR_copy_commands2 extension commands
    if (!strcmp(name, "CmdCopyBuffer2KHR")) return (void *)table->CmdCopyBuffer2KHR;
    if (!strcmp(name, "CmdCopyImage2KHR")) return (void *)table->CmdCopyImage2KHR;
    if (!strcmp(name, "CmdCopyBufferToImage2KHR")) return (void *)table->CmdCopyBufferToImage2KHR;
    if (!strcmp(name, "CmdCopyImageToBuffer2KHR")) return (void *)table->CmdCopyImageToBuffer2KHR;
    if (!strcmp(name, "CmdBlitImage2KHR")) return (void *)table->CmdBlitImage2KHR;
    if (!strcmp(name, "CmdResolveImage2KHR")) return (void *)table->CmdResolveImage2KHR;

    // ---- VK_EXT_display_control extension commands
    if (!strcmp(name, "DisplayPowerControlEXT")) return (void *)table->DisplayPowerControlEXT;
    if (!strcmp(name, "RegisterDeviceEventEXT")) return (void *)table->RegisterDeviceEventEXT;
    if (!strcmp(name, "RegisterDisplayEventEXT")) return (void *)table->RegisterDisplayEventEXT;
    if (!strcmp(name, "GetSwapchainCounterEXT")) return (void *)table->GetSwapchainCounterEXT;

    // ---- VK_EXT_discard_rectangles extension commands
    if (!strcmp(name, "CmdSetDiscardRectangleEXT")) return (void *)table->CmdSetDiscardRectangleEXT;
    if (!strcmp(name, "CmdSetDiscardRectangleEnableEXT")) return (void *)table->CmdSetDiscardRectangleEnableEXT;
    if (!strcmp(name, "CmdSetDiscardRectangleModeEXT")) return (void *)table->CmdSetDiscardRectangleModeEXT;

    // ---- VK_EXT_hdr_metadata extension commands
    if (!strcmp(name, "SetHdrMetadataEXT")) return (void *)table->SetHdrMetadataEXT;

    // ---- VK_EXT_debug_utils extension commands
    if (!strcmp(name, "SetDebugUtilsObjectNameEXT")) return dev->layer_extensions.ext_debug_utils_enabled ? (void *)SetDebugUtilsObjectNameEXT : NULL;
    if (!strcmp(name, "SetDebugUtilsObjectTagEXT")) return dev->layer_extensions.ext_debug_utils_enabled ? (void *)SetDebugUtilsObjectTagEXT : NULL;
    if (!strcmp(name, "QueueBeginDebugUtilsLabelEXT")) return (void *)table->QueueBeginDebugUtilsLabelEXT;
    if (!strcmp(name, "QueueEndDebugUtilsLabelEXT")) return (void *)table->QueueEndDebugUtilsLabelEXT;
    if (!strcmp(name, "QueueInsertDebugUtilsLabelEXT")) return (void *)table->QueueInsertDebugUtilsLabelEXT;
    if (!strcmp(name, "CmdBeginDebugUtilsLabelEXT")) return (void *)table->CmdBeginDebugUtilsLabelEXT;
    if (!strcmp(name, "CmdEndDebugUtilsLabelEXT")) return (void *)table->CmdEndDebugUtilsLabelEXT;
    if (!strcmp(name, "CmdInsertDebugUtilsLabelEXT")) return (void *)table->CmdInsertDebugUtilsLabelEXT;

    // ---- VK_EXT_sample_locations extension commands
    if (!strcmp(name, "CmdSetSampleLocationsEXT")) return (void *)table->CmdSetSampleLocationsEXT;

    // ---- VK_EXT_image_drm_format_modifier extension commands
    if (!strcmp(name, "GetImageDrmFormatModifierPropertiesEXT")) return (void *)table->GetImageDrmFormatModifierPropertiesEXT;

    // ---- VK_EXT_external_memory_host extension commands
    if (!strcmp(name, "GetMemoryHostPointerPropertiesEXT")) return (void *)table->GetMemoryHostPointerPropertiesEXT;

    // ---- VK_EXT_calibrated_timestamps extension commands
    if (!strcmp(name, "GetCalibratedTimestampsEXT")) return (void *)table->GetCalibratedTimestampsEXT;

    // ---- VK_EXT_line_rasterization extension commands
    if (!strcmp(name, "CmdSetLineStippleEXT")) return (void *)table->CmdSetLineStippleEXT;

    // ---- VK_EXT_extended_dynamic_state extension commands
    if (!strcmp(name, "CmdSetCullModeEXT")) return (void *)table->CmdSetCullModeEXT;
    if (!strcmp(name, "CmdSetFrontFaceEXT")) return (void *)table->CmdSetFrontFaceEXT;
    if (!strcmp(name, "CmdSetPrimitiveTopologyEXT")) return (void *)table->CmdSetPrimitiveTopologyEXT;
    if (!strcmp(name, "CmdSetViewportWithCountEXT")) return (void *)table->CmdSetViewportWithCountEXT;
    if (!strcmp(name, "CmdSetScissorWithCountEXT")) return (void *)table->CmdSetScissorWithCountEXT;
    if (!strcmp(name, "CmdBindVertexBuffers2EXT")) return (void *)table->CmdBindVertexBuffers2EXT;
    if (!strcmp(name, "CmdSetDepthTestEnableEXT")) return (void *)table->CmdSetDepthTestEnableEXT;
    if (!strcmp(name, "CmdSetDepthWriteEnableEXT")) return (void *)table->CmdSetDepthWriteEnableEXT;
    if (!strcmp(name, "CmdSetDepthCompareOpEXT")) return (void *)table->CmdSetDepthCompareOpEXT;
    if (!strcmp(name, "CmdSetDepthBoundsTestEnableEXT")) return (void *)table->CmdSetDepthBoundsTestEnableEXT;
    if (!strcmp(name, "CmdSetStencilTestEnableEXT")) return (void *)table->CmdSetStencilTestEnableEXT;
    if (!strcmp(name, "CmdSetStencilOpEXT")) return (void *)table->CmdSetStencilOpEXT;

    // ---- VK_EXT_vertex_input_dynamic_state extension commands
    if (!strcmp(name, "CmdSetVertexInputEXT")) return (void *)table->CmdSetVertexInputEXT;

    // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "GetFenceSciSyncFenceNV")) return (void *)table->GetFenceSciSyncFenceNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "GetFenceSciSyncObjNV")) return (void *)table->GetFenceSciSyncObjNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "ImportFenceSciSyncFenceNV")) return (void *)table->ImportFenceSciSyncFenceNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "ImportFenceSciSyncObjNV")) return (void *)table->ImportFenceSciSyncObjNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "GetSemaphoreSciSyncObjNV")) return (void *)table->GetSemaphoreSciSyncObjNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "ImportSemaphoreSciSyncObjNV")) return (void *)table->ImportSemaphoreSciSyncObjNV;
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "GetMemorySciBufNV")) return (void *)table->GetMemorySciBufNV;
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_EXT_extended_dynamic_state2 extension commands
    if (!strcmp(name, "CmdSetPatchControlPointsEXT")) return (void *)table->CmdSetPatchControlPointsEXT;
    if (!strcmp(name, "CmdSetRasterizerDiscardEnableEXT")) return (void *)table->CmdSetRasterizerDiscardEnableEXT;
    if (!strcmp(name, "CmdSetDepthBiasEnableEXT")) return (void *)table->CmdSetDepthBiasEnableEXT;
    if (!strcmp(name, "CmdSetLogicOpEXT")) return (void *)table->CmdSetLogicOpEXT;
    if (!strcmp(name, "CmdSetPrimitiveRestartEnableEXT")) return (void *)table->CmdSetPrimitiveRestartEnableEXT;

    // ---- VK_EXT_color_write_enable extension commands
    if (!strcmp(name, "CmdSetColorWriteEnableEXT")) return (void *)table->CmdSetColorWriteEnableEXT;

    // ---- VK_NV_external_sci_sync2 extension commands
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "CreateSemaphoreSciSyncPoolNV")) return (void *)table->CreateSemaphoreSciSyncPoolNV;
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_QNX_external_memory_screen_buffer extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    if (!strcmp(name, "GetScreenBufferPropertiesQNX")) return (void *)table->GetScreenBufferPropertiesQNX;
#endif // VK_USE_PLATFORM_SCREEN_QNX

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

    // ---- Core SC 1_0 commands
    if (!strcmp(name, "DestroyInstance")) return (void *)table->DestroyInstance;
    if (!strcmp(name, "EnumeratePhysicalDevices")) return (void *)table->EnumeratePhysicalDevices;
    if (!strcmp(name, "GetPhysicalDeviceFeatures")) return (void *)table->GetPhysicalDeviceFeatures;
    if (!strcmp(name, "GetPhysicalDeviceFormatProperties")) return (void *)table->GetPhysicalDeviceFormatProperties;
    if (!strcmp(name, "GetPhysicalDeviceImageFormatProperties")) return (void *)table->GetPhysicalDeviceImageFormatProperties;
    if (!strcmp(name, "GetPhysicalDeviceProperties")) return (void *)table->GetPhysicalDeviceProperties;
    if (!strcmp(name, "GetPhysicalDeviceQueueFamilyProperties")) return (void *)table->GetPhysicalDeviceQueueFamilyProperties;
    if (!strcmp(name, "GetPhysicalDeviceMemoryProperties")) return (void *)table->GetPhysicalDeviceMemoryProperties;
    if (!strcmp(name, "GetInstanceProcAddr")) return (void *)table->GetInstanceProcAddr;
    if (!strcmp(name, "EnumerateDeviceExtensionProperties")) return (void *)table->EnumerateDeviceExtensionProperties;
    if (!strcmp(name, "EnumerateDeviceLayerProperties")) return (void *)table->EnumerateDeviceLayerProperties;
    if (!strcmp(name, "EnumeratePhysicalDeviceGroups")) return (void *)table->EnumeratePhysicalDeviceGroups;
    if (!strcmp(name, "GetPhysicalDeviceFeatures2")) return (void *)table->GetPhysicalDeviceFeatures2;
    if (!strcmp(name, "GetPhysicalDeviceProperties2")) return (void *)table->GetPhysicalDeviceProperties2;
    if (!strcmp(name, "GetPhysicalDeviceFormatProperties2")) return (void *)table->GetPhysicalDeviceFormatProperties2;
    if (!strcmp(name, "GetPhysicalDeviceImageFormatProperties2")) return (void *)table->GetPhysicalDeviceImageFormatProperties2;
    if (!strcmp(name, "GetPhysicalDeviceQueueFamilyProperties2")) return (void *)table->GetPhysicalDeviceQueueFamilyProperties2;
    if (!strcmp(name, "GetPhysicalDeviceMemoryProperties2")) return (void *)table->GetPhysicalDeviceMemoryProperties2;
    if (!strcmp(name, "GetPhysicalDeviceExternalBufferProperties")) return (void *)table->GetPhysicalDeviceExternalBufferProperties;
    if (!strcmp(name, "GetPhysicalDeviceExternalFenceProperties")) return (void *)table->GetPhysicalDeviceExternalFenceProperties;
    if (!strcmp(name, "GetPhysicalDeviceExternalSemaphoreProperties")) return (void *)table->GetPhysicalDeviceExternalSemaphoreProperties;

    // ---- VK_KHR_surface extension commands
    if (!strcmp(name, "DestroySurfaceKHR")) return (void *)table->DestroySurfaceKHR;
    if (!strcmp(name, "GetPhysicalDeviceSurfaceSupportKHR")) return (void *)table->GetPhysicalDeviceSurfaceSupportKHR;
    if (!strcmp(name, "GetPhysicalDeviceSurfaceCapabilitiesKHR")) return (void *)table->GetPhysicalDeviceSurfaceCapabilitiesKHR;
    if (!strcmp(name, "GetPhysicalDeviceSurfaceFormatsKHR")) return (void *)table->GetPhysicalDeviceSurfaceFormatsKHR;
    if (!strcmp(name, "GetPhysicalDeviceSurfacePresentModesKHR")) return (void *)table->GetPhysicalDeviceSurfacePresentModesKHR;

    // ---- VK_KHR_swapchain extension commands
    if (!strcmp(name, "GetPhysicalDevicePresentRectanglesKHR")) return (void *)table->GetPhysicalDevicePresentRectanglesKHR;

    // ---- VK_KHR_display extension commands
    if (!strcmp(name, "GetPhysicalDeviceDisplayPropertiesKHR")) return (void *)table->GetPhysicalDeviceDisplayPropertiesKHR;
    if (!strcmp(name, "GetPhysicalDeviceDisplayPlanePropertiesKHR")) return (void *)table->GetPhysicalDeviceDisplayPlanePropertiesKHR;
    if (!strcmp(name, "GetDisplayPlaneSupportedDisplaysKHR")) return (void *)table->GetDisplayPlaneSupportedDisplaysKHR;
    if (!strcmp(name, "GetDisplayModePropertiesKHR")) return (void *)table->GetDisplayModePropertiesKHR;
    if (!strcmp(name, "CreateDisplayModeKHR")) return (void *)table->CreateDisplayModeKHR;
    if (!strcmp(name, "GetDisplayPlaneCapabilitiesKHR")) return (void *)table->GetDisplayPlaneCapabilitiesKHR;
    if (!strcmp(name, "CreateDisplayPlaneSurfaceKHR")) return (void *)table->CreateDisplayPlaneSurfaceKHR;

    // ---- VK_KHR_performance_query extension commands
    if (!strcmp(name, "EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR")) return (void *)table->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
    if (!strcmp(name, "GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR")) return (void *)table->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;

    // ---- VK_KHR_get_surface_capabilities2 extension commands
    if (!strcmp(name, "GetPhysicalDeviceSurfaceCapabilities2KHR")) return (void *)table->GetPhysicalDeviceSurfaceCapabilities2KHR;
    if (!strcmp(name, "GetPhysicalDeviceSurfaceFormats2KHR")) return (void *)table->GetPhysicalDeviceSurfaceFormats2KHR;

    // ---- VK_KHR_get_display_properties2 extension commands
    if (!strcmp(name, "GetPhysicalDeviceDisplayProperties2KHR")) return (void *)table->GetPhysicalDeviceDisplayProperties2KHR;
    if (!strcmp(name, "GetPhysicalDeviceDisplayPlaneProperties2KHR")) return (void *)table->GetPhysicalDeviceDisplayPlaneProperties2KHR;
    if (!strcmp(name, "GetDisplayModeProperties2KHR")) return (void *)table->GetDisplayModeProperties2KHR;
    if (!strcmp(name, "GetDisplayPlaneCapabilities2KHR")) return (void *)table->GetDisplayPlaneCapabilities2KHR;

    // ---- VK_KHR_fragment_shading_rate extension commands
    if (!strcmp(name, "GetPhysicalDeviceFragmentShadingRatesKHR")) return (void *)table->GetPhysicalDeviceFragmentShadingRatesKHR;

    // ---- VK_KHR_object_refresh extension commands
    if (!strcmp(name, "GetPhysicalDeviceRefreshableObjectTypesKHR")) return (void *)table->GetPhysicalDeviceRefreshableObjectTypesKHR;

    // ---- VK_EXT_direct_mode_display extension commands
    if (!strcmp(name, "ReleaseDisplayEXT")) return (void *)table->ReleaseDisplayEXT;

    // ---- VK_EXT_display_surface_counter extension commands
    if (!strcmp(name, "GetPhysicalDeviceSurfaceCapabilities2EXT")) return (void *)table->GetPhysicalDeviceSurfaceCapabilities2EXT;

    // ---- VK_EXT_debug_utils extension commands
    if (!strcmp(name, "CreateDebugUtilsMessengerEXT")) return (void *)table->CreateDebugUtilsMessengerEXT;
    if (!strcmp(name, "DestroyDebugUtilsMessengerEXT")) return (void *)table->DestroyDebugUtilsMessengerEXT;
    if (!strcmp(name, "SubmitDebugUtilsMessageEXT")) return (void *)table->SubmitDebugUtilsMessageEXT;

    // ---- VK_EXT_sample_locations extension commands
    if (!strcmp(name, "GetPhysicalDeviceMultisamplePropertiesEXT")) return (void *)table->GetPhysicalDeviceMultisamplePropertiesEXT;

    // ---- VK_EXT_calibrated_timestamps extension commands
    if (!strcmp(name, "GetPhysicalDeviceCalibrateableTimeDomainsEXT")) return (void *)table->GetPhysicalDeviceCalibrateableTimeDomainsEXT;

    // ---- VK_EXT_headless_surface extension commands
    if (!strcmp(name, "CreateHeadlessSurfaceEXT")) return (void *)table->CreateHeadlessSurfaceEXT;

    // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "GetPhysicalDeviceSciSyncAttributesNV")) return (void *)table->GetPhysicalDeviceSciSyncAttributesNV;
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "GetPhysicalDeviceExternalMemorySciBufPropertiesNV")) return (void *)table->GetPhysicalDeviceExternalMemorySciBufPropertiesNV;
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp(name, "GetPhysicalDeviceSciBufAttributesNV")) return (void *)table->GetPhysicalDeviceSciBufAttributesNV;
#endif // VK_USE_PLATFORM_SCI

    *found_name = false;
    return NULL;
}


// ---- VK_KHR_external_memory_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryFdKHR(
    VkDevice                                    device,
    const VkMemoryGetFdInfoKHR*                 pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryFdKHR: Invalid device "
                   "[VUID-vkGetMemoryFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryFdKHR(device, pGetFdInfo, pFd);
}

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryFdPropertiesKHR(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    int                                         fd,
    VkMemoryFdPropertiesKHR*                    pMemoryFdProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryFdPropertiesKHR: Invalid device "
                   "[VUID-vkGetMemoryFdPropertiesKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties);
}


// ---- VK_KHR_external_semaphore_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ImportSemaphoreFdKHR(
    VkDevice                                    device,
    const VkImportSemaphoreFdInfoKHR*           pImportSemaphoreFdInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportSemaphoreFdKHR: Invalid device "
                   "[VUID-vkImportSemaphoreFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSemaphoreFdKHR(
    VkDevice                                    device,
    const VkSemaphoreGetFdInfoKHR*              pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSemaphoreFdKHR: Invalid device "
                   "[VUID-vkGetSemaphoreFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSemaphoreFdKHR(device, pGetFdInfo, pFd);
}


// ---- VK_KHR_shared_presentable_image extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainStatusKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSwapchainStatusKHR: Invalid device "
                   "[VUID-vkGetSwapchainStatusKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSwapchainStatusKHR(device, swapchain);
}


// ---- VK_KHR_external_fence_fd extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL ImportFenceFdKHR(
    VkDevice                                    device,
    const VkImportFenceFdInfoKHR*               pImportFenceFdInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportFenceFdKHR: Invalid device "
                   "[VUID-vkImportFenceFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportFenceFdKHR(device, pImportFenceFdInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL GetFenceFdKHR(
    VkDevice                                    device,
    const VkFenceGetFdInfoKHR*                  pGetFdInfo,
    int*                                        pFd) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetFenceFdKHR: Invalid device "
                   "[VUID-vkGetFenceFdKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR: Invalid physicalDevice "
                   "[VUID-vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkAcquireProfilingLockKHR: Invalid device "
                   "[VUID-vkAcquireProfilingLockKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->AcquireProfilingLockKHR(device, pInfo);
}

VKAPI_ATTR void VKAPI_CALL ReleaseProfilingLockKHR(
    VkDevice                                    device) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkReleaseProfilingLockKHR: Invalid device "
                   "[VUID-vkReleaseProfilingLockKHR-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->ReleaseProfilingLockKHR(device);
}


// ---- VK_KHR_fragment_shading_rate extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceFragmentShadingRatesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pFragmentShadingRateCount,
    VkPhysicalDeviceFragmentShadingRateKHR*     pFragmentShadingRates) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceFragmentShadingRatesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceFragmentShadingRatesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetFragmentShadingRateKHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetFragmentShadingRateKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetFragmentShadingRateKHR(commandBuffer, pFragmentSize, combinerOps);
}


// ---- VK_KHR_object_refresh extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdRefreshObjectsKHR(
    VkCommandBuffer                             commandBuffer,
    const VkRefreshObjectListKHR*               pRefreshObjects) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdRefreshObjectsKHR: Invalid commandBuffer "
                   "[VUID-vkCmdRefreshObjectsKHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdRefreshObjectsKHR(commandBuffer, pRefreshObjects);
}

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceRefreshableObjectTypesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pRefreshableObjectTypeCount,
    VkObjectType*                               pRefreshableObjectTypes) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceRefreshableObjectTypesKHR: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceRefreshableObjectTypesKHR-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetEvent2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdSetEvent2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetEvent2KHR(commandBuffer, event, pDependencyInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdResetEvent2KHR(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags2                       stageMask) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdResetEvent2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdResetEvent2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdResetEvent2KHR(commandBuffer, event, stageMask);
}

VKAPI_ATTR void VKAPI_CALL CmdWaitEvents2KHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    eventCount,
    const VkEvent*                              pEvents,
    const VkDependencyInfo*                     pDependencyInfos) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWaitEvents2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdWaitEvents2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWaitEvents2KHR(commandBuffer, eventCount, pEvents, pDependencyInfos);
}

VKAPI_ATTR void VKAPI_CALL CmdPipelineBarrier2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkDependencyInfo*                     pDependencyInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdPipelineBarrier2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdPipelineBarrier2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdPipelineBarrier2KHR(commandBuffer, pDependencyInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteTimestamp2KHR(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags2                       stage,
    VkQueryPool                                 queryPool,
    uint32_t                                    query) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteTimestamp2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdWriteTimestamp2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteTimestamp2KHR(commandBuffer, stage, queryPool, query);
}

VKAPI_ATTR VkResult VKAPI_CALL QueueSubmit2KHR(
    VkQueue                                     queue,
    uint32_t                                    submitCount,
    const VkSubmitInfo2*                        pSubmits,
    VkFence                                     fence) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueSubmit2KHR: Invalid queue "
                   "[VUID-vkQueueSubmit2KHR-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->QueueSubmit2KHR(queue, submitCount, pSubmits, fence);
}

VKAPI_ATTR void VKAPI_CALL CmdWriteBufferMarker2AMD(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags2                       stage,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdWriteBufferMarker2AMD: Invalid commandBuffer "
                   "[VUID-vkCmdWriteBufferMarker2AMD-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdWriteBufferMarker2AMD(commandBuffer, stage, dstBuffer, dstOffset, marker);
}

VKAPI_ATTR void VKAPI_CALL GetQueueCheckpointData2NV(
    VkQueue                                     queue,
    uint32_t*                                   pCheckpointDataCount,
    VkCheckpointData2NV*                        pCheckpointData) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetQueueCheckpointData2NV: Invalid queue "
                   "[VUID-vkGetQueueCheckpointData2NV-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->GetQueueCheckpointData2NV(queue, pCheckpointDataCount, pCheckpointData);
}


// ---- VK_KHR_copy_commands2 extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdCopyBuffer2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferInfo2*                    pCopyBufferInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyBuffer2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyBuffer2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyBuffer2KHR(commandBuffer, pCopyBufferInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageInfo2*                     pCopyImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyImage2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyImage2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyImage2KHR(commandBuffer, pCopyImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyBufferToImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyBufferToImageInfo2*             pCopyBufferToImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyBufferToImage2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyBufferToImage2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyBufferToImage2KHR(commandBuffer, pCopyBufferToImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdCopyImageToBuffer2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkCopyImageToBufferInfo2*             pCopyImageToBufferInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdCopyImageToBuffer2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdCopyImageToBuffer2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdCopyImageToBuffer2KHR(commandBuffer, pCopyImageToBufferInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdBlitImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkBlitImageInfo2*                     pBlitImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBlitImage2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdBlitImage2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBlitImage2KHR(commandBuffer, pBlitImageInfo);
}

VKAPI_ATTR void VKAPI_CALL CmdResolveImage2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkResolveImageInfo2*                  pResolveImageInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdResolveImage2KHR: Invalid commandBuffer "
                   "[VUID-vkCmdResolveImage2KHR-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdResolveImage2KHR(commandBuffer, pResolveImageInfo);
}


// ---- VK_EXT_display_control extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL DisplayPowerControlEXT(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayPowerInfoEXT*                pDisplayPowerInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkDisplayPowerControlEXT: Invalid device "
                   "[VUID-vkDisplayPowerControlEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->DisplayPowerControlEXT(device, display, pDisplayPowerInfo);
}

VKAPI_ATTR VkResult VKAPI_CALL RegisterDeviceEventEXT(
    VkDevice                                    device,
    const VkDeviceEventInfoEXT*                 pDeviceEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkRegisterDeviceEventEXT: Invalid device "
                   "[VUID-vkRegisterDeviceEventEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->RegisterDeviceEventEXT(device, pDeviceEventInfo, pAllocator, pFence);
}

VKAPI_ATTR VkResult VKAPI_CALL RegisterDisplayEventEXT(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayEventInfoEXT*                pDisplayEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkRegisterDisplayEventEXT: Invalid device "
                   "[VUID-vkRegisterDisplayEventEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->RegisterDisplayEventEXT(device, display, pDisplayEventInfo, pAllocator, pFence);
}

VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainCounterEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkSurfaceCounterFlagBitsEXT                 counter,
    uint64_t*                                   pCounterValue) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSwapchainCounterEXT: Invalid device "
                   "[VUID-vkGetSwapchainCounterEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSwapchainCounterEXT(device, swapchain, counter, pCounterValue);
}


// ---- VK_EXT_discard_rectangles extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstDiscardRectangle,
    uint32_t                                    discardRectangleCount,
    const VkRect2D*                             pDiscardRectangles) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDiscardRectangleEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDiscardRectangleEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    discardRectangleEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDiscardRectangleEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDiscardRectangleEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDiscardRectangleEnableEXT(commandBuffer, discardRectangleEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDiscardRectangleModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkDiscardRectangleModeEXT                   discardRectangleMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDiscardRectangleModeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDiscardRectangleModeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDiscardRectangleModeEXT(commandBuffer, discardRectangleMode);
}


// ---- VK_EXT_hdr_metadata extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL SetHdrMetadataEXT(
    VkDevice                                    device,
    uint32_t                                    swapchainCount,
    const VkSwapchainKHR*                       pSwapchains,
    const VkHdrMetadataEXT*                     pMetadata) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetHdrMetadataEXT: Invalid device "
                   "[VUID-vkSetHdrMetadataEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->SetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata);
}


// ---- VK_EXT_debug_utils extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL SetDebugUtilsObjectNameEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetDebugUtilsObjectNameEXT: Invalid device "
                   "[VUID-vkSetDebugUtilsObjectNameEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    uint32_t icd_index = 0;
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev, &icd_index);
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
            VkIcdSurface *icd_surface = (VkIcdSurface *)(uintptr_t)pNameInfo->objectHandle;
            if (NULL != icd_surface->real_icd_surfaces) {
                local_name_info.objectHandle = (uint64_t)icd_surface->real_icd_surfaces[icd_index];
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkSetDebugUtilsObjectTagEXT: Invalid device "
                   "[VUID-vkSetDebugUtilsObjectTagEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    uint32_t icd_index = 0;
    struct loader_device *dev;
    struct loader_icd_term *icd_term = loader_get_icd_and_device(device, &dev, &icd_index);
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
            VkIcdSurface *icd_surface = (VkIcdSurface *)(uintptr_t)pTagInfo->objectHandle;
            if (NULL != icd_surface->real_icd_surfaces) {
                local_tag_info.objectHandle = (uint64_t)icd_surface->real_icd_surfaces[icd_index];
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueBeginDebugUtilsLabelEXT: Invalid queue "
                   "[VUID-vkQueueBeginDebugUtilsLabelEXT-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueEndDebugUtilsLabelEXT: Invalid queue "
                   "[VUID-vkQueueEndDebugUtilsLabelEXT-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(queue);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkQueueInsertDebugUtilsLabelEXT: Invalid queue "
                   "[VUID-vkQueueInsertDebugUtilsLabelEXT-queue-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBeginDebugUtilsLabelEXT: Invalid commandBuffer "
                   "[VUID-vkCmdBeginDebugUtilsLabelEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdEndDebugUtilsLabelEXT: Invalid commandBuffer "
                   "[VUID-vkCmdEndDebugUtilsLabelEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdInsertDebugUtilsLabelEXT: Invalid commandBuffer "
                   "[VUID-vkCmdInsertDebugUtilsLabelEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetSampleLocationsEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetSampleLocationsEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo);
}

VKAPI_ATTR void VKAPI_CALL GetPhysicalDeviceMultisamplePropertiesEXT(
    VkPhysicalDevice                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    VkMultisamplePropertiesEXT*                 pMultisampleProperties) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceMultisamplePropertiesEXT: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceMultisamplePropertiesEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetImageDrmFormatModifierPropertiesEXT: Invalid device "
                   "[VUID-vkGetImageDrmFormatModifierPropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetImageDrmFormatModifierPropertiesEXT(device, image, pProperties);
}


// ---- VK_EXT_external_memory_host extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetMemoryHostPointerPropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    const void*                                 pHostPointer,
    VkMemoryHostPointerPropertiesEXT*           pMemoryHostPointerProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemoryHostPointerPropertiesEXT: Invalid device "
                   "[VUID-vkGetMemoryHostPointerPropertiesEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties);
}


// ---- VK_EXT_calibrated_timestamps extension trampoline/terminators

VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceCalibrateableTimeDomainsEXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainEXT*                            pTimeDomains) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceCalibrateableTimeDomainsEXT-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceCalibrateableTimeDomainsEXT(unwrapped_phys_dev, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL terminator_GetPhysicalDeviceCalibrateableTimeDomainsEXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainEXT*                            pTimeDomains) {
    struct loader_physical_device_term *phys_dev_term = (struct loader_physical_device_term *)physicalDevice;
    struct loader_icd_term *icd_term = phys_dev_term->this_icd_term;
    if (NULL == icd_term->dispatch.GetPhysicalDeviceCalibrateableTimeDomainsEXT) {
        loader_log(icd_term->this_instance, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT, 0,
                   "ICD associated with VkPhysicalDevice does not support GetPhysicalDeviceCalibrateableTimeDomainsEXT");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return icd_term->dispatch.GetPhysicalDeviceCalibrateableTimeDomainsEXT(phys_dev_term->phys_dev, pTimeDomainCount, pTimeDomains);
}

VKAPI_ATTR VkResult VKAPI_CALL GetCalibratedTimestampsEXT(
    VkDevice                                    device,
    uint32_t                                    timestampCount,
    const VkCalibratedTimestampInfoEXT*         pTimestampInfos,
    uint64_t*                                   pTimestamps,
    uint64_t*                                   pMaxDeviation) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetCalibratedTimestampsEXT: Invalid device "
                   "[VUID-vkGetCalibratedTimestampsEXT-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetCalibratedTimestampsEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation);
}


// ---- VK_EXT_line_rasterization extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetLineStippleEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    lineStippleFactor,
    uint16_t                                    lineStipplePattern) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetLineStippleEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetLineStippleEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern);
}


// ---- VK_EXT_extended_dynamic_state extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetCullModeEXT(
    VkCommandBuffer                             commandBuffer,
    VkCullModeFlags                             cullMode) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetCullModeEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetCullModeEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetCullModeEXT(commandBuffer, cullMode);
}

VKAPI_ATTR void VKAPI_CALL CmdSetFrontFaceEXT(
    VkCommandBuffer                             commandBuffer,
    VkFrontFace                                 frontFace) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetFrontFaceEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetFrontFaceEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetFrontFaceEXT(commandBuffer, frontFace);
}

VKAPI_ATTR void VKAPI_CALL CmdSetPrimitiveTopologyEXT(
    VkCommandBuffer                             commandBuffer,
    VkPrimitiveTopology                         primitiveTopology) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPrimitiveTopologyEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetPrimitiveTopologyEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetPrimitiveTopologyEXT(commandBuffer, primitiveTopology);
}

VKAPI_ATTR void VKAPI_CALL CmdSetViewportWithCountEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetViewportWithCountEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetViewportWithCountEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetViewportWithCountEXT(commandBuffer, viewportCount, pViewports);
}

VKAPI_ATTR void VKAPI_CALL CmdSetScissorWithCountEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetScissorWithCountEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetScissorWithCountEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdBindVertexBuffers2EXT: Invalid commandBuffer "
                   "[VUID-vkCmdBindVertexBuffers2EXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdBindVertexBuffers2EXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes, pStrides);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthTestEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthTestEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthTestEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthTestEnableEXT(commandBuffer, depthTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthWriteEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthWriteEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthWriteEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthWriteEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthWriteEnableEXT(commandBuffer, depthWriteEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthCompareOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkCompareOp                                 depthCompareOp) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthCompareOpEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthCompareOpEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthCompareOpEXT(commandBuffer, depthCompareOp);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthBoundsTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBoundsTestEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthBoundsTestEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthBoundsTestEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthBoundsTestEnableEXT(commandBuffer, depthBoundsTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetStencilTestEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    stencilTestEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetStencilTestEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetStencilTestEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetStencilTestEnableEXT(commandBuffer, stencilTestEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetStencilOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    VkStencilOp                                 failOp,
    VkStencilOp                                 passOp,
    VkStencilOp                                 depthFailOp,
    VkCompareOp                                 compareOp) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetStencilOpEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetStencilOpEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetStencilOpEXT(commandBuffer, faceMask, failOp, passOp, depthFailOp, compareOp);
}


// ---- VK_EXT_vertex_input_dynamic_state extension trampoline/terminators

VKAPI_ATTR void VKAPI_CALL CmdSetVertexInputEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    vertexBindingDescriptionCount,
    const VkVertexInputBindingDescription2EXT*  pVertexBindingDescriptions,
    uint32_t                                    vertexAttributeDescriptionCount,
    const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetVertexInputEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetVertexInputEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetVertexInputEXT(commandBuffer, vertexBindingDescriptionCount, pVertexBindingDescriptions, vertexAttributeDescriptionCount, pVertexAttributeDescriptions);
}


// ---- VK_NV_external_sci_sync extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetFenceSciSyncFenceNV(
    VkDevice                                    device,
    const VkFenceGetSciSyncInfoNV*              pGetSciSyncHandleInfo,
    void*                                       pHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetFenceSciSyncFenceNV: Invalid device "
                   "[VUID-vkGetFenceSciSyncFenceNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetFenceSciSyncFenceNV(device, pGetSciSyncHandleInfo, pHandle);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetFenceSciSyncObjNV(
    VkDevice                                    device,
    const VkFenceGetSciSyncInfoNV*              pGetSciSyncHandleInfo,
    void*                                       pHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetFenceSciSyncObjNV: Invalid device "
                   "[VUID-vkGetFenceSciSyncObjNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetFenceSciSyncObjNV(device, pGetSciSyncHandleInfo, pHandle);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL ImportFenceSciSyncFenceNV(
    VkDevice                                    device,
    const VkImportFenceSciSyncInfoNV*           pImportFenceSciSyncInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportFenceSciSyncFenceNV: Invalid device "
                   "[VUID-vkImportFenceSciSyncFenceNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportFenceSciSyncFenceNV(device, pImportFenceSciSyncInfo);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL ImportFenceSciSyncObjNV(
    VkDevice                                    device,
    const VkImportFenceSciSyncInfoNV*           pImportFenceSciSyncInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportFenceSciSyncObjNV: Invalid device "
                   "[VUID-vkImportFenceSciSyncObjNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportFenceSciSyncObjNV(device, pImportFenceSciSyncInfo);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSciSyncAttributesNV(
    VkPhysicalDevice                            physicalDevice,
    const VkSciSyncAttributesInfoNV*            pSciSyncAttributesInfo,
    NvSciSyncAttrList                           pAttributes) {
    const VkLayerInstanceDispatchTable *disp;
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSciSyncAttributesNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSciSyncAttributesNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetSemaphoreSciSyncObjNV: Invalid device "
                   "[VUID-vkGetSemaphoreSciSyncObjNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetSemaphoreSciSyncObjNV(device, pGetSciSyncInfo, pHandle);
}

#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL ImportSemaphoreSciSyncObjNV(
    VkDevice                                    device,
    const VkImportSemaphoreSciSyncInfoNV*       pImportSemaphoreSciSyncInfo) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkImportSemaphoreSciSyncObjNV: Invalid device "
                   "[VUID-vkImportSemaphoreSciSyncObjNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->ImportSemaphoreSciSyncObjNV(device, pImportSemaphoreSciSyncInfo);
}

#endif // VK_USE_PLATFORM_SCI

// ---- VK_NV_external_memory_sci_buf extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL GetMemorySciBufNV(
    VkDevice                                    device,
    const VkMemoryGetSciBufInfoNV*              pGetSciBufInfo,
    NvSciBufObj*                                pHandle) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetMemorySciBufNV: Invalid device "
                   "[VUID-vkGetMemorySciBufNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice);
    if (VK_NULL_HANDLE == unwrapped_phys_dev) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetPhysicalDeviceSciBufAttributesNV: Invalid physicalDevice "
                   "[VUID-vkGetPhysicalDeviceSciBufAttributesNV-physicalDevice-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
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
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPatchControlPointsEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetPatchControlPointsEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetPatchControlPointsEXT(commandBuffer, patchControlPoints);
}

VKAPI_ATTR void VKAPI_CALL CmdSetRasterizerDiscardEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    rasterizerDiscardEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetRasterizerDiscardEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetRasterizerDiscardEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetRasterizerDiscardEnableEXT(commandBuffer, rasterizerDiscardEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetDepthBiasEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    depthBiasEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetDepthBiasEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetDepthBiasEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetDepthBiasEnableEXT(commandBuffer, depthBiasEnable);
}

VKAPI_ATTR void VKAPI_CALL CmdSetLogicOpEXT(
    VkCommandBuffer                             commandBuffer,
    VkLogicOp                                   logicOp) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetLogicOpEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetLogicOpEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetLogicOpEXT(commandBuffer, logicOp);
}

VKAPI_ATTR void VKAPI_CALL CmdSetPrimitiveRestartEnableEXT(
    VkCommandBuffer                             commandBuffer,
    VkBool32                                    primitiveRestartEnable) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetPrimitiveRestartEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetPrimitiveRestartEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetPrimitiveRestartEnableEXT(commandBuffer, primitiveRestartEnable);
}


// ---- VK_EXT_color_write_enable extension trampoline/terminators

VKAPI_ATTR void                                    VKAPI_CALL CmdSetColorWriteEnableEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    attachmentCount,
    const VkBool32*                             pColorWriteEnables) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(commandBuffer);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCmdSetColorWriteEnableEXT: Invalid commandBuffer "
                   "[VUID-vkCmdSetColorWriteEnableEXT-commandBuffer-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    disp->CmdSetColorWriteEnableEXT(commandBuffer, attachmentCount, pColorWriteEnables);
}


// ---- VK_NV_external_sci_sync2 extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCI)
VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphoreSciSyncPoolNV(
    VkDevice                                    device,
    const VkSemaphoreSciSyncPoolCreateInfoNV*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSemaphoreSciSyncPoolNV*                   pSemaphorePool) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkCreateSemaphoreSciSyncPoolNV: Invalid device "
                   "[VUID-vkCreateSemaphoreSciSyncPoolNV-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->CreateSemaphoreSciSyncPoolNV(device, pCreateInfo, pAllocator, pSemaphorePool);
}

#endif // VK_USE_PLATFORM_SCI

// ---- VK_QNX_external_memory_screen_buffer extension trampoline/terminators

#if defined(VK_USE_PLATFORM_SCREEN_QNX)
VKAPI_ATTR VkResult VKAPI_CALL GetScreenBufferPropertiesQNX(
    VkDevice                                    device,
    const struct _screen_buffer*                buffer,
    VkScreenBufferPropertiesQNX*                pProperties) {
    const VkLayerDispatchTable *disp = loader_get_dispatch(device);
    if (NULL == disp) {
        loader_log(NULL, VULKAN_LOADER_FATAL_ERROR_BIT | VULKAN_LOADER_ERROR_BIT | VULKAN_LOADER_VALIDATION_BIT, 0,
                   "vkGetScreenBufferPropertiesQNX: Invalid device "
                   "[VUID-vkGetScreenBufferPropertiesQNX-device-parameter]");
        abort(); /* Intentionally fail so user can correct issue. */
    }
    return disp->GetScreenBufferPropertiesQNX(device, buffer, pProperties);
}

#endif // VK_USE_PLATFORM_SCREEN_QNX
// GPA helpers for extensions
bool extension_instance_gpa(struct loader_instance *ptr_instance, const char *name, void **addr) {
    *addr = NULL;


    // ---- VK_KHR_external_memory_fd extension commands
    if (!strcmp("vkGetMemoryFdKHR", name)) {
        *addr = (void *)GetMemoryFdKHR;
        return true;
    }
    if (!strcmp("vkGetMemoryFdPropertiesKHR", name)) {
        *addr = (void *)GetMemoryFdPropertiesKHR;
        return true;
    }

    // ---- VK_KHR_external_semaphore_fd extension commands
    if (!strcmp("vkImportSemaphoreFdKHR", name)) {
        *addr = (void *)ImportSemaphoreFdKHR;
        return true;
    }
    if (!strcmp("vkGetSemaphoreFdKHR", name)) {
        *addr = (void *)GetSemaphoreFdKHR;
        return true;
    }

    // ---- VK_KHR_shared_presentable_image extension commands
    if (!strcmp("vkGetSwapchainStatusKHR", name)) {
        *addr = (void *)GetSwapchainStatusKHR;
        return true;
    }

    // ---- VK_KHR_external_fence_fd extension commands
    if (!strcmp("vkImportFenceFdKHR", name)) {
        *addr = (void *)ImportFenceFdKHR;
        return true;
    }
    if (!strcmp("vkGetFenceFdKHR", name)) {
        *addr = (void *)GetFenceFdKHR;
        return true;
    }

    // ---- VK_KHR_performance_query extension commands
    if (!strcmp("vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR", name)) {
        *addr = (void *)EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR", name)) {
        *addr = (void *)GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR;
        return true;
    }
    if (!strcmp("vkAcquireProfilingLockKHR", name)) {
        *addr = (void *)AcquireProfilingLockKHR;
        return true;
    }
    if (!strcmp("vkReleaseProfilingLockKHR", name)) {
        *addr = (void *)ReleaseProfilingLockKHR;
        return true;
    }

    // ---- VK_KHR_fragment_shading_rate extension commands
    if (!strcmp("vkGetPhysicalDeviceFragmentShadingRatesKHR", name)) {
        *addr = (void *)GetPhysicalDeviceFragmentShadingRatesKHR;
        return true;
    }
    if (!strcmp("vkCmdSetFragmentShadingRateKHR", name)) {
        *addr = (void *)CmdSetFragmentShadingRateKHR;
        return true;
    }

    // ---- VK_KHR_object_refresh extension commands
    if (!strcmp("vkCmdRefreshObjectsKHR", name)) {
        *addr = (void *)CmdRefreshObjectsKHR;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceRefreshableObjectTypesKHR", name)) {
        *addr = (void *)GetPhysicalDeviceRefreshableObjectTypesKHR;
        return true;
    }

    // ---- VK_KHR_synchronization2 extension commands
    if (!strcmp("vkCmdSetEvent2KHR", name)) {
        *addr = (void *)CmdSetEvent2KHR;
        return true;
    }
    if (!strcmp("vkCmdResetEvent2KHR", name)) {
        *addr = (void *)CmdResetEvent2KHR;
        return true;
    }
    if (!strcmp("vkCmdWaitEvents2KHR", name)) {
        *addr = (void *)CmdWaitEvents2KHR;
        return true;
    }
    if (!strcmp("vkCmdPipelineBarrier2KHR", name)) {
        *addr = (void *)CmdPipelineBarrier2KHR;
        return true;
    }
    if (!strcmp("vkCmdWriteTimestamp2KHR", name)) {
        *addr = (void *)CmdWriteTimestamp2KHR;
        return true;
    }
    if (!strcmp("vkQueueSubmit2KHR", name)) {
        *addr = (void *)QueueSubmit2KHR;
        return true;
    }
    if (!strcmp("vkCmdWriteBufferMarker2AMD", name)) {
        *addr = (void *)CmdWriteBufferMarker2AMD;
        return true;
    }
    if (!strcmp("vkGetQueueCheckpointData2NV", name)) {
        *addr = (void *)GetQueueCheckpointData2NV;
        return true;
    }

    // ---- VK_KHR_copy_commands2 extension commands
    if (!strcmp("vkCmdCopyBuffer2KHR", name)) {
        *addr = (void *)CmdCopyBuffer2KHR;
        return true;
    }
    if (!strcmp("vkCmdCopyImage2KHR", name)) {
        *addr = (void *)CmdCopyImage2KHR;
        return true;
    }
    if (!strcmp("vkCmdCopyBufferToImage2KHR", name)) {
        *addr = (void *)CmdCopyBufferToImage2KHR;
        return true;
    }
    if (!strcmp("vkCmdCopyImageToBuffer2KHR", name)) {
        *addr = (void *)CmdCopyImageToBuffer2KHR;
        return true;
    }
    if (!strcmp("vkCmdBlitImage2KHR", name)) {
        *addr = (void *)CmdBlitImage2KHR;
        return true;
    }
    if (!strcmp("vkCmdResolveImage2KHR", name)) {
        *addr = (void *)CmdResolveImage2KHR;
        return true;
    }

    // ---- VK_EXT_direct_mode_display extension commands
    if (!strcmp("vkReleaseDisplayEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_direct_mode_display == 1)
                     ? (void *)ReleaseDisplayEXT
                     : NULL;
        return true;
    }

    // ---- VK_EXT_display_surface_counter extension commands
    if (!strcmp("vkGetPhysicalDeviceSurfaceCapabilities2EXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_display_surface_counter == 1)
                     ? (void *)GetPhysicalDeviceSurfaceCapabilities2EXT
                     : NULL;
        return true;
    }

    // ---- VK_EXT_display_control extension commands
    if (!strcmp("vkDisplayPowerControlEXT", name)) {
        *addr = (void *)DisplayPowerControlEXT;
        return true;
    }
    if (!strcmp("vkRegisterDeviceEventEXT", name)) {
        *addr = (void *)RegisterDeviceEventEXT;
        return true;
    }
    if (!strcmp("vkRegisterDisplayEventEXT", name)) {
        *addr = (void *)RegisterDisplayEventEXT;
        return true;
    }
    if (!strcmp("vkGetSwapchainCounterEXT", name)) {
        *addr = (void *)GetSwapchainCounterEXT;
        return true;
    }

    // ---- VK_EXT_discard_rectangles extension commands
    if (!strcmp("vkCmdSetDiscardRectangleEXT", name)) {
        *addr = (void *)CmdSetDiscardRectangleEXT;
        return true;
    }
    if (!strcmp("vkCmdSetDiscardRectangleEnableEXT", name)) {
        *addr = (void *)CmdSetDiscardRectangleEnableEXT;
        return true;
    }
    if (!strcmp("vkCmdSetDiscardRectangleModeEXT", name)) {
        *addr = (void *)CmdSetDiscardRectangleModeEXT;
        return true;
    }

    // ---- VK_EXT_hdr_metadata extension commands
    if (!strcmp("vkSetHdrMetadataEXT", name)) {
        *addr = (void *)SetHdrMetadataEXT;
        return true;
    }

    // ---- VK_EXT_debug_utils extension commands
    if (!strcmp("vkSetDebugUtilsObjectNameEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_debug_utils == 1)
                     ? (void *)SetDebugUtilsObjectNameEXT
                     : NULL;
        return true;
    }
    if (!strcmp("vkSetDebugUtilsObjectTagEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_debug_utils == 1)
                     ? (void *)SetDebugUtilsObjectTagEXT
                     : NULL;
        return true;
    }
    if (!strcmp("vkQueueBeginDebugUtilsLabelEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_debug_utils == 1)
                     ? (void *)QueueBeginDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (!strcmp("vkQueueEndDebugUtilsLabelEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_debug_utils == 1)
                     ? (void *)QueueEndDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (!strcmp("vkQueueInsertDebugUtilsLabelEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_debug_utils == 1)
                     ? (void *)QueueInsertDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (!strcmp("vkCmdBeginDebugUtilsLabelEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_debug_utils == 1)
                     ? (void *)CmdBeginDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (!strcmp("vkCmdEndDebugUtilsLabelEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_debug_utils == 1)
                     ? (void *)CmdEndDebugUtilsLabelEXT
                     : NULL;
        return true;
    }
    if (!strcmp("vkCmdInsertDebugUtilsLabelEXT", name)) {
        *addr = (ptr_instance->enabled_known_extensions.ext_debug_utils == 1)
                     ? (void *)CmdInsertDebugUtilsLabelEXT
                     : NULL;
        return true;
    }

    // ---- VK_EXT_sample_locations extension commands
    if (!strcmp("vkCmdSetSampleLocationsEXT", name)) {
        *addr = (void *)CmdSetSampleLocationsEXT;
        return true;
    }
    if (!strcmp("vkGetPhysicalDeviceMultisamplePropertiesEXT", name)) {
        *addr = (void *)GetPhysicalDeviceMultisamplePropertiesEXT;
        return true;
    }

    // ---- VK_EXT_image_drm_format_modifier extension commands
    if (!strcmp("vkGetImageDrmFormatModifierPropertiesEXT", name)) {
        *addr = (void *)GetImageDrmFormatModifierPropertiesEXT;
        return true;
    }

    // ---- VK_EXT_external_memory_host extension commands
    if (!strcmp("vkGetMemoryHostPointerPropertiesEXT", name)) {
        *addr = (void *)GetMemoryHostPointerPropertiesEXT;
        return true;
    }

    // ---- VK_EXT_calibrated_timestamps extension commands
    if (!strcmp("vkGetPhysicalDeviceCalibrateableTimeDomainsEXT", name)) {
        *addr = (void *)GetPhysicalDeviceCalibrateableTimeDomainsEXT;
        return true;
    }
    if (!strcmp("vkGetCalibratedTimestampsEXT", name)) {
        *addr = (void *)GetCalibratedTimestampsEXT;
        return true;
    }

    // ---- VK_EXT_line_rasterization extension commands
    if (!strcmp("vkCmdSetLineStippleEXT", name)) {
        *addr = (void *)CmdSetLineStippleEXT;
        return true;
    }

    // ---- VK_EXT_extended_dynamic_state extension commands
    if (!strcmp("vkCmdSetCullModeEXT", name)) {
        *addr = (void *)CmdSetCullModeEXT;
        return true;
    }
    if (!strcmp("vkCmdSetFrontFaceEXT", name)) {
        *addr = (void *)CmdSetFrontFaceEXT;
        return true;
    }
    if (!strcmp("vkCmdSetPrimitiveTopologyEXT", name)) {
        *addr = (void *)CmdSetPrimitiveTopologyEXT;
        return true;
    }
    if (!strcmp("vkCmdSetViewportWithCountEXT", name)) {
        *addr = (void *)CmdSetViewportWithCountEXT;
        return true;
    }
    if (!strcmp("vkCmdSetScissorWithCountEXT", name)) {
        *addr = (void *)CmdSetScissorWithCountEXT;
        return true;
    }
    if (!strcmp("vkCmdBindVertexBuffers2EXT", name)) {
        *addr = (void *)CmdBindVertexBuffers2EXT;
        return true;
    }
    if (!strcmp("vkCmdSetDepthTestEnableEXT", name)) {
        *addr = (void *)CmdSetDepthTestEnableEXT;
        return true;
    }
    if (!strcmp("vkCmdSetDepthWriteEnableEXT", name)) {
        *addr = (void *)CmdSetDepthWriteEnableEXT;
        return true;
    }
    if (!strcmp("vkCmdSetDepthCompareOpEXT", name)) {
        *addr = (void *)CmdSetDepthCompareOpEXT;
        return true;
    }
    if (!strcmp("vkCmdSetDepthBoundsTestEnableEXT", name)) {
        *addr = (void *)CmdSetDepthBoundsTestEnableEXT;
        return true;
    }
    if (!strcmp("vkCmdSetStencilTestEnableEXT", name)) {
        *addr = (void *)CmdSetStencilTestEnableEXT;
        return true;
    }
    if (!strcmp("vkCmdSetStencilOpEXT", name)) {
        *addr = (void *)CmdSetStencilOpEXT;
        return true;
    }

    // ---- VK_EXT_vertex_input_dynamic_state extension commands
    if (!strcmp("vkCmdSetVertexInputEXT", name)) {
        *addr = (void *)CmdSetVertexInputEXT;
        return true;
    }

    // ---- VK_NV_external_sci_sync extension commands
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkGetFenceSciSyncFenceNV", name)) {
        *addr = (void *)GetFenceSciSyncFenceNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkGetFenceSciSyncObjNV", name)) {
        *addr = (void *)GetFenceSciSyncObjNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkImportFenceSciSyncFenceNV", name)) {
        *addr = (void *)ImportFenceSciSyncFenceNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkImportFenceSciSyncObjNV", name)) {
        *addr = (void *)ImportFenceSciSyncObjNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkGetPhysicalDeviceSciSyncAttributesNV", name)) {
        *addr = (void *)GetPhysicalDeviceSciSyncAttributesNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkGetSemaphoreSciSyncObjNV", name)) {
        *addr = (void *)GetSemaphoreSciSyncObjNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkImportSemaphoreSciSyncObjNV", name)) {
        *addr = (void *)ImportSemaphoreSciSyncObjNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_NV_external_memory_sci_buf extension commands
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkGetMemorySciBufNV", name)) {
        *addr = (void *)GetMemorySciBufNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV", name)) {
        *addr = (void *)GetPhysicalDeviceExternalMemorySciBufPropertiesNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkGetPhysicalDeviceSciBufAttributesNV", name)) {
        *addr = (void *)GetPhysicalDeviceSciBufAttributesNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_EXT_extended_dynamic_state2 extension commands
    if (!strcmp("vkCmdSetPatchControlPointsEXT", name)) {
        *addr = (void *)CmdSetPatchControlPointsEXT;
        return true;
    }
    if (!strcmp("vkCmdSetRasterizerDiscardEnableEXT", name)) {
        *addr = (void *)CmdSetRasterizerDiscardEnableEXT;
        return true;
    }
    if (!strcmp("vkCmdSetDepthBiasEnableEXT", name)) {
        *addr = (void *)CmdSetDepthBiasEnableEXT;
        return true;
    }
    if (!strcmp("vkCmdSetLogicOpEXT", name)) {
        *addr = (void *)CmdSetLogicOpEXT;
        return true;
    }
    if (!strcmp("vkCmdSetPrimitiveRestartEnableEXT", name)) {
        *addr = (void *)CmdSetPrimitiveRestartEnableEXT;
        return true;
    }

    // ---- VK_EXT_color_write_enable extension commands
    if (!strcmp("vkCmdSetColorWriteEnableEXT", name)) {
        *addr = (void *)CmdSetColorWriteEnableEXT;
        return true;
    }

    // ---- VK_NV_external_sci_sync2 extension commands
#if defined(VK_USE_PLATFORM_SCI)
    if (!strcmp("vkCreateSemaphoreSciSyncPoolNV", name)) {
        *addr = (void *)CreateSemaphoreSciSyncPoolNV;
        return true;
    }
#endif // VK_USE_PLATFORM_SCI

    // ---- VK_QNX_external_memory_screen_buffer extension commands
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    if (!strcmp("vkGetScreenBufferPropertiesQNX", name)) {
        *addr = (void *)GetScreenBufferPropertiesQNX;
        return true;
    }
#endif // VK_USE_PLATFORM_SCREEN_QNX
    return false;
}

// A function that can be used to query enabled extensions during a vkCreateInstance call
void extensions_create_instance(struct loader_instance *ptr_instance, const VkInstanceCreateInfo *pCreateInfo) {
    for (uint32_t i = 0; i < pCreateInfo->enabledExtensionCount; i++) {

    // ---- VK_EXT_direct_mode_display extension commands
        if (0 == strcmp(pCreateInfo->ppEnabledExtensionNames[i], VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME)) {
            ptr_instance->enabled_known_extensions.ext_direct_mode_display = 1;

    // ---- VK_EXT_display_surface_counter extension commands
        } else if (0 == strcmp(pCreateInfo->ppEnabledExtensionNames[i], VK_EXT_DISPLAY_SURFACE_COUNTER_EXTENSION_NAME)) {
            ptr_instance->enabled_known_extensions.ext_display_surface_counter = 1;

    // ---- VK_EXT_debug_utils extension commands
        } else if (0 == strcmp(pCreateInfo->ppEnabledExtensionNames[i], VK_EXT_DEBUG_UTILS_EXTENSION_NAME)) {
            ptr_instance->enabled_known_extensions.ext_debug_utils = 1;
        }
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

    // ---- Core SC 1_0 commands
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

    // ---- VK_EXT_calibrated_timestamps extension commands
    .GetPhysicalDeviceCalibrateableTimeDomainsEXT = terminator_GetPhysicalDeviceCalibrateableTimeDomainsEXT,

    // ---- VK_EXT_headless_surface extension commands
    .CreateHeadlessSurfaceEXT = terminator_CreateHeadlessSurfaceEXT,

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
                                                  NULL };

