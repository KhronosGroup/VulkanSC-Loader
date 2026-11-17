// *** THIS FILE IS GENERATED - DO NOT EDIT ***
// See loader_core_generator.py for modifications

/*
 * Copyright (c) 2026 The Khronos Group Inc.
 * Copyright (c) 2026 Valve Corporation
 * Copyright (c) 2026 LunarG, Inc.
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
 * Author: Charles Giessen <charles@lunarg.com>
 */

#include <vulkan/vulkan.h>
#include "vk_loader_platform.h"
#include "loader.h"

// ---- Core Vulkan SC 1.0 commands
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice,
                                                                     VkPhysicalDeviceFeatures* pFeatures) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceFeatures(unwrapped_phys_dev, pFeatures);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                             VkFormatProperties* pFormatProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceFormatProperties(unwrapped_phys_dev, format, pFormatProperties);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties(
    VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage,
    VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceImageFormatProperties(unwrapped_phys_dev, format, type, tiling, usage, flags,
                                                        pImageFormatProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice,
                                                                       VkPhysicalDeviceProperties* pProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceProperties(unwrapped_phys_dev, pProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice,
                                                                                  uint32_t* pQueueFamilyPropertyCount,
                                                                                  VkQueueFamilyProperties* pQueueFamilyProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceQueueFamilyProperties(unwrapped_phys_dev, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice,
                                                                             VkPhysicalDeviceMemoryProperties* pMemoryProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceMemoryProperties(unwrapped_phys_dev, pMemoryProperties);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits,
                                                           VkFence fence) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_queue_dispatch(queue, __FUNCTION__);
    return disp->QueueSubmit(queue, submitCount, pSubmits, fence);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkQueueWaitIdle(VkQueue queue) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_queue_dispatch(queue, __FUNCTION__);
    return disp->QueueWaitIdle(queue);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkDeviceWaitIdle(VkDevice device) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->DeviceWaitIdle(device);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo,
                                                              const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->AllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset,
                                                         VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->MapMemory(device, memory, offset, size, flags, ppData);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkUnmapMemory(VkDevice device, VkDeviceMemory memory) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->UnmapMemory(device, memory);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount,
                                                                       const VkMappedMemoryRange* pMemoryRanges) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->FlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount,
                                                                            const VkMappedMemoryRange* pMemoryRanges) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->InvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory,
                                                                     VkDeviceSize* pCommittedMemoryInBytes) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory,
                                                                VkDeviceSize memoryOffset) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->BindBufferMemory(device, buffer, memory, memoryOffset);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory,
                                                               VkDeviceSize memoryOffset) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->BindImageMemory(device, image, memory, memoryOffset);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer,
                                                                       VkMemoryRequirements* pMemoryRequirements) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements(VkDevice device, VkImage image,
                                                                      VkMemoryRequirements* pMemoryRequirements) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetImageMemoryRequirements(device, image, pMemoryRequirements);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo,
                                                           const VkAllocationCallbacks* pAllocator, VkFence* pFence) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateFence(device, pCreateInfo, pAllocator, pFence);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyFence(device, fence, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->ResetFences(device, fenceCount, pFences);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceStatus(VkDevice device, VkFence fence) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->GetFenceStatus(device, fence);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences,
                                                             VkBool32 waitAll, uint64_t timeout) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->WaitForFences(device, fenceCount, pFences, waitAll, timeout);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo,
                                                               const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySemaphore(VkDevice device, VkSemaphore semaphore,
                                                            const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroySemaphore(device, semaphore, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo,
                                                               const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery,
                                                                   uint32_t queryCount, size_t dataSize, void* pData,
                                                                   VkDeviceSize stride, VkQueryResultFlags flags) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->GetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo,
                                                            const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyBuffer(VkDevice device, VkBuffer buffer,
                                                         const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyBuffer(device, buffer, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo,
                                                           const VkAllocationCallbacks* pAllocator, VkImage* pImage) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateImage(device, pCreateInfo, pAllocator, pImage);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyImage(device, image, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetImageSubresourceLayout(VkDevice device, VkImage image,
                                                                     const VkImageSubresource* pSubresource,
                                                                     VkSubresourceLayout* pLayout) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetImageSubresourceLayout(device, image, pSubresource, pLayout);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo,
                                                               const VkAllocationCallbacks* pAllocator, VkImageView* pView) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateImageView(device, pCreateInfo, pAllocator, pView);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyImageView(VkDevice device, VkImageView imageView,
                                                            const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyImageView(device, imageView, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo,
                                                                 const VkAllocationCallbacks* pAllocator,
                                                                 VkCommandPool* pCommandPool) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(VkDevice device, VkCommandPool commandPool,
                                                                VkCommandPoolResetFlags flags) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->ResetCommandPool(device, commandPool, flags);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool,
                                                              uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->FreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBeginCommandBuffer(VkCommandBuffer commandBuffer,
                                                                  const VkCommandBufferBeginInfo* pBeginInfo) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    return disp->BeginCommandBuffer(commandBuffer, pBeginInfo);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEndCommandBuffer(VkCommandBuffer commandBuffer) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    return disp->EndCommandBuffer(commandBuffer);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    return disp->ResetCommandBuffer(commandBuffer, flags);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer,
                                                         uint32_t regionCount, const VkBufferCopy* pRegions) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage,
                                                        VkImageLayout srcImageLayout, VkImage dstImage,
                                                        VkImageLayout dstImageLayout, uint32_t regionCount,
                                                        const VkImageCopy* pRegions) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage,
                                                                VkImageLayout dstImageLayout, uint32_t regionCount,
                                                                const VkBufferImageCopy* pRegions) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage,
                                                                VkImageLayout srcImageLayout, VkBuffer dstBuffer,
                                                                uint32_t regionCount, const VkBufferImageCopy* pRegions) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer,
                                                           VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset,
                                                         VkDeviceSize size, uint32_t data) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask,
                                                              VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags,
                                                              uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers,
                                                              uint32_t bufferMemoryBarrierCount,
                                                              const VkBufferMemoryBarrier* pBufferMemoryBarriers,
                                                              uint32_t imageMemoryBarrierCount,
                                                              const VkImageMemoryBarrier* pImageMemoryBarriers) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers,
                             bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query,
                                                         VkQueryControlFlags flags) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdBeginQuery(commandBuffer, queryPool, query, flags);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdEndQuery(commandBuffer, queryPool, query);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool,
                                                             uint32_t firstQuery, uint32_t queryCount) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage,
                                                             VkQueryPool queryPool, uint32_t query) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool,
                                                                   uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer,
                                                                   VkDeviceSize dstOffset, VkDeviceSize stride,
                                                                   VkQueryResultFlags flags) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount,
                                                              const VkCommandBuffer* pCommandBuffers) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo,
                                                           const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateEvent(device, pCreateInfo, pAllocator, pEvent);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyEvent(device, event, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetEventStatus(VkDevice device, VkEvent event) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->GetEventStatus(device, event);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkSetEvent(VkDevice device, VkEvent event) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->SetEvent(device, event);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetEvent(VkDevice device, VkEvent event) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->ResetEvent(device, event);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo,
                                                                const VkAllocationCallbacks* pAllocator, VkBufferView* pView) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateBufferView(device, pCreateInfo, pAllocator, pView);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyBufferView(VkDevice device, VkBufferView bufferView,
                                                             const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyBufferView(device, bufferView, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo,
                                                                   const VkAllocationCallbacks* pAllocator,
                                                                   VkPipelineCache* pPipelineCache) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache,
                                                                const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyPipelineCache(device, pipelineCache, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache,
                                                                      uint32_t createInfoCount,
                                                                      const VkComputePipelineCreateInfo* pCreateInfos,
                                                                      const VkAllocationCallbacks* pAllocator,
                                                                      VkPipeline* pPipelines) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyPipeline(VkDevice device, VkPipeline pipeline,
                                                           const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyPipeline(device, pipeline, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo,
                                                                    const VkAllocationCallbacks* pAllocator,
                                                                    VkPipelineLayout* pPipelineLayout) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout,
                                                                 const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyPipelineLayout(device, pipelineLayout, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo,
                                                             const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateSampler(device, pCreateInfo, pAllocator, pSampler);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySampler(VkDevice device, VkSampler sampler,
                                                          const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroySampler(device, sampler, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorSetLayout(VkDevice device,
                                                                         const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
                                                                         const VkAllocationCallbacks* pAllocator,
                                                                         VkDescriptorSetLayout* pSetLayout) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout,
                                                                      const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo,
                                                                    const VkAllocationCallbacks* pAllocator,
                                                                    VkDescriptorPool* pDescriptorPool) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool,
                                                                   VkDescriptorPoolResetFlags flags) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->ResetDescriptorPool(device, descriptorPool, flags);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkAllocateDescriptorSets(VkDevice device,
                                                                      const VkDescriptorSetAllocateInfo* pAllocateInfo,
                                                                      VkDescriptorSet* pDescriptorSets) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->AllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool,
                                                                  uint32_t descriptorSetCount,
                                                                  const VkDescriptorSet* pDescriptorSets) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->FreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount,
                                                                const VkWriteDescriptorSet* pDescriptorWrites,
                                                                uint32_t descriptorCopyCount,
                                                                const VkCopyDescriptorSet* pDescriptorCopies) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->UpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint,
                                                           VkPipeline pipeline) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer,
                                                                 VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout,
                                                                 uint32_t firstSet, uint32_t descriptorSetCount,
                                                                 const VkDescriptorSet* pDescriptorSets,
                                                                 uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets,
                                dynamicOffsetCount, pDynamicOffsets);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image,
                                                              VkImageLayout imageLayout, const VkClearColorValue* pColor,
                                                              uint32_t rangeCount, const VkImageSubresourceRange* pRanges) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY,
                                                       uint32_t groupCountZ) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer,
                                                               VkDeviceSize offset) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDispatchIndirect(commandBuffer, buffer, offset);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event,
                                                       VkPipelineStageFlags stageMask) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetEvent(commandBuffer, event, stageMask);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event,
                                                         VkPipelineStageFlags stageMask) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdResetEvent(commandBuffer, event, stageMask);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents,
                                                         VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask,
                                                         uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers,
                                                         uint32_t bufferMemoryBarrierCount,
                                                         const VkBufferMemoryBarrier* pBufferMemoryBarriers,
                                                         uint32_t imageMemoryBarrierCount,
                                                         const VkImageMemoryBarrier* pImageMemoryBarriers) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers,
                        bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout,
                                                            VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size,
                                                            const void* pValues) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache,
                                                                       uint32_t createInfoCount,
                                                                       const VkGraphicsPipelineCreateInfo* pCreateInfos,
                                                                       const VkAllocationCallbacks* pAllocator,
                                                                       VkPipeline* pPipelines) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo,
                                                                 const VkAllocationCallbacks* pAllocator,
                                                                 VkFramebuffer* pFramebuffer) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer,
                                                              const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyFramebuffer(device, framebuffer, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo,
                                                                const VkAllocationCallbacks* pAllocator,
                                                                VkRenderPass* pRenderPass) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass,
                                                             const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroyRenderPass(device, renderPass, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass,
                                                                    VkExtent2D* pGranularity) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetRenderAreaGranularity(device, renderPass, pGranularity);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport,
                                                          uint32_t viewportCount, const VkViewport* pViewports) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor,
                                                         uint32_t scissorCount, const VkRect2D* pScissors) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetLineWidth(commandBuffer, lineWidth);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor,
                                                           float depthBiasClamp, float depthBiasSlopeFactor) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetBlendConstants(commandBuffer, blendConstants);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds,
                                                             float maxDepthBounds) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask,
                                                                    uint32_t compareMask) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetStencilCompareMask(commandBuffer, faceMask, compareMask);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask,
                                                                  uint32_t writeMask) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetStencilWriteMask(commandBuffer, faceMask, writeMask);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask,
                                                                  uint32_t reference) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetStencilReference(commandBuffer, faceMask, reference);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset,
                                                              VkIndexType indexType) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding,
                                                                uint32_t bindingCount, const VkBuffer* pBuffers,
                                                                const VkDeviceSize* pOffsets) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount,
                                                   uint32_t firstVertex, uint32_t firstInstance) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount,
                                                          uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset,
                                                          uint32_t firstInstance) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset,
                                                           uint32_t drawCount, uint32_t stride) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer,
                                                                  VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage,
                                                        VkImageLayout srcImageLayout, VkImage dstImage,
                                                        VkImageLayout dstImageLayout, uint32_t regionCount,
                                                        const VkImageBlit* pRegions, VkFilter filter) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image,
                                                                     VkImageLayout imageLayout,
                                                                     const VkClearDepthStencilValue* pDepthStencil,
                                                                     uint32_t rangeCount, const VkImageSubresourceRange* pRanges) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount,
                                                               const VkClearAttachment* pAttachments, uint32_t rectCount,
                                                               const VkClearRect* pRects) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage,
                                                           VkImageLayout srcImageLayout, VkImage dstImage,
                                                           VkImageLayout dstImageLayout, uint32_t regionCount,
                                                           const VkImageResolve* pRegions) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass(VkCommandBuffer commandBuffer,
                                                              const VkRenderPassBeginInfo* pRenderPassBegin,
                                                              VkSubpassContents contents) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdNextSubpass(commandBuffer, contents);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass(VkCommandBuffer commandBuffer) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdEndRenderPass(commandBuffer);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory2(VkDevice device, uint32_t bindInfoCount,
                                                                 const VkBindBufferMemoryInfo* pBindInfos) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->BindBufferMemory2(device, bindInfoCount, pBindInfos);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory2(VkDevice device, uint32_t bindInfoCount,
                                                                const VkBindImageMemoryInfo* pBindInfos) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->BindImageMemory2(device, bindInfoCount, pBindInfos);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex,
                                                                            uint32_t localDeviceIndex, uint32_t remoteDeviceIndex,
                                                                            VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdSetDeviceMask(commandBuffer, deviceMask);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo,
                                                                       VkMemoryRequirements2* pMemoryRequirements) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetImageMemoryRequirements2(device, pInfo, pMemoryRequirements);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements2(VkDevice device,
                                                                        const VkBufferMemoryRequirementsInfo2* pInfo,
                                                                        VkMemoryRequirements2* pMemoryRequirements) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice,
                                                                      VkPhysicalDeviceFeatures2* pFeatures) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceFeatures2(unwrapped_phys_dev, pFeatures);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice,
                                                                        VkPhysicalDeviceProperties2* pProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceProperties2(unwrapped_phys_dev, pProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format,
                                                                              VkFormatProperties2* pFormatProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceFormatProperties2(unwrapped_phys_dev, format, pFormatProperties);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL
vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo,
                                          VkImageFormatProperties2* pImageFormatProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    return disp->GetPhysicalDeviceImageFormatProperties2(unwrapped_phys_dev, pImageFormatInfo, pImageFormatProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceQueueFamilyProperties2(unwrapped_phys_dev, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL
vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceMemoryProperties2(unwrapped_phys_dev, pMemoryProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalBufferProperties(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo,
    VkExternalBufferProperties* pExternalBufferProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceExternalBufferProperties(unwrapped_phys_dev, pExternalBufferInfo, pExternalBufferProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalFenceProperties(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo,
    VkExternalFenceProperties* pExternalFenceProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceExternalFenceProperties(unwrapped_phys_dev, pExternalFenceInfo, pExternalFenceProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalSemaphoreProperties(
    VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties* pExternalSemaphoreProperties) {
    VkPhysicalDevice unwrapped_phys_dev = loader_unwrap_physical_device(physicalDevice, __FUNCTION__);
    const VkLayerInstanceDispatchTable* disp = loader_get_instance_layer_dispatch(physicalDevice);
    disp->GetPhysicalDeviceExternalSemaphoreProperties(unwrapped_phys_dev, pExternalSemaphoreInfo, pExternalSemaphoreProperties);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY,
                                                           uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY,
                                                           uint32_t groupCountZ) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSupport(VkDevice device,
                                                                         const VkDescriptorSetLayoutCreateInfo* pCreateInfo,
                                                                         VkDescriptorSetLayoutSupport* pSupport) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateSamplerYcbcrConversion(VkDevice device,
                                                                            const VkSamplerYcbcrConversionCreateInfo* pCreateInfo,
                                                                            const VkAllocationCallbacks* pAllocator,
                                                                            VkSamplerYcbcrConversion* pYcbcrConversion) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkDestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion,
                                                                         const VkAllocationCallbacks* pAllocator) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->DestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery,
                                                          uint32_t queryCount) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->ResetQueryPool(device, queryPool, firstQuery, queryCount);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->GetSemaphoreCounterValue(device, semaphore, pValue);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkWaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo,
                                                              uint64_t timeout) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->WaitSemaphores(device, pWaitInfo, timeout);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkSignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->SignalSemaphore(device, pSignalInfo);
}
LOADER_EXPORT VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetBufferDeviceAddress(VkDevice device,
                                                                             const VkBufferDeviceAddressInfo* pInfo) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->GetBufferDeviceAddress(device, pInfo);
}
LOADER_EXPORT VKAPI_ATTR uint64_t VKAPI_CALL vkGetBufferOpaqueCaptureAddress(VkDevice device,
                                                                             const VkBufferDeviceAddressInfo* pInfo) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->GetBufferOpaqueCaptureAddress(device, pInfo);
}
LOADER_EXPORT VKAPI_ATTR uint64_t VKAPI_CALL
vkGetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->GetDeviceMemoryOpaqueCaptureAddress(device, pInfo);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset,
                                                                VkBuffer countBuffer, VkDeviceSize countBufferOffset,
                                                                uint32_t maxDrawCount, uint32_t stride) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer,
                                                                       VkDeviceSize offset, VkBuffer countBuffer,
                                                                       VkDeviceSize countBufferOffset, uint32_t maxDrawCount,
                                                                       uint32_t stride) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo,
                                                                 const VkAllocationCallbacks* pAllocator,
                                                                 VkRenderPass* pRenderPass) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->CreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass2(VkCommandBuffer commandBuffer,
                                                               const VkRenderPassBeginInfo* pRenderPassBegin,
                                                               const VkSubpassBeginInfo* pSubpassBeginInfo) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass2(VkCommandBuffer commandBuffer,
                                                           const VkSubpassBeginInfo* pSubpassBeginInfo,
                                                           const VkSubpassEndInfo* pSubpassEndInfo) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass2(VkCommandBuffer commandBuffer,
                                                             const VkSubpassEndInfo* pSubpassEndInfo) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_command_buffer_dispatch(commandBuffer, __FUNCTION__);
    disp->CmdEndRenderPass2(commandBuffer, pSubpassEndInfo);
}
LOADER_EXPORT VKAPI_ATTR void VKAPI_CALL vkGetCommandPoolMemoryConsumption(VkDevice device, VkCommandPool commandPool,
                                                                           VkCommandBuffer commandBuffer,
                                                                           VkCommandPoolMemoryConsumption* pConsumption) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    disp->GetCommandPoolMemoryConsumption(device, commandPool, commandBuffer, pConsumption);
}
LOADER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkGetFaultData(VkDevice device, VkFaultQueryBehavior faultQueryBehavior,
                                                            VkBool32* pUnrecordedFaults, uint32_t* pFaultCount,
                                                            VkFaultData* pFaults) {
    const VkLayerDispatchTable* disp = loader_validate_and_get_device_dispatch(device, __FUNCTION__);
    return disp->GetFaultData(device, faultQueryBehavior, pUnrecordedFaults, pFaultCount, pFaults);
}
