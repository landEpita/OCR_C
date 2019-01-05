CC = gcc -g3
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS= -L Preprocessing,Segmentation,neural\ network,Interface
LDLIBS= `pkg-config --libs sdl` -lSDL_image
SRC= all.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}




compile_all: all
 

main: ${OBJ}

 


-include ${DEP}





compile_module:
	cd Preprocessing; make
	cd Segmentation; make
	cd neural\ network; make
	cd Interface; make
	rm -f gui
	rm -f all
	cp -p Interface/gui .


ocr: compile_module compile_all

clean:
	cd Preprocessing; make clean
	cd Segmentation; make clean
	cd neural\ network; make clean
	cd Interface; make clean
	rm -f all gui all.d all.o
	rm -f Interface/gui



