# Compiler
CXX := g++

# C++ standard
CXXSTD := c++11

# Compiler flags
CXXFLAGS := -Wall -g -std=$(CXXSTD)

# Directories definitions
TEST_DIR := "."
ROOT_DIR := ".."
SRC_DIR := "$(ROOT_DIR)/src"

# Target C++ file
TARGETCPP := $(shell find "$(TEST_DIR)" -type f -name "test*.cpp")

# Target
TARGET := $(TARGETCPP:.cpp=.out)

# Command to run tests
RUN_TESTS_CMD := $(shell echo $(TARGET) | sed 's/ /; /g')

# Header files
HEADERS := $(shell find "$(SRC_DIR)" -type f -name "*.h")

# Implementation C++ files
IMPLCPP := $(shell find "$(SRC_DIR)/structs" -type f -name "*.cpp" -not -path "$(SRC_DIR)/structs/cpp_data_structures_and_algorithms/.tests/*")

# Implementation files
IMPL := $(IMPLCPP:.cpp=.o)

# Source files
SRCS := $(TARGETCPP) $(IMPLCPP)

# Object files
OBJS := $(SRCS:.cpp=.o)

# Default rule to build and run the executable
all: build test

# Rule to compile test*.cpp files into test*.o files
test%.o: test%.cpp $(HEADERS)
	./update_testcase.sh $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile .cpp files into .o files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.out: %.o $(IMPL)
	$(CXX) $(CXXFLAGS) $< $(IMPL) -o $@

# Rule to compile all source .cpp files
compile: $(OBJS)

# Rule to build the executable
build: $(TARGET)

# Rule to run the executable
test: $(TARGET)
	$(RUN_TESTS_CMD)

# Update the testcases in the testfile
update_tests:
	find ./ -type f -name "*.cpp" -exec ./update_testcase.sh "{}" \;

# Clean rule to remove generated files
clean:
	rm $(TARGET) $(OBJS) || true
	find ./ -type d -name "*.dSYM" -exec rm -r "{}" \; || true
