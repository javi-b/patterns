#pragma once

#include "utils.h"
#include "img.h"
using namespace std;

/**
 * Pattern base class.
 */
class Pattern {
public:
    // constructor and destructor
    Pattern(const int height, const float aspect_ratio);
    ~Pattern();

protected:
    int width_, height_; // Pattern size.
    float aspect_ratio_; // Pattern size aspect ratio.

    // The following variables are different ways to generate the pattern.
    // Only one should be used, each derived Pattern class uses one.
    double * matrix_; // Pattern pixels matrix (values from 0.0 to 1.0).
    vector<utils::Point> points_; // Vector of points that form the pattern.
    vector<utils::Line> lines_; // Vector of lines that form the pattern.

    // helper functions
    void NormalizeMatrix(const double min, const double max);
};
