#!/usr/bin/env python3
# Copyright (c) 2019 The Khronos Group Inc.
# Copyright (c) 2019 Valve Corporation
# Copyright (c) 2019 LunarG, Inc.
# Copyright (c) 2019 Google Inc.
# Copyright (c) 2021-2022 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# Copyright (c) 2023-2023 RasterGrid Kft.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Author: Mike Schuchardt <mikes@lunarg.com>

import argparse
import common_codegen
import filecmp
import os
import shutil
import subprocess
import sys
import tempfile

# files to exclude from --verify check
verify_exclude = ['.clang-format']

def main(argv):
    parser = argparse.ArgumentParser(description='Generate source code for this repository')
    parser.add_argument('registry', metavar='REGISTRY_PATH', help='path to the Vulkan-Headers registry directory')
    parser.add_argument('--api',
                        default='vulkan',
                        choices=['vulkan', 'vulkansc'],
                        help='Specify API name to generate')
    group = parser.add_mutually_exclusive_group()
    group.add_argument('-i', '--incremental', action='store_true', help='only update repo files that change')
    group.add_argument('-v', '--verify', action='store_true', help='verify repo files match generator output')
    args = parser.parse_args(argv)

    vksc_filenames =['vk_loader_extensions.h',
                     'vk_loader_extensions.c',
                     'vk_dispatch_table_helper.h',
                     'vk_layer_dispatch_table.h',
                     'loader_generated_header_version.cmake']

    vk_filenames   =['vk_dispatch_table_helper.h',
                     'vk_layer_dispatch_table.h',
                     'vk_loader_extensions.h',
                     'vk_loader_extensions.c',
                     'vk_object_types.h',
                     'loader_generated_header_version.cmake']

    gen_filenames = vk_filenames

    if args.api == 'vulkansc' :
        gen_filenames = vksc_filenames

    gen_cmds = [[common_codegen.repo_relative('scripts/loader_genvk.py'),
                 '-api', args.api,
                 '-registry', os.path.abspath(os.path.join(args.registry,  'vk.xml')),
                 '-quiet',
                 filename] for filename in gen_filenames]

    repo_dir = common_codegen.repo_relative('loader/generated')
    if args.api == 'vulkansc':
        repo_dir = common_codegen.repo_relative('loader/generated-vksc')

    # get directory where generators will run
    if args.verify or args.incremental:
        # generate in temp directory so we can compare or copy later
        temp_obj = tempfile.TemporaryDirectory(prefix='VulkanLoader_generated_source_')
        temp_dir = temp_obj.name
        gen_dir = temp_dir
    else:
        # generate directly in the repo
        gen_dir = repo_dir

    # run each code generator
    for cmd in gen_cmds:
        print(' '.join(cmd))
        try:
            subprocess.check_call([sys.executable] + cmd,
                                  # ignore generator output, vk_validation_stats.py is especially noisy
                                  stdout=subprocess.DEVNULL,
                                  cwd=gen_dir)
        except Exception as e:
            print('ERROR:', str(e))
            return 1

    # optional post-generation steps
    if args.verify:
        # compare contents of temp dir and repo
        temp_files = set(os.listdir(temp_dir))
        repo_files = set(os.listdir(repo_dir))
        files_match = True
        for filename in sorted((temp_files | repo_files) - set(verify_exclude)):
            if filename not in repo_files:
                print('ERROR: Missing repo file', filename)
                files_match = False
            elif filename not in temp_files:
                print('ERROR: Missing generator for', filename)
                files_match = False
            elif not filecmp.cmp(os.path.join(temp_dir, filename),
                               os.path.join(repo_dir, filename),
                               shallow=False):
                print('ERROR: Repo files do not match generator output for', filename)
                files_match = False

        # return code for test scripts
        if files_match:
            print('SUCCESS: Repo files match generator output')
            return 0
        return 1

    elif args.incremental:
        # copy missing or differing files from temp directory to repo
        for filename in os.listdir(temp_dir):
            temp_filename = os.path.join(temp_dir, filename)
            repo_filename = os.path.join(repo_dir, filename)
            if not os.path.exists(repo_filename) or \
               not filecmp.cmp(temp_filename, repo_filename, shallow=False):
                print('update', repo_filename)
                shutil.copyfile(temp_filename, repo_filename)

    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))

