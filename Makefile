prog:fn.o main.o
	gcc fn.o main.o  -o prog -lSDL -lSDL_ttf -g -lSDL_image -lSDL_mixer 
main.o:main.c
	gcc -c main.c  -g
fn.o:fn.c
	gcc -c fn.c -g
clean:
	rm -rf *.o prog

