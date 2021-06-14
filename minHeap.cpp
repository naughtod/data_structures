#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

// min heap implementation using dynamic array
class MinHeap {
public:
    MinHeap();
    void insert(int element);
    int deleteMinimum();
    int findIndex(int element);
    void changeKey(int index, int element);
    void print();
    void treePrint();
    int size();
    
private:
    vector<int> vect;
    int getParent(int index);
    int getRightChild(int index);
    int getLeftChild(int index);
    void bubbleUp(int index);
    void bubbleDown(int index);
    void swap(int i, int j);
    void checkIndex(int index);
};

// test code for min heap
int main( ) {
    MinHeap m = MinHeap();
    for (int i=9;i>=0;i--) {
        m.insert(i);
    }
    m.treePrint();
    m.deleteMinimum();
    m.treePrint();
    m.findIndex(9);
    m.changeKey(7,0);
    m.treePrint();
    
    return 0;
}

// insert an element into the heap
void MinHeap::insert(int element) {
    vect.push_back(element);
    bubbleUp(vect.size());
}

// swap child with parent if smaller, all the way up the heap
void MinHeap::bubbleUp(int index) {
    int parentIndex;

    while ((parentIndex = getParent(index)) > 0 && 
        vect[parentIndex-1] > vect[index-1]) {
        swap(parentIndex-1, index-1);
        index = parentIndex;
    }
}

// delete minimum (root)
int MinHeap::deleteMinimum() {
    int root = vect[0];
    swap(0, vect.size()-1);
    vect.pop_back();

    bubbleDown(1);
    return root;
}

// swap parent with smallest child if larger, all the way down the heap
void MinHeap::bubbleDown(int index) {
    int leftChildIndex = -1;
    int rightChildIndex = -1;
    int minChildIndex = -1;

    while (true) {
        // if right child exists
        if ((rightChildIndex = getRightChild(index)) < vect.size()) {
            minChildIndex = getLeftChild(index);

            // if right child less than left, set to min
            if (vect[minChildIndex-1] > vect[rightChildIndex-1])
                minChildIndex = rightChildIndex;

        } else if ((leftChildIndex = getLeftChild(index)) < vect.size()) {
            // only left child exists
            minChildIndex = leftChildIndex;
        } else {
            // leaf node
            break;
        }

        // if min child is less than parent, swap then iterate
        if (vect[minChildIndex-1] < vect[index-1]) {
            swap(minChildIndex-1, index-1);
            index = minChildIndex;
        } else {
            break;
        }
    }
}

// finds the given element in heap and return index, 
// if not found then returns -1
int MinHeap::findIndex(int element) {
    for (int i=0;i<vect.size();i++) {
        if (vect[i] == element) return i;
    }
    return -1;
}

// changes the key at the given index and maintains heap property
void MinHeap::changeKey(int index, int element) {
    checkIndex(index);

    // if new key is greater than old key, bubble down and vice versa
    if (vect[index] < element) {
        vect[index]=element;
        bubbleDown(index+1);
    } else if (vect[index] > element) {
        vect[index]=element;
        bubbleUp(index+1);
    }
}

// swap elements at given indexes
void MinHeap::swap(int i, int j) {
    int temp = vect[i];
    vect[i]=vect[j];
    vect[j]=temp;
}

// mapping child to parent in array representation of heap
int MinHeap::getParent(int index) {
    return index/2;
}

// mapping parent to right child in array representation of heap
int MinHeap::getRightChild(int index) {
    return 2*index+1;
}

// mapping parent to left child in array representation of heap
int MinHeap::getLeftChild(int index) {
    return 2*index;
}

// return size of heap
int MinHeap::size() {
    return vect.size();
}

// prints error message and exits if heap indexed incorrectly
void MinHeap::checkIndex(int index) {
    
    if (index<0 | index>=vect.size()) {
        cout << "invalid index - heap of size : " + to_string(vect.size()) +
            " indexed at position : " + to_string(index) + "\n";
        exit(EXIT_FAILURE);
    }
}

// prints tree left to right by level in array format
void MinHeap::print() {
    if (vect.size() > 0) {
        string output = "[" + to_string(vect[0]);

        for (int i=1;i<vect.size();i++) output += "," + to_string(vect[i]);
        output += "]\n";
        
        cout << output;
    }
}

// prints min heap in tree format
void MinHeap::treePrint() {
    // need to use consistent number of digits in representation for 
    // even padding, uses the digits of maximum key
    int digits= ceil(log10(*max_element(vect.begin(), vect.end())));
    int height = 1+log2(vect.size());
    int padding=digits;
    string output = "\n";

    // print out tree level by level
    for (int i=height;i>=0;i--) {

        for (int j=pow(2,i)-2;j>=pow(2,i-1)-1;j--) {
            if (j<vect.size()) {
                string vectStr = string(digits - to_string(vect[j]).length(),
                    '0') + to_string(vect[j]);

                if (j==pow(2,i-1)-1) {
                    vectStr = vectStr.insert(0, (padding-digits)*0.5,' ');
                } else {
                    vectStr = vectStr.insert(0, padding,' ');
                }

                output = vectStr + output;
            }
        }
        padding =2*padding+digits;
        if (i>0) output = "\n" + output;
    }
    cout << output;
} 

// no arg constructor
MinHeap::MinHeap() {}