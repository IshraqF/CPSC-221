/**
 * @file quack.h
 * Definition of the Quack class.
 *
 * You **should not** modify this file for the PA!
 *
 */
#ifndef QUACK_H
#define QUACK_H

#include <vector>
using namespace std;

/**
 * Quack class: represents a standard deque, templated to hold elements of
 * any type. **You must only use the private member vector as your
 * storage space! You cannot create new private member variables to hold
 * your objects!**  We have given you two other integers that you might
 * find useful.
 *
 * You **should not** modify this file for the PA! (We will use this
 * version of the file for the test cases.)
 *
 */
template <class T>
class Quack {
public:
    /* Constructor, initializes member variables appropriately. */
    Quack();

    /**
     * Adds the parameter object to the "right" end of the Quack.
     *
     * @note This fuction should have O(1) behavior per operation, over n operations!
     * You may trust that the vector class resizes the array appropriately
     * for additions to the structure, so no resizing is necessary for
     * function pushR.
     *
     * @param newItem object to be added to the Quack.
     */
    void pushR(T newItem);

    /**
     * Removes the object at the left of the Quack, and returns it to
     * the caller. You may assume that this function is only called
     * when the Quack is non-empty.
     *
     * To achieve amortized O(1) cost per operation, we will resize
     * the array downward at strategic points of the computation.
     * Specifically, suppose L is the index of the
     * leftmost data element in the quack.
     * If at any point the data will fit into array indices 0..L-1,
     * the array should be reinitialized to hold the data beginning
     * at index 0 and occupying the next num cells, where num is the
     * number of data elements in the structure.
     *
     * @return The item that used to be at the left of the Quack.
     */
    T popL();

    /**
     * Removes the object at the right of the Quack, and returns it to
     * the caller. You may assume that this function is only called
     * when the Quack is non-empty.
     *
     * To achieve amortized O(1) cost per operation, we will resize
     * the array downward at strategic points of the computation.
     * Specifically, suppose L is the index of the
     * leftmost data element in the quack.
     * If at any point the data will fit into array indices 0..L-1,
     * the array should be reinitialized to hold the data beginning
     * at index 0 and occupying the next num cells, where num is the
     * number of data elements in the structure.
     *
     * @return The item that used to be at the right of the Quack.
     */
    T popR();

    /**
     * Finds the object at the left of the Quack, and returns it to
     * the caller. Unlike popL(), this operation does not alter the
     * quack. You may assume that this function is only called when the
     * Quack is non-empty.
     *
     * @note This function should have O(1) behavior.
     *
     * @return The item at the left of the quack.
     */
    T peekL();

    /**
     * Finds the object at the right of the Quack, and returns it to
     * the caller. Unlike popR(), this operation does not alter the
     * quack. You may assume that this function is only called when the
     * Quack is non-empty.
     *
     * @note This function should have O(1) behavior.
     *
     * @return The item at the right of the quack.
     */
    T peekR();

    /**
     * Determines if the Quack is empty.
     *
     * @note This function should have O(1) behavior.
     *
     * @return bool which is true if the Quack is empty, false
     *	otherwise.
     */
    bool isEmpty() const;

private:
    vector<T> data; /* Store the quack data here! */
    int n1;
    int n2;
};

#include "quack.cpp"
#endif
