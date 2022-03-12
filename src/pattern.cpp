#include "pattern.h"

/**
 * Pattern class constructor.
 */
Pattern::Pattern(const int height, const float aspect_ratio)
    : width_(int(height * aspect_ratio)), height_(height),
        aspect_ratio_(aspect_ratio) {

    // initializes pattern pixels matrix
    matrix_ = new double[width_ * height_];
}

/**
 * Pattern class destructor.
 */
Pattern::~Pattern() {

    delete[] matrix_;
}

/**
 * Generates pattern image.
 */
void Pattern::GenerateImg(const string & dir, const string & name) {

    // creates img
    Img img(width_, height_);

    // draws matrix in img
    img.DrawMatrixBW(matrix_, true);

    // applies filters
    img.Normalize();
    img. Blur();

    // writes img to file
    img.Write(dir, name);
}

/**
 * Normalizes matrix to values from 0.0 to 1.0.
 */
void Pattern::NormalizeMatrix(const double min, const double max ) {

    if(max - min == 0)
        return;

    for(int i = 0; i < width_; i++) {
        for(int j = 0; j < height_; j++) {
            double val = matrix_[i + j * width_];
            matrix_[i + j * width_] = (val - min) / (max - min);
        }
    }
}
