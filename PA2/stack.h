/**
 * @file stack.h
 * Definition of the Stack class.
 *
 * You **should not** modify this file for the PA!
 *
 */
#ifndef STACK_H
#define STACK_H

#include "quack.h"

/**
 * Stack class: represents a standard stack. Templated to hold elements of
 * any type. **You must only use the private member quack as your
 * storage space! You cannot create new private member variables to hold
 * your objects!** It is up to you to determine how to use it.
 *
 * Your Stack class should have O(1) running time per operation, over n operations
 * (amortized).
 *
 * You **should not** modify this file for the PA!
 *
 */
template <class T>
class Stack {
public:
    /**
     * Adds the parameter object to the top of the Stack.
     *
     * @note This function should have O(1) behavior per operation, over n operations!
     *
     * @param newItem The object to be added to the Stack.
     */
    void push(T newItem);

    /**
     * Removes the object on top of the Stack, and returns it.
     * You may assume
     * this function is only called when the Stack is not empty.
     *
     * @note This function should have O(1) behavior per operation, over n operations!
     *
     * @return The element that used to be at the top of the Stack.
     */
    T pop();

    /**
     * Finds the object on top of the Stack, and returns it to the caller.
     * Unlike pop(), this operation does not alter the Stack itself.
     * You may assume this
     * function is only called when the Stack is not empty.
     *
     * @note This function should have O(1) behavior per operation, over n operations!
     *
     * @return The element at the top of the Stack.
     */
    T peek();

    /**
     * Determines if the Stack is empty.
     *
     * @note This function should have O(1) behavior per operation, over n operations!
     *
     * @return Whether or not the stack is empty (bool).
     */
    bool isEmpty() const;

private:
    /**
     * The quack representing our Stack.
     **/
    Quack<T> myStack;
};

#include "stack.cpp"  // needed for template instantiation
#endif
