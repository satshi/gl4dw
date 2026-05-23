# Windows Binary Distribution

This document describes how to build and verify a Windows ZIP package for
`gl4dw`.

## Build Prerequisites

- Visual Studio with the C++ toolchain
- CMake 3.20 or newer
- vcpkg, either from Visual Studio integration or a standalone checkout

The project dependencies are declared in `vcpkg.json`.

## Configure

Open a Visual Studio Developer Command Prompt from the repository root.

If vcpkg is integrated with CMake in your environment:

```bat
cmake -S . -B build
```

If you use a standalone vcpkg checkout:

```bat
cmake -S . -B build ^
  -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
```

To include a runtime DLL explicitly, pass `GL4DW_PACKAGE_EXTRA_DLLS` at configure
time:

```bat
cmake -S . -B build ^
  -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake ^
  -DGL4DW_PACKAGE_EXTRA_DLLS=%VCPKG_ROOT%\installed\x64-windows\bin\freeglut.dll
```

Use semicolons to pass more than one DLL:

```bat
-DGL4DW_PACKAGE_EXTRA_DLLS="C:\path\to\one.dll;C:\path\to\two.dll"
```

## Build, Test, and Package

```bat
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
cmake --build build --config Release --target package
```

The generated ZIP is written to the build directory. Its file name follows this
pattern:

```text
gl4dw-<version>-Windows-<architecture>.zip
```

For example:

```text
gl4dw-0.1.0-Windows-AMD64.zip
```

## Package Contents

The ZIP should contain a single top-level folder with:

```text
gl4dw.exe
freeglut.dll
data_json/
config/
README.md
LICENSE
docs/
```

`freeglut.dll` may only appear when CMake can discover the runtime location or
when `GL4DW_PACKAGE_EXTRA_DLLS` is set.

## Release Verification Checklist

Before publishing the ZIP:

- Build the Release configuration.
- Run `ctest --test-dir build -C Release --output-on-failure`.
- Generate the ZIP with the `package` target.
- Inspect the ZIP and confirm it contains `gl4dw.exe`, `data_json/`, `config/`,
  `README.md`, `LICENSE`, and `docs/`.
- Confirm `freeglut.dll` is present for dynamic freeglut builds.
- Extract the ZIP into a fresh temporary folder.
- From the extracted folder, run `gl4dw.exe c8`.
- Confirm the viewer opens and `q`, `Q`, or `Esc` exits it.
- Confirm `docs/third_party_notices.md` is present.

## Notes for GitHub Releases

Attach the generated ZIP to the release. Include the CMake configure command,
compiler version, architecture, and whether `freeglut.dll` is bundled in the
release notes.
