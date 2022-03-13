#include <iostream>
#include "lissajous.h"

/**
 * Pattern config data structure constructor.
 */
Lissajous::Cfg::Cfg(const double t_step, const double x_amp,
        const double y_amp, const double x_freq, const double y_freq,
        const double x_phase, const double y_phase)
    : t_step(t_step), x_amp(x_amp), y_amp(y_amp), x_freq(x_freq),
        y_freq(y_freq), x_phase(x_phase), y_phase(y_phase) {}

/**
 * Embellished Lissajous Figures pattern constructor.
 */
Lissajous::Lissajous(const int height, const double aspect_ratio)
        : Pattern(height, aspect_ratio) {}

/**
 * Generates Lissajous pattern's points.
 */
void Lissajous::GeneratePattern(const Cfg & cfg) {

    double first_x = 0.0, first_y = 0.0;

    for (double t = 0.0; true; t += cfg.t_step) {

        // calculates point
        double x = cfg.x_amp * sin(cfg.x_freq * t + cfg.x_phase);
        double y = cfg.y_amp * sin(cfg.y_freq * t + cfg.y_phase);

        // centers point
        x += width_ / 2.0;
        y += height_ / 2.0;

        // inserts point to vector
        points_.push_back(utils::Point(x, y));

        // checks if loop is done
        if (t == 0.0)
            first_x = x, first_y = y;
        else if (abs(x - first_x) < 0.1 && abs(y - first_y) < 0.1)
            break;
    }
}

/**
 * Generates pattern image.
 */
void Lissajous::GenerateImg(const string & dir, const string & name,
        const Img::EmbellishedPointsCfg & embellished_cfg) {

    // creates img
    Img img(width_, height_);

    // draws matrix in img
    img.DrawEmbellishedPoints(points_, "black", embellished_cfg);

    // applies filters
    //img.Normalize();
    //img. Blur();

    // writes img to file
    img.Write(dir, name);
}
