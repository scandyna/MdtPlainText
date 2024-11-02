from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake
import os

class MdtPlainTextConan(ConanFile):
  name = "mdtplaintext"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtplaintext"
  description = "Provides some libraries to read and write simple plain text using the boost Spirit library, typically CSV."
  settings = "os", "compiler", "build_type", "arch"
  options = {"shared": [True, False]}
  default_options = {"shared": True}
  generators = "CMakeDeps", "VirtualBuildEnv"

  def requirements(self):
    self.requires("boost/1.72.0")
    self.requires("qt/5.15.6")

  def build_requirements(self):
    self.test_requires("catch2/2.13.9")
    self.test_requires("MdtCMakeModules/0.19.3@scandyna/testing")

  def generate(self):
    tc = CMakeToolchain(self)
    #tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    tc.generate()
