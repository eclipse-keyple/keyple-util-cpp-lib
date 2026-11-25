# *****************************************************************************
# Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/     *
#                                                                             *
# This program and the accompanying materials are made available under the    *
# terms of the Eclipse Public License 2.0 which is available at               *
# http://www.eclipse.org/legal/epl-2.0                                        *
#                                                                             *
# SPDX-License-Identifier: EPL-2.0                                            *
# *****************************************************************************/

import os
import re

from conan import ConanFile
from conan.tools.build import can_run
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, load


class KeypleUtilCppLibConan(ConanFile):
    name = "keyple-util-cpp-lib"
    license = "EPL-2.0"
    author = "Calypso Networks Association <https://calypsonet.org/>"
    url = "https://github.com/eclipse-keyple/keyple-util-cpp-lib"
    homepage = "https://keyple.org/apis/core-layer/util-lib/"
    description = "C++ implementation of the Eclipse Keyple utility classes"
    topics = ("keyple", "calypso")

    package_type = "library"
    settings = "os", "arch", "compiler", "build_type"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_tests": [True, False]
    }

    default_options = {
        "shared": True,
        "fPIC": True,
        "with_tests": False
    }

    exports_sources = [
        "include/*",
        "src/*",
        "CMakeLists.txt",
        "LICENSE",
        "NOTICE.md"
    ]

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def set_version(self):
        cmake_lists = load(self, os.path.join(self.recipe_folder, "CMakeLists.txt"))
        match = re.search(r"VERSION\s+(\d+\.\d+\.\d+)", cmake_lists)
        self.version = match.group(1)

    def layout(self):
        cmake_layout(self)

    def build_requirements(self):
        if self.options.with_tests:
            # 1.12.1 is the last GoogleTest release still compiling as C++11,
            # matching this project's CMAKE_CXX_STANDARD.
            self.test_requires("gtest/1.12.1")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["LIBRARY_TYPE"] = "SHARED" if self.options.shared else "STATIC"
        tc.variables["BUILD_TESTING"] = bool(self.options.with_tests)
        tc.generate()
        if self.options.with_tests:
            CMakeDeps(self).generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if self.options.with_tests and can_run(self):
            bin_dir = os.path.join(self.build_folder, "bin")
            if self.settings.os == "Windows":
                bin_dir = os.path.join(bin_dir, str(self.settings.build_type))
            bin_name = "keypleutilcpplib_ut.exe" if self.settings.os == "Windows" else "keypleutilcpplib_ut"
            self.run(os.path.join(bin_dir, bin_name))

    def package(self):
        copy(self, "LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["keypleutilcpplib"]
        self.cpp_info.set_property("cmake_file_name", "keyple-util-cpp-lib")
        self.cpp_info.set_property("cmake_target_name", "Keyple::Util")

    def package_id(self):
        self.info.options.rm_safe("with_tests")
