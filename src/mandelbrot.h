#pragma once

#include <complex>
#include "pattern.h"
using namespace std;

/**
 * Mandelbrot pattern derived class.
 */
class Mandelbrot : public Pattern {
public:
    /// Mandelbrot pattern config data structure.
    struct Cfg {
        double x, y; // Mandelbrot position center.
        double zoom; // Mandelbrot zoom.
        int max_n; // Max number of iterations to check mandelbrot point.

        // constructor
        Cfg(const double x, const double y, const double zoom,
                const int max_n);
    };

    // constructor
    Mandelbrot(const int height, const double aspect_ratio,
            const Cfg & cfg);

    // public functions
    void GenerateMatrix();

private:
    Cfg cfg_; ///< Config data structure.

    // helper functions
    long GetMandelbrotValue(const complex<double> c);
};
