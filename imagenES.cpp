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

bool coordinatesCheck(int x, int y, int rows, int cols){
  bool good = false;
  if((x >= 0 && x <= rows) && (y >= 0 && y <= cols)){
    good = true;
  }

  return good;
}

// _____________________________________________________________________________

Image subImage(const char *nameFichOrig, const char *nameFichOut, const int fil, const int col, const int rowsToSubstract, const int colsToSubstract){

  Image image(readImage(nameFichOrig));

  if(!coordinatesCheck(rowsToSubstract + fil, colsToSubstract + col, image.getRows(), image.getCols())){
    cout << "No se puede recortar la imagen debido a que los parámetros pasados están mal" << endl;
    exit(-1);
  }

  Image imOut(rowsToSubstract, colsToSubstract);

  for(int i = 0; i < rowsToSubstract; i++){
    for(int j = 0; j < colsToSubstract; j++){
      imOut.setPixel(i, j, image.getValuePixel(i + fil, j + col));
    }
  }

  saveImage(nameFichOut, imOut, rowsToSubstract, colsToSubstract);

  return imOut;
}

// _____________________________________________________________________________

void zoomImage(const char *nameFichOrig, const char *nameFichOut, const int x1, const int y1, const int x2, const int y2){
  int rows = abs(x2 - x1);
  int cols = abs(y2 - y1);

  if(!coordinatesCheck(x1, y1, x2, y2)){
    cout << "No se puede hacer zoom a la imagen debido a que los parámetros pasados están mal";
    exit(-1);
  }

  //Ya tenemos la imagen recortada a la que queremos hacerle zoom;
  Image image(subImage(nameFichOrig, nameFichOut, x1, y1, rows, cols));

  //Creamos la imagen de salida (2*N - 1) * (2*N -1)
  Image imOut(2*rows-1, 2*cols-1);

  int row_util = 0;
  int col_util = 0;
  /*
  Copiamos la informacion de la imagen original en los lugares que corresponden
  ya que si metemos entre las columnas y filas originales ahora una más estas tendrán
  de separación una por lo cual vemos que coinciden con las de %2 == 0 por eso iteramos de 2 en 2
  */
  for(int i = 0; i < 2*rows-1; i+=2){
    for(int j = 0; j < 2*cols-1; j+=2){
      imOut.setPixel(i, j, image.getValuePixel(row_util, col_util));
      col_util++;
    }
    row_util++;
    col_util = 0;
  }

  //Generamos la media de las columnas vacias de las filas %2 == 0
  for(int i = 0; i < (2*rows)-1; i+=2){
    for(int j = 1; j < (2*cols-2); j+=2){
      imOut.setPixel(i, j, (imOut.getValuePixel(i, j - 1)+imOut.getValuePixel(i, j + 1))/2);
    }
  }

  //En este caso ahora tenemos una fila totalmente vacia que es la que coincide con %2 != 0 por lo cualquier
  //tendremos que iterar sobre toda la fila poniendo el nuevo valor que es la media del valor de arriba y abajo
  for(int i = 1; i < (2*rows)-2; i+=2){
    for(int j = 0; j < (2*cols-1); j+=1){
      imOut.setPixel(i, j, (imOut.getValuePixel(i - 1, j)+imOut.getValuePixel(i + 1, j))/2);
    }
  }

  saveImage(nameFichOut, imOut, 2*rows-1, 2*cols-1);

}

// _____________________________________________________________________________

void contraste(const char *nameFichOrig, const char *nameFichOut, double a, double b, double newMax, double newMin){

  Image image(readImage(nameFichOrig));

  for(int i = 0; i < image.getRows(); i++){
    for(int j = 0; j < image.getCols(); j++){
      int z = (double) image.getValuePixel(i,j);
      image.setPixel(i, j, (newMin + (((newMax - newMin) / (b - a)) * (z - a))));
    }
  }

  saveImage(nameFichOut, image, image.getRows(), image.getCols());

}

// _____________________________________________________________________________

void saveImage(const char* nameFichOut, Image image, int rows, int cols){
  unsigned char *imageOutput = new unsigned char[rows * cols];
  int util = 0;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      imageOutput[util] = image.getValuePixel(i, j);
      //imageOutput[util] = matrix[i][j];
      util++;
    }
  }

  EscribirImagenPGM(nameFichOut, imageOutput, rows, cols);

  //cout << "*********** La acción se ha realizado correctamente!! **********" << endl;

  delete [] imageOutput;
}

//_____________________________________________________________________________

void morphing(const char *nameFichStart, const char *nameFichEnd, int numTransitions){
    
    if (numTransitions > 256 || numTransitions < 0){
        cout << "Ha introducido un valor para las transiciones erróneo. El valor debe ser entre 0-256" << endl;
        return;
    }

  Image imv[(numTransitions + 1)];
  imv[0] = readImage(nameFichStart);
  imv[numTransitions] = readImage(nameFichEnd);

  if (imv[0].getCols() != imv[numTransitions].getCols() || imv[0].getRows() != imv[numTransitions].getRows()){
    cout << "ERROR: tamaño de imagenes distintas" << imv[0].getCols() << imv[numTransitions].getCols() << endl;
    return;
  }

  double transValue[imv[0].getRows()][imv[0].getCols()];
  for(int i = 0; i < imv[0].getRows(); i++){
    for(int j = 0; j < imv[0].getCols(); j++){
      double a = imv[numTransitions].getValuePixel(i,j);
      double b = imv[0].getValuePixel(i,j);
      transValue[i][j] = (a - b) / (double) numTransitions;
    }
  }

  //cout << imv[0].getCols() << endl;

  saveImage("gif_images/000_frame.pgm", imv[0], imv[0].getRows(), imv[0].getCols());
  string numerator = "gif_images/";
  for (int i = 0; i < 3 - to_string(numTransitions).length(); i++){
    numerator += "0";
  }
  numerator += to_string(numTransitions) + "_frame.pgm";
  saveImage(numerator.c_str(), imv[numTransitions], imv[0].getRows(), imv[0].getCols());

  for (int x = 1; x < numTransitions; x++){
    imv[x] = imv[0];
    for(int i = 0; i < imv[0].getRows(); i++){
      for(int j = 0; j < imv[0].getCols(); j++){
          imv[x].setPixel(i, j, (imv[0].getValuePixel(i,j) + transValue[i][j]*x));
      }
    }
    numerator = "gif_images/";
    for (int i = 0; i < 3 - to_string(x).length(); i++){
      numerator += "0";
    }
    numerator += to_string(x) + "_frame.pgm";
    saveImage(numerator.c_str(), imv[x], imv[0].getRows(), imv[0].getCols());
  }

}


/* Fin Fichero: imagenES.cpp */
