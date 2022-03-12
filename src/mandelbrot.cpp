#include <iostream>
#include "mandelbrot.h"

#define CUR_0 "\033[0G"

/**
 * Pattern config data structure constructor.
 */
Mandelbrot::Cfg::Cfg(const int height, const double ar,
        const double x, const double y, const double zoom, const int max_n)
    : width(int(height * ar)), height(height), ar(ar),
        x(x), y(y), zoom(zoom), max_n(max_n) {}

/**
 * Generates a Mandelbrot pattern image.
 */
void Mandelbrot::GenerateImg(const string & dir, const string & name,
        Cfg & cfg) {

    cfg_ = &cfg;

    // creates img
    Img img(cfg_->width, cfg_->height);

    // draws matrix in img
    img.DrawMatrixBW(GenerateMatrix(), true);

    // applies filters
    img.Normalize();
    img. Blur();

    // writes img to file
    img.Write(dir, name);
}

/**
 * Generates matrix of Mandelbrot values (0.0 to 1.0).
 */
double * Mandelbrot::GenerateMatrix() {

    const int w = cfg_->width, h = cfg_->height;
    const double ar = cfg_->ar;
    const double x = cfg_->x, y = cfg_->y, zoom = cfg_->zoom;

    double * matrix = new double[w * h];
    double min = cfg_->max_n, max = 0.0;

    for (int i = 0; i < w; i++) {

        cout << CUR_0 << "Generating Mandelbrot matrix "
            << int(i / float(w) * 100) << "%...";

        for (int j = 0; j < h; j++) {

            const double a = (i - w / 2.0) * (4 * ar) / (w * zoom) + x,
                    b = (j - h / 2.0) * 4 / (h * zoom) + y;
            const complex<double> c (a, b);

            const double value = double(GetMandelbrotValue(c));
            matrix[i + j * w] = value;

            if (value < min)
                min = value;
            if (value > max)
                max = value;
        }
    }

    cout << endl;

    NormalizeMatrix(matrix, w, h, min, max);

    return matrix;
}

/**
 * Gets Mandelbrot number of iterations for specific complex number.
 */
long Mandelbrot::GetMandelbrotValue(const complex<double> c) {

    complex<double> z (0.0, 0.0);

    for (int n = 0; n < cfg_->max_n; n++) {
        if (z.real() * z.real() + z.imag() * z.imag() > 2 * 2)
            return n;
        z = z * z + c;
    }
    return cfg_->max_n;
}

/**
 * Normalizes matrix of values from 0.0 to 1.0.
 */
void Mandelbrot::NormalizeMatrix(double * matrix, const int w, const int h,
        const double min, const double max ) {

    if(max - min == 0)
        return;

    for(int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            double val = matrix[i + j * w];
            matrix[i + j * w] = (val - min) / (max - min);
        }
    }
}
