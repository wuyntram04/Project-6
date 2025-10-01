#include <iostream>
using namespace std;

class MyBag
{
private:
    int* data;
    int size;
    int capacity;
public:

    // Precondition: none.
    // Postcondition: creates an empty bag with capacity 0 and size 0.
    MyBag()
    {
        capacity = 0;
        size = 0;
        data = new int[capacity];
    }

    // destructor
    // Precondition: none.
    // Postcondition: releases all allocated memory.
    ~MyBag() {
        delete[] data;
    }

    // Precondition: none.
    // Postcondition: returns the current number of elements.
    int getSize() const
    {
        return size;
    }

    // Precondition: none.
    // Postcondition: returns the current capacity.
    int getCapacity() const
    {
        return capacity;
    }
    
    // Precondition: none.
    // Postcondition: returns true if bag has no elements, false otherwise.
    bool isEmpty() const
    {
        return size == 0;
    }

    // Precondition: newCap >= size (to preserve existing elements).
    // Postcondition: capacity is changed to newCap and existing elements are preserved.
    void resize(int newCap) 
    {

        int* newData = new int[newCap];

        // copy old values
        for (int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCap;
    }

    // Precondition: none.
    // Postcondition: value added at the end; size increased by 1 (resized if needed).
    void insert(int value)
    {
        if (size == capacity)
        {
            resize(capacity + 1);
        }

        data[size] = value;
        size++;
    }

    // Precondition: none (bag may be empty).
    // Postcondition: prints message indicating whether the value was found; bag unchanged.
    void search(int value)
    {
        bool found = false;
        for (int i = 0; i < size; i++)
        {
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

    // Precondition: index >= 0 and index < size.
    // Postcondition: element at index removed; subsequent elements shifted left; size decreased by 1.
    void remove(int index)
    {
        if (index < 0 || index >= size) 
        {
            cout << "\n\tInvalid index. Please enter an index between 0 and " << size - 1 << ".";
            return;
        }

        int deletedValue = data[index];

        // shift elements left
        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
           
        }

        cout << "\n\t\tValue " << deletedValue << " has been deleted from MyBag.";

        size--;
        
    }

    // Precondition: none.
   // Postcondition: bag is emptied; size = 0; capacity = 0.
    void clear()
    {
        delete[] data;
        capacity = 0;
        size = 0;
        data = new int[capacity];
    }

    // Precondition: elements must support operator> for comparison.
    // Postcondition: bag elements sorted in ascending order.
    void sortAscending()
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - i - 1; j++)
            {
                if (data[j] > data[j + 1])
                {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
        cout << "\n\t\tMybag has been sorted.";
    }

    // Precondition: none.
    // Postcondition: outputs the bag contents to the given stream.
    friend ostream& operator<<(ostream& out, const MyBag& bag)
    {
        if (bag.size == 0)
        {
            out << "\n\t\tMyBag is empty.";
        }
        else
        {
            out << "\n\tMybag contains these integers: \n";
            for (int i = 0; i < bag.size; i++) {
                out << "\n\t[" << i << "] - ";
                out << bag.data[i];
                if (i < bag.size - 1) out;
            }
        }
        return out;
    }
};
