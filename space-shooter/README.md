# Space Shooter

Arcade-style Asteroids clone built with C++17 and SFML.

## Project Layout
- `src/` game sources and headers
- `include/` shared headers (`constants.h`, `XYData.h`)
- `assets/` runtime assets (fonts, textures, sounds)
- `data/` runtime data (e.g., `scores.txt`)
- `vendor/sfml/` platform-specific SFML binaries (`windows-mingw64/`, `linux-x86_64/`, `macos-x86_64/`, `macos-arm64/`)

## Build
From `space-shooter/`:
```bash
make
```
This builds `asteroids` (or `asteroids.exe` on Windows) using the sources in `src/` and headers in `include/`. Update library paths in the `Makefile` if you are not using the provided Windows MinGW64 binaries.

## Run
After building:
```bash
./asteroids   # or .\\asteroids.exe on Windows
```
Keep the working directory at `space-shooter/` so the game can load assets (e.g., `assets/fonts/arcade1.ttf`) and data (`data/scores.txt`).

## Controls
- `W/A/S/D` to thrust/strafe/rotate
- Mouse to aim
- Left click or `Space` to shoot
- `Enter` to start; `Esc` to quit
