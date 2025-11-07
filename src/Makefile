CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -I../include

SRC_DIR   := .
INC_DIR   := ../include
BUILD_DIR := build
BIN_DIR   := ../bin

TARGET  := $(BIN_DIR)/program

SOURCES := $(SRC_DIR)/main.c \
           $(INC_DIR)/database.c \
           $(INC_DIR)/mystring.c \
           $(INC_DIR)/parents.c \
           $(INC_DIR)/sorts.c

OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, \
             $(filter $(SRC_DIR)/%.c,$(SOURCES))) \
           $(patsubst $(INC_DIR)/%.c,$(BUILD_DIR)/%.o, \
             $(filter $(INC_DIR)/%.c,$(SOURCES)))

.PHONY: all clean

all: dirs $(TARGET)

dirs:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(INC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(BUILD_DIR) $(BIN_DIR)