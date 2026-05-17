# gl4dw

`gl4dw` is a legacy OpenGL viewer for 4D polytopes, now buildable with CMake on Windows and Linux/WSL.

## Layout

- `src/` - C++ implementation files
- `include/` - project headers and compatibility wrappers
- `tests/` - smoke and data validation tests
- `data/` - polytope datasets
- `config/` - optional configuration examples
- `docs/` - notes preserved from the legacy project

## Dependencies

Required for all builds:

- CMake 3.20 or newer
- C++17 compiler
- nlohmann-json

Required for the viewer:

- OpenGL
- GLUT/freeglut

On Windows, dependencies are declared in `vcpkg.json`.

On Ubuntu/WSL:

```bash
sudo apt update
sudo apt install cmake ninja-build g++ nlohmann-json3-dev freeglut3-dev
```

## Windows Build

Open a Visual Studio developer shell, then run:

```bat
call "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" -arch=x86
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Linux/WSL Build

Core and tests only:

```bash
cmake -S . -B build-wsl-ninja -G Ninja -DGL4DW_BUILD_VIEWER=OFF
cmake --build build-wsl-ninja
ctest --test-dir build-wsl-ninja --output-on-failure
```

Viewer build:

```bash
cmake -S . -B build-wsl-viewer -G Ninja -DGL4DW_BUILD_VIEWER=ON
cmake --build build-wsl-viewer
ctest --test-dir build-wsl-viewer --output-on-failure
```

## Build Targets

The core library is `gl4dw_core`.

Test executables:

- `gl4dw_smoke`
- `gl4dw_config_smoke`
- `gl4dw_data_smoke`
- `gl4dw_data_validation`
- `gl4dw_readpolytope_failure`

Viewer executable:

- `gl4dw`

`ReadPolytope` lives in `src/polytope_loader.cpp`, so data loading tests do not require OpenGL/GLUT.

## Running

The default data directory is `data`, and the default polytope name is `c8`.

Windows:

```bat
build\gl4dw.exe c8
```

WSL/Linux:

```bash
./build-wsl-viewer/gl4dw c8
```

If WSLg does not show GUI windows, restart WSL from Windows:

```powershell
wsl --shutdown
```

Then reopen WSL and run the viewer again. If OpenGL acceleration is unreliable, try:

```bash
LIBGL_ALWAYS_SOFTWARE=1 ./build-wsl-viewer/gl4dw c8
```

The program writes startup progress to `gl4dw.log`.

## Configuration

Optional viewer settings can be stored in `gl4d.json` in the project root.
See `config/gl4d.json.example` for the supported keys.

Example:

```json
{
  "dataDir": "data",
  "width": 800,
  "extendRate": 0.06,
  "clip": false,
  "clipPlane": [1.0, -1.0, -1.0, 0.0],
  "hidePoly": 0,
  "fillType": 0
}
```

## Controls

- Drag with the left mouse button to rotate in one set of 4D planes.
- Drag with another mouse button to rotate in the alternate planes.
- After releasing the mouse, the polytope keeps spinning.
- Press `q`, `Q`, or `Esc` to exit.
