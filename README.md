
| Topic                    | Status                                                                                                                                 |
|:-------------------------|:---------------------------------------------------------------------------------------------------------------------------------------|
| `Build / test (CI)`  | [![pipeline status](https://gitlab.com/scandyna/mdtplaintext/badges/experimental/pipeline.svg)](https://gitlab.com/scandyna/mdtplaintext/-/commits/experimental)   |
| `Coverity`               | [![Coverity](https://scan.coverity.com/projects/21719/badge.svg)](https://scan.coverity.com/projects/scandyna-mdtplaintext) |
| `OpenHub`                | [View on OpenHub](https://www.openhub.net/p/MdtPlainText) |

# MdtPlainText

Provides some libraries to read and write simple plain text
using the [boost Spirit](https://www.boost.org/doc/libs/1_73_0/libs/spirit/doc/html/index.html) library.

The main use case is a CSV parser, that should read files conform to
[CSV-1203](https://idoc.pub/documents/csv-file-format-specification-standard-csv-1203-6nq88y5xr9nw)
and
[RFC 4180](https://tools.ietf.org/html/rfc4180)


# Usage

For the available classes, functions, and their usage,
see [the API documentation](https://scandyna.gitlab.io/mdtplaintext)

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
cmake_minimum_required(VERSION 3.15)
project(MyApp)

find_package(Mdt0 REQUIRED COMPONENTS PlainText)

add_executable(myApp myApp.cpp)
target_link_libraries(myApp Mdt0::PlainText)
```

If you use Qt, you can use `PlainText_QtCore`:
```cmake
cmake_minimum_required(VERSION 3.15)
project(MyApp)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(Mdt0 REQUIRED COMPONENTS PlainText_QtCore)

add_executable(myApp myApp.cpp)
target_link_libraries(myApp Mdt0::PlainText_QtCore)
```

## Project using Conan

If you use [Conan](https://conan.io/),
add MdtPlainText as requirement in your `conanfile.txt`:
```conan
[requires]
mdtplaintext/x.y.z@scandyna/testing

[generators]
CMakeDeps
CMakeToolchain
VirtualBuildEnv
```

If you need better unicode support,
you may choose the Qt based one:
```conan
[requires]
mdtplaintext_qtcore/x.y.z@scandyna/testing

[generators]
CMakeDeps
CMakeToolchain
VirtualBuildEnv
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
 - boost
 - Qt

Here are the available options:

| Option           | Default | Possible Values  | Explanations |
| -----------------|:------- |:----------------:|--------------|
| shared           | True    |  [True, False]   | Build as shared library |

### Using Conan profiles

When using Conan for dependency management,
it is recommended to use Conan profiles.
This permits to have personal binary repository,
avoiding to recompile everything everytime.
This becomes more important if Qt is managed by Conan.

This requires modifications in the `settings_user.yml` Conan configuration,
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
cmake -G"MinGW Makefiles" -DCMAKE_INSTALL_PREFIX=C:\some\path -DCMAKE_BUILD_TYPE=Release ..
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

## Build

See [BUILD](BUILD.md).

## Create Conan package

See [README](packaging/conan/README.md) in the conan packaging folder.
