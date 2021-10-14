//
//  imagen.cpp
//
//
//  Created by Alejandro Nieto Alarcon on 8/10/21.
//

#include "imagen.hpp"
#include <cstddef>
#include <iostream>
using namespace std;

Image::Image(){
  this->cols = 5;
  this->rows = 5;

  this->image = new byte * [this->getRows()];
  for(int i = 0; i < this->getRows(); i++){
    this->image[i] = new byte[this->getCols()];
  }

  for(int i = 0; i < this->rows; i++){ //Añadi esto para poder hmmm, empezar con una imagen al principio, no solo ponerlo al final en printf
    for(int j = 0; j < this->cols; j++){
      this->image[i][j] = '0';
    }
  }

}

Image::Image(const Image & J){
  this->cols = J.getCols();
  this->rows = J.getRows();

  this->image = new byte * [this->getRows()];
  for(int i = 0; i < this->getRows(); i++){
    this->image[i] = new byte[this->getCols()];
  }

  for(int i = 0; i < this->getRows(); i++){
    for(int j = 0; j < this->getCols(); j++){
      this->setPixel(i, j, J.getValuePixel(i, j));
    }
  }

}

Image::Image(int rows, int cols){
  this->cols = cols;
  this->rows = rows;

  this->image = new byte * [this->getRows()];
  for(int i = 0; i < this->getRows(); i++){
    this->image[i] = new byte[this->getCols()];
  }

  for(int i = 0; i < this->rows; i++){
    for(int j = 0; j < this->cols; j++){
      this->image[i][j] = '0';
    }
  }
}

Image::~Image(){
  for(int i = 0; i < this->rows; i++){
    delete [] this->image[i];
  }

  delete [] this->image;
}


void Image::printf(){
/*   Innecesario, que cambia cualquier valor. Lo dejo para mostrar los cambios.
  for(int i = 0; i < this->rows; i++){
    for(int j = 0; j < this->cols; j++){
      this->image[i][j] = '1';
    }
  }
*/
  for(int i = 0; i < this->rows; i++){
    for(int j = 0; j < this->cols; j++){
      cout << this->image[i][j];
    }
    cout << endl;
  }
}
