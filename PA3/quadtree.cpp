
/**
 *
 * quadtree (pa3)
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
using namespace std;

// Node constructor, given.
quadtree::Node::Node(pair<int, int> ul, int d, RGBAPixel a, double v)
    : upLeft(ul), dim(d), avg(a), var(v), NW(nullptr), NE(nullptr), SE(nullptr), SW(nullptr) {}

// quadtree destructor, given.
quadtree::~quadtree() {
    clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree& other) {
    copy(other);
}
// quadtree assignment operator, given.
quadtree& quadtree::operator=(const quadtree& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

quadtree::quadtree(PNG& imIn) {
    int width = imIn.width();
    int height = imIn.height();

    stats s(imIn);
    this->edge = width;
    int k = std::floor(std::log2(width));

    if (width != height) {
        k = std::floor(std::log2(std::min(width, height)));
        this->edge = std::pow(2, k);
    } 

    root = buildTree(s, make_pair(0, 0), k);
}

quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    Node* node = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));

    if (dim > 0) {
        int new_dim = dim-1; // since children have one dimension less
        int shift = std::pow(2, dim)/2; // ul shift for children

        // recursively buld NW
        pair<int, int> NW_ul = ul; // (x, y)
        int NW_dim = new_dim;
        node->NW = buildTree(s, NW_ul, NW_dim);

        // recursively build NE
        pair<int, int>NE_ul = make_pair(ul.first+shift, ul.second); // (x+shift, y)
        int NE_dim = new_dim;
        node->NE = buildTree(s, NE_ul, NE_dim);

        // recursively build SW
        pair<int, int>SW_ul = make_pair(ul.first, ul.second+shift); // (x, y+shift)
        int SW_dim = new_dim;
        node->SW = buildTree(s, SW_ul, SW_dim);

        // recursively build SE
        pair<int, int>SE_ul = make_pair(ul.first+shift, ul.second+shift); // (x+shift, y+shift)
        int SE_dim = new_dim;
        node->SE = buildTree(s, SE_ul, SE_dim);
    }

    return node;
}

PNG quadtree::render() const {
    PNG image(edge, edge);
    renderRecursive(image, root);
    return image;
}

int quadtree::idealPrune(const int leaves) const {
    int tol = 1;
	while (pruneSize(tol) > leaves) {
		tol *= 2;
	} 
 
    return minTolerance(leaves, tol / 2, tol);
}

int quadtree::minTolerance(const int leaves, int min, int max) const {
    if (min >= max) return min;
    int mid = (min + max) / 2;
	//if (pruneSize(mid) == leaves) return mid;
	if (pruneSize(mid) > leaves) {
		return minTolerance(leaves, mid + 1, max);
	}
	return minTolerance(leaves, min, mid);
}

int quadtree::pruneSize(const int tol) const {
    queue<Node*> nodeQueue;
    queue<Node*> leaves;
    Node * currNode;
    if(!root) return 0;
    nodeQueue.push(root);
    while(!nodeQueue.empty()){
        if(nodeQueue.front()){
            currNode=nodeQueue.front();
            if(prunable(currNode,tol)){
                leaves.push(currNode);        
            } else{
                nodeQueue.push(currNode->NW);
                nodeQueue.push(currNode->NE);
                nodeQueue.push(currNode->SW);
                nodeQueue.push(currNode->SE);
            }
        }
        nodeQueue.pop();
    }
    return leaves.size();
}

void quadtree::prune(const int tol) {
    queue<Node*> nodeQueue;
    Node * currNode;
    nodeQueue.push(root);
    while(!nodeQueue.empty()){
        currNode=nodeQueue.front();
        nodeQueue.pop();
        if(prunable(currNode,tol)){
            removeSubtree(currNode);
        } else{
            nodeQueue.push(currNode->NW);
            nodeQueue.push(currNode->NE);
            nodeQueue.push(currNode->SW);
            nodeQueue.push(currNode->SE);
        }
    }
}

void quadtree::removeSubtree(Node * node){
    clearRecursive(node->SW);
    clearRecursive(node->SE);
    clearRecursive(node->NW);
    clearRecursive(node->NE);
}

void quadtree::clear() {
    clearRecursive(root);
}

void quadtree::copy(const quadtree& orig) {
    if (orig.root == NULL) {
        return;
    }

    root = new Node(orig.root->upLeft, orig.root->dim, orig.root->avg, orig.root->var);
    this->edge = pow(2, orig.root->dim);
    copyRecursive(&root, orig.root);
}

void quadtree::clearRecursive(Node* & curr) {
    if (curr == NULL) {
        return;
    }

    clearRecursive(curr->NW);
    clearRecursive(curr->NE);
    clearRecursive(curr->SW);
    clearRecursive(curr->SE);

    delete(curr);
    curr = NULL;
}

void quadtree::copyRecursive(Node** curr, const Node* other) {
    if (other->NW == nullptr) {
        return;
    }

    (*curr)->NW = new Node(other->NW->upLeft, other->NW->dim, other->NW->avg, other->NW->var);
    (*curr)->NE = new Node(other->NE->upLeft, other->NE->dim, other->NE->avg, other->NE->var);
    (*curr)->SW = new Node(other->SW->upLeft, other->SW->dim, other->SW->avg, other->SW->var);
    (*curr)->SE = new Node(other->SE->upLeft, other->SE->dim, other->SE->avg, other->SE->var);

    copyRecursive(&((*curr)->NW), other->NW);
    copyRecursive(&((*curr)->NE), other->NE);
    copyRecursive(&((*curr)->SW), other->SW);
    copyRecursive(&((*curr)->SE), other->SE);
}

void quadtree::renderRecursive(PNG &image, Node* node) const {
    if (!node) {
        return;
    }

    if (isLeaf(node)) {
        int x = node->upLeft.first;
        int y = node->upLeft.second;
        int dim = node->dim;
        RGBAPixel color = node->avg;

        for (int i = x; i < x + std::pow(2, dim); i++) {
            for (int j = y; j < y + std::pow(2, dim); j++) {
                RGBAPixel* pixel = image.getPixel(i, j);
                pixel->r = color.r;
                pixel->g = color.g;
                pixel->b = color.b;
            }
        }
    }
    else {
        renderRecursive(image, node->NW);
        renderRecursive(image, node->NE);
        renderRecursive(image, node->SW);
        renderRecursive(image, node->SE);
    }
}

bool quadtree::isLeaf(Node* node) const {
    return node->NW == NULL && node->NE == NULL && node->SW == NULL & node->SE == NULL;
}
