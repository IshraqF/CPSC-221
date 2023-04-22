/**
 * @file PNG.cpp
 * Implementation of a simple PNG class using RGBAPixels and the lodepng PNG library.
 *
 * @author CS 221: Data Structures
 */

#include "PNG.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "lodepng/lodepng.h"
using std::pair;
using std::queue;

namespace cs221util {
    void PNG::_copy(PNG const& other) {
        // Clear self
        delete[] imageData_;

        // Copy `other` to self
        width_ = other.width_;
        height_ = other.height_;
        imageData_ = new RGBAPixel[width_ * height_];
        for (unsigned i = 0; i < width_ * height_; i++) {
            imageData_[i] = other.imageData_[i];
        }
    }

    PNG::PNG() {
        width_ = 0;
        height_ = 0;
        imageData_ = nullptr;
    }

    PNG::PNG(unsigned int width, unsigned int height) {
        width_ = width;
        height_ = height;
        imageData_ = new RGBAPixel[width * height];
    }

    PNG::PNG(PNG const& other) {
        imageData_ = nullptr;
        _copy(other);
    }

    PNG::~PNG() {
        delete[] imageData_;
    }

    PNG const& PNG::operator=(PNG const& other) {
        if (this != &other) { _copy(other); }
        return *this;
    }

    bool PNG::operator==(PNG const& other) const {
        if (width_ != other.width_) { return false; }
        if (height_ != other.height_) { return false; }

        for (unsigned i = 0; i < width_ * height_; i++) {
            RGBAPixel& p1 = imageData_[i];
            RGBAPixel& p2 = other.imageData_[i];
            if (p1 != p2) { return false; }
        }

        return true;
    }

    bool PNG::operator!=(PNG const& other) const {
        return !(*this == other);
    }

    RGBAPixel* PNG::getPixel(unsigned int x, unsigned int y) {
        if (width_ == 0 || height_ == 0) {
            cerr << "ERROR: Call to cs221util::PNG::getPixel() made on an image with no pixels." << endl;
            cerr << "     : Returning nullptr." << endl;
            return nullptr;
        }

        if (x >= width_) {
            cerr << "WARNING: Call to cs221util::PNG::getPixel(" << x << "," << y << ") tries to access x=" << x
                 << ", which is outside of the image (image width: " << width_ << ")." << endl;
            cerr << "       : Truncating x to " << (width_ - 1) << endl;
            x = width_ - 1;
        }

        if (y >= height_) {
            cerr << "WARNING: Call to cs221util::PNG::getPixel(" << x << "," << y << ") tries to access y=" << y
                 << ", which is outside of the image (image height: " << height_ << ")." << endl;
            cerr << "       : Truncating y to " << (height_ - 1) << endl;
            y = height_ - 1;
        }

        unsigned index = x + (y * width_);
        return imageData_ + index;
    }

    bool PNG::readFromFile(string const& fileName) {
        vector<unsigned char> byteData;
        unsigned error = lodepng::decode(byteData, width_, height_, fileName);

        if (error) {
            cerr << "PNG decoder error " << error << ": " << lodepng_error_text(error) << endl;
            return false;
        }

        delete[] imageData_;
        imageData_ = new RGBAPixel[width_ * height_];

        for (unsigned i = 0; i < byteData.size(); i += 4) {
            RGBAPixel& pixel = imageData_[i / 4];
            pixel.r = byteData[i];
            pixel.g = byteData[i + 1];
            pixel.b = byteData[i + 2];
            pixel.a = byteData[i + 3] / 255.;
        }

        return true;
    }

    bool PNG::writeToFile(string const& fileName) {
        unsigned char* byteData = new unsigned char[width_ * height_ * 4];

        for (unsigned i = 0; i < width_ * height_; i++) {
            byteData[(i * 4)] = imageData_[i].r;
            byteData[(i * 4) + 1] = imageData_[i].g;
            byteData[(i * 4) + 2] = imageData_[i].b;
            byteData[(i * 4) + 3] = imageData_[i].a * 255;
        }

        unsigned error = lodepng::encode(fileName, byteData, width_, height_);
        if (error) {
            cerr << "PNG encoding error " << error << ": " << lodepng_error_text(error) << endl;
        }

        delete[] byteData;
        return (error == 0);
    }

