# Vulkan SC Loader

This project provides the Khronos official Vulkan SC Loader for all platforms.

> **IMPORTANT NOTE:** This repository is to be used with the [Vulkan SC](https://www.khronos.org/vulkansc/) API and should not be confused with the similar repository that exists for the Vulkan API (see https://github.com/KhronosGroup/Vulkan-Loader). While it is possible to build the Vulkan version from this repository, this repository contains a forked version of the upstream code and may not be up-to-date with the latest changes in the upstream repository.

## Introduction

Vulkan is an explicit API, enabling direct control over how GPUs actually work.
As such, Vulkan supports systems that have multiple GPUs, each running with a different driver, or ICD (Installable Client Driver).
Vulkan also supports multiple global contexts (instances, in Vulkan terminology).
The ICD loader is a library that is placed between a Vulkan application and any number of Vulkan drivers, in order to support multiple drivers and the instance-level functionality that works across these drivers.
Additionally, the loader manages inserting Vulkan layer libraries, such as validation layers, between an application and the drivers.

Vulkan SC is an API derived from Vulkan with various changes applied to fulfill the special
requirements of safety critical applications. The Vulkan SC API has a large overlap with Vulkan.
As such, we endeavor to leverage as many of the Vulkan Ecosystem components as possible.

This repository contains the Vulkan SC loader that is used for Linux, Windows, and QNX.

The following components are available in this repository:

- [ICD Loader](loader/)
- [Loader Documentation](docs/LoaderInterfaceArchitecture.md)
- [Tests](tests/)

This repository contains the Vulkan SC Loader which is intended for **development** environments,
and is not expected to be used in **production** (safety) environments.

**NOTE**: This repository is a downstream fork of
[KhronosGroup/Vulkan-Loader](https://github.com/KhronosGroup/Vulkan-Loader)
which is periodically rebased.

This repository continues to have a functioning Vulkan loader with equivalent functionality
to the upstream branch point.

The choice of Vulkan or Vulkan SC support is determined at build time.

The `sc_main` branch is currently based on the `sdk-1.3.257` Vulkan-Loader tag and contains Vulkan SC modifications to support the Vulkan SC 1.0 API.

## Contact Information

- [Charles Giessen](mailto:charles@lunarg.com)
- [Mark Young](mailto:marky@lunarg.com)

## Information for Developing or Contributing

Please see the [CONTRIBUTING.md](CONTRIBUTING.md) file in this repository for more details.
Please see the [GOVERNANCE.md](GOVERNANCE.md) file in this repository for repository management details.

## How to Build and Run

[BUILD.md](BUILD.md) includes directions for building all components.

Architecture and interface information for the loader is in [docs/LoaderInterfaceArchitecture.md](docs/LoaderInterfaceArchitecture.md).

## Version Tagging Scheme

Updates to this repository which correspond to a new Vulkan specification release are tagged using the following format: `v<`_`version`_`>` (e.g., `v1.3.266`).

**Note**: Marked version releases have undergone thorough testing but do not imply the same quality level as SDK tags. SDK tags follow the `vulkan-sdk-<`_`version`_`>.<`_`patch`_`>` format (e.g., `vulkan-sdk-1.3.266.0`).

This scheme was adopted following the `1.3.266` Vulkan specification release.

For Vulkan SC, updates to a new API version will be tagged using the following format `vksc<`_`version`_`>.<`_`patch`_`>` (e.g., `vksc1.0.13`).

## License

This work is released as open source under a Apache-style license from Khronos including a Khronos copyright.

## Acknowledgements

While this project has been developed primarily by LunarG, Inc., there are many other
companies and individuals making this possible: Valve Corporation, funding
project development; Khronos providing oversight and hosting of the project.

Original Vulkan SC modifications have been contributed by NVIDIA CORPORATION.
