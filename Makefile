all : structure.o pipeline.o sequentiel.o ual.o analyseurS.o Interface.o main.o
	gcc structure.o pipeline.o sequentiel.o ual.o analyseurS.o Interface.o main.o -o prog `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

main.o: main.c structure.h Interface.h
	gcc -o main.o -c main.c  `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`

analyseurS.o : analyseurS.c analyseurS.h structure.h
	gcc -o analyseurS.o -c analyseurS.c	

ual.o : ual.c ual.h sequentiel.h
	gcc -o ual.o -c ual.c	

sequentiel.o : sequentiel.c structure.h
	gcc -o sequentiel.o -c sequentiel.c	

pipeline.o : pipeline.c pipeline.h structure.h
	gcc -o pipeline.o -c pipeline.c
	
structure.o : structure.c structure.h
	gcc -o structure.o -c structure.c
	
Interface.o : Interface.c Interface.h structure.h 
	gcc -o Interface.o -c Interface.c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
	
run:
	./prog
	
clean:
	rm -rf *.o
	
supp: clean
	rm -rf prog
