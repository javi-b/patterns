#pragma once

#include <complex>
#include "utils.h"
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
    Mandelbrot(const int height, const double aspect_ratio);

    // public functions
    void GeneratePattern(const Cfg & cfg);
    void GenerateImg(const string & dir, const string & name);

private:
    // helper functions
    long GetMandelbrotValue(const complex<double> c, const int max_n);
};
