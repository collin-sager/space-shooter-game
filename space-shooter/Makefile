# THE NAME OF YOUR EXECUTABLE
TARGET = asteroids
# PROJECT LAYOUT
SRC_DIR = src
INC_DIR = include
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = $(addprefix $(SRC_DIR)/, main.cpp game.cpp kinematics.cpp spaceship.cpp asteroid.cpp gamedisplay.cpp bullet.cpp)

# SFML
SFML_VENDOR := vendor/sfml

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic-errors
CXXFLAGS_DEBUG = -g
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	DEL = rm -f
	Q =

	# Prefer SFML vendored next to the project
	ifneq ("$(wildcard $(SFML_VENDOR)/include)","")
		INC_PATH := $(SFML_VENDOR)/include
		LIB_PATH := $(SFML_VENDOR)/lib
	else
		# Fallback if user didn't vendor SFML (MSYS2 default, optional)
		INC_PATH ?= /mingw64/include
		LIB_PATH ?= /mingw64/lib
	endif

	ARCH =
	RPATH =
else
	DEL = rm -f
	Q = "

	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
		RPATH =
	endif
	ifeq ($(UNAME_S),Darwin)
		TARGET_MAKEFILE = Makefile.osx
		CXXFLAGS += -D OSX
		RPATH = -Wl,-rpath,/Library/Frameworks
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH = 
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH = 
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH = 
	endif
endif

INCLUDE_FLAGS = -I$(INC_PATH) -I$(INC_DIR) -I$(SRC_DIR)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Default target: build + run
all: build

build: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ARCH) -o $@ $^ $(RPATH) -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(ARCH) $(CXXVERSION) -o $@ -c $< -I$(INC_PATH) -I$(INC_DIR) -I$(SRC_DIR)

clean:
	$(DEL) $(TARGET) $(OBJECTS)

depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) $(INCLUDE_FLAGS) >> Makefile

# Where SFML DLLs live when using vendored SFML
SFML_BIN := $(SFML_VENDOR)/bin
SFML_BIN_POSIX := $(shell cygpath -u "$(CURDIR)/$(SFML_BIN)")

run: $(TARGET)
	@echo Running $(TARGET) with SFML DLLs from $(SFML_BIN)
	@PATH="$(SFML_BIN_POSIX):$$PATH" ./$(TARGET)

.PHONY: all build run clean depend

# DEPENDENCIES
src/main.o: src/main.cpp 
