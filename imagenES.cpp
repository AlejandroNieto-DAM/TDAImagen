 /**
  * @file imagenES.cpp
  * @brief Fichero con definiciones para la E/S de im�genes
  *
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */

#include <fstream>
#include <string>

#include "imagenES.h"
#include "imagen.hpp"

using namespace std;

TipoImagen LeerTipo(ifstream& f){
  char c1,c2;
  TipoImagen res= IMG_DESCONOCIDO;

  if (f){
    c1=f.get();
    c2=f.get();
    if (f && c1=='P')
      switch (c2) {
        case '5': res= IMG_PGM; break;
        case '6': res= IMG_PPM; break;
        default: res= IMG_DESCONOCIDO;
      }
  }
  return res;
}

// _____________________________________________________________________________


Image readImage(const char *nameFichOrig){

  int rows, cols;

  unsigned char *readImage = LeerImagenPGM (nameFichOrig, rows, cols);
  if (!readImage){
    cerr << "Error: No pudo leerse la imagen." << endl;
    cerr << "Terminando la ejecucion del programa." << endl;
    exit (1);
  }

  Image image(rows, cols);
  int util = 0;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      image.setPixel(i, j, readImage[util]);
      util++;
    }
  }

  return image;

  delete [] readImage;

}

// _____________________________________________________________________________


void subImage(const char *nameFichOrig, const char *nameFichOut, const int fil, const int col, const int rowsToSubstract, const int colsToSubstract){

  Image image(readImage(nameFichOrig));

  unsigned char *imageOutput = new unsigned char[rowsToSubstract * colsToSubstract];
  int util = 0;
  for(int i = 0; i < rowsToSubstract; i++){
    for(int j = 0; j < colsToSubstract; j++){
      imageOutput[util] = image.getValuePixel(i + fil, j + col);
      util++;
    }
  }

  EscribirImagenPGM(nameFichOut, imageOutput, rowsToSubstract, colsToSubstract);

  delete [] imageOutput;

}


void zoomImage(const char *nameFichOrig, const char *nameFichOut, const int x1, const int y1, const int x2, const int y2){
  int rows = abs(x2 - x1);
  int cols = abs(y2 - y1);

  cout << "stop1" << endl;

  subImage(nameFichOrig, nameFichOut, x1, y1, rows, cols);

  cout << "stop2" << endl;
  //Ya tenemos la imagen recortada a la que queremos hacerle zoom;
  Image image(readImage(nameFichOut));
  cout << "stop3" << endl;
  //Falta construir la matriz (2N - 1) * (2N - 1) y hacer la media de los valores entre una y otra columnas. Lo mismo para las filas.
  unsigned char matrix[2*rows-1][2*cols-1];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      matrix[i*2-1][j*2-1] = image.getValuePixel(i,j);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols - 1; j++)
      matrix[i*2-1][j*2] = (matrix[i*2-1][j*2-1]+matrix[i*2-1][j*2+1])/2;

  for (int i = 0; i < rows - 1; i++)
    for (int j = 0; j < 2 * cols - 1; j++)
      matrix[i*2][j] = (matrix[i*2-1][j]+matrix[i*2+1][j])/2;

  unsigned char *imageOutput = new unsigned char[(2*rows-1) * (2*cols-1)];
  int util = 0;
  for (int i = 0; i < 2*rows-1; i++)
    for (int j = 0; j < 2*cols - 1; j++){
      imageOutput[util] = matrix[i][j];
      util++;
    }
  EscribirImagenPGM(nameFichOut, imageOutput, 2*rows-1, 2*cols-1);
  delete [] imageOutput;
}


void contraste(const char *nameFichOrig, const char *nameFichOut, double a, double b, double newMax, double newMin){

  Image image(readImage(nameFichOrig));

  unsigned char *imageOutput = new unsigned char[image.getRows() * image.getCols()];
  int util = 0;
  for(int i = 0; i < image.getRows(); i++){
    for(int j = 0; j < image.getCols(); j++){
      int z = (double) image.getValuePixel(i,j);
      imageOutput[util] = (unsigned char) (newMin + (((newMax - newMin) / (b - a)) * (z - a)));
      util++;
    }
  }

  EscribirImagenPGM(nameFichOut, imageOutput, image.getRows(), image.getCols());

  delete [] imageOutput;

}


// _____________________________________________________________________________

TipoImagen LeerTipoImagen(const char *nombre){
  ifstream f(nombre);
  return LeerTipo(f);
}


// _____________________________________________________________________________

char SaltarSeparadores (ifstream& f){
  char c;
  do{
    c= f.get();
  } while (isspace(c));
  f.putback(c);
  return c;
}

// _____________________________________________________________________________

bool LeerCabecera (ifstream& f, int& fils, int& cols){
    int maxvalor;
    string linea;
    while (SaltarSeparadores(f)=='#')
      getline(f,linea);
    f >> cols >> fils >> maxvalor;

    if (/*str &&*/ f && fils>0 && fils<5000 && cols>0 && cols<5000){
        f.get(); // Saltamos separador
        return true;
    }
    else
      return false;
}



// _____________________________________________________________________________

unsigned char *LeerImagenPPM (const char *nombre, int& fils, int& cols){
  unsigned char *res=0;
  fils=0;
  cols=0;
  ifstream f(nombre);

  if (LeerTipo(f)==IMG_PPM){
    if (LeerCabecera (f, fils, cols)){
        res= new unsigned char[fils*cols*3];
        f.read(reinterpret_cast<char *>(res),fils*cols*3);
        if (!f){
          delete[] res;
          res= 0;
        }
    }
  }
  return res;
}

// _____________________________________________________________________________

unsigned char *LeerImagenPGM (const char *nombre, int& fils, int& cols){
  unsigned char *res=0;
  fils=0;
  cols=0;
  ifstream f(nombre);

  if (LeerTipo(f)==IMG_PGM){
    if (LeerCabecera (f, fils, cols)){
      res= new unsigned char[fils*cols];
      f.read(reinterpret_cast<char *>(res),fils*cols);
      if (!f){
        delete[] res;
        res= 0;
      }
    }
  }
  return res;
}

// _____________________________________________________________________________

bool EscribirImagenPPM (const char *nombre, const unsigned char *datos,
                        const int fils, const int cols){
  ofstream f(nombre);
  bool res= true;

  if (f){
    f << "P6" << endl;
    f << cols << ' ' << fils << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(datos),fils*cols*3);
    if (!f)
      res=false;
  }
  return res;
}
// _____________________________________________________________________________

bool EscribirImagenPGM (const char *nombre, const unsigned char *datos,
                        const int fils, const int cols){
  ofstream f(nombre);
  bool res= true;

  if (f){
    f << "P5" << endl;
    f << cols << ' ' << fils << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(datos),fils*cols);
    if (!f)
      res=false;
  }
  return res;
}

// _____________________________________________________________________________




/* Fin Fichero: imagenES.cpp */
