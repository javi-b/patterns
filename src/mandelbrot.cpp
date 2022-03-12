#include <iostream>
#include "mandelbrot.h"

#define CUR_0 "\033[0G"

/**
 * Pattern config data structure constructor.
 */
Mandelbrot::Cfg::Cfg(const double x, const double y, const double zoom,
        const int max_n) : x(x), y(y), zoom(zoom), max_n(max_n) {}

/**
 * Mandelbrot pattern constructor.
 */
Mandelbrot::Mandelbrot(const int height, const double aspect_ratio,
        const Cfg & cfg) : Pattern(height, aspect_ratio), cfg_(cfg) {}

/**
 * Generates pixels matrix of Mandelbrot values.
 */
void Mandelbrot::GenerateMatrix() {

    const double x = cfg_.x, y = cfg_.y, zoom = cfg_.zoom;
    double min = cfg_.max_n, max = 0.0;

    for (int i = 0; i < width_; i++) {

        cout << CUR_0 << "Generating Mandelbrot matrix "
            << int(i / float(width_) * 100) << "%...";

        for (int j = 0; j < height_; j++) {

            const double a = (i - width_ / 2.0) * (4 * aspect_ratio_)
                / (width_ * zoom) + x;
            const double b = (j - height_ / 2.0) * 4
                / (height_ * zoom) + y;
            const complex<double> c (a, b);

            const double value = double(GetMandelbrotValue(c));
            matrix_[i + j * width_] = value;

            if (value < min)
                min = value;
            if (value > max)
                max = value;
        }
    }

    cout << endl;

    NormalizeMatrix(min, max);
}

/**
 * Gets Mandelbrot number of iterations for specific complex number.
 */
long Mandelbrot::GetMandelbrotValue(const complex<double> c) {

    complex<double> z (0.0, 0.0);

    for (int n = 0; n < cfg_.max_n; n++) {
        if (z.real() * z.real() + z.imag() * z.imag() > 2 * 2)
            return n;
        z = z * z + c;
    }
    return cfg_.max_n;
}
