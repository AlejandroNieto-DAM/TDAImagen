#include <iostream>
#include "imagen.hpp"
#include <string>
#include "imagenES.h"

using namespace std;

void mensajePrincipal(){
  cout << "\nBienvenido al editor de imágenes! " << endl;
  cout << "1 - Recortar imagen" << endl;
  cout << "2 - Cambiar contraste de la imagen" << endl;
  cout << "3 - Hacer zoom a una imagen" << endl;
  cout << "4 - Crear transicion entre dos imagenes" << endl;
  cout << "0 - SALIR" << endl;
  cout << "Introduzca la opcion que desea realizar: ";
}

void menu() {
  int option = -1;
  int x, y, x2, y2;
  string nombreFicheroEntrada, nombreFicheroEntrada2;
  string nombreFicheroSalida;

  while(option != 0){

    mensajePrincipal();
    cin >> option;

    switch(option){
      case 1:

        cout << "\nHa elegido la opcion de realizar un recorte de imagen!" << endl;
        cout << "Introduce el nombre del directorio de la imagen que desea recortar: ";
        cin >> nombreFicheroEntrada;
        cout << "Introduce el nombre del directorio de la imagen que desea de salida: ";
        cin >> nombreFicheroSalida;
        cout << "Introduce las coordenadas desde las que se quiere recortar la imagen (x, y): ";
        cin >> x >> y;
        cout << "Introduce las filas y columnas que se quiere recortar la imagen a partir de las anteriores coordenadas: ";
        cin >> x2 >> y2;
        subImage(nombreFicheroEntrada.c_str(), nombreFicheroSalida.c_str(), x, y, x2, y2);
        break;

      case 2:

        cout << "\nHa elegido la opcion de cambiar el contraste de la imagen!" << endl;
        cout << "troduce el nombre del directorio de la imagen que desea cambiar: ";
        cin >> nombreFicheroEntrada;
        cout << "Introduce el nombre del directorio de la imagen que desea de salida: ";
        cin >> nombreFicheroSalida;
        cout << "Introduce el minimo y el maximo valor de contraste actual (0-255)(0-255): ";
        cin >> x >> y;
        cout << "Introduce el maximo y minimo valor de contraste que se desea (0-255)(0-255): ";
        cin >> x2 >> y2;
        contraste(nombreFicheroEntrada.c_str(), nombreFicheroSalida.c_str(), x, y, x2, y2);
        break;

      case 3:

        cout << "\nHa elegido la opcion de hacer zoom a una imagen!" << endl;
        cout << "Introduce el nombre del directorio de la imagen que desea hacer zoom: ";
        cin >> nombreFicheroEntrada;
        cout << "Introduce el nombre del directorio de la imagen que desea de salida: ";
        cin >> nombreFicheroSalida;
        cout << "Introduce las coordenadas desde donde se quiere hacer zoom a la imagen (x, y): ";
        cin >> x >> y;
        cout << "Introduce las coordenadas hasta donde se quiere hacer zoom a la imagen (x, y): ";
        cin >> x2 >> y2;
        zoomImage(nombreFicheroEntrada.c_str(), nombreFicheroSalida.c_str(), x, y, x2, y2);
        break;

      case 4:

        cout << "\nHa elegido la opcion de hacer una transicion!!" << endl;
        cout << "Introduce el nombre del directorio de la primera imagen: ";
        cin >> nombreFicheroEntrada;
        cout << "Introduce el nombre del directorio de la segunda imagen: ";
        cin >> nombreFicheroEntrada2;
        cout << "Introduce el numero de transiciones: ";
        cin >> x;

        morphingDese(nombreFicheroEntrada.c_str(), nombreFicheroSalida.c_str(), x);
        break;


    }
  }
}
int main() {

  menu();

}
