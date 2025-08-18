CC = g++
CFLAGS = -g -Wall
OBJFILES = calc.cpp
TARGET = a.out

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS) 
clean:
	$(RM) -f (TARGET) *~
