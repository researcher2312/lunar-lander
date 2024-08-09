import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout


class LunarLander(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("sdl/2.30.3", force=True)
        self.requires("sdl_ttf/2.22.0")

    def layout(self):
        cmake_layout(self)