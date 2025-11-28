[[_TOC_]]

# Build MdtPlainText

Get the sources:
```bash
git clone https://gitlab.com/scandyna/mdtapplication.git
```

Create a build directory and cd to it:
```bash
mkdir build
cd build
```

Install the dependencies:
```bash
conan install --output-folder . --profile:build $CONAN_PROFILE --profile:host $CONAN_PROFILE --settings:build build_type=Release --settings:host build_type=$BUILD_TYPE --options:host "&:shared=$BUILD_SHARED_LIBS"  ..
```

If dependencies are managed by Conan,
update the environment of the current shell for the build:
```bash
source conanbuild.sh
```

Configure the project:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON -DBUILD_EXAMPLES=ON ..
```

Maybe adjust some settings:
```bash
cmake-gui .
```

Build:
```bash
cmake --build . --config $BUILD_TYPE -j4
```

Restore the environment for the build (if dependencies are managed by Conan):
```bash
source deactivate_conanbuild.sh
```
Note: once the project was completely configured,
the environment for the build should not be needed anymore.


If dependencies are managed by Conan,
update the environment of the current shell to run the tests:
```bash
source conanrun.sh
```
Note: the environment to run the tests will probably be required everytime.
[mdt-cmake-modules](https://gitlab.com/scandyna/mdt-cmake-modules)
provides a helper that build an environment with CMake to execute the tests,
but its currently not working.
For details, see: https://gitlab.com/scandyna/mdt-cmake-modules/-/issues/12

To run the tests:
```bash
ctest --output-on-failure -C $BUILD_TYPE -j4
```

Restore the environment (if dependencies are managed by Conan):
```bash
source deactivate_conanrun.sh
```

# OLD stuff

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

