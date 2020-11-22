from conans import ConanFile, CMake
import os

class MdtPlainTextConan(ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  generators = "cmake", "virtualenv"
  build_requires = "MdtCMakeModules/[>=0.14.12]@scandyna/testing"

  def configure_cmake(self):
    cmake = CMake(self)

    #cmake.definitions["SOME_DEF"] = "SOME_VALUE"

    return cmake

  def build(self):
      cmake = self.configure_cmake()
      cmake.configure()
      cmake.build()

  def test(self):
      cmake = self.configure_cmake()
      cmake.test()
