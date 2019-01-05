## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= pixel_operations.c main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

-include ${DEP}

# END
