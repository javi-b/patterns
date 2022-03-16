#pragma once

#include <math.h>
using namespace std;

/**
 * General purpose utilities that can be used anywhere in the whole
 * project.
 */
namespace utils {

/// Point data structure.
struct Point {
    double x = 0, y = 0;
    Point();
    Point(const double x, const double y) : x(x), y(y) {};
};

/// Line data structure.
struct Line {
    Point a, b;
    Line();
    Line(const Point a, const Point b) : a(a), b(b) {};
};

/**
 * Converts degrees to radians.
 */
inline double Radians(const double degrees) {

    return (degrees * M_PI / 180.0);
}

/**
 * Converts degrees to radians.
 */
inline double Degrees(const double radians) {

    return (radians * 180.0 / M_PI);
}

}
