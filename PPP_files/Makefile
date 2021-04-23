# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# the compiler: gcc for C program, define as g++ for C++
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -std=c14 by default, it seems

CFLAGS  = -g -ggdb -Wall -std=c++17
LDFLAGS = -lfltk -lXext -lX11 -lm -lfltk_images

OBJDIR = obj
OBJFILES = foo.o Graph.o GUI.o Window.o
# -ggdb doesnt work here:
OBJECTS = $(patsubst %,$(OBJDIR)/%,$(OBJFILES))
# -ggdb adds symbols if this is objects:
#OBJECTS = foo.cpp
# the build target executable:
TARGET = a.out

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS) 

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $(OBJDIR)/$*.o $*.cpp

clean:
	$(RM) -f $(OBJECTS) $(TARGET) *~



# g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp Simple_window.cpp foo.cpp `fltk-config --ldflags --use-images`
# g++ -w -Wall -std=c++11 Graph.cpp Window.cpp GUI.cpp foo.cpp `fltk-config --ldflags --use-images`

# https://www.fltk.org/doc-1.3/basics.html
