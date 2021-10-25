/**
  * @file imagenES.h
  * @brief Fichero cabecera para la E/S de im�genes
  *
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */

#ifndef _IMAGEN_ES_H_
#define _IMAGEN_ES_H_

#include <string>
#include "imagen.hpp"


/**
  * @brief Tipo de imagen
  *
  * Declara una serie de constantes para representar los distintos tipos
  * de im�genes que se pueden manejar.
  *
  * @see LeerTipoImagen
  */
enum TipoImagen {IMG_DESCONOCIDO, IMG_PGM, IMG_PPM};

/**
  * @brief Devuelve el tipo de imagen del archivo
  *
  * @param nombre indica el archivo de disco que consultar
  * @return Devuelve el tipo de la imagen en el archivo
  *
  * @see TipoImagen
  */
TipoImagen LeerTipoImagen (const char *nombre);

/**
  * @brief Lee una imagen de tipo PPM
  *
  * @param nombre archivo a leer
  * @param filas Par�metro de salida con las filas de la imagen.
  * @param columnas Par�metro de salida con las columnas de la imagen.
  * @return puntero a una nueva zona de memoria que contiene @a filas x @a columnas x 3
  * bytes que corresponden a los colores de todos los p�xeles en formato
  * RGB (desde la esquina superior izqda a la inferior drcha). En caso de que no
  * no se pueda leer, se devuelve cero. (0).
  * @post En caso de �xito, el puntero apunta a una zona de memoria reservada en
  * memoria din�mica. Ser� el usuario el responsable de liberarla.
  */
unsigned char *LeerImagenPPM (const char *nombre, int& fils, int& cols);

/**
  * @brief Escribe una imagen de tipo PPM
  *
  * @param nombre archivo a escribir
  * @param datos punteros a los @a f x @a c x 3 bytes que corresponden a los valores
  *    de los p�xeles de la imagen en formato RGB.
  * @param f filas de la imagen
  * @param c columnas de la imagen
  * @return si ha tenido �xito en la escritura.
  */
bool EscribirImagenPPM (const char *nombre, const unsigned char *datos,
                        const int fils, const int cols);

/**
  * @brief Lee una imagen de tipo PGM
  *
  * @param nombre archivo a leer
  * @param filas Par�metro de salida con las filas de la imagen.
  * @param columnas Par�metro de salida con las columnas de la imagen.
  * @return puntero a una nueva zona de memoria que contiene @a filas x @a columnas
  * bytes que corresponden a los grises de todos los p�xeles
  * (desde la esquina superior izqda a la inferior drcha). En caso de que no
  * no se pueda leer, se devuelve cero. (0).
  * @post En caso de �xito, el puntero apunta a una zona de memoria reservada en
  * memoria din�mica. Ser� el usuario el responsable de liberarla.
  */
unsigned char *LeerImagenPGM (const char *nombre, int& fils, int& cols);

/**
  * @brief Escribe una imagen de tipo PGM
  *
  * @param nombre archivo a escribir
  * @param datos punteros a los @a f x @a c bytes que corresponden a los valores
  *    de los p�xeles de la imagen de grises.
  * @param f filas de la imagen
  * @param c columnas de la imagen
  * @return si ha tenido �xito en la escritura.
  */
bool EscribirImagenPGM (const char *nombre, const unsigned char *datos,
                        const int fils, const int cols);


/**
 * @brief A traves de la ruta del archivo que pasamos por parametros convertimos
 * la imagen de un char* a nuestra clase Imagen
 *
 * @param nameFichOrig Es el nombre de de la imagen que queremos leer
 * @return Image que es la imagen con el contenido de los bytes de la imagen que
 * está en el directorio que hemos pasado como parámetro
 */
Image readImage(const char *nameFichOrig);

/**
 * @brief Is a function to make sure the x and y value are under the value of rows
 * and cols pertinent and are not negatives because its imposible to get a sub image
 * that starts in (-1, -100) or exceeds the number of rows and cols
 *
 * @param x Value we want to compare
 * @param y Value we want to compare
 * @param rows number of rows of an image
 * @param cols number of cols of an image
 * @return true if the point (x, y) its correct
 * @return false if the point (x, y) its not correct
 */
bool coordinatesCheck(int x, int y, int rows, int cols);

/**
 * @brief Recorta una imagen dado el punto superior izquierdo desde el que queremos partir
 * para recortar la imagen dando un numero de filas y columnas para recortar
 *
 * @param nameFichOrig Es el nombre del fichero al que le recortaremos las filas
 * y columnas deseadas.
 * @param nameFichOut Es el nombre del fichero de salida sobre el que guardaremos
 * la imagen final una vez hecho el recorte.
 * @param fil Es el numero de fila desde el que partiremos para hacer el recorte.
 * @param cols Es el numero de columna desde el que partiremos para hacer el recorte.
 * @param rowsToSubstract Es el número de filas que queremos recortar a partir del anterior
 * parámetro fil.
 * @param colsToSubstract Es el número de columnas que queremos recortar a partir del
 * anterior parámetro cols.
 * @return Image which is the new image
 */
Image subImage(const char *nameFichOrig, const char *nameFichOut, const int fil, const int cols, const int rowsToSubstract, const int colsToSubstract);

/**
 * @brief Realiza el recorte de una imagen para depués hacerle zoom a esta de una
 * forma interpolada
 *
 * @param nameFichOrig nombre del fichero origen al que le queremos hacer zoom.
 * @param nameFichOut  nombre del fichero de salida sobre el que escribiremos la
 * imagen zoomeada.
 * @param x1 Fila desde la que partiremos para hacer el recorte
 * @param y1 Columna desde la que partiremos para hacer el recorte
 * @param x2 Fila destino a la que llegaremos para hacer el recorte.
 * @param y2 Columna destino a la que llegaremos para hacer el recorte.
 */
void zoomImage(const char *nameFichOrig, const char *nameFichOut, const int x1, const int y1, const int x2, const int y2);

/**
 * @brief Es una funcion que aumenta el contraste de una imagen segun los parámetros
 *
 * @param nameFichOrig nombre del fichero origen sobre el que queremos cambiar el contraste
 * @param nameFichOut nombre del fichero de salida sobre que guardaremos la imagen con
 * el nuevo constraste
 * @param a contraste minimo que contiene la imagen
 * @param b contraste maximo que contiene la imagen
 * @param newMax nuevo contraste maximo que tendrá la imagen
 * @param newMin nuevo contraste minimo que tendrá la imagen
 */
void contraste(const char *nameFichOrig, const char *nameFichOut, double a, double b, double newMax, double newMin);

/**
 * @brief Recibe el nombre de un fichero y una imagen con sus valores y los convierte
 * a char* para poder utilizar la funcion de EscribirImagenPGM
 *
 * @param nameFichOut nombre del archivo a escribir.
 * @param image es una instancia del objeto Image que contiene los valores de cada
 * uno de los bytes de la imagen para ser escrita.
 * @param rows Filas de la imagen
 * @param cols Columnas de la imagen.
 */
void saveImage(const char* nameFichOut, Image image, int rows, int cols);

void morphingDese(const char *nameFichStart, const char *nameFichEnd, int numTransitions);


#endif

/* Fin Fichero: imagenES.h */
