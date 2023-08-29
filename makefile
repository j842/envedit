MAKEFLAGS+="-j -l $(shell grep -c ^processor /proc/cpuinfo)"

EXE_NAME := envedit

COM_COLOR   := \033[0;34m
CRE_COLOR   := \033[0;35m
LIN_COLOR   := \033[0;33m
OBJ_COLOR   := \033[0;36m
VER_COLOR	:= \033[0;92m
NO_COLOR    := \033[m

ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))


BUILD_DIR := build
SRC_DIRS := src
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)

CXX=g++
LD=g++
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := $(INC_FLAGS) -MMD -MP
CXXFLAGS := -g -Wall -std=c++17 
LDFLAGS  := -g
LDLIBS   := -l:libncurses.a -l:libtinfo.a


$(EXE_NAME): $(OBJS) 
	@printf "%b" "$(LIN_COLOR)Linking   $(OBJ_COLOR)$(@)$(NO_COLOR)\n";
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)
	@rm -f null.d
	@echo 

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp 
	@printf "%b" "$(COM_COLOR)Compiling $(OBJ_COLOR)$(@)$(NO_COLOR)\n";
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
