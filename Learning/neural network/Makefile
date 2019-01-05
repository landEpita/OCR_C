## Simple SDL mini code
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl gtk+-3.0` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-3.0` -lSDL_image -lm
 
OBJ= function.o main.o tools_network.o correction.o tools_letter.o segmentation.o resize.o
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
	${RM} ${OBJ} ${DEP} *~
	${RM} main
 
-include ${DEP}
 
# END
