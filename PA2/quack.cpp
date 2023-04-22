/**
 * @file quack.cpp
 * Implementation of the Quack class.
 *
 */

template <class T>
Quack<T>::Quack() {
    /**
     * @todo Your code here!
     */
     n1=-1;
     n2=0;
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */
template <class T>
void Quack<T>::pushR(T newItem) {
    /**
     * @todo Your code here!
     */
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */
template <class T>
T Quack<T>::popL() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */

    if (this->isEmpty()) {
        throw std::out_of_range("Quack is empty");
    }

    T retItem=data[++n1];

    
    if((n2-n1-2)<=n1){
        vector<T> smallData;
        for(int i=n1+1;i<n2;i++){
            smallData.push_back(data[i]);
        }
        data=smallData;
        n1=-1;
        n2=smallData.size();
    }

    return retItem;
}
/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::popR() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (this->isEmpty()) {
        throw std::out_of_range("Quack is empty");
    }

    T retItem=data.back();
    n2--;
    data.pop_back();

    if((n2-n1-2)<=n1){
        vector<T> smallData;
        for(int i=n1+1;i<n2;i++){
            smallData.push_back(data[i]);
        }
        data=smallData;
        n1=-1;
        n2=smallData.size();
    }
    
    return retItem;
}

/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike popL(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (this->isEmpty()) {
        throw std::out_of_range("Quack is empty");
    }
    return data[n1+1];
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike popR(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR() {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (this->isEmpty()) {
        throw std::out_of_range("Quack is empty");
    }
    return data[n2-1];
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::isEmpty() const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    return (n2==(n1+1));
}
