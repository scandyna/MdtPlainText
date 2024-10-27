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
  #build_requires = "MdtCMakeModules/[>=0.14.12]@scandyna/testing", "Catch2/[>=2.11.1]@catchorg/stable"
  #generators = "cmake", "cmake_paths", "virtualenv"
  generators = "CMakeDeps", "VirtualBuildEnv"
  #exports_sources = "libs/PlainText/*", "libs/PlainText_QtCore/*", "CMakeLists.txt", "conanfile.py", "LICENSE.txt", "COPYING", "COPYING.LESSER"
  # If no_copy_source is False, conan copies sources to build directory and does in-source build,
  # resulting having build files installed in the package
  # See also: https://github.com/conan-io/conan/issues/350
  #no_copy_source = True

  # See: https://docs.conan.io/en/latest/reference/conanfile/attributes.html#short-paths
  # Should only be enabled if building with MSVC on Windows causes problems
  short_paths = False

  #def set_version(self):
    #if os.path.exists(".git"):
      #git = tools.Git()
      #self.version = "%s" % (git.get_tag())
    #self.output.info( "%s: version is %s" % (self.name, self.version) )


  def requirements(self):
    self.requires("boost/1.72.0")
    self.requires("qt/5.15.6")

  def build_requirements(self):
    self.test_requires("catch2/2.13.9")
    self.test_requires("MdtCMakeModules/0.19.3@scandyna/testing")

  # TODO: remove from here once packages done
  def configure_cmake(self):
    cmake = CMake(self)
    cmake.definitions["FROM_CONAN_PROJECT_VERSION"] = self.version
    cmake.definitions["CMAKE_TOOLCHAIN_FILE"] = "%s/conan_paths.cmake" % (self.build_folder)
    cmake.definitions["WARNING_AS_ERROR"] = "ON"

    if self.settings.compiler == "gcc" or self.settings.compiler == "clang":
      if self.settings.compiler.sanitizer == "Thread":
        cmake.definitions["SANITIZER_ENABLE_THREAD"] = "ON"

    return cmake

  def generate(self):
    tc = CMakeToolchain(self)
    #tc.variables["FROM_CONAN_PROJECT_VERSION"] = self.version
    tc.generate()

  #def build(self):
    #cmake = self.configure_cmake()
    #cmake.configure()
    #cmake.build()


  #def package(self):
    #cmake = self.configure_cmake()
    #cmake.install()
