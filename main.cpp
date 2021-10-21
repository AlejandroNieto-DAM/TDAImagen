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

  subImage("imagenespgmppm/vacas.pgm", "cabeza.pgm", 85, 145, 60, 80);
  //contraste("imagenespgmppm/vacas.pgm", "espectaculo.pgm", 0, 255, 255, 0);
  zoomImage("imagenespgmppm/vacas.pgm", "cabezaZ.pgm", 85, 145, 40, 80);
}
