from conan import ConanFile
from conan.tools.env import VirtualBuildEnv
from conan.tools.cmake import CMakeToolchain, CMakeDeps, CMake, cmake_layout
from conan.tools.files import copy
import os

class MdtPlainTextQtCoreConan(ConanFile):
  name = "mdtplaintext_qtcore"
  license = "BSD 3-Clause"
  url = "https://gitlab.com/scandyna/mdtplaintext"
  description = "Provides some libraries to read and write simple plain text using the boost Spirit library and Qt, typically CSV."
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
    self.requires("MdtCMakeConfig/0.0.5@scandyna/testing")
    self.requires(f"mdtplaintext/{self.version}@scandyna/testing")
    self.requires("qt/5.15.6")

  def build_requirements(self):
    self.test_requires("MdtCMakeModules/0.19.3@scandyna/testing")

  def export_sources(self):
    source_root = os.path.join(self.recipe_folder, "../../../")
    copy(self, "CMakeLists.txt", source_root, self.export_sources_folder)
    copy(self, "COPYING", source_root, self.export_sources_folder)
    copy(self, "COPYING.LESSER", source_root, self.export_sources_folder)
    copy(self, "LICENSE.txt", source_root, self.export_sources_folder)
    copy(self, "libs/PlainText_QtCore/CMakeLists.txt", source_root, self.export_sources_folder)
    copy(self, "libs/PlainText_QtCore/src/*", source_root, self.export_sources_folder)

  def layout(self):
    cmake_layout(self)

  def generate(self):
    tc = CMakeToolchain(self)
    tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    tc.variables["ENABLE_QT_SUPPORT"] = "ON"
    tc.variables["USE_PACKAGED_PLAIN_TEXT"] = "ON"
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
    self.cpp_info.set_property("cmake_file_name", "Mdt0PlainText_QtCore")
    self.cpp_info.set_property("cmake_target_name", "Mdt0::PlainText_QtCore")
    self.cpp_info.libs = ["Mdt0PlainText_QtCore"]
