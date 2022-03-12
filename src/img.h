#pragma once

#include <Magick++.h>
using namespace std;

/**
 * Image class.
 */
class Img {
public:
    // constructor
    Img(const int width, const int height);

    // public functions

    void DrawMatrixBW(double * matrix, const bool inverse);

    void DrawLine(const float start_x, const float start_y,
            const float end_x, const float end_y, const string & color);

    void Normalize();
    void Blur(const double radius = 1.0, const double sigma = 0.5);

    void Write(const string & dir, const string & name);

private:
    Magick::Image img_ = NULL; ///< Magick++ Image object.
    int width_, height_; // Image width and height sizes.
};
