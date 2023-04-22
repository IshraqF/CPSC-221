/**
 * @file RGBAPixel.cpp
 * Implementation of a simple RGBAPixel class
 *
 * @author Farhan Ishraq
 */

#include <iostream>
#include <string>
#include <algorithm>
#include "RGBAPixel.h"

namespace cs221util {
    RGBAPixel::RGBAPixel() : r(255), g(255), b(255), a(1.0) {}

    RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b), a(1.0) {}

    RGBAPixel::RGBAPixel(unsigned char r, unsigned char g, unsigned char b, double a) : r(r), g(g), b(b), a(a) {}
}
