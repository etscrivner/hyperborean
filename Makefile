# Hyperborean makefile.
#

default: all

CORE=.MAKEFILE-VERSION

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

# Compiler selection and flags
#

RM=rm -f
ifneq ($(UNAME),FreeBSD)
  CXX=g++
else
  CXX=c++
endif

INCLUDE=src

CXXFLAGS=-std=c++11 \
         -I$(INCLUDE)
CXXWFLAGS=-Wall \
	  -Wextra \
	  -Werror

# Misc

TAGS=.tags \
     .etags

# Files to be made
#

HYPERBOREAN_OFILES=src/Application.o

# Make targets
#

all: hyperborean

hyperborean: $(BUILD)/hyperborean

$(BUILD)/hyperborean: $(HYPERBOREAN_OFILES)
	@echo "    BUILD  $(BUILD)/hyperborean"
	@mkdir -p $(BUILD)
	@$(CXX) $(CXXFLAGS) -o $(BUILD)/hyperborean $(HYPERBOREAN_OFILES)

%.o: %.cpp
	@echo "    CXX    $@"
	@$(CXX) -c $(CXXWFLAGS) $(CXXFLAGS) -o $@ $<

tags: etags

etags:
	@etags -f .etags $$(find . -name '*.cpp' -or -name '*.hpp') || true

clean:
	$(RM) $(HYPERBOREAN_OFILES) $(BUILD)/hyperborean $(TAGS)

.PHONY: clean
