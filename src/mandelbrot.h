#pragma once

#include <complex>
#include "img.h"
using namespace std;

/**
 * Mandelbrot pattern class.
 */
class Mandelbrot {
public:
    /// Pattern config data structure.
    struct Cfg {
        int width, height; // Image's size.
        double ar; // Image's aspect ratio.
        double x, y; // Mandelbrot position center.
        double zoom; // Mandelbrot zoom.
        int max_n; // Max number of iterations to check mandelbrot point.

        // constructor
        Cfg(const int height, const double ar,
                const double x, const double y, const double zoom,
                const int max_n);
    };

    // public functions
    void GenerateImg(const string & dir, const string & name, Cfg & cfg);

private:
    Cfg * cfg_; ///< Pointer to current config data structure.

    // helper functions
    double * GenerateMatrix();
    long GetMandelbrotValue(const complex<double> c);
    void NormalizeMatrix(double * matrix, const int w, const int h,
            const double min, const double max);
};
