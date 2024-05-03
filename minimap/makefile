game: main.o minimap.o
	gcc main.o minimap.o -o game -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf

minimap.o: minimap.c minimap.h
	gcc minimap.c -c -o minimap.o

main.o: main.c minimap.h
	gcc main.c -c -o main.o
