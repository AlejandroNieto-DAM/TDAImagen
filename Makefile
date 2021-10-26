all: tdaImagen

tdaImagen: main.o imagenEs.o imagen.o
	g++ -o tdaimagen main.o imagenEs.o imagen.o

main.o: main.cpp
	g++ -c main.cpp

imagenEs.o: imagenEs.cpp
	g++ -c imagenEs.cpp

imagen.o: imagen.cpp
	g++ -c imagen.cpp

clean:
	rm -f tdaimagen *.o *.pgm

perm:
	chmod 777 tdaimagen
