all: tdaImagen

tdaImagen: main.o imagenES.o imagen.o
	g++ -o tdaimagen main.o imagenES.o imagen.o

main.o: main.cpp
	g++ -c main.cpp

imagenEs.o: imagenES.cpp
	g++ -c imagenES.cpp

imagen.o: imagen.cpp
	g++ -c imagen.cpp

clean:
	rm -f tdaimagen *.o *.pgm

perm:
	chmod 777 tdaimagen

gif:
	convert -delay 2 -loop 0 *_frame.pgm merge.gif
