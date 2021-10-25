//
//  imagen.hpp
//
//
//  Created by Alejandro Nieto Alarcon and Joel Slot 8/10/21.
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

        /**
         * @brief Construct a new Image object
         *
         */
        Image();

        /**
         * @brief Construct a new Image object based on a instance of other Image
         *
         * @param J is the image we want to copy in this one
         */
        Image(const Image & J);

        /**
         * @brief Construct a new Image object by the params rows and cols
         *
         * @param rows are going to be the rows of our image
         * @param cols are going to be the cols of our image
         */
        Image(int rows, int cols);

        /**
         * @brief Destroy the Image object
         *
         */
        ~Image();

        /**
         * @brief Get the Rows of the Image
         *
         * @return int with the value of the rows
         */
        inline int getRows() const { return this->rows; };

        /**
         * @brief Get the Cols of the Image
         *
         * @return int with the value of the cols
         */
        inline int getCols() const { return this->cols; };

        /**
         * @brief Set the value in the exact row and col of the image
         *
         * @param row is the row value in which position we will put the value
         * @param col is the col value in which position we will put the value
         * @param value is the value we want to assign in the position
         */
        inline void setPixel (int row, int col, byte value) { this->image[row][col] = value; }

        /**
         * @brief Get the value of a position in our Image by row and col
         *
         * @param row is the row of we want to know the value
         * @param col is the col of we want to know the value
         * @return byte which is the value of the pixel selected
         */
        inline byte getValuePixel(int row, int col) const { return this->image[row][col]; }

};

#endif /* imagen_hpp */
