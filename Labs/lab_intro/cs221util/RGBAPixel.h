/**
 * @file RGBAPixel.h
 *
 * @author Farhan Ishraq
 */

#ifndef CS221UTIL_RGBAPixel_H
#define CS221UTIL_RGBAPixel_H

using namespace std;

namespace cs221util {
    class RGBAPixel {
    public:

        unsigned char r;
        unsigned char g;
        unsigned char b;
        double a;

        /*
        * sets defaul pixel to white
        */
        RGBAPixel();

        /*
        * Creates a new pixel of the specified rgb level
        * @param r level of color red
        * @param g level of color green
        * @param b level of color blue
        */
        RGBAPixel(unsigned char r, unsigned char g, unsigned char b);

        /*
        * Creates a new pixel of the specified rgb level
        * @param r level of color red
        * @param g level of color green
        * @param b level of color blue
        * @param a transparency value
        */
        RGBAPixel(unsigned char r, unsigned char g, unsigned char b, double alpha);
    };
}

#endif