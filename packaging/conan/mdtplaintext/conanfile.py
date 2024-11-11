from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy
import os

class MdtPlainTextConan(ConanFile):
  name = "mdtplaintext"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtplaintext"
  description = "Provides some libraries to read and write simple plain text using the boost Spirit library, typically CSV."
  settings = "os", "compiler", "build_type", "arch"
  options = {
    "shared": [True, False]
  }
  default_options = {
    "shared": True
  }
  generators = "CMakeDeps", "VirtualBuildEnv"

  # See: https://docs.conan.io/en/latest/reference/conanfile/attributes.html#short-paths
  # Should only be enabled if building with MSVC on Windows causes problems
  short_paths = False

  def set_version(self):
    if not self.version:
      self.version = "0.0.0"

  def requirements(self):
    self.requires("mdtcmakeconfig/0.1.0@scandyna/testing")
    self.requires("boost/1.72.0")

  def build_requirements(self):
    self.test_requires("MdtCMakeModules/0.19.3@scandyna/testing")

  def export_sources(self):
    source_root = os.path.join(self.recipe_folder, "../../../")
    copy(self, "CMakeLists.txt", source_root, self.export_sources_folder)
    copy(self, "COPYING", source_root, self.export_sources_folder)
    copy(self, "COPYING.LESSER", source_root, self.export_sources_folder)
    copy(self, "LICENSE.txt", source_root, self.export_sources_folder)
    copy(self, "libs/PlainText/CMakeLists.txt", source_root, self.export_sources_folder)
    copy(self, "libs/PlainText/src/*", source_root, self.export_sources_folder)

  def layout(self):
    cmake_layout(self)

  def generate(self):
    tc = CMakeToolchain(self)
    tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    tc.variables["ENABLE_QT_SUPPORT"] = "OFF"
    #tc.variables["CMAKE_MESSAGE_LOG_LEVEL"] = "DEBUG"
    #tc.variables["INSTALL_CONAN_PACKAGE_FILES"] = "ON"
    tc.generate()

  def build(self):
    cmake = CMake(self)
    cmake.configure()
    cmake.build()

  def package(self):
    cmake = CMake(self)
    cmake.install()

  def package_info(self):
    self.cpp_info.set_property("cmake_file_name", "Mdt0PlainText")
    self.cpp_info.set_property("cmake_target_name", "Mdt0::PlainText")
    self.cpp_info.libs = ["Mdt0PlainText"]
    self.cpp_info.defines = ["BOOST_SPIRIT_UNICODE"]
