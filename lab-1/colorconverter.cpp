#include "colorconverter.h"

// RGB -> CMYK
CMYKColor ColorConverter::rgbToCmyk(const RGBColor& rgb) {
    double r_norm = rgb.r / 255.0;
    double g_norm = rgb.g / 255.0;
    double b_norm = rgb.b / 255.0;

    double k = 1.0 - std::max({r_norm, g_norm, b_norm});
    if (std::abs(k - 1.0) < 1e-6) {
        return {0.0, 0.0, 0.0, 1.0};
    }

    double c = (1.0 - r_norm - k) / (1.0 - k);
    double m = (1.0 - g_norm - k) / (1.0 - k);
    double y = (1.0 - b_norm - k) / (1.0 - k);

    return {c, m, y, k};
}

// CMYK -> RGB
RGBColor ColorConverter::cmykToRgb(const CMYKColor& cmyk) {
    double r = 255.0 * (1.0 - cmyk.c) * (1.0 - cmyk.k);
    double g = 255.0 * (1.0 - cmyk.m) * (1.0 - cmyk.k);
    double b = 255.0 * (1.0 - cmyk.y) * (1.0 - cmyk.k);

    return {r, g, b};
}

// RGB -> HLS
HLSColor ColorConverter::rgbToHls(const RGBColor& rgb) {
    double r = rgb.r / 255.0;
    double g = rgb.g / 255.0;
    double b = rgb.b / 255.0;

    double maxVal = std::max({r, g, b});
    double minVal = std::min({r, g, b});
    double delta = maxVal - minVal;

    double h = 0.0;
    double l = (maxVal + minVal) / 2.0;
    double s = 0.0;

    if (delta > 1e-6) {
        if (l < 0.5) {
            s = delta / (maxVal + minVal);
        } else {
            s = delta / (2.0 - maxVal - minVal);
        }

        if (std::abs(r - maxVal) < 1e-6) {
            h = (g - b) / delta + (g < b ? 6.0 : 0.0);
        } else if (std::abs(g - maxVal) < 1e-6) {
            h = (b - r) / delta + 2.0;
        } else {
            h = (r - g) / delta + 4.0;
        }
        h *= 60.0;
    }

    return {h, l, s};
}

// HLS -> RGB
double ColorConverter::hueToRgb(double v1, double v2, double vH) {
    if (vH < 0.0) vH += 1.0;
    if (vH > 1.0) vH -= 1.0;
    if ((6.0 * vH) < 1.0) return v1 + (v2 - v1) * 6.0 * vH;
    if ((2.0 * vH) < 1.0) return v2;
    if ((3.0 * vH) < 2.0) return v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;
    return v1;
}

RGBColor ColorConverter::hlsToRgb(const HLSColor& hls) {
    double r, g, b;

    if (hls.s < 1e-6) {
        r = g = b = hls.l * 255.0;
    } else {
        double v2 = (hls.l < 0.5) ? (hls.l * (1.0 + hls.s)) : ((hls.l + hls.s) - (hls.l * hls.s));
        double v1 = 2.0 * hls.l - v2;
        double hNorm = hls.h / 360.0;

        r = 255.0 * hueToRgb(v1, v2, hNorm + (1.0 / 3.0));
        g = 255.0 * hueToRgb(v1, v2, hNorm);
        b = 255.0 * hueToRgb(v1, v2, hNorm - (1.0 / 3.0));
    }

    return {r, g, b};
}