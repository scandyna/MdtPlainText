
# Conant install

build_tests option must not be part of the package ID hash:

See:
```
  def package_id(self):
    del self.info.options.build_tests
```

Document how to specify options,
like gui, use_conan_qt,
in the caller conanfile.txt/py

# Tests

Also check with files exported by LibreOffice and MS Excel

# Examples

Hello wolrd example
