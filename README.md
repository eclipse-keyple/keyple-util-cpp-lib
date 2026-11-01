# Keyple Util C++ Library

## Overview

The **Keyple Util C++ library** contains various utility classes used by all Keyple components.

## Documentation & Contribution Guide

The full documentation, including the **user guide**, **download information** and **contribution guide**, is available on the Keyple website [keyple.org](https://keyple.org).

## Doxygen

The doxygen is available online: [docs.keyple.org/keyple-util-cpp-lib/](https://docs.keyple.org/keyple-util-cpp-lib/)

## Building with Conan

This repository is packaged as a [Conan](https://conan.io/) recipe (`conanfile.py`), providing the `Keyple::Util`
CMake target as `keyple-util-cpp-lib`. Downstream keyple recipes should consume it with a regular
`self.requires("keyple-util-cpp-lib/2.4.1")` instead of `FetchContent`. Unlike the header-only keypop/keyple APIs,
this is a real compiled library: the `shared` option (default `True`, matching this project's historical toolchain
default) controls whether a shared or static library is built, and `fPIC` is available for static, non-Windows builds.

The unit test suite is opt-in via the `with_tests` option (default `False`), so consumers of the package don't pay
for compiling GoogleTest.

### Local development

Use `conan build` to configure/compile in-tree, in a regular `build/` folder you can inspect, rerun and debug
against (and which generates a `CMakeUserPresets.json` for IDE integration). The build type defaults to `Release`;
pass `-s build_type=Debug` for a debug build, which lands in its own `build/Debug` subfolder alongside `build/Release`:

```bash
# Release build, with the unit test suite, under ./build/Release
conan build . -o with_tests=True --build=missing

# Debug build, under ./build/Debug
conan build . -o with_tests=True -s build_type=Debug --build=missing

# Re-run the tests directly afterwards
./build/Release/bin/keypleutilcpplib_ut
./build/Debug/bin/keypleutilcpplib_ut
```

### Packaging to the local cache

Use `conan create` to export the recipe and package to your local Conan cache, for consumption by other
recipes/repos (no remote upload involved):

```bash
# Build and export the package to the local cache
conan create . --build=missing

# Same, but also build and run the unit test suite as part of the recipe build
conan create . -o with_tests=True --build=missing

# Package a static build instead (default is shared)
conan create . -o shared=False --build=missing
```

### CI profiles

`profiles/` holds one Conan profile per platform built in CI (`linux-gcc`, `macos-clang`, `windows-msvc`),
replacing the old per-toolchain `.cmake` files. Pass one with `-pr:h` to build/package for that target; the
build type is still selected separately with `-s build_type=...`:

```bash
conan build . -pr:h=profiles/linux-gcc -o with_tests=True --build=missing
conan create . -pr:h=profiles/windows-msvc -s build_type=Debug --build=missing
```

## About the source code

The code is built with different flavours of **GCC, CLang and MSVC ** in order to address a wide range of applications.
