# Compiler
CC = g++

# Compiler flags
CFLAGS = -g -Wall

# Source files
SRCS = TokenStream.cpp Token.cpp Parser.cpp Lexer.cpp Lisp.cpp

# Header files
HDRS = TokenStream.hh Token.hh Parser.hh Lexer.hh libs.hh

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = lisp

# Default target
all: $(EXEC)

# Compile .cpp files into object files
%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)
