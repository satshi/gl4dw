# Third Party Notices

This file summarizes third party components used by `gl4dw` builds and Windows
binary packages. Review the exact dependency versions and their upstream license
files before each public release.

## Runtime Components

### freeglut

- Purpose: GLUT-compatible windowing and input library for the OpenGL viewer.
- Used by: `gl4dw.exe`
- Windows package impact: `freeglut.dll` may be bundled next to `gl4dw.exe`.
- License: MIT/X Consortium style license.
- Upstream project: `https://freeglut.sourceforge.net/`

When bundling `freeglut.dll`, include the freeglut license text or a complete
third party notice that satisfies the license terms.

### OpenGL and GLU

- Purpose: graphics APIs used by the viewer.
- Used by: `gl4dw.exe`
- Windows package impact: normally provided by Windows and graphics drivers.

The Windows ZIP does not intentionally redistribute OpenGL or GLU system
components.

## Build-Time and Header Components

### nlohmann-json

- Purpose: JSON parsing for polytope data and configuration.
- Used by: `gl4dw_core` and related executables.
- Windows package impact: header-only dependency; no separate DLL is expected.
- License: MIT.
- Upstream project: `https://github.com/nlohmann/json`

Include the nlohmann-json license text or a complete third party notice when
publishing a binary package if your release process requires notices for
header-only dependencies.

## Project License

`gl4dw` source code and bundled polytope data are licensed under the BSD Zero
Clause License. See the top-level `LICENSE` file.

## Distributor Checklist

- Confirm whether `freeglut.dll` is bundled.
- Include the license text for any bundled DLL.
- Confirm the generated ZIP includes the top-level `LICENSE` file.
- Update this file if new dependencies are added.
