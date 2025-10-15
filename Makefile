CC = gcc
CFLAGS = -Wall -I./headers
TARGET = studendb.o

all: $(TARGET)

$(TARGET): src/main.c headers/student.c
	$(CC) $(CFLAGS) src/main.c headers/student.c -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
