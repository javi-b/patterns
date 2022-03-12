#include "mandelbrot.h"

/**
 * Main function.
 */
int main() {

    const Mandelbrot::Cfg cfg = Mandelbrot::Cfg(
        -0.761574, -0.0847596, // coordinates
        78125.0, // zoom
        1000 // max n
    );
    Mandelbrot mandelbrot(2160, 1.0 / 1.0, cfg);
    mandelbrot.GenerateMatrix();
    mandelbrot.GenerateImg("output/", "mandelbrot.png");

    return 0;
}
