# 1. Introduction

This project is a small Asteroids-style game written in C++ using SFML. Clone repo and install SFML following instructions below (should take <5 min) to play!
<p align="left">
  <img src="space-shooter/assets/screenshots/gameplay.PNG" width="450">
</p>

### Requirements

- C++ compiler (g++ recommended)
- `make`
- SFML 2.6.x
  - This project uses a vendored SFML setup: you download SFML for your operating system and place it into the correct folder under `vendor/sfml/`.
  - No Makefile edits are required.

---

# 2. Installing SFML

SFML is downloaded manually and placed inside the vendor/sfml/ directory.  
No Makefile edits are required.

1. Download SFML 2.6.x from:  
   https://www.sfml-dev.org/download.php

2. Choose the build that matches your operating system:
    - Windows: `GCC 13.1.0 MinGW (SEH) - 64-bit`
    - macOS: `Clang – ARM64 (macOS 11+)`
    - Linux: `GCC - 64-bit`

    ...and move it into the correct folder (follow OS specific instructions below):
    
        space-shooter/
        ├── src/
        ├── include/
        ├── assets/
        ├── vendor/
        │   └── sfml/
        │       ├── windows-mingw64/
        │       ├── linux-x86_64/
        │       └── macos-arm64/
        └── Makefile

### Windows (MinGW / g++)
1. Extract the SFML zip.
2. Copy the contents:
   ```text
    SFML-2.6.x/include/ -> space-shooter/vendor/sfml/windows-mingw64/include/
    SFML-2.6.x/lib/     -> space-shooter/vendor/sfml/windows-mingw64/lib/
    SFML-2.6.x/bin/     -> space-shooter/vendor/sfml/windows-mingw64/bin/
### macOS
1. Extract the SFML archive.
2. Copy the contents:
   ```text
    SFML-2.6.x/include/ -> space-shooter/vendor/sfml/macos-arm64/include/
    SFML-2.6.x/lib/     -> space-shooter/vendor/sfml/macos-arm64/lib/
### Linux
1. Extract the SFML archive.
2. Copy the contents:
   ```text
    SFML-2.6.x/include/ -> space-shooter/vendor/sfml/linux-x86_64/include/
    SFML-2.6.x/lib/     -> space-shooter/vendor/sfml/linux-x86_64/lib/
---

# 3. Build and Run

Run these commands in the terminal from project root:

    make build   # compiles the game
    make run     # runs the game
    make clean   # removes build artifacts



