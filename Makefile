# Hyperborean makefile.
#

default: all

# Pick one of:
#   linux
#   macos
#   windows

UNAME=$(shell uname)
ifeq ($(UNAME),Darwin)
  OS=macos
else ifeq ($(UNAME),Linux)
  OS=linux
else ifeq ($(UNAME),FreeBSD)
  OS=bsd
else ifeq ($(UNAME),OpenBSD)
  OS=bsd
else ifneq (,$(findstring MINGW32_NT,$(UNAME)))
  OS=win
else
  $(error unknown os $(UNAME))
endif

# Build directory
#

BUILD=build
INCLUDE=src

# Library versions
#

LUAJIT_VER=luajit-2.0.4
CATCH_VER=catch-1.5.6
PHYSFS_VER=physfs-3.0.0
SDL2_VER=SDL2-2.0.5
SFML_VER=SFML-2.4.2
ALLEGRO_VER=allegro-5.2.2.0

# Compiler selection and flags
#

RM=rm -f
ifneq ($(UNAME),FreeBSD)
  CXX=g++
else
  CXX=c++
endif

CXXFLAGS=-std=c++14 \
         -I$(INCLUDE) \
	 -Ioutside/$(LUAJIT_VER)/src \
	 -Ioutside/$(CATCH_VER) \
	 -Ioutside/$(PHYSFS_VER)/src

CXXWFLAGS=-Wall \
	  -Wextra \
	  -Werror

# Misc
#

TAGS=.tags \
     .etags

# Files to be made
#

HYPERBOREAN_MAIN=src/Main.o
HYPERBOREAN_ROOT_FILES=src/Application.o \
		       src/Log.o \
		       src/Settings.o \
		       src/SettingsParser.o

HYPERBOREAN_ASSETS_FILES=src/Assets/Asset.o \
			 src/Assets/Store.o \
			 src/Assets/ManifestParser.o

HYPERBOREAN_EVENTS_FILES=src/Events/EventChannel.o \
			 src/Events/EventListener.o

HYPERBOREAN_OS_FILES=src/OS.o \
		     src/OS/File.o \
		     src/OS/FileSystem.o

HYPERBOREAN_SCRIPTING_FILES=src/Scripting/Environment.o

HYPERBOREAN_TEST_FILES=tests/Main.o \
	               tests/Unit/Scripting/TestEnvironment.o \
		       tests/Unit/Events/TestEventChannel.o

HYPERBOREAN_OFILES=$(HYPERBOREAN_ROOT_FILES) \
		   $(HYPERBOREAN_ASSETS_FILES) \
		   $(HYPERBOREAN_EVENTS_FILES) \
		   $(HYPERBOREAN_OS_FILES) \
	           $(HYPERBOREAN_SCRIPTING_FILES) \

# External dependencies
#

# LuaJIT
ifeq ($(OS),win)
  LIBLUAJIT=outside/$(LUAJIT_VER)/src/lua51.dll
else
  LIBS=-ldl
  LIBLUAJIT=outside/$(LUAJIT_VER)/src/libluajit.a
endif

ifeq ($(OS),macos)
  # Additional flags required by LuaJIT to correctly link against 64-bit macOS app.
  LIBS+=-pagezero_size 10000 \
        -image_base 100000000
endif

# PhysFS
LIBS+=-lz
LIBPHYSFS=outside/$(PHYSFS_VER)/libphysfs.a

ifeq ($(OS),macos)
  # Additional frameworks required for PhysFS on macOS
  LIBS+=-framework CoreFoundation \
	-framework CoreServices \
	-framework IOKit \
	-framework ApplicationServices \
	-framework Foundation
endif

# SDL2
LIBSDL2=outside/$(SDL2_VER)/build/libSDL2main.a
#LIBS+=-pthread -lsndio -lrt -lasound -lSDL2 -lSDL2main -lGL -lGLU -lglut

# SFML
#LIBS+=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBSFML=outside/$(SFML_VER)/lib/libsfml-audio.so

# Allegro
# LIBS+=-lallegro -lallegro_main -lallegro_image -lallegro_ttf -lallegro_font -lallegro_color

# Make targets
#

all: hyperborean

hyperborean: $(BUILD)/hyperborean
ifeq ($(OS),win)
	@echo "    COPY   $(LIBLUAJIT) -> ./build"
	@cp $(LIBLUAJIT) ./build
endif

tests: CXXFLAGS+=-DUNITTESTS
tests: clean $(HYPERBOREAN_OFILES) $(HYPERBOREAN_TEST_MAIN) $(HYPERBOREAN_TEST_FILES) $(LIBLUAJIT) $(LIBPHYSFS)
	@echo "    BUILD  $(BUILD)/test_hyperborean"
	@mkdir -p $(BUILD)
	@$(CXX) $(CXXFLAGS) -o $(BUILD)/test_hyperborean $(HYPERBOREAN_OFILES) $(HYPERBOREAN_TEST_FILES) $(LIBLUAJIT) $(LIBPHYSFS) $(LIBS)

$(BUILD)/hyperborean: $(HYPERBOREAN_MAIN) $(HYPERBOREAN_OFILES) $(LIBLUAJIT) $(LIBPHYSFS)
	@echo "    BUILD  $(BUILD)/hyperborean"
	@mkdir -p $(BUILD)
	@$(CXX) $(CXXFLAGS) -o $(BUILD)/hyperborean $(HYPERBOREAN_MAIN) $(HYPERBOREAN_OFILES) $(LIBLUAJIT) $(LIBPHYSFS) $(LIBS)

%.o: %.cpp
	@echo "    CXX    $@"
	@$(CXX) -c $(CXXWFLAGS) $(CXXFLAGS) -o $@ $<

$(LIBLUAJIT):
	@echo "    LIB    $(LUAJIT_VER)"
	$(MAKE) -C outside/$(LUAJIT_VER)/src

$(LIBPHYSFS):
	@echo "    LIB    $(PHYSFS_VER)"
	cd outside/$(PHYSFS_VER) && cmake .
	$(MAKE) -C outside/$(PHYSFS_VER)

$(LIBSDL2):
	@echo "    LIB    $(SDL2_VER)"
	cd outside && unzip $(SDL2_VER).zip
	cd outside/$(SDL2_VER) && ./configure
	$(MAKE) -C outside/$(SDL2_VER)

$(LIBSFML):
	@echo "    LIB    $(SFML_VER)"
	cd outside && unzip $(SFML_VER).zip
	cd outside/$(SFML_VER) && cmake .
	$(MAKE) -C outside/$(SFML_VER)

tags: etags

etags:
	etags -f .etags $$(find ./src -name '*.cpp' -or -name '*.hpp') || true

# Only clean out project-related files
#
clean:
	@echo "    CLEAN"
	@$(RM) $(HYPERBOREAN_MAIN) \
	       $(HYPERBOREAN_OFILES) \
	       $(HYPERBOREAN_TEST_FILES) \
	       $(BUILD)/hyperborean \
	       $(BUILD)/test_hyperborean \
	       $(TAGS)

# Clean out project and dependency-related files
#
full-clean: clean
	$(MAKE) clean -C outside/$(LUAJIT_VER)/src
	$(MAKE) clean -C outside/$(PHYSFS_VER)/

.PHONY: clean full-clean etags tags
