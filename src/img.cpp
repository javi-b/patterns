#include <iostream>
#include <fstream>
#include <filesystem>
#include "img.h"

/**
 * Constructor.
 * Creates the image and sets its background.
 */
Img::Img(const int width, const int height)
    : width_(width), height_(height) {

    img_ = Magick::Image(Magick::Geometry(width_, height_),
            Magick::Color(0, 0, 0, 0));
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
 * Draws line on image.
 */
void Img::DrawLine(const float start_x, const float start_y,
        const float end_x, const float end_y, const string & color) {

    img_.strokeColor(Magick::Color(color));
    img_.draw(Magick::DrawableLine(start_x, start_y, end_x, end_y));

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
