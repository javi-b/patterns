#include <iostream>
#include <fstream>
#include <filesystem>
#include <climits>
#include "img.h"

/**
 * Embellished Points config data structure constructor.
 */
Img::EmbellishedPointsCfg::EmbellishedPointsCfg(const double angle_offset,
        const double curvature, const double length, const bool symmetric,
        const Heading heading)
    : angle_offset(angle_offset), curvature(curvature), length(length),
        symmetric(symmetric), heading(heading) {}

/**
 * Constructor.
 * Creates the image and sets a transparent background.
 */
Img::Img(const int width, const int height)
    : width_(width), height_(height) {

    img_ = Magick::Image(Magick::Geometry(width_, height_),
            Magick::Color(0, 0, 0, 0));
}

/**
 * Constructor.
 * Creates the image and sets a specific color background.
 */
Img::Img(const int width, const int height, const string & color)
    : width_(width), height_(height) {

    img_ = Magick::Image(Magick::Geometry(width_, height_),
            Magick::Color(color));
}

/**
 * Draws matrix of values from 0.0 to 1.0 as black and white pixels.
 */
void Img::DrawMatrixBW(double * matrix, const bool inverse) {

    cout << "Drawing matrix to image..." << endl;

    img_.modifyImage();
    img_.type(Magick::TrueColorType);
    Magick::Quantum * pixels = img_.getPixels(0, 0, width_, height_);
    for (int i = 0; i < width_; i++) {
        for (int j = 0; j < height_; j++) {
            // this is not intuitive but it must be this way
            const auto value = (inverse)
                ? 1.0 - matrix[j + i * height_] : matrix[j + i * height_];
            const auto color = Magick::ColorGray(value);
            *pixels++ = color.quantumRed();
            *pixels++ = color.quantumGreen();
            *pixels++ = color.quantumBlue();
        }
    }
    img_.syncPixels();
}

/**
 * Draws collection of points to image.
 */
void Img::DrawPoints(const vector<utils::Point> & points,
        const string & color) {

    cout << "Drawing " << points.size() << " points to image..." << endl;

    vector<Magick::Drawable> draw_list;

    img_.strokeColor(Magick::Color(color));
    for (const auto & p : points)
        draw_list.push_back(Magick::DrawablePoint(p.x, p.y));

    img_.draw(draw_list);
}

/**
 * Draws collection of points to image. However, it draws them embellished.
 * For each point it draws two arcs following the config parametres.
 */
