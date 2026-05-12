CC ?= cc
CFLAGS ?= -Wall -Wextra -std=c11
TARGET := spinning-towel
SOURCES := assn5.c group.c player.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) group.h player.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o result_game.txt
