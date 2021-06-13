#include <iostream>
#include <algorithm>
using namespace std;

// dynamic array implementation builds on top of static array
class DynamicArray {
public:
    DynamicArray();
    DynamicArray(int length);
    void append(int element);
    void insert(int index, int element);
    void del(int index);
    void sort_();
    void print();
    void set(int index, int element);
    int get(int index);
    int length();
    

private:
    int INIT_LENGTH=1;
    int used=0;
    int allocated=INIT_LENGTH;
    int *array = new int[INIT_LENGTH];
    void checkIndex(int index);
};

// basic test code
int main( ) {
    DynamicArray d = DynamicArray();

    d.append(1);
    d.insert(0,2);
    d.del(1);
    d.print();
    
    return 0;
}

// append element to the back of array, implements resize if needs more memory
void DynamicArray::append(int element) {

    if (used == allocated) {
        allocated *=2;
        int *newArray = new int[allocated];
        for (int i=0;i<used;i++) newArray[i]=array[i];
        
        newArray[used++] = element;

        array = newArray;
        newArray = NULL;
    } else {
        array[used++] = element;
    }   
}

// insert element at index and shuffle elements back
void DynamicArray::insert(int index, int element) {
    checkIndex(index);
    append(0);

    for (int i=used-1;i>index;i--) {
        array[i] = array[i-1];
    }
    array[index]=element;
}

// overwrites element at given index and shuffles elements forward
void DynamicArray::del(int index) {
    checkIndex(index);

    for (int i=index;i<used;i++) {
        array[i] = array[i+1];
    }

    used--;
}

// sorts the array
void DynamicArray::sort_() {
    sort(array , array+used);
}

// print array in nice format
void DynamicArray::print() {
    if (used > 0) {
        string output = "[" + to_string(get(0));

        for (int i=1;i<used;i++) output += "," + to_string(get(i));
        output += "]\n";
        
        cout << output;
    }
}

// get array value at index
int DynamicArray::get(int index) {
    checkIndex(index);
    return array[index];
}

// set array value at index
void DynamicArray::set(int index, int element) {
    checkIndex(index);
    array[index] = element;
}

// return length of array for iterating
int DynamicArray::length() {
    return used;
}

// prints error message and exits if array indexed incorrectly
void DynamicArray::checkIndex(int index) {
    
    if (index<0 | index>=used) {
        cout << "invalid index - array of size : " + to_string(used) +
            " indexed at position : " + to_string(index) + "\n";
        exit(EXIT_FAILURE);
    }
}

// no arg constructor does nothing
DynamicArray::DynamicArray() { }

// constructor sets initial size of array
DynamicArray::DynamicArray(int length) {
    INIT_LENGTH = length;
}