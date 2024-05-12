
game: main.o tb.o
	gcc main.o tb.o -o game -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
tb.o: tb.c tb.h
	gcc tb.c -c -o tb.o

main.o: main.c tb.h
	gcc main.c -c -o main.o
