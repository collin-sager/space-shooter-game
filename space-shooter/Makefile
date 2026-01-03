# THE NAME OF YOUR EXECUTABLE
TARGET = asteroids

# PROJECT LAYOUT
SRC_DIR = src
INC_DIR = include

# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = $(addprefix $(SRC_DIR)/, main.cpp game.cpp kinematics.cpp spaceship.cpp asteroid.cpp gamedisplay.cpp bullet.cpp)
OBJECTS   = $(SRC_FILES:.cpp=.o)

# SFML (vendored under vendor/sfml/<platform>/...)
SFML_VENDOR := vendor/sfml

# NO EDITS NEEDED BELOW THIS LINE
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

DEL = rm -f
RPATH =
ARCH =

# ---------------------------
# Detect OS / platform folder
# ---------------------------
UNAME_S := $(shell uname -s 2>/dev/null)

ifeq ($(OS),Windows_NT)
	SFML_PLATFORM := windows-mingw64
else ifeq ($(UNAME_S),Linux)
	SFML_PLATFORM := linux-x86_64
else ifeq ($(UNAME_S),Darwin)
	# Apple Silicon only
	SFML_PLATFORM := macos-arm64
else
	SFML_PLATFORM := unknown
endif

SFML_ROOT := $(SFML_VENDOR)/$(SFML_PLATFORM)

# Prefer vendored SFML; fall back to system defaults if not present
ifneq ("$(wildcard $(SFML_ROOT)/include)","")
	INC_PATH := $(SFML_ROOT)/include
	LIB_PATH := $(SFML_ROOT)/lib
	SFML_BIN := $(SFML_ROOT)/bin
else
	# System fallbacks (optional)
	ifeq ($(OS),Windows_NT)
		INC_PATH ?= /mingw64/include
		LIB_PATH ?= /mingw64/lib
		SFML_BIN ?= /mingw64/bin
	else
		INC_PATH ?= /usr/local/include
		LIB_PATH ?= /usr/local/lib
	endif
endif

INCLUDE_FLAGS = -I$(INC_PATH) -I$(INC_DIR) -I_
