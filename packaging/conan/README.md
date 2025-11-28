[[_TOC_]]

# Create a Conan package

If working on MdtPlainText, go to the root of the source tree:
```bash
conan create --version x.y.z --user scandyna --channel testing packaging/conan/$LIBRARY --profile:build $CONAN_PROFILE_BUILD --profile:host $CONAN_PROFILE_HOST --settings:build build_type=Release --settings:host build_type=$BUILD_TYPE -o "&:$OPTION=$OPTION_VALUE"
```

# OLD stuff

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
