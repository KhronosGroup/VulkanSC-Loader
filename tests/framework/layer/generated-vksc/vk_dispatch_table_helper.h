#pragma once
// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See dispatch_table_helper_generator.py for modifications

/*
 * Copyright (c) 2015-2025 The Khronos Group Inc.
 * Copyright (c) 2015-2025 Valve Corporation
 * Copyright (c) 2015-2025 LunarG, Inc.
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
 * Author: Courtney Goeltzenleuchter <courtney@LunarG.com>
 * Author: Jon Ashburn <jon@lunarg.com>
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 */

#include <vulkan/vulkan.h>
#include <vulkan/vk_layer.h>
#include <string.h>
#include "vk_layer_dispatch_table.h"

// clang-format off
static inline void layer_init_device_dispatch_table(VkDevice device, VkLayerDispatchTable *table, PFN_vkGetDeviceProcAddr gpa) {
    memset(table, 0, sizeof(*table));
    table->magic = DEVICE_DISP_TABLE_MAGIC_NUMBER;

    // Device function pointers
    table->GetDeviceProcAddr = gpa;
    table->DestroyDevice = (PFN_vkDestroyDevice)gpa(device, "vkDestroyDevice");
    table->GetDeviceQueue = (PFN_vkGetDeviceQueue)gpa(device, "vkGetDeviceQueue");
    table->QueueSubmit = (PFN_vkQueueSubmit)gpa(device, "vkQueueSubmit");
    table->QueueWaitIdle = (PFN_vkQueueWaitIdle)gpa(device, "vkQueueWaitIdle");
    table->DeviceWaitIdle = (PFN_vkDeviceWaitIdle)gpa(device, "vkDeviceWaitIdle");
    table->AllocateMemory = (PFN_vkAllocateMemory)gpa(device, "vkAllocateMemory");
    table->MapMemory = (PFN_vkMapMemory)gpa(device, "vkMapMemory");
    table->UnmapMemory = (PFN_vkUnmapMemory)gpa(device, "vkUnmapMemory");
    table->FlushMappedMemoryRanges = (PFN_vkFlushMappedMemoryRanges)gpa(device, "vkFlushMappedMemoryRanges");
    table->InvalidateMappedMemoryRanges = (PFN_vkInvalidateMappedMemoryRanges)gpa(device, "vkInvalidateMappedMemoryRanges");
    table->GetDeviceMemoryCommitment = (PFN_vkGetDeviceMemoryCommitment)gpa(device, "vkGetDeviceMemoryCommitment");
    table->BindBufferMemory = (PFN_vkBindBufferMemory)gpa(device, "vkBindBufferMemory");
    table->BindImageMemory = (PFN_vkBindImageMemory)gpa(device, "vkBindImageMemory");
    table->GetBufferMemoryRequirements = (PFN_vkGetBufferMemoryRequirements)gpa(device, "vkGetBufferMemoryRequirements");
    table->GetImageMemoryRequirements = (PFN_vkGetImageMemoryRequirements)gpa(device, "vkGetImageMemoryRequirements");
    table->CreateFence = (PFN_vkCreateFence)gpa(device, "vkCreateFence");
    table->DestroyFence = (PFN_vkDestroyFence)gpa(device, "vkDestroyFence");
    table->ResetFences = (PFN_vkResetFences)gpa(device, "vkResetFences");
    table->GetFenceStatus = (PFN_vkGetFenceStatus)gpa(device, "vkGetFenceStatus");
    table->WaitForFences = (PFN_vkWaitForFences)gpa(device, "vkWaitForFences");
    table->CreateSemaphore = (PFN_vkCreateSemaphore)gpa(device, "vkCreateSemaphore");
    table->DestroySemaphore = (PFN_vkDestroySemaphore)gpa(device, "vkDestroySemaphore");
    table->CreateEvent = (PFN_vkCreateEvent)gpa(device, "vkCreateEvent");
    table->DestroyEvent = (PFN_vkDestroyEvent)gpa(device, "vkDestroyEvent");
    table->GetEventStatus = (PFN_vkGetEventStatus)gpa(device, "vkGetEventStatus");
    table->SetEvent = (PFN_vkSetEvent)gpa(device, "vkSetEvent");
    table->ResetEvent = (PFN_vkResetEvent)gpa(device, "vkResetEvent");
    table->CreateQueryPool = (PFN_vkCreateQueryPool)gpa(device, "vkCreateQueryPool");
    table->GetQueryPoolResults = (PFN_vkGetQueryPoolResults)gpa(device, "vkGetQueryPoolResults");
    table->CreateBuffer = (PFN_vkCreateBuffer)gpa(device, "vkCreateBuffer");
    table->DestroyBuffer = (PFN_vkDestroyBuffer)gpa(device, "vkDestroyBuffer");
    table->CreateBufferView = (PFN_vkCreateBufferView)gpa(device, "vkCreateBufferView");
    table->DestroyBufferView = (PFN_vkDestroyBufferView)gpa(device, "vkDestroyBufferView");
    table->CreateImage = (PFN_vkCreateImage)gpa(device, "vkCreateImage");
    table->DestroyImage = (PFN_vkDestroyImage)gpa(device, "vkDestroyImage");
    table->GetImageSubresourceLayout = (PFN_vkGetImageSubresourceLayout)gpa(device, "vkGetImageSubresourceLayout");
    table->CreateImageView = (PFN_vkCreateImageView)gpa(device, "vkCreateImageView");
    table->DestroyImageView = (PFN_vkDestroyImageView)gpa(device, "vkDestroyImageView");
    table->CreatePipelineCache = (PFN_vkCreatePipelineCache)gpa(device, "vkCreatePipelineCache");
    table->DestroyPipelineCache = (PFN_vkDestroyPipelineCache)gpa(device, "vkDestroyPipelineCache");
    table->CreateGraphicsPipelines = (PFN_vkCreateGraphicsPipelines)gpa(device, "vkCreateGraphicsPipelines");
    table->CreateComputePipelines = (PFN_vkCreateComputePipelines)gpa(device, "vkCreateComputePipelines");
    table->DestroyPipeline = (PFN_vkDestroyPipeline)gpa(device, "vkDestroyPipeline");
    table->CreatePipelineLayout = (PFN_vkCreatePipelineLayout)gpa(device, "vkCreatePipelineLayout");
    table->DestroyPipelineLayout = (PFN_vkDestroyPipelineLayout)gpa(device, "vkDestroyPipelineLayout");
    table->CreateSampler = (PFN_vkCreateSampler)gpa(device, "vkCreateSampler");
    table->DestroySampler = (PFN_vkDestroySampler)gpa(device, "vkDestroySampler");
    table->CreateDescriptorSetLayout = (PFN_vkCreateDescriptorSetLayout)gpa(device, "vkCreateDescriptorSetLayout");
    table->DestroyDescriptorSetLayout = (PFN_vkDestroyDescriptorSetLayout)gpa(device, "vkDestroyDescriptorSetLayout");
    table->CreateDescriptorPool = (PFN_vkCreateDescriptorPool)gpa(device, "vkCreateDescriptorPool");
    table->ResetDescriptorPool = (PFN_vkResetDescriptorPool)gpa(device, "vkResetDescriptorPool");
    table->AllocateDescriptorSets = (PFN_vkAllocateDescriptorSets)gpa(device, "vkAllocateDescriptorSets");
    table->FreeDescriptorSets = (PFN_vkFreeDescriptorSets)gpa(device, "vkFreeDescriptorSets");
    table->UpdateDescriptorSets = (PFN_vkUpdateDescriptorSets)gpa(device, "vkUpdateDescriptorSets");
    table->CreateFramebuffer = (PFN_vkCreateFramebuffer)gpa(device, "vkCreateFramebuffer");
    table->DestroyFramebuffer = (PFN_vkDestroyFramebuffer)gpa(device, "vkDestroyFramebuffer");
    table->CreateRenderPass = (PFN_vkCreateRenderPass)gpa(device, "vkCreateRenderPass");
    table->DestroyRenderPass = (PFN_vkDestroyRenderPass)gpa(device, "vkDestroyRenderPass");
    table->GetRenderAreaGranularity = (PFN_vkGetRenderAreaGranularity)gpa(device, "vkGetRenderAreaGranularity");
    table->CreateCommandPool = (PFN_vkCreateCommandPool)gpa(device, "vkCreateCommandPool");
    table->ResetCommandPool = (PFN_vkResetCommandPool)gpa(device, "vkResetCommandPool");
    table->AllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)gpa(device, "vkAllocateCommandBuffers");
    table->FreeCommandBuffers = (PFN_vkFreeCommandBuffers)gpa(device, "vkFreeCommandBuffers");
    table->BeginCommandBuffer = (PFN_vkBeginCommandBuffer)gpa(device, "vkBeginCommandBuffer");
    table->EndCommandBuffer = (PFN_vkEndCommandBuffer)gpa(device, "vkEndCommandBuffer");
    table->ResetCommandBuffer = (PFN_vkResetCommandBuffer)gpa(device, "vkResetCommandBuffer");
    table->CmdBindPipeline = (PFN_vkCmdBindPipeline)gpa(device, "vkCmdBindPipeline");
    table->CmdSetViewport = (PFN_vkCmdSetViewport)gpa(device, "vkCmdSetViewport");
    table->CmdSetScissor = (PFN_vkCmdSetScissor)gpa(device, "vkCmdSetScissor");
    table->CmdSetLineWidth = (PFN_vkCmdSetLineWidth)gpa(device, "vkCmdSetLineWidth");
    table->CmdSetDepthBias = (PFN_vkCmdSetDepthBias)gpa(device, "vkCmdSetDepthBias");
    table->CmdSetBlendConstants = (PFN_vkCmdSetBlendConstants)gpa(device, "vkCmdSetBlendConstants");
    table->CmdSetDepthBounds = (PFN_vkCmdSetDepthBounds)gpa(device, "vkCmdSetDepthBounds");
    table->CmdSetStencilCompareMask = (PFN_vkCmdSetStencilCompareMask)gpa(device, "vkCmdSetStencilCompareMask");
    table->CmdSetStencilWriteMask = (PFN_vkCmdSetStencilWriteMask)gpa(device, "vkCmdSetStencilWriteMask");
    table->CmdSetStencilReference = (PFN_vkCmdSetStencilReference)gpa(device, "vkCmdSetStencilReference");
    table->CmdBindDescriptorSets = (PFN_vkCmdBindDescriptorSets)gpa(device, "vkCmdBindDescriptorSets");
    table->CmdBindIndexBuffer = (PFN_vkCmdBindIndexBuffer)gpa(device, "vkCmdBindIndexBuffer");
    table->CmdBindVertexBuffers = (PFN_vkCmdBindVertexBuffers)gpa(device, "vkCmdBindVertexBuffers");
    table->CmdDraw = (PFN_vkCmdDraw)gpa(device, "vkCmdDraw");
    table->CmdDrawIndexed = (PFN_vkCmdDrawIndexed)gpa(device, "vkCmdDrawIndexed");
    table->CmdDrawIndirect = (PFN_vkCmdDrawIndirect)gpa(device, "vkCmdDrawIndirect");
    table->CmdDrawIndexedIndirect = (PFN_vkCmdDrawIndexedIndirect)gpa(device, "vkCmdDrawIndexedIndirect");
    table->CmdDispatch = (PFN_vkCmdDispatch)gpa(device, "vkCmdDispatch");
    table->CmdDispatchIndirect = (PFN_vkCmdDispatchIndirect)gpa(device, "vkCmdDispatchIndirect");
    table->CmdCopyBuffer = (PFN_vkCmdCopyBuffer)gpa(device, "vkCmdCopyBuffer");
    table->CmdCopyImage = (PFN_vkCmdCopyImage)gpa(device, "vkCmdCopyImage");
    table->CmdBlitImage = (PFN_vkCmdBlitImage)gpa(device, "vkCmdBlitImage");
    table->CmdCopyBufferToImage = (PFN_vkCmdCopyBufferToImage)gpa(device, "vkCmdCopyBufferToImage");
    table->CmdCopyImageToBuffer = (PFN_vkCmdCopyImageToBuffer)gpa(device, "vkCmdCopyImageToBuffer");
    table->CmdUpdateBuffer = (PFN_vkCmdUpdateBuffer)gpa(device, "vkCmdUpdateBuffer");
    table->CmdFillBuffer = (PFN_vkCmdFillBuffer)gpa(device, "vkCmdFillBuffer");
    table->CmdClearColorImage = (PFN_vkCmdClearColorImage)gpa(device, "vkCmdClearColorImage");
    table->CmdClearDepthStencilImage = (PFN_vkCmdClearDepthStencilImage)gpa(device, "vkCmdClearDepthStencilImage");
    table->CmdClearAttachments = (PFN_vkCmdClearAttachments)gpa(device, "vkCmdClearAttachments");
    table->CmdResolveImage = (PFN_vkCmdResolveImage)gpa(device, "vkCmdResolveImage");
    table->CmdSetEvent = (PFN_vkCmdSetEvent)gpa(device, "vkCmdSetEvent");
    table->CmdResetEvent = (PFN_vkCmdResetEvent)gpa(device, "vkCmdResetEvent");
    table->CmdWaitEvents = (PFN_vkCmdWaitEvents)gpa(device, "vkCmdWaitEvents");
    table->CmdPipelineBarrier = (PFN_vkCmdPipelineBarrier)gpa(device, "vkCmdPipelineBarrier");
    table->CmdBeginQuery = (PFN_vkCmdBeginQuery)gpa(device, "vkCmdBeginQuery");
    table->CmdEndQuery = (PFN_vkCmdEndQuery)gpa(device, "vkCmdEndQuery");
    table->CmdResetQueryPool = (PFN_vkCmdResetQueryPool)gpa(device, "vkCmdResetQueryPool");
    table->CmdWriteTimestamp = (PFN_vkCmdWriteTimestamp)gpa(device, "vkCmdWriteTimestamp");
    table->CmdCopyQueryPoolResults = (PFN_vkCmdCopyQueryPoolResults)gpa(device, "vkCmdCopyQueryPoolResults");
    table->CmdPushConstants = (PFN_vkCmdPushConstants)gpa(device, "vkCmdPushConstants");
    table->CmdBeginRenderPass = (PFN_vkCmdBeginRenderPass)gpa(device, "vkCmdBeginRenderPass");
    table->CmdNextSubpass = (PFN_vkCmdNextSubpass)gpa(device, "vkCmdNextSubpass");
    table->CmdEndRenderPass = (PFN_vkCmdEndRenderPass)gpa(device, "vkCmdEndRenderPass");
    table->CmdExecuteCommands = (PFN_vkCmdExecuteCommands)gpa(device, "vkCmdExecuteCommands");
    table->BindBufferMemory2 = (PFN_vkBindBufferMemory2)gpa(device, "vkBindBufferMemory2");
    table->BindImageMemory2 = (PFN_vkBindImageMemory2)gpa(device, "vkBindImageMemory2");
    table->GetDeviceGroupPeerMemoryFeatures = (PFN_vkGetDeviceGroupPeerMemoryFeatures)gpa(device, "vkGetDeviceGroupPeerMemoryFeatures");
    table->CmdSetDeviceMask = (PFN_vkCmdSetDeviceMask)gpa(device, "vkCmdSetDeviceMask");
    table->CmdDispatchBase = (PFN_vkCmdDispatchBase)gpa(device, "vkCmdDispatchBase");
    table->GetImageMemoryRequirements2 = (PFN_vkGetImageMemoryRequirements2)gpa(device, "vkGetImageMemoryRequirements2");
    table->GetBufferMemoryRequirements2 = (PFN_vkGetBufferMemoryRequirements2)gpa(device, "vkGetBufferMemoryRequirements2");
    table->GetDeviceQueue2 = (PFN_vkGetDeviceQueue2)gpa(device, "vkGetDeviceQueue2");
    table->CreateSamplerYcbcrConversion = (PFN_vkCreateSamplerYcbcrConversion)gpa(device, "vkCreateSamplerYcbcrConversion");
    table->DestroySamplerYcbcrConversion = (PFN_vkDestroySamplerYcbcrConversion)gpa(device, "vkDestroySamplerYcbcrConversion");
    table->GetDescriptorSetLayoutSupport = (PFN_vkGetDescriptorSetLayoutSupport)gpa(device, "vkGetDescriptorSetLayoutSupport");
    table->CmdDrawIndirectCount = (PFN_vkCmdDrawIndirectCount)gpa(device, "vkCmdDrawIndirectCount");
    table->CmdDrawIndexedIndirectCount = (PFN_vkCmdDrawIndexedIndirectCount)gpa(device, "vkCmdDrawIndexedIndirectCount");
    table->CreateRenderPass2 = (PFN_vkCreateRenderPass2)gpa(device, "vkCreateRenderPass2");
    table->CmdBeginRenderPass2 = (PFN_vkCmdBeginRenderPass2)gpa(device, "vkCmdBeginRenderPass2");
    table->CmdNextSubpass2 = (PFN_vkCmdNextSubpass2)gpa(device, "vkCmdNextSubpass2");
    table->CmdEndRenderPass2 = (PFN_vkCmdEndRenderPass2)gpa(device, "vkCmdEndRenderPass2");
    table->ResetQueryPool = (PFN_vkResetQueryPool)gpa(device, "vkResetQueryPool");
    table->GetSemaphoreCounterValue = (PFN_vkGetSemaphoreCounterValue)gpa(device, "vkGetSemaphoreCounterValue");
    table->WaitSemaphores = (PFN_vkWaitSemaphores)gpa(device, "vkWaitSemaphores");
    table->SignalSemaphore = (PFN_vkSignalSemaphore)gpa(device, "vkSignalSemaphore");
    table->GetBufferDeviceAddress = (PFN_vkGetBufferDeviceAddress)gpa(device, "vkGetBufferDeviceAddress");
    table->GetBufferOpaqueCaptureAddress = (PFN_vkGetBufferOpaqueCaptureAddress)gpa(device, "vkGetBufferOpaqueCaptureAddress");
    table->GetDeviceMemoryOpaqueCaptureAddress = (PFN_vkGetDeviceMemoryOpaqueCaptureAddress)gpa(device, "vkGetDeviceMemoryOpaqueCaptureAddress");
    table->CreatePrivateDataSlot = (PFN_vkCreatePrivateDataSlot)gpa(device, "vkCreatePrivateDataSlot");
    table->DestroyPrivateDataSlot = (PFN_vkDestroyPrivateDataSlot)gpa(device, "vkDestroyPrivateDataSlot");
    table->SetPrivateData = (PFN_vkSetPrivateData)gpa(device, "vkSetPrivateData");
    table->GetPrivateData = (PFN_vkGetPrivateData)gpa(device, "vkGetPrivateData");
    table->CmdSetEvent2 = (PFN_vkCmdSetEvent2)gpa(device, "vkCmdSetEvent2");
    table->CmdResetEvent2 = (PFN_vkCmdResetEvent2)gpa(device, "vkCmdResetEvent2");
    table->CmdWaitEvents2 = (PFN_vkCmdWaitEvents2)gpa(device, "vkCmdWaitEvents2");
    table->CmdPipelineBarrier2 = (PFN_vkCmdPipelineBarrier2)gpa(device, "vkCmdPipelineBarrier2");
    table->CmdWriteTimestamp2 = (PFN_vkCmdWriteTimestamp2)gpa(device, "vkCmdWriteTimestamp2");
    table->QueueSubmit2 = (PFN_vkQueueSubmit2)gpa(device, "vkQueueSubmit2");
    table->CmdCopyBuffer2 = (PFN_vkCmdCopyBuffer2)gpa(device, "vkCmdCopyBuffer2");
    table->CmdCopyImage2 = (PFN_vkCmdCopyImage2)gpa(device, "vkCmdCopyImage2");
    table->CmdCopyBufferToImage2 = (PFN_vkCmdCopyBufferToImage2)gpa(device, "vkCmdCopyBufferToImage2");
    table->CmdCopyImageToBuffer2 = (PFN_vkCmdCopyImageToBuffer2)gpa(device, "vkCmdCopyImageToBuffer2");
    table->CmdBlitImage2 = (PFN_vkCmdBlitImage2)gpa(device, "vkCmdBlitImage2");
    table->CmdResolveImage2 = (PFN_vkCmdResolveImage2)gpa(device, "vkCmdResolveImage2");
    table->CmdBeginRendering = (PFN_vkCmdBeginRendering)gpa(device, "vkCmdBeginRendering");
    table->CmdEndRendering = (PFN_vkCmdEndRendering)gpa(device, "vkCmdEndRendering");
    table->CmdSetCullMode = (PFN_vkCmdSetCullMode)gpa(device, "vkCmdSetCullMode");
    table->CmdSetFrontFace = (PFN_vkCmdSetFrontFace)gpa(device, "vkCmdSetFrontFace");
    table->CmdSetPrimitiveTopology = (PFN_vkCmdSetPrimitiveTopology)gpa(device, "vkCmdSetPrimitiveTopology");
    table->CmdSetViewportWithCount = (PFN_vkCmdSetViewportWithCount)gpa(device, "vkCmdSetViewportWithCount");
    table->CmdSetScissorWithCount = (PFN_vkCmdSetScissorWithCount)gpa(device, "vkCmdSetScissorWithCount");
    table->CmdBindVertexBuffers2 = (PFN_vkCmdBindVertexBuffers2)gpa(device, "vkCmdBindVertexBuffers2");
    table->CmdSetDepthTestEnable = (PFN_vkCmdSetDepthTestEnable)gpa(device, "vkCmdSetDepthTestEnable");
    table->CmdSetDepthWriteEnable = (PFN_vkCmdSetDepthWriteEnable)gpa(device, "vkCmdSetDepthWriteEnable");
    table->CmdSetDepthCompareOp = (PFN_vkCmdSetDepthCompareOp)gpa(device, "vkCmdSetDepthCompareOp");
    table->CmdSetDepthBoundsTestEnable = (PFN_vkCmdSetDepthBoundsTestEnable)gpa(device, "vkCmdSetDepthBoundsTestEnable");
    table->CmdSetStencilTestEnable = (PFN_vkCmdSetStencilTestEnable)gpa(device, "vkCmdSetStencilTestEnable");
    table->CmdSetStencilOp = (PFN_vkCmdSetStencilOp)gpa(device, "vkCmdSetStencilOp");
    table->CmdSetRasterizerDiscardEnable = (PFN_vkCmdSetRasterizerDiscardEnable)gpa(device, "vkCmdSetRasterizerDiscardEnable");
    table->CmdSetDepthBiasEnable = (PFN_vkCmdSetDepthBiasEnable)gpa(device, "vkCmdSetDepthBiasEnable");
    table->CmdSetPrimitiveRestartEnable = (PFN_vkCmdSetPrimitiveRestartEnable)gpa(device, "vkCmdSetPrimitiveRestartEnable");
    table->GetDeviceBufferMemoryRequirements = (PFN_vkGetDeviceBufferMemoryRequirements)gpa(device, "vkGetDeviceBufferMemoryRequirements");
    table->GetDeviceImageMemoryRequirements = (PFN_vkGetDeviceImageMemoryRequirements)gpa(device, "vkGetDeviceImageMemoryRequirements");
    table->GetDeviceImageSparseMemoryRequirements = (PFN_vkGetDeviceImageSparseMemoryRequirements)gpa(device, "vkGetDeviceImageSparseMemoryRequirements");
    table->CmdSetLineStipple = (PFN_vkCmdSetLineStipple)gpa(device, "vkCmdSetLineStipple");
    table->MapMemory2 = (PFN_vkMapMemory2)gpa(device, "vkMapMemory2");
    table->UnmapMemory2 = (PFN_vkUnmapMemory2)gpa(device, "vkUnmapMemory2");
    table->CmdBindIndexBuffer2 = (PFN_vkCmdBindIndexBuffer2)gpa(device, "vkCmdBindIndexBuffer2");
    table->GetRenderingAreaGranularity = (PFN_vkGetRenderingAreaGranularity)gpa(device, "vkGetRenderingAreaGranularity");
    table->GetDeviceImageSubresourceLayout = (PFN_vkGetDeviceImageSubresourceLayout)gpa(device, "vkGetDeviceImageSubresourceLayout");
    table->GetImageSubresourceLayout2 = (PFN_vkGetImageSubresourceLayout2)gpa(device, "vkGetImageSubresourceLayout2");
    table->CmdPushDescriptorSet = (PFN_vkCmdPushDescriptorSet)gpa(device, "vkCmdPushDescriptorSet");
    table->CmdSetRenderingAttachmentLocations = (PFN_vkCmdSetRenderingAttachmentLocations)gpa(device, "vkCmdSetRenderingAttachmentLocations");
    table->CmdSetRenderingInputAttachmentIndices = (PFN_vkCmdSetRenderingInputAttachmentIndices)gpa(device, "vkCmdSetRenderingInputAttachmentIndices");
    table->CmdBindDescriptorSets2 = (PFN_vkCmdBindDescriptorSets2)gpa(device, "vkCmdBindDescriptorSets2");
    table->CmdPushConstants2 = (PFN_vkCmdPushConstants2)gpa(device, "vkCmdPushConstants2");
    table->CmdPushDescriptorSet2 = (PFN_vkCmdPushDescriptorSet2)gpa(device, "vkCmdPushDescriptorSet2");
    table->CopyMemoryToImage = (PFN_vkCopyMemoryToImage)gpa(device, "vkCopyMemoryToImage");
    table->CopyImageToMemory = (PFN_vkCopyImageToMemory)gpa(device, "vkCopyImageToMemory");
    table->CopyImageToImage = (PFN_vkCopyImageToImage)gpa(device, "vkCopyImageToImage");
    table->TransitionImageLayout = (PFN_vkTransitionImageLayout)gpa(device, "vkTransitionImageLayout");
    table->GetCommandPoolMemoryConsumption = (PFN_vkGetCommandPoolMemoryConsumption)gpa(device, "vkGetCommandPoolMemoryConsumption");
    table->GetFaultData = (PFN_vkGetFaultData)gpa(device, "vkGetFaultData");
    table->CreateSwapchainKHR = (PFN_vkCreateSwapchainKHR)gpa(device, "vkCreateSwapchainKHR");
    table->GetSwapchainImagesKHR = (PFN_vkGetSwapchainImagesKHR)gpa(device, "vkGetSwapchainImagesKHR");
    table->AcquireNextImageKHR = (PFN_vkAcquireNextImageKHR)gpa(device, "vkAcquireNextImageKHR");
    table->QueuePresentKHR = (PFN_vkQueuePresentKHR)gpa(device, "vkQueuePresentKHR");
    table->GetDeviceGroupPresentCapabilitiesKHR = (PFN_vkGetDeviceGroupPresentCapabilitiesKHR)gpa(device, "vkGetDeviceGroupPresentCapabilitiesKHR");
    table->GetDeviceGroupSurfacePresentModesKHR = (PFN_vkGetDeviceGroupSurfacePresentModesKHR)gpa(device, "vkGetDeviceGroupSurfacePresentModesKHR");
    table->AcquireNextImage2KHR = (PFN_vkAcquireNextImage2KHR)gpa(device, "vkAcquireNextImage2KHR");
    table->CreateSharedSwapchainsKHR = (PFN_vkCreateSharedSwapchainsKHR)gpa(device, "vkCreateSharedSwapchainsKHR");
    table->GetMemoryFdKHR = (PFN_vkGetMemoryFdKHR)gpa(device, "vkGetMemoryFdKHR");
    table->GetMemoryFdPropertiesKHR = (PFN_vkGetMemoryFdPropertiesKHR)gpa(device, "vkGetMemoryFdPropertiesKHR");
    table->ImportSemaphoreFdKHR = (PFN_vkImportSemaphoreFdKHR)gpa(device, "vkImportSemaphoreFdKHR");
    table->GetSemaphoreFdKHR = (PFN_vkGetSemaphoreFdKHR)gpa(device, "vkGetSemaphoreFdKHR");
    table->GetSwapchainStatusKHR = (PFN_vkGetSwapchainStatusKHR)gpa(device, "vkGetSwapchainStatusKHR");
    table->ImportFenceFdKHR = (PFN_vkImportFenceFdKHR)gpa(device, "vkImportFenceFdKHR");
    table->GetFenceFdKHR = (PFN_vkGetFenceFdKHR)gpa(device, "vkGetFenceFdKHR");
    table->AcquireProfilingLockKHR = (PFN_vkAcquireProfilingLockKHR)gpa(device, "vkAcquireProfilingLockKHR");
    table->ReleaseProfilingLockKHR = (PFN_vkReleaseProfilingLockKHR)gpa(device, "vkReleaseProfilingLockKHR");
    table->CmdSetFragmentShadingRateKHR = (PFN_vkCmdSetFragmentShadingRateKHR)gpa(device, "vkCmdSetFragmentShadingRateKHR");
    table->CmdRefreshObjectsKHR = (PFN_vkCmdRefreshObjectsKHR)gpa(device, "vkCmdRefreshObjectsKHR");
    table->CmdSetEvent2KHR = (PFN_vkCmdSetEvent2KHR)gpa(device, "vkCmdSetEvent2KHR");
    table->CmdResetEvent2KHR = (PFN_vkCmdResetEvent2KHR)gpa(device, "vkCmdResetEvent2KHR");
    table->CmdWaitEvents2KHR = (PFN_vkCmdWaitEvents2KHR)gpa(device, "vkCmdWaitEvents2KHR");
    table->CmdPipelineBarrier2KHR = (PFN_vkCmdPipelineBarrier2KHR)gpa(device, "vkCmdPipelineBarrier2KHR");
    table->CmdWriteTimestamp2KHR = (PFN_vkCmdWriteTimestamp2KHR)gpa(device, "vkCmdWriteTimestamp2KHR");
    table->QueueSubmit2KHR = (PFN_vkQueueSubmit2KHR)gpa(device, "vkQueueSubmit2KHR");
    table->CmdCopyBuffer2KHR = (PFN_vkCmdCopyBuffer2KHR)gpa(device, "vkCmdCopyBuffer2KHR");
    table->CmdCopyImage2KHR = (PFN_vkCmdCopyImage2KHR)gpa(device, "vkCmdCopyImage2KHR");
    table->CmdCopyBufferToImage2KHR = (PFN_vkCmdCopyBufferToImage2KHR)gpa(device, "vkCmdCopyBufferToImage2KHR");
    table->CmdCopyImageToBuffer2KHR = (PFN_vkCmdCopyImageToBuffer2KHR)gpa(device, "vkCmdCopyImageToBuffer2KHR");
    table->CmdBlitImage2KHR = (PFN_vkCmdBlitImage2KHR)gpa(device, "vkCmdBlitImage2KHR");
    table->CmdResolveImage2KHR = (PFN_vkCmdResolveImage2KHR)gpa(device, "vkCmdResolveImage2KHR");
    table->CmdSetLineStippleKHR = (PFN_vkCmdSetLineStippleKHR)gpa(device, "vkCmdSetLineStippleKHR");
    table->GetCalibratedTimestampsKHR = (PFN_vkGetCalibratedTimestampsKHR)gpa(device, "vkGetCalibratedTimestampsKHR");
    table->DisplayPowerControlEXT = (PFN_vkDisplayPowerControlEXT)gpa(device, "vkDisplayPowerControlEXT");
    table->RegisterDeviceEventEXT = (PFN_vkRegisterDeviceEventEXT)gpa(device, "vkRegisterDeviceEventEXT");
    table->RegisterDisplayEventEXT = (PFN_vkRegisterDisplayEventEXT)gpa(device, "vkRegisterDisplayEventEXT");
    table->GetSwapchainCounterEXT = (PFN_vkGetSwapchainCounterEXT)gpa(device, "vkGetSwapchainCounterEXT");
    table->CmdSetDiscardRectangleEXT = (PFN_vkCmdSetDiscardRectangleEXT)gpa(device, "vkCmdSetDiscardRectangleEXT");
    table->CmdSetDiscardRectangleEnableEXT = (PFN_vkCmdSetDiscardRectangleEnableEXT)gpa(device, "vkCmdSetDiscardRectangleEnableEXT");
    table->CmdSetDiscardRectangleModeEXT = (PFN_vkCmdSetDiscardRectangleModeEXT)gpa(device, "vkCmdSetDiscardRectangleModeEXT");
    table->SetHdrMetadataEXT = (PFN_vkSetHdrMetadataEXT)gpa(device, "vkSetHdrMetadataEXT");
    table->SetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)gpa(device, "vkSetDebugUtilsObjectNameEXT");
    table->SetDebugUtilsObjectTagEXT = (PFN_vkSetDebugUtilsObjectTagEXT)gpa(device, "vkSetDebugUtilsObjectTagEXT");
    table->QueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)gpa(device, "vkQueueBeginDebugUtilsLabelEXT");
    table->QueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)gpa(device, "vkQueueEndDebugUtilsLabelEXT");
    table->QueueInsertDebugUtilsLabelEXT = (PFN_vkQueueInsertDebugUtilsLabelEXT)gpa(device, "vkQueueInsertDebugUtilsLabelEXT");
    table->CmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)gpa(device, "vkCmdBeginDebugUtilsLabelEXT");
    table->CmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)gpa(device, "vkCmdEndDebugUtilsLabelEXT");
    table->CmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)gpa(device, "vkCmdInsertDebugUtilsLabelEXT");
    table->CmdSetSampleLocationsEXT = (PFN_vkCmdSetSampleLocationsEXT)gpa(device, "vkCmdSetSampleLocationsEXT");
    table->GetImageDrmFormatModifierPropertiesEXT = (PFN_vkGetImageDrmFormatModifierPropertiesEXT)gpa(device, "vkGetImageDrmFormatModifierPropertiesEXT");
    table->GetMemoryHostPointerPropertiesEXT = (PFN_vkGetMemoryHostPointerPropertiesEXT)gpa(device, "vkGetMemoryHostPointerPropertiesEXT");
    table->CmdSetLineStippleEXT = (PFN_vkCmdSetLineStippleEXT)gpa(device, "vkCmdSetLineStippleEXT");
    table->CmdSetCullModeEXT = (PFN_vkCmdSetCullModeEXT)gpa(device, "vkCmdSetCullModeEXT");
    table->CmdSetFrontFaceEXT = (PFN_vkCmdSetFrontFaceEXT)gpa(device, "vkCmdSetFrontFaceEXT");
    table->CmdSetPrimitiveTopologyEXT = (PFN_vkCmdSetPrimitiveTopologyEXT)gpa(device, "vkCmdSetPrimitiveTopologyEXT");
    table->CmdSetViewportWithCountEXT = (PFN_vkCmdSetViewportWithCountEXT)gpa(device, "vkCmdSetViewportWithCountEXT");
    table->CmdSetScissorWithCountEXT = (PFN_vkCmdSetScissorWithCountEXT)gpa(device, "vkCmdSetScissorWithCountEXT");
    table->CmdBindVertexBuffers2EXT = (PFN_vkCmdBindVertexBuffers2EXT)gpa(device, "vkCmdBindVertexBuffers2EXT");
    table->CmdSetDepthTestEnableEXT = (PFN_vkCmdSetDepthTestEnableEXT)gpa(device, "vkCmdSetDepthTestEnableEXT");
    table->CmdSetDepthWriteEnableEXT = (PFN_vkCmdSetDepthWriteEnableEXT)gpa(device, "vkCmdSetDepthWriteEnableEXT");
    table->CmdSetDepthCompareOpEXT = (PFN_vkCmdSetDepthCompareOpEXT)gpa(device, "vkCmdSetDepthCompareOpEXT");
    table->CmdSetDepthBoundsTestEnableEXT = (PFN_vkCmdSetDepthBoundsTestEnableEXT)gpa(device, "vkCmdSetDepthBoundsTestEnableEXT");
    table->CmdSetStencilTestEnableEXT = (PFN_vkCmdSetStencilTestEnableEXT)gpa(device, "vkCmdSetStencilTestEnableEXT");
    table->CmdSetStencilOpEXT = (PFN_vkCmdSetStencilOpEXT)gpa(device, "vkCmdSetStencilOpEXT");
    table->CmdSetVertexInputEXT = (PFN_vkCmdSetVertexInputEXT)gpa(device, "vkCmdSetVertexInputEXT");
