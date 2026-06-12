# macOS Binary Distribution

This document describes how to build and verify a macOS ZIP package for
`gl4dw`.

## Build Prerequisites

- macOS with Xcode Command Line Tools
- CMake 3.20 or newer
- nlohmann-json

Install the user-space dependencies with Homebrew:

```bash
brew install cmake nlohmann-json
```

OpenGL and GLUT are provided by macOS. Apple marks those APIs as deprecated, but
the viewer still builds and links against the system frameworks.

## Configure

From the repository root:

```bash
cmake -S . -B build-viewer-mac -DGL4DW_BUILD_VIEWER=ON
```

For an Apple Silicon release from an Apple Silicon Mac, the default architecture
is usually `arm64`. To force a specific architecture, pass
`CMAKE_OSX_ARCHITECTURES`:

```bash
cmake -S . -B build-viewer-mac \
  -DGL4DW_BUILD_VIEWER=ON \
  -DCMAKE_OSX_ARCHITECTURES=arm64
```

For Intel:

```bash
cmake -S . -B build-viewer-mac \
  -DGL4DW_BUILD_VIEWER=ON \
  -DCMAKE_OSX_ARCHITECTURES=x86_64
```

Universal binaries can be requested with:

```bash
cmake -S . -B build-viewer-mac \
  -DGL4DW_BUILD_VIEWER=ON \
  -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"
```

## Build, Test, and Package

```bash
cmake --build build-viewer-mac
ctest --test-dir build-viewer-mac --output-on-failure
cmake --build build-viewer-mac --target package
```

The generated ZIP is written to the build directory. Its file name follows this
pattern:

```text
gl4dw-<version>-Darwin-<architecture>.zip
```

For example:

```text
gl4dw-0.1.0-Darwin-x86_64.zip
```

## Package Contents

The ZIP should contain a single top-level folder with:

```text
gl4dw
data_json/
config/
README.md
LICENSE
docs/
```

The executable uses the system OpenGL and GLUT frameworks, so no extra dynamic
libraries are bundled for the default macOS build.

## Release Verification Checklist

Before publishing the ZIP:

- Build the viewer configuration.
- Run `ctest --test-dir build-viewer-mac --output-on-failure`.
- Generate the ZIP with the `package` target.
- Inspect the ZIP and confirm it contains `gl4dw`, `data_json/`, `config/`,
  `README.md`, `LICENSE`, and `docs/`.
- Confirm the architecture with `file build-viewer-mac/gl4dw`.
- Extract the ZIP into a fresh temporary folder.
- From the extracted folder, run `./gl4dw c8`.
- Confirm the viewer opens and `q`, `Q`, or `Esc` exits it.
- Confirm `docs/third_party_notices.md` is present.

If macOS blocks the downloaded binary because it is unsigned, remove the
quarantine attribute after extraction:

```bash
xattr -dr com.apple.quarantine gl4dw-<version>-Darwin-<architecture>
```

## Notes for GitHub Releases

Attach the generated ZIP to the release. Include the CMake configure command,
compiler version, target architecture, and whether the binary is signed or
unsigned in the release notes.
