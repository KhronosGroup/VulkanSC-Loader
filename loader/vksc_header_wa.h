/*
 * Copyright (c) 2023-2023 The Khronos Group Inc.
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
 */
#pragma once

#ifdef VULKANSC
#include <vulkan/vulkan_sc.h>
#else
#include <vulkan/vulkan.h>
#endif // VULKANSC

// Workaround for missing definitions from the 1.0.12 header otherwise present in the XML
#if VK_HEADER_VERSION <= 12
typedef void (VKAPI_PTR *PFN_vkCmdSetDiscardRectangleEnableEXT)(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable);
typedef void (VKAPI_PTR *PFN_vkCmdSetDiscardRectangleModeEXT)(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode);

typedef VkDependencyInfoKHR VkDependencyInfo;
typedef VkPipelineStageFlags2KHR VkPipelineStageFlags2;
typedef VkSubmitInfo2KHR VkSubmitInfo2;
typedef VkCopyBufferInfo2KHR VkCopyBufferInfo2;
typedef VkCopyImageInfo2KHR VkCopyImageInfo2;
typedef VkCopyBufferToImageInfo2KHR VkCopyBufferToImageInfo2;
typedef VkCopyImageToBufferInfo2KHR VkCopyImageToBufferInfo2;
typedef VkBlitImageInfo2KHR VkBlitImageInfo2;
typedef VkResolveImageInfo2KHR VkResolveImageInfo2;
#endif
