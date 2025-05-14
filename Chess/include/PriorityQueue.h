#pragma once
#include <list>
#include <stdexcept>

/**
 * @struct MyComparator
 * @brief A comparator functor that compares two objects of type T.
 *
 * This comparator is used to define the priority order of elements in the priority queue.
 * It returns a negative value if the first argument is less than the second,
 * zero if they are equal, and a positive value if the first argument is greater.
 *
 * @tparam T The type of the elements to compare.
 */
template <typename T>
struct MyComparator {
    /**
     * @brief Compares two elements.
     * @param a The first element.
     * @param b The second element.
     * @return A negative value if a < b, zero if a == b, or a positive value if a > b.
     */
    int operator()(T a, T b) const {
        return a - b;
    }
};

/**
 * @class PriorityQueue
 * @brief A priority queue implementation that stores elements in order based on priority.
 *
 * This class uses a list to store elements and a comparator to define the priority order.
 * It allows insertion of elements while maintaining order, retrieval of the highest priority
 * element, and provides methods to check the size of the queue and print the top elements.
 *
 * @tparam T The type of elements in the priority queue.
 */
template <typename T>
class PriorityQueue {
private:
    std::list<T> _data; ///< A list to store the elements in the priority queue.
    MyComparator<T> _comparator; ///< A comparator object used to compare the elements' priorities.

public:
    /**
     * @brief Inserts a new element into the priority queue.
     *
     * This method inserts the given element into the queue while maintaining the priority order.
     * The element is inserted in a way that the highest priority element is at the front of the queue.
     *
     * @param value The element to insert into the queue.
     */
    void push(T &value);

    /**
     * @brief Removes and returns the highest priority element from the queue.
     *
     * The element with the highest priority (lowest value, as defined by the comparator) is removed
     * from the front of the queue and returned.
     *
     * @return The highest priority element.
     * @throws std::out_of_range If the queue is empty when this method is called.
     */
    T poll();

    /**
     * @brief Returns the number of elements currently in the queue.
     *
     * @return The size of the queue.
     */
    int size();

    /**
     * @brief Prints the top three elements of the priority queue.
     *
     * This method prints the top three elements of the priority queue in order of priority.
     * If there are fewer than three elements, it will print all available elements.
     */
    void print();
};

template<typename T>
void PriorityQueue<T>::print() {
    int bestThree = 3;
    int count = 0;

    auto it = this->_data.rbegin(); // reverse iterator
    std::cout << "Top " << bestThree << " elements in priority queue:" << std::endl;

    for (; it != this->_data.rend() && count < bestThree; ++it, ++count) {
        std::cout << *it ;
    }

}

template<typename T>
int PriorityQueue<T>::size() {
    return this->_data.size();
}


template<typename T>
T PriorityQueue<T>::poll() {
    if (_data.empty()) {
        throw std::out_of_range("PriorityQueue is empty");
    }

    T result = _data.front();
    _data.pop_front();
    return result;
}


template<typename T>
void PriorityQueue<T>::push(T &value) {
    if (this->_data.empty()) {
        this->_data.push_back(value);
        return;
    }

    auto it = this->_data.begin();
    for (; it != this->_data.end(); ++it) {
        if (this->_comparator(value, *it) < 0) {

            this->_data.insert(it, value);
            return;
        }
    }

    this->_data.push_back(value);

}


