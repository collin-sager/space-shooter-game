# Space Shooter (C++ / SFML)

A small Asteroids-style game written in **C++ using SFML**.

This project uses a **vendored SFML setup**: you download SFML for your operating system and place it into the correct folder under `vendor/sfml/`.  
**No Makefile edits are required.**

---

## Requirements
- C++ compiler (`g++` recommended)
- `make`
- SFML **2.6.x**

---

## Project Structure (important)
space-shooter/
├── src/
├── include/
├── assets/
├── vendor/
│ └── sfml/
│ ├── windows-mingw64/
│ ├── linux-x86_64/
│ ├── macos-x86_64/
│ └── macos-arm64/
└── Makefile

You only need to place files inside **one** of the `vendor/sfml/*` folders, depending on your OS.

---

## Installing SFML (vendored)

### 🪟 Windows (MinGW / g++)
1. Download **SFML for GCC / MinGW (SEH) – 64-bit** from  
   https://www.sfml-dev.org/download.php

2. Extract the zip. Inside you will see:
include/
lib/
bin/


3. Copy those folders into:
vendor/sfml/windows-mingw64/


Final result:
vendor/sfml/windows-mingw64/include/SFML/...
vendor/sfml/windows-mingw64/lib/libsfml-.a
vendor/sfml/windows-mingw64/bin/sfml-.dll

---

### 🐧 Linux (64-bit)
1. Download **SFML → Linux → GCC – 64-bit** from  
   https://www.sfml-dev.org/download.php

2. Extract the archive.

3. Copy `include/` and `lib/` into:
vendor/sfml/linux-x86_64/


---

### 🍎 macOS

Choose based on your CPU:

- **Apple Silicon (M1 / M2 / M3 / M4)**  
Download **Clang – ARM64 (macOS 11+)**
- **Intel Mac**  
Download **Clang – 64-bit (macOS 10.15+)**

From: https://www.sfml-dev.org/download.php

After extracting, copy `include/` and `lib/` into one of:
vendor/sfml/macos-arm64/
vendor/sfml/macos-x86_64/

---

## Build and Run

From the project root:

```bash
make build
make run
make build → compiles the game

make run → runs it with the correct SFML libraries (no copying required)




