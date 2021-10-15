#include <iostream>
#include "imagen.hpp"
#include "imagenES.h"

void frameImage (Image & I, unsigned char frame){
  // Crear el marco que delimita la imagen
  int f, c;
  for (f = 0; f < I.getRows (); f++) // lado izquierdo
    I.setPixel (f, 0, frame);

  for (f=0; f < I.getRows (); f++) // lado derecho
    I.setPixel (f, I.getCols () - 1, frame);

  for (c=0; c < I.getCols (); c++) // lado superior
    I.setPixel (0, c, frame);

  for (c=0; c < I.getCols (); c++) // lado inferior
    I.setPixel (I.getRows () - 1, c, frame);


}



int main() {

//Se vienen cositas
  Image imagen;
  imagen.printf();

  //EJ marco (2.1.3)
  int f = 10, c = 10;

  // Construir la imagen de "nf" filas y "nc" columnas
  Image I (f, c);

  // Crear una imagen plana con valor 255 (blanco)
  for (f=0; f < I.getRows (); f++)
    for (c=0; c < I.getCols (); c++)
      I.setPixel (f, c, 255);

    frameImage( I , '1' );
    I.printf();
  //subImage("imagenespgmppm/vacas.pgm", "cabeza.pgm", 85, 145, 60, 80);
  //contraste("imagenespgmppm/vacas.pgm", "espectaculo.pgm", 0, 255, 255, 0);

}
