# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

CFLAGS  = -g -ggdb -Wall -std=c++17
LDFLAGS =
# OBJFILES = goo.cpp#c++17_test.cpp #goo.cpp
OBJFILES = main.cpp Vector3d.cpp Point3d.cpp
# the build target executable:
TARGET = a.out

# all is a convention - when ran with 0 args, make will run the first thing it sees,
# which by convention is all
# http://www.gnu.org/software/make/manual/html_node/Standard-Targets.html#Standard-Targets
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) 
clean:
	$(RM) -f  $(TARGET) *~
	# $(RM) -f $(OBJFILES) $(TARGET) *~

