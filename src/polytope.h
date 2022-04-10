#pragma once

#include "utils.h"
#include "pattern.h"
using namespace std;

/**
 * Polytope pattern derived class.
 */
class Polytope : public Pattern {
public:
    // constructor
    Polytope(const int height, const double aspect_ratio);

    // public functions
    void GeneratePattern();
    void GenerateImg(const string & dir, const string & name);

private:

};

