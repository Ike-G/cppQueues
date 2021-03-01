#include <stdio.h>
#include <math.h>
#include <list> 
#include <stdlib.h>
#include <stdexcept>
#include <vector>
#include <string>

template <typename T> 
struct QueueData {
    T* vals; 
    int startPtr; 
    int endPtr; 
    unsigned int length; 
    unsigned int size; 
};

template <typename T> 
class Queue { 

    public: 
        Queue<T>(unsigned int s) { 
            size = s;
            vals = new T[size]; 
            startPtr = 0; 
            endPtr = -1; 
        };

        int push(T item) {
            endPtr++; 
            if (size <= endPtr) { // Increment the end pointer while comparing it to the array size. 
                endPtr--; 
                printf("No space to push.\n");
                return 0;
            }
            vals[endPtr] = item; // If there is space, place the item at the end pointer. 
            return 1; 
        };

        T pop() {
            int i = startPtr; 
            startPtr++; 
            if (i > endPtr) { 
                startPtr--; 
                printf("No value to pop\n"); 
                return 0;
            }
            return vals[i]; 
        };

        T operator [](int k) {
            return vals[startPtr+k]; 
        };

        int getLength() { 
            return endPtr - startPtr + 1; 
        };

        void getPointers() { 
            printf("Start: %d, End: %d", startPtr, endPtr); 
        }

        bool isEmpty() { 
            return (this->getLength() == 0);
        }

        bool isFull() {
            return (this->getLength() == size);
        }

        QueueData<T> display() {
            QueueData<T> output; 
            T* conciseArray = new T[getLength()]; 
            for (int i = 0; i < getLength(); i++) {
                conciseArray[i] = vals[startPtr+i]; 
            }
            output.vals = conciseArray; 
            output.startPtr = startPtr; 
            output.endPtr = endPtr; 
            output.length = getLength(); 
            output.size = size; 
            return output; 
        }

    protected: 
        int startPtr;
        int endPtr;
        unsigned int size; 
        T* vals; 

};

template <typename T>
class circularQueue : public Queue<T> { 
    public: 
        circularQueue<T>(int s) : Queue<T>(s) {
            length = 0; 
            size = s;
            vals = new T[s]; 
            startPtr = 0; 
            endPtr = -1; 
        }

        int push(T item) {
            if (length == size) { 
                printf("No space to push\n"); 
                return 0; 
            }
            endPtr = (endPtr+1)%size; 
            vals[endPtr] = item;
            length++; 
            return 1; 
        }

        T pop() { 
            int tPtr = (startPtr+1)%size; // First: 1, Second: 2 
            int tVal = vals[startPtr]; 
            if (length == 0) { 
                printf("Nothing to pop\n"); 
                return 0; 
            }
            startPtr = tPtr; 
            length--; 
            return tVal;
        }

        int getLength() { 
            return length; 
        }
        
        T operator [](int k) {
            return vals[(startPtr+k)%size]; 
        };


        QueueData<T> display() {
            QueueData<T> output; 
            T* conciseArray = new T[getLength()]; 
            for (int i = 0; i < getLength(); i++) {
                conciseArray[i] = vals[(startPtr+i)%size]; 
            }
            output.vals = conciseArray; 
            output.startPtr = startPtr; 
            output.endPtr = endPtr; 
            output.length = getLength(); 
            output.size = size;
            return output; 
        }

    protected: 
        unsigned int length; 
        int startPtr;
        int endPtr;
        unsigned int size; 
        T* vals; 
};

// Not implemented due to lack of time
// If it was implemented I would use the following method: 
//     Use a vector of vectors (linked lists) 
//     To push to the queue use a priority integer, extend the outer vector to contain the maximum 
//     priority integer thus far entered
//
//     Push value to the end of selected inner vector corresponding to priority 
//
//     To pop from the queue simply take the first value
//
//template <typename T> 
//class priorityQueue {
//    public: 
//        priorityQueue(unsigned int s) {
//            size = s; 
//        }
//
//        int push(T item, int priority) { 
//            
//        } 
//            
//    private: 
//        std::vector<std::vector<T>> qs; 
//        int size; 
//};

void displayIntQueue(QueueData<int> qd) {
    for (int i = 0; i < qd.length; i++) {
        printf("Position %d: %d\n", i, qd.vals[i]); 
    }
    printf("Length: %d\n", qd.length); 
    printf("Max size: %d\n", qd.size); 
    printf("Start Pointer: %d\n", qd.startPtr); 
    printf("End Pointer: %d\n", qd.endPtr); 
}

bool testQueue() { 
    Queue<int> q(10); 
    for (int i = 0; i < 11; i++) {
        q.push((int)pow((double)i, double(2))); // Expectation: Last value exceeds queue size
    }
    printf("Popped: %d\n", q.pop()); 
    printf("Popped: %d\n", q.pop()); 
    displayIntQueue(q.display()); 
    int* oVals = q.display().vals; 
    int* expectation = new int[8] {4, 9, 16, 25, 36, 49, 64, 81}; 
    for (int i = 0; i < 8; i++) {
        if (oVals[i] != expectation[i]) 
            return false; 
    }
    return true; 
}

bool testCircularQueue() { 
    circularQueue<int> q(3); 
    for (int i = 0; i < 4; i++) {
        q.push(2*i); // Expectation: Queue is [0, 2, 4]
    }
    printf("Popped: %d\n", q.pop()); 
    int so = q.pop(); 
    printf("Popped: %d\n", so); 
    if (so != 2) 
        return false; 
    q.push(6); 
    q.push(7); // Expectation: Queue is [4, 6, 7]
    displayIntQueue(q.display());
    int* oVals = q.display().vals; 
    int* expectation = new int[3] {4, 6, 7}; 
    for (int i = 0; i < 3; i++) {
        printf("Returned %d: %d, Expectation: %d\n", i, oVals[i], expectation[i]);
        if (oVals[i] != expectation[i]) 
            return false; 
    }
    return true; 
}

int main() {
    bool cQf, qf; 
    cQf = testCircularQueue(); 
    qf = testQueue(); 
    if (cQf && qf) 
        printf("Both queues function."); 
    else 
        printf("Failure.");
    return 0;
};
