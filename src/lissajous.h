#pragma once

#include "utils.h"
#include "pattern.h"
using namespace std;

/**
 * Embellished Lissajous Figures pattern derived class.
 */
class Lissajous : public Pattern {
public:
    /// Pattern config data structure.
    struct Cfg {
        double t_step; // T step.
        double x_amp, y_amp; // Amplitud.
        double x_freq, y_freq; // Frequencey.
        double x_phase, y_phase; // Phase.

        // constructor
        Cfg(const double t_step, const double x_amp, const double y_amp,
                const double x_freq, const double y_freq,
                const double x_phase, const double y_phase);
    };

    // constructor
    Lissajous(const int height, const double aspect_ratio);

    // public functions
    void GeneratePattern(const Cfg & cfg);
    void GenerateImg(const string & dir, const string & name,
            const Img::EmbellishedPointsCfg & embellished_cfg);

private:

};

