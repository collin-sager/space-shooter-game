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
UNAME_M := $(shell uname -m 2>/dev/null)

ifeq ($(OS),Windows_NT)
	SFML_PLATFORM := windows-mingw64
else ifeq ($(UNAME_S),Linux)
	SFML_PLATFORM := linux-x86_64
else ifeq ($(UNAME_S),Darwin)
	ifeq ($(UNAME_M),arm64)
		SFML_PLATFORM := macos-arm64
	else
		SFML_PLATFORM := macos-x86_64
	endif
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

INCLUDE_FLAGS = -I$(INC_PATH) -I$(INC_DIR) -I$(SRC_DIR)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Windows executable suffix
ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
endif

# ---------------------------
# Targets
# ---------------------------
all: build
build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ARCH) -o $@ $^ $(RPATH) -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(ARCH) $(CXXVERSION) -o $@ -c $< $(INCLUDE_FLAGS)

clean:
	$(DEL) $(TARGET) $(OBJECTS)

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo "# DEPENDENCIES" >> Makefile
	@$(CXX) -MM $(SRC_FILES) $(INCLUDE_FLAGS) >> Makefile

# ---------------------------
# Run (keeps SFML runtime libs in vendor/sfml/...; no copying required)
# ---------------------------
# ---------------------------
# Run (keeps SFML runtime libs in vendor/sfml/...; no copying required)
# ---------------------------
ifeq ($(OS),Windows_NT)

# Avoid PATH breakage from C:/... by converting to /c/... form
SFML_BIN_POSIX := $(shell cygpath -u "$(CURDIR)/$(SFML_BIN)")

run: $(TARGET)
	@echo Running $(TARGET) with SFML DLLs from $(SFML_BIN)
	@PATH="$(SFML_BIN_POSIX):$$PATH" ./$(TARGET)

else ifeq ($(UNAME_S),Linux)

run: $(TARGET)
	@echo Running $(TARGET) with SFML libs from $(LIB_PATH)
	@LD_LIBRARY_PATH="$(LIB_PATH):$$LD_LIBRARY_PATH" ./$(TARGET)

else ifeq ($(UNAME_S),Darwin)

run: $(TARGET)
	@echo Running $(TARGET) with SFML libs from $(LIB_PATH)
	@DYLD_LIBRARY_PATH="$(LIB_PATH):$$DYLD_LIBRARY_PATH" ./$(TARGET)

else

run:
	@echo "Unsupported platform for 'run' target. Build with: make build"

endif


.PHONY: all build run clean depend

# DEPENDENCIES
