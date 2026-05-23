# Windows Quick Start

This guide is for people using the prebuilt Windows ZIP package.

## Start the Viewer

1. Extract the ZIP file to a writable folder.
2. Open Command Prompt or PowerShell in the extracted folder.
3. Run:

```bat
gl4dw.exe c8
```

The viewer opens the `c8` polytope from `data_json/c8.json`.

## Try Other Polytopes

The ZIP includes sample JSON data in `data_json/`. Pass the file name without
the `.json` extension:

```bat
gl4dw.exe c24
gl4dw.exe c120
gl4dw.exe c600
```

## Common Options

```bat
gl4dw.exe -h c8
gl4dw.exe -s c24
gl4dw.exe -c -n "gl4dw clipped c8" c8
```

- `-h` draws facets as hollow frames.
- `-s` draws facets as solid surfaces. This is the default.
- `-c` enables the extra clipping plane.
- `-n <title>` sets the viewer window title.

## Controls

- Drag with the left mouse button to rotate in one set of 4D planes.
- Drag with another mouse button to rotate in the alternate planes.
- After releasing the mouse, the polytope keeps spinning.
- Press `q`, `Q`, or `Esc` to exit.

## Expected Package Layout

The extracted folder should contain:

```text
gl4dw.exe
freeglut.dll
data_json/
config/
README.md
LICENSE
docs/
```

If `freeglut.dll` is missing and the viewer does not start, ask the package
provider for a complete Windows ZIP package.

## Troubleshooting

If the viewer cannot find a polytope, run it from the extracted package folder
so the default `data_json/` path resolves correctly.

If you want to run `gl4dw.exe` from another working directory, copy
`config/gl4d.json.example` to `gl4d.json` and set `dataDir` to the full path of
the package's `data_json` directory.
