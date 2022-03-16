#pragma once

#include <Magick++.h>
#include "utils.h"
using namespace std;

/**
 * Image class.
 */
class Img {
public:
    /// Embellished Points config data structure.
    struct EmbellishedPointsCfg {
        /// Heading types enumeration.
        enum Heading {
            kHeadingNatural,
            kHeadingSin, kHeadingStrongSin, kHeadingChaosSin,
            kHeadingNaturalSin, kHeadingNaturalStrongSin,
            kHeadingNaturalChaosSin
        };

        double angle_offset; ///< Angle offset from heading to arcs.
        double curvature; ///< Arcs curvature.
        double length; ///< Arcs length.
        bool symmetric; ///< Whether if 2 arcs are symmetric.
        Heading heading; ///< Heading type.

        // constructor
        EmbellishedPointsCfg(const double angle_offset,
                const double curvature, const double length,
                const bool symmetric, const Heading heading);
    };

    // constructors
    Img(const int width, const int height);
    Img(const int width, const int height, const string & color);

    // public functions

    void DrawMatrixBW(double * matrix, const bool inverse);

    void DrawPoints(const vector<utils::Point> & points,
            const string & color);
    void DrawEmbellishedPoints(const vector<utils::Point> & points,
            const string & color, const EmbellishedPointsCfg & cfg);

    void DrawLine(const float start_x, const float start_y,
            const float end_x, const float end_y, const string & color);

    void Normalize();
    void Blur(const double radius = 1.0, const double sigma = 0.5);

    void Write(const string & dir, const string & name);

private:
    Magick::Image img_ = NULL; ///< Magick++ Image object.
    int width_, height_; // Image width and height sizes.
};