#if defined(VK_USE_PLATFORM_SCI)
    table->GetFenceSciSyncFenceNV = (PFN_vkGetFenceSciSyncFenceNV)gpa(device, "vkGetFenceSciSyncFenceNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->GetFenceSciSyncObjNV = (PFN_vkGetFenceSciSyncObjNV)gpa(device, "vkGetFenceSciSyncObjNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->ImportFenceSciSyncFenceNV = (PFN_vkImportFenceSciSyncFenceNV)gpa(device, "vkImportFenceSciSyncFenceNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->ImportFenceSciSyncObjNV = (PFN_vkImportFenceSciSyncObjNV)gpa(device, "vkImportFenceSciSyncObjNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->GetSemaphoreSciSyncObjNV = (PFN_vkGetSemaphoreSciSyncObjNV)gpa(device, "vkGetSemaphoreSciSyncObjNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->ImportSemaphoreSciSyncObjNV = (PFN_vkImportSemaphoreSciSyncObjNV)gpa(device, "vkImportSemaphoreSciSyncObjNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->GetMemorySciBufNV = (PFN_vkGetMemorySciBufNV)gpa(device, "vkGetMemorySciBufNV");
#endif  // VK_USE_PLATFORM_SCI
    table->CmdSetPatchControlPointsEXT = (PFN_vkCmdSetPatchControlPointsEXT)gpa(device, "vkCmdSetPatchControlPointsEXT");
    table->CmdSetRasterizerDiscardEnableEXT = (PFN_vkCmdSetRasterizerDiscardEnableEXT)gpa(device, "vkCmdSetRasterizerDiscardEnableEXT");
    table->CmdSetDepthBiasEnableEXT = (PFN_vkCmdSetDepthBiasEnableEXT)gpa(device, "vkCmdSetDepthBiasEnableEXT");
    table->CmdSetLogicOpEXT = (PFN_vkCmdSetLogicOpEXT)gpa(device, "vkCmdSetLogicOpEXT");
    table->CmdSetPrimitiveRestartEnableEXT = (PFN_vkCmdSetPrimitiveRestartEnableEXT)gpa(device, "vkCmdSetPrimitiveRestartEnableEXT");
    table->CmdSetColorWriteEnableEXT = (PFN_vkCmdSetColorWriteEnableEXT)gpa(device, "vkCmdSetColorWriteEnableEXT");
#if defined(VK_USE_PLATFORM_SCI)
    table->CreateSemaphoreSciSyncPoolNV = (PFN_vkCreateSemaphoreSciSyncPoolNV)gpa(device, "vkCreateSemaphoreSciSyncPoolNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCREEN_QNX)
    table->GetScreenBufferPropertiesQNX = (PFN_vkGetScreenBufferPropertiesQNX)gpa(device, "vkGetScreenBufferPropertiesQNX");
#endif  // VK_USE_PLATFORM_SCREEN_QNX
    // clang-format on
}

// clang-format off
static inline void layer_init_instance_dispatch_table(VkInstance instance, VkLayerInstanceDispatchTable *table, PFN_vkGetInstanceProcAddr gpa) {
    memset(table, 0, sizeof(*table));

    // Instance function pointers
    table->CreateInstance = (PFN_vkCreateInstance)gpa(instance, "vkCreateInstance");
    table->DestroyInstance = (PFN_vkDestroyInstance)gpa(instance, "vkDestroyInstance");
    table->EnumeratePhysicalDevices = (PFN_vkEnumeratePhysicalDevices)gpa(instance, "vkEnumeratePhysicalDevices");
    table->GetPhysicalDeviceFeatures = (PFN_vkGetPhysicalDeviceFeatures)gpa(instance, "vkGetPhysicalDeviceFeatures");
    table->GetPhysicalDeviceFormatProperties = (PFN_vkGetPhysicalDeviceFormatProperties)gpa(instance, "vkGetPhysicalDeviceFormatProperties");
    table->GetPhysicalDeviceImageFormatProperties = (PFN_vkGetPhysicalDeviceImageFormatProperties)gpa(instance, "vkGetPhysicalDeviceImageFormatProperties");
    table->GetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)gpa(instance, "vkGetPhysicalDeviceProperties");
    table->GetPhysicalDeviceQueueFamilyProperties = (PFN_vkGetPhysicalDeviceQueueFamilyProperties)gpa(instance, "vkGetPhysicalDeviceQueueFamilyProperties");
    table->GetPhysicalDeviceMemoryProperties = (PFN_vkGetPhysicalDeviceMemoryProperties)gpa(instance, "vkGetPhysicalDeviceMemoryProperties");
    table->GetInstanceProcAddr = gpa;
    table->CreateDevice = (PFN_vkCreateDevice)gpa(instance, "vkCreateDevice");
    table->EnumerateInstanceExtensionProperties = (PFN_vkEnumerateInstanceExtensionProperties)gpa(instance, "vkEnumerateInstanceExtensionProperties");
    table->EnumerateDeviceExtensionProperties = (PFN_vkEnumerateDeviceExtensionProperties)gpa(instance, "vkEnumerateDeviceExtensionProperties");
    table->EnumerateInstanceLayerProperties = (PFN_vkEnumerateInstanceLayerProperties)gpa(instance, "vkEnumerateInstanceLayerProperties");
    table->EnumerateDeviceLayerProperties = (PFN_vkEnumerateDeviceLayerProperties)gpa(instance, "vkEnumerateDeviceLayerProperties");
    table->EnumerateInstanceVersion = (PFN_vkEnumerateInstanceVersion)gpa(instance, "vkEnumerateInstanceVersion");
    table->EnumeratePhysicalDeviceGroups = (PFN_vkEnumeratePhysicalDeviceGroups)gpa(instance, "vkEnumeratePhysicalDeviceGroups");
    table->GetPhysicalDeviceFeatures2 = (PFN_vkGetPhysicalDeviceFeatures2)gpa(instance, "vkGetPhysicalDeviceFeatures2");
    table->GetPhysicalDeviceProperties2 = (PFN_vkGetPhysicalDeviceProperties2)gpa(instance, "vkGetPhysicalDeviceProperties2");
    table->GetPhysicalDeviceFormatProperties2 = (PFN_vkGetPhysicalDeviceFormatProperties2)gpa(instance, "vkGetPhysicalDeviceFormatProperties2");
    table->GetPhysicalDeviceImageFormatProperties2 = (PFN_vkGetPhysicalDeviceImageFormatProperties2)gpa(instance, "vkGetPhysicalDeviceImageFormatProperties2");
    table->GetPhysicalDeviceQueueFamilyProperties2 = (PFN_vkGetPhysicalDeviceQueueFamilyProperties2)gpa(instance, "vkGetPhysicalDeviceQueueFamilyProperties2");
    table->GetPhysicalDeviceMemoryProperties2 = (PFN_vkGetPhysicalDeviceMemoryProperties2)gpa(instance, "vkGetPhysicalDeviceMemoryProperties2");
    table->GetPhysicalDeviceExternalBufferProperties = (PFN_vkGetPhysicalDeviceExternalBufferProperties)gpa(instance, "vkGetPhysicalDeviceExternalBufferProperties");
    table->GetPhysicalDeviceExternalFenceProperties = (PFN_vkGetPhysicalDeviceExternalFenceProperties)gpa(instance, "vkGetPhysicalDeviceExternalFenceProperties");
    table->GetPhysicalDeviceExternalSemaphoreProperties = (PFN_vkGetPhysicalDeviceExternalSemaphoreProperties)gpa(instance, "vkGetPhysicalDeviceExternalSemaphoreProperties");
    table->GetPhysicalDeviceToolProperties = (PFN_vkGetPhysicalDeviceToolProperties)gpa(instance, "vkGetPhysicalDeviceToolProperties");
    table->DestroySurfaceKHR = (PFN_vkDestroySurfaceKHR)gpa(instance, "vkDestroySurfaceKHR");
    table->GetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)gpa(instance, "vkGetPhysicalDeviceSurfaceSupportKHR");
    table->GetPhysicalDeviceSurfaceCapabilitiesKHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR)gpa(instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR");
    table->GetPhysicalDeviceSurfaceFormatsKHR = (PFN_vkGetPhysicalDeviceSurfaceFormatsKHR)gpa(instance, "vkGetPhysicalDeviceSurfaceFormatsKHR");
    table->GetPhysicalDeviceSurfacePresentModesKHR = (PFN_vkGetPhysicalDeviceSurfacePresentModesKHR)gpa(instance, "vkGetPhysicalDeviceSurfacePresentModesKHR");
    table->GetPhysicalDevicePresentRectanglesKHR = (PFN_vkGetPhysicalDevicePresentRectanglesKHR)gpa(instance, "vkGetPhysicalDevicePresentRectanglesKHR");
    table->GetPhysicalDeviceDisplayPropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPropertiesKHR)gpa(instance, "vkGetPhysicalDeviceDisplayPropertiesKHR");
    table->GetPhysicalDeviceDisplayPlanePropertiesKHR = (PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR)gpa(instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR");
    table->GetDisplayPlaneSupportedDisplaysKHR = (PFN_vkGetDisplayPlaneSupportedDisplaysKHR)gpa(instance, "vkGetDisplayPlaneSupportedDisplaysKHR");
    table->GetDisplayModePropertiesKHR = (PFN_vkGetDisplayModePropertiesKHR)gpa(instance, "vkGetDisplayModePropertiesKHR");
    table->CreateDisplayModeKHR = (PFN_vkCreateDisplayModeKHR)gpa(instance, "vkCreateDisplayModeKHR");
    table->GetDisplayPlaneCapabilitiesKHR = (PFN_vkGetDisplayPlaneCapabilitiesKHR)gpa(instance, "vkGetDisplayPlaneCapabilitiesKHR");
    table->CreateDisplayPlaneSurfaceKHR = (PFN_vkCreateDisplayPlaneSurfaceKHR)gpa(instance, "vkCreateDisplayPlaneSurfaceKHR");
    table->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = (PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR)gpa(instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR");
    table->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = (PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR)gpa(instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR");
    table->GetPhysicalDeviceSurfaceCapabilities2KHR = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR)gpa(instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR");
    table->GetPhysicalDeviceSurfaceFormats2KHR = (PFN_vkGetPhysicalDeviceSurfaceFormats2KHR)gpa(instance, "vkGetPhysicalDeviceSurfaceFormats2KHR");
    table->GetPhysicalDeviceDisplayProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayProperties2KHR)gpa(instance, "vkGetPhysicalDeviceDisplayProperties2KHR");
    table->GetPhysicalDeviceDisplayPlaneProperties2KHR = (PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR)gpa(instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR");
    table->GetDisplayModeProperties2KHR = (PFN_vkGetDisplayModeProperties2KHR)gpa(instance, "vkGetDisplayModeProperties2KHR");
    table->GetDisplayPlaneCapabilities2KHR = (PFN_vkGetDisplayPlaneCapabilities2KHR)gpa(instance, "vkGetDisplayPlaneCapabilities2KHR");
    table->GetPhysicalDeviceFragmentShadingRatesKHR = (PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR)gpa(instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR");
    table->GetPhysicalDeviceRefreshableObjectTypesKHR = (PFN_vkGetPhysicalDeviceRefreshableObjectTypesKHR)gpa(instance, "vkGetPhysicalDeviceRefreshableObjectTypesKHR");
    table->GetPhysicalDeviceCalibrateableTimeDomainsKHR = (PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR)gpa(instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR");
    table->ReleaseDisplayEXT = (PFN_vkReleaseDisplayEXT)gpa(instance, "vkReleaseDisplayEXT");
    table->GetPhysicalDeviceSurfaceCapabilities2EXT = (PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT)gpa(instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT");
    table->CreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)gpa(instance, "vkCreateDebugUtilsMessengerEXT");
    table->DestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)gpa(instance, "vkDestroyDebugUtilsMessengerEXT");
    table->SubmitDebugUtilsMessageEXT = (PFN_vkSubmitDebugUtilsMessageEXT)gpa(instance, "vkSubmitDebugUtilsMessageEXT");
    table->GetPhysicalDeviceMultisamplePropertiesEXT = (PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT)gpa(instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT");
    table->CreateHeadlessSurfaceEXT = (PFN_vkCreateHeadlessSurfaceEXT)gpa(instance, "vkCreateHeadlessSurfaceEXT");
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->AcquireWinrtDisplayNV = (PFN_vkAcquireWinrtDisplayNV)gpa(instance, "vkAcquireWinrtDisplayNV");
#endif  // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    table->GetWinrtDisplayNV = (PFN_vkGetWinrtDisplayNV)gpa(instance, "vkGetWinrtDisplayNV");
#endif  // VK_USE_PLATFORM_WIN32_KHR
#if defined(VK_USE_PLATFORM_SCI)
    table->GetPhysicalDeviceSciSyncAttributesNV = (PFN_vkGetPhysicalDeviceSciSyncAttributesNV)gpa(instance, "vkGetPhysicalDeviceSciSyncAttributesNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->GetPhysicalDeviceExternalMemorySciBufPropertiesNV = (PFN_vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV)gpa(instance, "vkGetPhysicalDeviceExternalMemorySciBufPropertiesNV");
#endif  // VK_USE_PLATFORM_SCI
#if defined(VK_USE_PLATFORM_SCI)
    table->GetPhysicalDeviceSciBufAttributesNV = (PFN_vkGetPhysicalDeviceSciBufAttributesNV)gpa(instance, "vkGetPhysicalDeviceSciBufAttributesNV");
#endif  // VK_USE_PLATFORM_SCI
    // clang-format on
}
