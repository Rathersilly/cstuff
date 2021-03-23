
CC = g++

CFLAGS = -Wall
LDFLAGS = #-lX11 -lm etc

OBJDIR = obj
OBJFILES = foo.o goo.o
OBJECTS = $(patsubst %,$(OBJDIR)/%,$(OBJFILES))
# this substituion doesnt work in variables, just commands or rules
# ok idk why the above works but this didnt, but at least it works
#OBJFILES = $(OBJDIR)/foo.o $(OBJDIR)/goo.o
#OBJECTS=  obj/foo.o obj/goo.o
SRCFILES = foo.cpp goo.cpp
TARGET = asdf

# want to substi each obj file name with objdir/obj file
#OBJECTS = $(patsubst %,$(OBJDIR)/%)

$(TARGET): $(OBJECTS) #OBJECTS needs to be obj/foo.o etc
	$(CC) -o $(TARGET) $(OBJECTS)

#OBJECTS: $(OJBDIR)/foo.o $(OJBDIR)/goo.o

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) -c -o $(OBJDIR)/$*.o $*.cpp #$<

#obj/%.o: %.cpp
	#$(CC) -c $< -o $@

clean: 
	rm  asdf obj/*.o

sup:
	echo "sup"
