CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra -pedantic -I./include
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# SDL
CFLAGS += $(shell sdl2-config --cflags)
LDLIBS += $(shell sdl2-config --libs)

ifdef DEBUG
CFLAGS += -g -DDEBUG #-fsanitize=address
endif

SRC = $(wildcard src/*.c)
OBJ = ${SRC:.c=.o}

GAME = game

all: $(GAME)

$(GAME): ${OBJ}
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^

list:
	$(CC) $(CFLAGS) $(LDLIBS) -o list tests/list_test.c src/list.c

map:
	$(CC) $(CFLAGS) $(LDLIBS) -o map tests/map_test.c src/map.c src/list.c

check:
	tests/test.sh $(commands)

clean:
	$(RM) $(GAME) $(OBJ)
	$(RM) list map

.PHONY: all check clean
