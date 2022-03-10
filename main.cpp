#include "mandelbrot.h"

/**
 * Main function.
 */
int main() {

    Mandelbrot mandelbrot;

    Mandelbrot::Cfg cfg = Mandelbrot::Cfg(
        2160, // height
        1.0 / 1.0, // aspect ratio
        -0.761574, -0.0847596, // coordinates
        78125.0, // zoom
        1000 // max n
    );
    mandelbrot.GenerateImg("output/", "mandelbrot.png", cfg);

    return 0;
}
