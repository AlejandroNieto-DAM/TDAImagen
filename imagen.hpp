//
//  imagen.hpp
//
//
//  Created by Alejandro Nieto Alarcon on 8/10/21.
//

#ifndef imagen_hpp
#define imagen_hpp

#include <iostream>
#include <cstddef>
using namespace std;

typedef unsigned char byte;

class Image {

    private:

        unsigned char **image;
        int rows;
        int cols;

    public:

        Image();
        Image(const Image & J);
        Image(int rows, int cols);
        ~Image();
        inline int getRows() const { return this->rows; };
        inline int getCols() const { return this->cols; };
        inline void setPixel (int row, int col, byte value) { this->image[row][col] = value; }
        inline byte getValuePixel(int row, int col) const { return this->image[row][col]; }
        void printf();



};

#endif /* imagen_hpp */
