# Define the C and C++ compilers to use 
CXX = g++
CC = gcc 

# Define warning/debugging flags 
FLAGS   = -Wall -Wextra -g

# Define name of final executable
TARGET = helloTriangle 

# Define library flags 
LIBS = -lglfw -lGL 

# List all C and C++ source files 
SRCS_C = glad.c 
SRCS_CPP = main.cpp 

# Generate object file names from source file names 
OBJS_C = $(SRCS_C:.c=.o)
OBJS_CPP = $(SRCS_CPP:.cpp=.o)
OBJS = $(OBJS_C) $(OBJS_CPP)

# The 'all' target is the default one, executed when you just run 'make'
.PHONY: all
all: $(TARGET)

# Command to link all obj files into final executable 
$(TARGET): $(OBJS)
	@echo "Linking ... "
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)
	@echo "Build finished: $(TARGET)"

# Command to compile .cpp src files to .obj files 
%.o : %.cpp
	@echo "Compiling ..."
	@$(CXX) $(FLAGS) -c $^ -o $@
	@echo "done"

# Command to compile .c src files to .obj files
%.o : %.c 
	@echo "Compiling ..."
	@$(CC) $(FLAGS) -c $^ -o $@
	@echo "done"

# The 'clean' target removes all generated files
.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(TARGET) $(OBJS)
	@echo "Clean complete."

