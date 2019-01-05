## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` -MMD
CFLAGS= -Wall -Wextra -std=c99 
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` 

SRC= gui.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: gui

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} 

-include ${DEP}

# END
