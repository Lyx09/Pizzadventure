CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra -pedantic -I./include
LDLIBS = -lSDL2 -lSDL_image

# SDL
CFLAGS += $(shell sdl2-config --cflags)
LDLIBS += $(shell sdl2-config --libs)

ifdef DEBUG
CFLAGS += -g -fsanitize=address
endif

SRC = $(wildcard src/*.c)
OBJ = ${SRC:.c=.o}

GAME = game

.PHONY: all $(GAME) check clean

all: $(GAME)

$(GAME): ${OBJ}

check:
	tests/test.sh $(commands)

clean:
	$(RM) $(GAME) $(OBJ)
