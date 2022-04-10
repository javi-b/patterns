#include <iostream>
#include "polytope.h"

/**
 * Polytope pattern constructor.
 */
Polytope::Polytope(const int height, const double aspect_ratio)
    : Pattern(height, aspect_ratio) {}

/**
 * Generates polytope pattern 3D polygons.
 */
void Polytope::GeneratePattern() {

    double x = -100.0, y = -100.0, z = 200.0, len = 200.0;
    x += width_ / 2.0;
    y += height_ / 2.0;

    vector<utils::Point3D> points;

    // back
    points.push_back(utils::Point3D(x, y, z + len));
    points.push_back(utils::Point3D(x + len, y, z + len));
    points.push_back(utils::Point3D(x + len, y + len, z + len));
    points.push_back(utils::Point3D(x, y + len, z + len));
    points.push_back(utils::Point3D(x, y, z + len));
    polygons_3d_.push_back(utils::Polygon3D(points));
    points.clear();

    // left
    points.push_back(utils::Point3D(x, y, z));
    points.push_back(utils::Point3D(x, y, z + len));
    points.push_back(utils::Point3D(x, y + len, z + len));
    points.push_back(utils::Point3D(x, y + len, z));
    points.push_back(utils::Point3D(x, y, z));
    polygons_3d_.push_back(utils::Polygon3D(points));
    points.clear();

    // right
    points.push_back(utils::Point3D(x + len, y, z));
    points.push_back(utils::Point3D(x + len, y, z + len));
    points.push_back(utils::Point3D(x + len, y + len, z + len));
    points.push_back(utils::Point3D(x + len, y + len, z));
    points.push_back(utils::Point3D(x + len, y, z));
    polygons_3d_.push_back(utils::Polygon3D(points));
    points.clear();

    // top
    points.push_back(utils::Point3D(x, y, z));
    points.push_back(utils::Point3D(x, y, z + len));
    points.push_back(utils::Point3D(x + len, y, z + len));
    points.push_back(utils::Point3D(x + len, y, z));
    points.push_back(utils::Point3D(x, y, z));
    polygons_3d_.push_back(utils::Polygon3D(points));
    points.clear();

    // bottom
    points.push_back(utils::Point3D(x, y + len, z));
    points.push_back(utils::Point3D(x, y + len, z + len));
    points.push_back(utils::Point3D(x + len, y + len, z + len));
    points.push_back(utils::Point3D(x + len, y + len, z));
    points.push_back(utils::Point3D(x, y + len, z));
    polygons_3d_.push_back(utils::Polygon3D(points));
    points.clear();

    // front
    points.push_back(utils::Point3D(x, y, z));
    points.push_back(utils::Point3D(x + len, y, z));
    points.push_back(utils::Point3D(x + len, y + len, z));
    points.push_back(utils::Point3D(x, y + len, z));
    points.push_back(utils::Point3D(x, y, z));
    polygons_3d_.push_back(utils::Polygon3D(points));
    points.clear();
}

/**
 * Generates pattern image.
 */
void Polytope::GenerateImg(const string & dir, const string & name) {

    // creates img
    Img img(width_, height_);

    // draws 3D polygons in img
    const auto camera = utils::Camera3D(
            utils::Point3D(width_ * 0.7, height_ * 0.3, 0.0),
            utils::Point3D(utils::Radians(0.0), utils::Radians(10.0),
                utils::Radians(10.0)),
            utils::Point3D(width_ * 0.7, height_ * 0.3, 150.0));
    img.DrawPolygons3D(polygons_3d_, camera, "black");

    // writes img to file
    img.Write(dir, name);
}

