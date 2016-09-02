# Hyperborean makefile.
#

default: all

# Pick one of:
#   linux
#   osx
#   windows

UNAME=$(shell uname)
ifeq ($(UNAME),Darwin)
  OS=osx
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

# Compiler selection and flags
#

RM=rm -f
ifneq ($(UNAME),FreeBSD)
  CXX=g++
else
  CXX=c++
endif

CXXFLAGS=-std=c++11 \
         -I$(INCLUDE) \
	 -Ioutside/$(LUAJIT_VER)/src \
	 -Ioutside/$(CATCH_VER)

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
		       src/Log.o

HYPERBOREAN_SCRIPTING_FILES=src/Scripting/Environment.o

HYPERBOREAN_TEST_FILES=tests/Main.o \
	               tests/Unit/Scripting/TestEnvironment.o

HYPERBOREAN_OFILES=$(HYPERBOREAN_ROOT_FILES) \
	           $(HYPERBOREAN_SCRIPTING_FILES)

# External dependencies
#

ifeq ($(OS),win)
  LIBLUAJIT=outside/$(LUAJIT_VER)/src/lua51.dll
else
  LIBS=-ldl
  LIBLUAJIT=outside/$(LUAJIT_VER)/src/libluajit.a
endif

ifeq ($(OS),osx)
  # Additional flags required by LuaJIT to correctly link against 64-bit OSX app.
  LIBS+=-pagezero_size 10000 \
        -image_base 100000000
endif

# Make targets
#

all: hyperborean

hyperborean: $(BUILD)/hyperborean
ifeq ($(OS),win)
	@echo "    COPY   $(LIBLUAJIT) -> ./build"
	@cp $(LIBLUAJIT) ./build
endif

tests: CXXFLAGS+=-DUNITTESTS
tests: clean $(HYPERBOREAN_OFILES) $(HYPERBOREAN_TEST_MAIN) $(HYPERBOREAN_TEST_FILES) $(LIBLUAJIT)
	@echo "    BUILD  $(BUILD)/test_hyperborean"
	@mkdir -p $(BUILD)
	@$(CXX) $(CXXFLAGS) -o $(BUILD)/test_hyperborean $(HYPERBOREAN_OFILES) $(HYPERBOREAN_TEST_FILES) $(LIBLUAJIT) $(LIBS)

$(BUILD)/hyperborean: $(HYPERBOREAN_MAIN) $(HYPERBOREAN_OFILES) $(LIBLUAJIT)
	@echo "    BUILD  $(BUILD)/hyperborean"
	@mkdir -p $(BUILD)
	@$(CXX) $(CXXFLAGS) -o $(BUILD)/hyperborean $(HYPERBOREAN_MAIN) $(HYPERBOREAN_OFILES) $(LIBLUAJIT) $(LIBS)

%.o: %.cpp
	@echo "    CXX    $@"
	@$(CXX) -c $(CXXWFLAGS) $(CXXFLAGS) -o $@ $<

$(LIBLUAJIT):
	@echo "    LIB    $(LUAJIT_VER)"
	$(MAKE) -C outside/$(LUAJIT_VER)/src

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

.PHONY: clean full-clean
