#include <stdio.h>
#include "mandelbrot.h"
#include "lissajous.h"

/**
 * Generates Mandelbrot pattern image.
 */
void GenerateMandelbrot() {

    Mandelbrot mandelbrot(600, 1.0 / 1.0);

    const Mandelbrot::Cfg cfg(
        -0.761574, -0.0847596, // coordinates
        625.0, // zoom
        1000 // max n
    );
    mandelbrot.GeneratePattern(cfg);

    char name[100];
    sprintf(name, "mandelbrot_%f_%f_%.0f_%d.png",
            cfg.x, cfg.y, cfg.zoom, cfg.max_n);
    mandelbrot.GenerateImg("output", name);
}

/**
 * Generates Embellished Lissajous Figures pattern image.
 */
void GenerateLissajous() {

    Lissajous lissajous(600, 1.0 / 1.0);

    const Lissajous::Cfg cfg(
        0.5, // t step
        200.0, 200.0, // amplitud
        5.0, 6.0, // frequency
        M_PI / 2.0, 0.0 // phase
    );
    lissajous.GeneratePattern(cfg);

    const Img::EmbellishedPointsCfg embellished_cfg(
        80.0, // angle offset
        2.0, // curvature
        80.0, // length
        true // symmetric
    );
    char name[100];
    sprintf(name, "lissajous_%.0f-%.0f_%.0f-%.0f_%.0f-%.0f-%.0f-%s.png",
            cfg.x_freq, cfg.y_freq, cfg.x_phase * 100, cfg.y_phase * 100,
            embellished_cfg.angle_offset, embellished_cfg.curvature * 100,
            embellished_cfg.length,
            (embellished_cfg.symmetric) ? "s" : "a");
    lissajous.GenerateImg("output", name, embellished_cfg);
}

/**
 * Main function.
 */
int main() {

    //GenerateMandelbrot();
    GenerateLissajous();

    return 0;
}
