
CFLAGS = -Wall 

busca: busca.o func.o

busca.o: busca.c
func.o: func.c func.h

clean:
	rm -f *.o

purge: clean
	rm -f busca
