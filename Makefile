CC = cc
CFLAGS = -std=c11 -Wall -Wextra -O2 -Iheaders
LDFLAGS = 

SRC = \
	src/main.c \
	src/data_structures.c \
	src/technical_requirements.c \
	src/special_challenges.c \
	src/cli.c

OBJ = $(SRC:.c=.o)

BIN_DIR = bin
TARGET = $(BIN_DIR)/inventory

all: $(TARGET)
$(TARGET): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR) db

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
