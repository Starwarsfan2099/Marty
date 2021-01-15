ifeq ($(OS),Windows_NT)
	# If on Windows, use gcc
	CC = gcc
	INCLUDES = -I/usr/include/json-c
else
	# On Mac and Linux, we prefer Clang, but GCC can also be used
	CC = clang
	INCLUDES = -I/usr/local/include/json-c -I/usr/local/include
endif

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -O0
LIBS = -L/usr/local/lib -lsqlite3 -ljson-c
VERBOSE = -v

# the build target executable:
TARGET = marty
HEADERS = callbacks.h commands.h
HEADERS_C = callbacks.c commands.c

# Get OS
UNAME_S := $(shell uname -s)

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(HEADERS_C) $(INCLUDES) $(LIBS)

clean:
	$(RM) $(TARGET)

# If on Mac OS, remove the debug symbol file as well
    ifeq ($(UNAME_S),Darwin)
		$(RM) -rf $(TARGET).dSYM
    endif

