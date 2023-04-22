/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template <class T>
void Queue<T>::enqueue(T newItem) {
    /**
     * @todo Your code here!
     */
    myQueue.pushR(newItem);
}

/**
 * Removes the object at the front of the Queue, and returns it.
 * You may assume this function
 * is only called when the Queue is not empty.
 *
 * @note This function must be O(1)!
 *
 * @return The element that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::dequeue() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */

    return myQueue.popL();
}

/**
 * Finds the object at the front of the Queue, and returns it to the caller.
 * Unlike dequeue(), this operation does not alter the Queue itself.
 * You may assume this function is only
 * called when the Queue is not empty.
 *
 * @return The value of the element at the front of the Queue.
 */
template <class T>
T Queue<T>::peek() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return myQueue.peekL();
}

/**
 * Determines if the Queue is empty.
 *
 * @return Whether or not the queue is empty (bool).
 */
template <class T>
bool Queue<T>::isEmpty() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return myQueue.isEmpty();
}
