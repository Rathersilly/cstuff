# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

CFLAGS  = -g -Wall
LDFLAGS =
OBJFILES = foo.cpp
# the build target executable:
TARGET = a.out

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) 
clean:
	$(RM) -f $(OBJFILES) $(TARGET) *~

