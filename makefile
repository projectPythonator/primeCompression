BUILD_DIR := ./build
OBJS_DIR := ./build/objs
INCS_DIR := ./src/header
SRCS_DIR := ./src

# find the source files and header files
SRCS=$(shell find $(SRCS_DIR) -name '*.cpp')
INCS=$(shell find $(INCS_DIR) -name '*.hpp')
# generate obj and header object file strings
OBJS=$(patsubst $(SRCS_DIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))
INC_OBJS=$(patsubst $(INCS_DIR)/%.hpp,$(OBJS_DIR)/%.o,$(INCS))
# generate the target strings with a filter on the header strings (might break if gets more complex)
TARGETS=$(patsubst $(OBJS_DIR)/%.o,$(BUILD_DIR)/%.out,$(filter-out $(INC_OBJS),$(OBJS)))

#add prefix to ind dir for includes
INC_FLAGS := $(addprefix -I,$(INCS_DIR)) 

# for now all we need is this?
CPPFLAGS := $(INC_FLAGS)

# using c++23 might change this for other versions too later on, change warnings?
CXXFLAGS := -std=c++23 -O3 -Wall -Wextra -Wpedantic -Werror

.PHONY: all OBJECT_FILES PROGRAMS clean
all: OBJECT_FILES PROGRAMS

OBJECT_FILES: $(OBJS)
	
PROGRAMS: $(TARGETS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ 

$(BUILD_DIR)/%.out: $(OBJS_DIR)/%.o
	$(CXX) $^ $(INC_OBJS) -o $@ 

# TODO move this part to be prebuild instead of after cleaning
clean:
	rm -r $(BUILD_DIR)
	mkdir -p $(OBJS_DIR)
	mkdir -p $(BUILD_DIR)/data
