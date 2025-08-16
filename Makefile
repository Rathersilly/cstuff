# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -Werror treats warnings as errors

CFLAGS  = -g -ggdb -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion -std=c++20
LDFLAGS =
OBJFILES = foo.cpp #goo.cpp
# the build target executable:
TARGET = a.out

# all is a convention - when ran with 0 args, make will run the first thing it sees,
# which by convention is all
# http://www.gnu.org/software/make/manual/html_node/Standard-Targets.html#Standard-Targets
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) 
clean:
	$(RM) -f $(OBJFILES) $(TARGET) *~

