#ifndef COLORCONVERTER_H
#define COLORCONVERTER_H

#include <algorithm>
#include <cmath>

struct RGBColor {
    double r; // [0, 255]
    double g; // [0, 255]
    double b; // [0, 255]
};

struct CMYKColor {
    double c; // [0, 1]
    double m; // [0, 1]
    double y; // [0, 1]
    double k; // [0, 1]
};

struct HLSColor {
    double h; // [0, 360)
    double l; // [0, 1]
    double s; // [0, 1]
};

class ColorConverter {
public:
    // RGB <-> CMYK
    static CMYKColor rgbToCmyk(const RGBColor& rgb);
    static RGBColor cmykToRgb(const CMYKColor& cmyk);

    // RGB <-> HLS
    static HLSColor rgbToHls(const RGBColor& rgb);
    static RGBColor hlsToRgb(const HLSColor& hls);

private:
    static double hueToRgb(double v1, double v2, double vH);
};

#endif // COLORCONVERTER_H