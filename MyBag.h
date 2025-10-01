#include <iostream>
using namespace std; 

class MyBag
{
private:
	int* data;      
    int size;       
    int capacity;
public:

    MyBag() {
        capacity = 0;
        size = 0;
        data = new int[capacity];
    }

    // destructor
    ~MyBag() {
        delete[] data;
    }

    int getSize() const
    {
        return size;
    }

    int getCapacity() const 
    { 
        return capacity; 
    }

    // resize to new capacity
    void resize(int newCap) {
 
        int* newData = new int[newCap];

        // copy old values
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCap;
    }

    void insert(int value) {
        if (size == capacity) {
            resize(capacity + 1); 
        }

        data[size] = value;
        size++;
    }

    void search(int value) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                cout << "\n\tValue " << value << " found at index " << i;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "\n\tValue " << value << " not found";
        }
    }



    friend ostream& operator<<(ostream& out, const MyBag& bag) {
        if (bag.size == 0)
        {
            out << "\n\tMyBag is empty.";
        }
        else
        {
            out << "\n\tMybag contains these integers: ";
            for (int i = 0; i < bag.size; i++) {
                out << "\n\t[" << i << "] - ";
                out << bag.data[i];
                if (i < bag.size - 1) out;
            }
        }
        return out;
    }
};

