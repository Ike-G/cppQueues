#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdexcept>
#include <vector>

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
                printf("No space to push.");
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
                printf("No value to pop"); 
                return 0;
            }
            return vals[i]; 
        };

        T operator [](int k) {
            return vals[startPtr+k]; 
        };

        int getLength() { 
            return endPtr - startPtr; 
        };

        void getPointers() { 
            printf("Start: %d, End: %d", startPtr, endPtr); 
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
        circularQueue<T>(int size) : Queue<T>(size) {
            empty = true; 
        }
        int push(T item) {
            int tPtr = (*&endPtr)++%size; 
            if (tPtr == startPtr) { // As the pointer is only incremented by 1, the only issue can occur if it collides with startPtr
                printf("No space to push"); 
                return 0; 
            }
            endPtr = tPtr;
            vals[endPtr] = item;
            empty = false; 
            return 1; 
        }

        T pop() { 
            int tPtr = (*&endPtr)++%size; 
            int tVal = vals[endPtr]; 
            if (empty) { 
                printf("Nothing to pop"); 
                return 0; 
            } else if (endPtr == startPtr) {
                empty = true; 
            }
            endPtr = tPtr; 
            return tVal;
        }

        int getLength() { 
            return 0; // Not possible to implement in O(1) time with current implementation 
        }

    protected: 
        bool empty; 
};

template <typename T> 
class priorityQueue {
    public: 
        priorityQueue(unsigned int s) {
            qs = new vector<circularQueue<T>>(); 
            size = s; 
        };

        int push(T item, int priority) { 
            int sumSize = 0; 
            for (auto i = qs.begin(); i != qs.end(); ++i) {
                sumSize += 
            }
        }

    private: 
        vector<circularQueue<T>> qs; 
        int size; 
}

int main() {
//    char* ti;
//    ti = (char*)malloc(5);  
//    ti[3] = 5; 
//    for (int i = 0; i < 5; i++) {
//        printf("%d\n", (int)*(ti+i));
//        if (ti+i == nullptr) {
//            
//        }
//    }
    Queue<int> q(10); 
    for (int i = 0; i < 11; i++) {
        q.push((int)pow((double)i,(double)2)); 
    }
    printf("\n");
    for (int i = 0; i < 11; i++) {
        printf("Pop result: %d\n", q.pop());
        q.getPointers(); 
        printf("Length: %d\n", q.getLength());
    }
    printf("\n");
    printf("%d\n", q.push(90));
    for (int i = 0; i < q.getLength(); i++) {
        printf("%d\n", q[i]);
    }
    q.getPointers(); 
    printf("Program functions");
    return 0;
};
