/*
 *
 * Copyright (c) 2016-2021 The Khronos Group Inc.
 * Copyright (c) 2016-2021 Valve Corporation
 * Copyright (c) 2016-2021 LunarG, Inc.
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
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Charles Giessen <charles@lunarg.com>
 *
 */
#pragma once

#include <stdbool.h>
#ifdef VULKANSC
#include <vulkan/vulkan_sc.h>
#else
#include <vulkan/vulkan.h>
#endif

// Linked list node for tree of debug callbacks
#ifndef VULKANSC
typedef struct VkDebugReportContent {
    VkDebugReportCallbackEXT msgCallback;
    PFN_vkDebugReportCallbackEXT pfnMsgCallback;
    VkFlags msgFlags;
} VkDebugReportContent;
#endif  // VULKANSC

typedef struct VkDebugUtilsMessengerContent {
    VkDebugUtilsMessengerEXT messenger;
    VkDebugUtilsMessageSeverityFlagsEXT messageSeverity;
    VkDebugUtilsMessageTypeFlagsEXT messageType;
    PFN_vkDebugUtilsMessengerCallbackEXT pfnUserCallback;
} VkDebugUtilsMessengerContent;

typedef struct VkLayerDbgFunctionNode_ {
    bool is_messenger;
    union {
#ifndef VULKANSC
        VkDebugReportContent report;
#endif  // VULKANSC
        VkDebugUtilsMessengerContent messenger;
    };
    void *pUserData;
    struct VkLayerDbgFunctionNode_ *pNext;
} VkLayerDbgFunctionNode;
