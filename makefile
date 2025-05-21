# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

# Project folders
SRC_DIR := src
BIN_DIR := bin
INC_DIR := include

# Target name and source files
TARGET := $(BIN_DIR)/pe-analyzer
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=%.o)

# Default rule
all: $(TARGET)

# Link the final binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(addprefix build/, $^)

# Compile .cpp to .o into build/
build/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pattern rule for implicit .o building
%.o: $(SRC_DIR)/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o build/$@

# Clean rule
clean:
	rm -rf build $(BIN_DIR) *.o

# Run the program
run: $(TARGET)
	./$(TARGET)
