#pragma once

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

    // public functions
    void GenerateImg(const string & dir, const string & name);

protected:
    int width_, height_; // Pattern size.
    float aspect_ratio_; // Pattern size aspect ratio.

    double * matrix_; // Pattern pixels matrix (values from 0.0 to 1.0).

    // helper functions
    void NormalizeMatrix(const double min, const double max);
};
