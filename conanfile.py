import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout


class LunarLander(ConanFile):
    name = "lunar-lander"
    version = "0.1"
    license = "GPL-3.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"
    default_options = {"libalsa*:shared": True}

    def requirements(self):
        self.requires("sdl/2.30.9", force=True)
        self.requires("sdl_ttf/2.22.0")

    def layout(self):
        cmake_layout(self)

