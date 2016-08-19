# Hyperborean makefile.
#

default: all

# Pick one of:
#   linux
#   osx
# TODO: windows

UNAME=$(shell uname)
ifeq ($(UNAME),Darwin)
  OS=osx
else ifeq ($(UNAME),Linux)
  OS=linux
else ifeq ($(UNAME),FreeBSD)
  OS=bsd
else ifeq ($(UNAME),OpenBSD)
  OS=bsd
else
  $(error unknown unix)
endif

# Build directory
#

BUILD=build
INCLUDE=src

# Library versions
#

LUAJIT_VER=luajit-2.0.4

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
	 -Ioutside/$(LUAJIT_VER)/src

CXXWFLAGS=-Wall \
	  -Wextra \
	  -Werror

# Misc
#

TAGS=.tags \
     .etags

# Files to be made
#

HYPERBOREAN_OFILES=src/Application.o

# External dependencies
#

LIBS=-ldl
LIBLUAJIT=outside/$(LUAJIT_VER)/src/libluajit.a

# Make targets
#

all: hyperborean

hyperborean: $(BUILD)/hyperborean

$(BUILD)/hyperborean: $(HYPERBOREAN_OFILES) $(LIBLUAJIT)
	@echo "    BUILD  $(BUILD)/hyperborean"
	@mkdir -p $(BUILD)
	@$(CXX) $(CXXFLAGS) -o $(BUILD)/hyperborean $(HYPERBOREAN_OFILES) $(LIBLUAJIT) $(LIBS)

%.o: %.cpp
	@echo "    CXX    $@"
	@$(CXX) -c $(CXXWFLAGS) $(CXXFLAGS) -o $@ $<

$(LIBLUAJIT):
	@echo "    LIB    $(LUAJIT_VER)"
	$(MAKE) -C outside/$(LUAJIT_VER)/src

tags: etags

etags:
	@etags -f .etags $$(find . -name '*.cpp' -or -name '*.hpp') || true

clean:
	$(RM) $(HYPERBOREAN_OFILES) $(BUILD)/hyperborean $(TAGS)

.PHONY: clean
