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
    mandelbrot.GenerateImg("output/mandelbrot", name);
}

/**
 * Generates Embellished Lissajous Figures pattern image.
 */
void GenerateLissajous() {

    Lissajous lissajous(600, 1.0 / 1.0);

    const Lissajous::Cfg cfg(
        0.4, // t step
        200.0, 200.0, // amplitud
        5.0, 4.0, // frequency
        M_PI / 2.0, 0.0 // phase
    );
    lissajous.GeneratePattern(cfg);

    const Img::EmbellishedPointsCfg embellished_cfg(
        0.0, // angle offset
        5.0, // curvature
        10.0, // length
        true, // symmetric
        Img::EmbellishedPointsCfg::kHeadingNatural // heading type
    );
    char name[100];
    sprintf(name, "lissajous_%.0f-%.0f_%.0f-%.0f_%.0f-%.0f-%.0f-%s-%d.png",
            cfg.x_freq, cfg.y_freq, cfg.x_phase * 100, cfg.y_phase * 100,
            embellished_cfg.angle_offset, embellished_cfg.curvature * 100,
            embellished_cfg.length,
            (embellished_cfg.symmetric) ? "s" : "a",
            embellished_cfg.heading);
    lissajous.GenerateImg("output/lissajous", name, embellished_cfg);
}

/**
 * Main function.
 */
int main() {

    //GenerateMandelbrot();
    GenerateLissajous();

    return 0;
}