    unsigned int PNG::width() const {
        return width_;
    }

    unsigned int PNG::height() const {
        return height_;
    }

    void PNG::resize(unsigned int newWidth, unsigned int newHeight) {
        // Create a new vector to store the image data for the new (resized) image
        RGBAPixel* newImageData = new RGBAPixel[newWidth * newHeight];

        // Copy the current data to the new image data, using the existing pixel
        // for coordinates within the bounds of the old image size
        for (unsigned x = 0; x < newWidth; x++) {
            for (unsigned y = 0; y < newHeight; y++) {
                if (x < width_ && y < height_) {
                    RGBAPixel* oldPixel = this->getPixel(x, y);
                    RGBAPixel& newPixel = newImageData[(x + (y * newWidth))];
                    newPixel = *oldPixel;
                }
            }
        }

        // Clear the existing image
        delete[] imageData_;

        // Update the image to reflect the new image size and data
        width_ = newWidth;
        height_ = newHeight;
        imageData_ = newImageData;
    }

    vector<pair<int, int>> PNG::drawLine(pair<int, int> p1, pair<int, int> p2, const RGBAPixel& colour) {
        vector<pair<int, int>> coords;
        int x1 = p1.first;
        int x2 = p2.first;
        int y1 = p1.second;
        int y2 = p2.second;

        // reorder so that x1 <= x2
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }

        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;
        int err = dx - dy;

        while (true) {
            // Colour the current pixel
            RGBAPixel* pixel = getPixel(x1, y1);
            *pixel = colour;
            coords.push_back({x1, y1});

            // If the end of the line has been reached, break out of the loop
            if (x1 == x2 && y1 == y2)
                break;

            int e2 = 2 * err;

            if (e2 > -dy) {
                err -= dy;
                x1 += sx;
            }

            if (e2 < dx) {
                err += dx;
                y1 += sy;
            }
        }

        return coords;
    }

    void PNG::drawHexagon(vector<pair<int, int>> points, const RGBAPixel& edgeColour, const RGBAPixel& fillColour) {
        if (points.size() != 6) {
            cerr << "ERROR: points size not equal to 6" << endl;
            return;
        }

        vector<pair<int, int>> edgePoints;

        int minX = width_;
        int minY = height_;
        int maxX = -1;
        int maxY = -1;

        for (int i = 0; i < 6; i++) {
            pair<int, int> p1 = points[i % 6];
            pair<int, int> p2 = points[(i + 1) % 6];

            // draw the edge and add the edge pixels to edgePoints
            vector<pair<int, int>> newEdgePoints = drawLine(p1, p2, edgeColour);
            edgePoints.insert(edgePoints.end(), newEdgePoints.begin(), newEdgePoints.end());

            // keep track of the min and max x y coordinates to compute the midpoint later
            minX = min(minX, min(p1.first, p2.first));
            minY = min(minY, min(p1.second, p2.second));
            maxX = max(maxX, max(p1.first, p2.first));
            maxY = max(maxY, max(p1.second, p2.second));
        }

        pair<int, int> midPoint = {(maxX + minX) / 2, (maxY + minY) / 2};
        floodFill(midPoint, fillColour, edgePoints);
    }

    void PNG::floodFill(pair<int, int> start, const RGBAPixel& fillColour, const vector<pair<int, int>>& edge_coords) {
        const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
        // set for O(log n) time checking if a pixel is an edge
        set<pair<int, int>> edgePoints(edge_coords.begin(), edge_coords.end());
        // keeps track of visited pixels
        set<pair<int, int>> visited;
        queue<pair<int, int>> q;
        visited.insert(start);
        q.push(start);

        // BFS
        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            *getPixel(curr.first, curr.second) = fillColour;

            for (auto& dir : directions) {
                pair<int, int> neigh = {curr.first + dir.first, curr.second + dir.second};

                // only explore a neighbour if it is not visited and not an edge
                if (visited.find(neigh) == visited.end() && edgePoints.find(neigh) == edgePoints.end()) {
                    visited.insert(neigh);
                    q.push(neigh);
                }
            }
        }
    }
}
