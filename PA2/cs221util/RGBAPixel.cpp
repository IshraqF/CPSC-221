/**
 * @file RGBAPixel.cpp
 * Implementation of the RGBAPixel class for use with the PNG library.
 */

#include "RGBAPixel.h"

#include <cmath>
#include <iostream>

namespace cs221util {
    bool RGBAPixel::operator==(RGBAPixel const& other) const {
        if (this->a == 0 && other.a == 0) {
            return true;
        } else {
            return (this->r == other.r &&
                    this->g == other.g &&
                    this->b == other.b &&
                    this->a == other.a);
        }
    }

    bool RGBAPixel::operator!=(RGBAPixel const& other) const {
        return !(*this == other);
    }

    RGBAPixel::RGBAPixel() {
        r = 255;
        g = 255;
        b = 255;
        a = 1.0;
    }

    RGBAPixel::RGBAPixel(int red, int green, int blue) {
        r = red;
        g = green;
        b = blue;
        a = 1.0;
    }

    RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    // From: https://en.wikipedia.org/wiki/HSL_and_HSV#Color_conversion_formulae
    void RGBAPixel::from_hsl(double h, double s, double l) {
        double c = (1 - fabs(2 * l - 1)) * s;
        double hh = h / 60;
        double x = c * (1 - fabs(fmod(hh, 2) - 1));
        double dr, dg, db;

        if (hh <= 1) {
            dr = c;
            dg = x;
            db = 0;
        } else if (hh <= 2) {
            dr = x;
            dg = c;
            db = 0;
        } else if (hh <= 3) {
            dr = 0;
            dg = c;
            db = x;
        } else if (hh <= 4) {
            dr = 0;
            dg = x;
            db = c;
        } else if (hh <= 5) {
            dr = x;
            dg = 0;
            db = c;
        } else {
            dr = c;
            dg = 0;
            db = x;
        }

        double m = l - c / 2;
        r = round((dr + m) * 255);
        g = round((dg + m) * 255);
        b = round((db + m) * 255);
    }
}
