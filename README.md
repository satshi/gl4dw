# gl4dw

`gl4dw` is a legacy Visual C++ 6/OpenGL viewer for 4D polytopes.

## Layout

- `src/` - C++ implementation files
- `include/` - project headers and small VC6 compatibility headers
- `tests/` - smoke-test programs
- `data/` - polytope datasets
- `config/` - optional configuration examples
- `docs/` - notes preserved from the legacy project

## Modern Windows build

Open a Visual Studio developer shell, then run:

```bat
call "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" -arch=x64
cmake -S . -B build -G "NMake Makefiles" -DCMAKE_TOOLCHAIN_FILE="C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" -DGL4DW_BUILD_VIEWER=ON
cmake --build build
```

This builds:

- `build\gl4dw_core.lib`
- `build\gl4dw_smoke.exe`
- `build\gl4dw_data_smoke.exe`
- `build\gl4dw.exe`

The viewer depends on `freeglut` and `nlohmann-json`, which are declared in `vcpkg.json`.

## Running

The default data directory is `data`, and the default polytope name is `c8`.

Run from the project root so the relative data path resolves correctly:

```bat
build\gl4dw.exe
```

If double-clicking appears to do nothing, run it from PowerShell or Command
Prompt instead so startup errors stay visible:

```bat
cd /d F:\usr\ai\work\gl4dw
build\gl4dw.exe
```

The program also writes startup progress to `gl4dw.log`.

Optional viewer settings can be stored in `gl4d.json` in the project root.
See `config\gl4d.json.example` for the supported keys.

To open another dataset, pass the name without the `.poi` extension:

```bat
build\gl4dw.exe C24
```

## Core-only build

If GLUT/freeglut is not available, build only the geometry core and smoke test:

```bat
cmake -S . -B build -G "NMake Makefiles" -DGL4DW_BUILD_VIEWER=OFF
cmake --build build
```
