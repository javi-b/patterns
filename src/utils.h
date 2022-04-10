#pragma once

#include <math.h>
#include <vector>
using namespace std;

/**
 * General purpose utilities that can be used anywhere in the whole
 * project.
 */
namespace utils {

/// Point data structure.
struct Point {
    double x = 0, y = 0;
    Point() {};
    Point(const double x, const double y) : x(x), y(y) {};
};

/// Line data structure.
struct Line {
    Point a, b;
    Line() {};
    Line(const Point & a, const Point & b) : a(a), b(b) {};
};

/// 3D Point data structure.
struct Point3D {
    double x = 0, y = 0, z = 0;
    Point3D() {};
    Point3D(const double x, const double y, const double z)
        : x(x), y(y), z(z) {};
};

/// 3D Line data structure.
struct Line3D {
    Point3D a, b;
    Line3D() {};
    Line3D(const Point3D & a, const Point3D & b) : a(a), b(b) {};
};

/// Polygon in a 3D space data structure.
struct Polygon3D {
    vector<Point3D> points;
    Polygon3D() {};
    explicit Polygon3D(const vector<Point3D> & points) : points(points) {};
};

/// 3D projection camera data structure.
struct Camera3D {
    Point3D c; // camera point
    Point3D o; // camera orientation angles
    Point3D e; // display surface's position relative to the camera point
    Camera3D(const Point3D & c, const Point3D & o, const Point3D & e)
        : c(c), o(o), e(e) {};
};

/**
 * Gets the distance between two 3D points.
 */
inline double Distance(const Point3D & a, const Point3D & b) {

    const double x_diff = b.x - a.x, y_diff = b.y - a.y,
          z_diff = b.z - a.z;
    return (sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff));
}

/**
 * 3D projection into a 2D point. 'a' is the 3D point to project.
 * https://en.wikipedia.org/wiki/3D_projection#Perspective_projection
 */
inline Point Projection(const Point3D & a, const Camera3D & camera) {

    const double x = a.x - camera.c.x, y = a.y - camera.c.y,
          z = a.z - camera.c.z;
    const double c_x = cos(camera.o.x), c_y = cos(camera.o.y),
          c_z = cos(camera.o.z);
    const double s_x = sin(camera.o.x), s_y = sin(camera.o.y),
          s_z = sin(camera.o.z);

    // camera transform
    Point3D d;
    d.x = c_y * (s_z * y + c_z * x) - s_y * z;
    d.y = s_x * (c_y * z + s_y * (s_z * y + c_z * x))
        + c_x * (c_z * y - s_z * x);
    d.z = c_x * (c_y * z + s_y * (s_z * y + c_z * x))
        - s_x * (c_z * y - s_z * x);

    // projection
    Point b;
    b.x = (camera.e.z / d.z) * d.x + camera.e.x;
    b.y = (camera.e.z / d.z) * d.y + camera.e.y;

    return b;
}

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
