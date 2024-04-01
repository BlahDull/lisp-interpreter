# Compiler
CC = g++

# Compiler flags
CFLAGS = -g -Wall

# Directories
SRC_DIR = src
INC_DIR = headers
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Header files
HDRS = $(wildcard $(INC_DIR)/*.hh)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable name
EXEC = lisp

# Default target
all: $(EXEC)

# Compile .cpp files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(HDRS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Link object files into executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(EXEC)

.PHONY: all clean
