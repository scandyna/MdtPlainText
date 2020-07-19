
[![pipeline status](https://gitlab.com/scandyna/mdtplaintext/badges/experimental/pipeline.svg)](https://gitlab.com/scandyna/mdtplaintext/-/commits/experimental)

# MdtPlainText

Provides some libraries to read and write simple plain text
using the [boost Spirit](https://www.boost.org/doc/libs/1_73_0/libs/spirit/doc/html/index.html) library.

The main use case is a CSV parser, that should read files conform to
[CSV-1203](https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw)
and
[RFC 4180](https://tools.ietf.org/html/rfc4180)

# Usage

For the available classes, functions, and their usage,
see [the API documentation](https://scandyna.gitlab.io/projectname)

## Required tools and libraries

Some tools and libraries are required to use MdtPlainText:
 - Git
 - CMake
 - Conan (optional)
 - A compiler (Gcc or Clang or MSVC)
 - Make (optional)
 - Qt5 (optional: for libraries with Qt support or for the tests)

For a overview how to install them, see https://gitlab.com/scandyna/build-and-install-cpp

## CMake project description

Update your CMakeLists.txt to use the required libraries:
```cmake
cmake_minimum_required(VERSION 3.10)
project(MyApp)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Mdt0 COMPONENTS PlainText_QtCore REQUIRED)

add_executable(myApp myApp.cpp)
target_link_libraries(myApp Mdt0::PlainText_QtCore)
```

# Build and install MdtPlainText

This chapter covers only the installation of the library.
To run the unit tests, see the next chapter.

Get MdtPlainText:
```bash
git clone git@gitlab.com:scandyna/mdtplaintext.git
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

## Note about install prefix

Some note on the `CMAKE_INSTALL_PREFIX`:
 - To target a system wide installation on Linux, set it to `/usr` (`-DCMAKE_INSTALL_PREFIX=/usr`) .
 - For other locations, spcecify also the `<package-name>`, (for example `-DCMAKE_INSTALL_PREFIX=~/opt/MdtPlainText`).

For details about that, see:
 - https://scandyna.gitlab.io/mdt-cmake-modules/Modules/MdtInstallDirs.html
 - https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html
 - https://scandyna.gitlab.io/mdt-cmake-modules/Modules/MdtInstallLibrary.html

## Build and install MdtPlainText using Conan

This is the recommended way.

## Project configuration using Conan

MdtPlainText has those dependencies:
 - [mdt-cmake-modules](https://gitlab.com/scandyna/mdt-cmake-modules)
 - Qt5

Qt5 can be installed using Conan, which can be usefull
if the required binaries are not distributed by Qt.
If you use the native compiler, it is possible to not manage Qt as Conan dependency.

Here are the available options:

| Option           | Default | Possible Values  | Explanations |
| -----------------|:------- |:----------------:|--------------|
| shared           | True    |  [True, False]   | Build as shared library |
| use_conan_boost  | False   |  [True, False]   | Use Boost as conan dependency |
| use_conan_qt     | False   |  [True, False]   | Use [conan Qt](https://github.com/bincrafters/conan-qt) as conan dependency |
| build_tests      | False   |  [True, False]   | If True, will also require Catch2 |

### Using Conan profiles

When using Conan for dependency management,
it is recommended to use Conan profiles.
This permits to have personal binary repository,
avoiding to recompile everything everytime.
This becomes more important if Qt is managed by Conan.

This requires modifications in the `settings.yml` Conan configuration,
and also some profile files.
See my [conan-config repository](https://gitlab.com/scandyna/conan-config) for more informations.

Some following sections will rely on Conan profiles.

### Build and install on Linux with the native compiler

Install the dependencies:
```bash
conan install -s build_type=Release --build=missing ..
```

Configure MdtPlainText:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=~/opt/MdtPlainText ..
cmake-gui .
```

To build and install, run:
```bash
cmake --build . --target INSTALL
```

### Build and install on Windows MinGW

Open a terminal that has gcc and mingw32-make in the PATH.

Create a build directory and go to it:
```bash
mkdir build
cd build
```

Install the required dependencies:
```bash
conan install --profile windows_gcc7_x86_64 -s build_type=Release --build=missing ..
```

Configure the project:
```bash
cmake -G"MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=C:\some\path -DCMAKE_TOOLCHAIN_FILE=conan_paths.cmake -DCMAKE_BUILD_TYPE=Release ..
cmake-gui .
```

If `QT_PREFIX_PATH` was not specified, and no Qt5 installation is in the `PATH`,
a error will probably occur, telling that Qt was not found.
Set the `QT_PREFIX_PATH` by choosing the path to the Qt5 installation,
then run "Configure".

Also choose different options, like the components to build.
Once done, run "Generate", then quit cmake-gui.

To build and install, run:
```bash
cmake --build . --target INSTALL
```

# Work on MdtPlainText

This chapter is like the previous (Install MdtPlainText),
but covers some more details, like the dependencies and options to run the unit tests.

## Required tools and libraries

The dependencies are the same as in previous chapter plus those:
 - [Catch2](https://github.com/catchorg/Catch2)

If you use Conan, nothing has to be installed explicitely.
Otherwise, see the documentation of the dependencies.


## Build on Linux with the native compiler

Install the dependencies:
```bash
conan install -s build_type=Debug -o build_tests=True --build=missing ..
```

Configure MdtPlainText:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON ..
cmake-gui .
```

To build , run:
```cmd
cmake --build .
```

## Build on Linux with Clang and libc++

Install the dependencies if Qt is used:
```bash
conan install --profile linux_clang6.0_x86_64_libc++_qt_gui_modules -s build_type=Debug -o use_conan_qt=True -o build_tests=True --build=missing ..
```

Activate the build environment:
```bash
source activate.sh
```

Configure MdtPlainText:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON ..
cmake-gui .
```

Build and run the tests:
```bash
cmake --build .
ctest . --output-on-failure
```

To restore the standard environment:
```bash
source deactivate.sh
```

## Configure and build with ThreadSanitizer

Gcc supports ThreadSanitizer, but Clang seems to give less false positive.
This is what I experieced on Ubuntu 18.04 with those default compilers.

Install the required dependencies:
```bash
conan install --profile linux_clang6.0_x86_64_libc++_tsan_qt_gui_modules -o use_conan_qt=True -o build_tests=True  ..
```

Activate the build environment:
```bash
source activate.sh
```

Configure MdtPlainText:
```bash
cmake -DCMAKE_BUILD_TYPE=Instrumented -DSANITIZER_ENABLE_THREAD=ON ..
cmake-gui .
```

Build and run the tests:
```bash
cmake --build . --config Instrumented
ctest . --output-on-failure -C Instrumented
```

To restore the standard environment:
```bash
source deactivate.sh
```

# Create a Conan package

The package version is picked up from git tag.
If working on MdtPlainText, go to the root of the source tree:
```bash
git tag x.y.z
conan create . scandyna/testing --profile $CONAN_PROFILE -s build_type=$BUILD_TYPE
```

Above examples will generate a package that uses the Qt and boost version that are installed on the system,
or passed to the `CMAKE_PREFIX_PATH` of your build.

To create packages that depend on Conan Qt and boost:
```bash
conan create . scandyna/testing -o MdtPlainText:use_conan_qt=True -o MdtPlainText:use_conan_boost=True
```

Because Qt offers binary compatibility,
it should not be required to create package for each minor Qt version,
but more a package per compiler and other things that breaks binary compatibility.
