#include <iostream>
#include "imagen.hpp"
#include "imagenES.h"

int main() {

  //subImage("imagenespgmppm/vacas.pgm", "cabeza.pgm", 85, 145, 60, 80);
  //contraste("imagenespgmppm/vacas.pgm", "espectaculo.pgm", 0, 255, 140, 80);
  //zoomImage("cabeza.pgm", "cabezaZ.pgm", 0, 0, 60, 80);
  cout << "a";
  try{
  morphingDese("imagenespgmppm/vacas.pgm", "espectaculo.pgm", 5);
  }
  catch(const std::exception& e){
    cout << "error in call";
  }
}