void Img::DrawEmbellishedPoints(const vector<utils::Point> & points,
        const string & color, const EmbellishedPointsCfg & cfg) {

    cout << "Drawing " << points.size()
            << " embellished points to image..." << endl;

    img_.strokeWidth(0.5);
    img_.strokeColor(Magick::Color(color));
    img_.fillColor(Magick::Color(0, 0, 0, 0));

    vector<Magick::VPath> path;

    for (int i = 1; i < int(points.size()); i++) {

        // calculates arcs angles
        double heading_angle = 0.0;
        switch (cfg.heading) {
        case EmbellishedPointsCfg::kHeadingNatural:
            heading_angle =
                utils::Degrees(atan2(points[i].y - points[i - 1].y,
                            points[i].x - points[i - 1].x));
              break;
        case EmbellishedPointsCfg::kHeadingSin:
            heading_angle = 360 * abs(sin(i));
            break;
        case EmbellishedPointsCfg::kHeadingStrongSin:
            heading_angle = 360 * abs(sin(i * 2));
            break;
        case EmbellishedPointsCfg::kHeadingChaosSin:
            heading_angle = 360 * abs(sin(i * 10));
            break;
        case EmbellishedPointsCfg::kHeadingNaturalSin:
            heading_angle = 360 * abs(sin(i))
                - utils::Degrees(atan2(points[i].y - points[i - 1].y,
                            points[i].x - points[i - 1].x));
            break;
        case EmbellishedPointsCfg::kHeadingNaturalStrongSin:
            heading_angle = 360 * abs(sin(i * 2))
                - utils::Degrees(atan2(points[i].y - points[i - 1].y,
                            points[i].x - points[i - 1].x));
            break;
        case EmbellishedPointsCfg::kHeadingNaturalChaosSin:
            heading_angle = 360 * abs(sin(i * 10))
                - utils::Degrees(atan2(points[i].y - points[i - 1].y,
                            points[i].x - points[i - 1].x));
            break;
        }
        const double arc_a_angle =
            utils::Radians(heading_angle + cfg.angle_offset);
        const double arc_b_angle =
            utils::Radians(heading_angle - cfg.angle_offset);

        // calculates arcs end points
        const utils::Point end_point_a(cfg.length * cos(arc_a_angle),
                cfg.length * sin(arc_a_angle)),
            end_point_b(cfg.length * cos(arc_b_angle),
                cfg.length * sin(arc_b_angle));

        // calculates arcs control points
        const utils::Point control_point_a(
                end_point_a.x / 2.0 + cfg.length * cfg.curvature
                    * cos(arc_a_angle - M_PI / 2.0),
                end_point_a.y / 2.0 + cfg.length * cfg.curvature
                    * sin(arc_a_angle - M_PI / 2.0));
        const utils::Point control_point_b(
                end_point_b.x / 2.0 + cfg.length * cfg.curvature
                    * cos(arc_b_angle
                        + ((cfg.symmetric) ? M_PI : -M_PI) / 2.0),
                end_point_b.y / 2.0 + cfg.length * cfg.curvature
                    * sin(arc_b_angle
                        + ((cfg.symmetric) ? M_PI : -M_PI) / 2.0));

        // adds arc a to path
        path.push_back(Magick::PathMovetoAbs(
                    Magick::Coordinate(points[i].x, points[i].y)));
        path.push_back(Magick::PathQuadraticCurvetoRel(
                    Magick::PathQuadraticCurvetoArgs(control_point_a.x,
                        control_point_a.y, end_point_a.x, end_point_a.y)));

        // adds arc b to path
        path.push_back(Magick::PathMovetoAbs(
                    Magick::Coordinate(points[i].x, points[i].y)));
        path.push_back(Magick::PathQuadraticCurvetoRel(
                    Magick::PathQuadraticCurvetoArgs(control_point_b.x,
                        control_point_b.y, end_point_b.x, end_point_b.y)));
    }

    img_.draw(Magick::DrawablePath(path));
}

/**
 * Draws line on image.
 */
void Img::DrawLine(const float start_x, const float start_y,
        const float end_x, const float end_y, const string & color) {

    img_.strokeColor(Magick::Color(color));
    img_.draw(Magick::DrawableLine(start_x, start_y, end_x, end_y));
}

/**
 * Draw collection of Polygons in a 3D space.
 */
void Img::DrawPolygons3D(const vector<utils::Polygon3D> & polygons,
        const utils::Camera3D & camera, const string & color) {

    img_.strokeWidth(0.5);
    img_.strokeColor(Magick::Color(color));

    for (const auto & polygon : polygons) {

        vector<Magick::Coordinate> coordinates;

        for (const auto & point_3d : polygon.points) {

            const auto point = Projection(point_3d, camera);
            coordinates.push_back(Magick::Coordinate(point.x, point.y));
        }

        const int r = rand();
        img_.fillColor(Magick::Color((r % 100) / 100.0 * USHRT_MAX,
                    ((r + 33) % 100) / 100.0 * USHRT_MAX,
                    ((r + 66) % 100) / 100.0 * USHRT_MAX, 0.1 * USHRT_MAX));
        img_.draw(Magick::DrawablePolygon(coordinates));
    }
}

/**
 * Applies normalization filter on image.
 */
void Img::Normalize() {

    img_.normalize();
}

/**
 * Applies blur filter on image.
 */
void Img::Blur(const double radius, const double sigma) {

    img_.blur(radius, sigma);
}

/**
 * Writes image to file.
 */
void Img::Write(const string & dir, const string & name) {

    // if the directory doesn't exist yet creates it
    if (!(filesystem::exists(dir) && filesystem::is_directory(dir)))
        filesystem::create_directories(dir);

    const string path = dir + "/" + name;

    cout << "Writting image to '" << path << "'..." << endl;

    ofstream file(path, ios::trunc); // creates or truncates file
    if (file.is_open()) {
        file.close(); // closes file
        img_.write(path); // writes img to file
    } else {
        cerr << "Error: could not open " << path << endl;
    }
}
