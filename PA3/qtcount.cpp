#include "qtcount.h"

bool qtcount::prunable(Node* node, const int tol) const {
    /* Your code here */
    if (isLeaf(node)) {
        return true;
    }
    else {
        return checkTol(node, node->avg, tol);
    }
}

bool qtcount::isLeaf(Node* node) const {
    return node->NW == NULL && node->NE == NULL && node->SW == NULL & node->SE == NULL;
}

bool qtcount::checkTol(Node* node, RGBAPixel &avg, const int tol) const {
    if (isLeaf(node)) {
        return pow((node->avg.r - avg.r), 2) + pow((node->avg.g - avg.g), 2) + pow((node->avg.b - avg.b), 2) <= tol;
    }
    else {
        return checkTol(node->NW, avg, tol) && checkTol(node->NE, avg, tol) && checkTol(node->SW, avg, tol) && checkTol(node->SE, avg, tol);
    }
}