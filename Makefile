all: tdaImagen

tdaImagen: main.o imagenES.o imagen.o
	mkdir gif_images
	g++ -o tdaimagen main.o imagenES.o imagen.o

main.o: main.cpp
	g++ -c main.cpp

imagenEs.o: imagenES.cpp
	g++ -c imagenES.cpp

imagen.o: imagen.cpp
	g++ -c imagen.cpp

clean:
	rm -f tdaimagen *.o *.pgm
	rm -r gif_images/ 

exe:
	chmod 777 tdaimagen
	./tdaimagen

gif:
	convert -delay 2 -loop 0 gif_images/*_frame.pgm gif_images/merge.gif
	rm gif_images/*_frame.pgm
