#pragma once
#include <iostream>
using namespace std;


namespace nonTemplate
{
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
            // If array is full, grow it
            if (size == capacity)
            {
                int newCap;
                if (capacity == 0) {
                    newCap = 1;          // start with 1 if nothing yet
                }
                else {
                    newCap = capacity * 2;  // double each time
                }

                resize(newCap);
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
                    cout << "\n\t\tValue " << value << " found at index " << i;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\n\t\tValue " << value << " not found";
            }
        }

        // Precondition: index >= 0 and index < size.
        // Postcondition: element at index removed; subsequent elements shifted left; size decreased by 1.
        void remove(int index)
        {
            if (index < 0 || index >= size)
            {
                cout << "\n\t\tInvalid index. Please enter an index between 0 and " << size - 1 << ".";
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
        void clear() {
            delete[] data;
            capacity = 2;   // safe default
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
}

namespace TemplateVersion
{

    template <typename T>
    class MyBagT
    {
    private:
        T* data;
        int size;
        int capacity;
    public:

        // Precondition: none.
        // Postcondition: Creates an empty bag with size 0 and capacity 0.
        MyBagT() {
            capacity = 0;
            size = 0;
            data = new T[capacity];
        }

        // 1. Copy constructor
        // Precondition: other must be a valid MyBagT.
        // Postcondition: Creates a deep copy of other. Changes to this object do not affect other.
        MyBagT(const MyBagT& other)
            : size(other.size), capacity(other.capacity)
        {
            data = new T[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }

        // 2. Copy assignment
        // Precondition: this and other must be valid MyBagT objects.
        // Postcondition: Current bag becomes a deep copy of other. Old data is freed.
        MyBagT& operator=(const MyBagT& other)
        {
            if (this != &other) {
                T* newData = new T[other.capacity];
                for (int i = 0; i < other.size; ++i) newData[i] = other.data[i];
                delete[] data;
                data = newData;
                size = other.size;
                capacity = other.capacity;
            }
            return *this;
        }

        // 3. Move constructor
         // Precondition: other must be a valid MyBagT.
        // Postcondition: Takes ownership of other's data; other is left empty.
        MyBagT(MyBagT&& other) noexcept
            : data(other.data), size(other.size), capacity(other.capacity)
        {
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }

        // 4. Move assignment
        // Precondition: this and other must be valid MyBagT objects.
        // Postcondition: Current bag frees its data and takes over other's data; other left empty.
        MyBagT& operator=(MyBagT&& other) noexcept
        {
            if (this != &other) {
                delete[] data;
                data = other.data;
                size = other.size;
                capacity = other.capacity;
                other.data = nullptr;
                other.size = 0;
                other.capacity = 0;
            }
            return *this;
        }

        // Precondition: none.
        // Postcondition: Releases all allocated memory.
        ~MyBagT() { delete[] data; }

        // Precondition: none.
        // Postcondition: Returns the current number of elements.
        int getSize() const { return size; }

        // Precondition: none.
        // Postcondition: Returns the current allocated capacity.
        int getCapacity() const { return capacity; }

        // Precondition: none.
        // Postcondition: Returns true if the bag is empty, false otherwise.
        bool isEmpty() const { return size == 0; }

        // Precondition: newCap >= size to preserve existing elements.
        // Postcondition: Capacity changed to newCap, existing elements copied over.
        void resize(int newCap) {
            T* newData = new T[newCap];
            for (int i = 0; i < size; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
            capacity = newCap;
        }

        // Precondition: none.
        // Postcondition: Appends value to the bag; resizes if necessary.
        void insert(const T& value)
        {
            // If array is full, grow it
            if (size == capacity)
            {
                int newCap;
                if (capacity == 0) {
                    newCap = 1;          // start with 1 if nothing yet
                }
                else {
                    newCap = capacity * 2;  // double each time
                }

                resize(newCap);
            }

            data[size] = value;
            size++;
        }

        // Precondition: none.
        // Postcondition: Prints to cout whether value exists and its index; bag is not modified.
        void search(const T& value)
        {
            bool found = false;
            for (int i = 0; i < size; i++)
            {
                if (data[i] == value)
                {
                    cout << "\n\t\tValue " << value << " found at index " << i;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "\n\t\tValue " << value << " not found";
        }

        // Precondition: index must be between 0 and size-1.
        // Postcondition: Removes the element at index and shifts subsequent elements left.
        void remove(int index)
        {
            if (index < 0 || index >= size) {
                cout << "\n\t\tInvalid index. Please enter an index between 0 and " << size - 1 << ".";
                return;
            }

            T deletedValue = data[index];
            for (int i = index; i < size - 1; i++) data[i] = data[i + 1];
            size--;
            /*cout << "\n\t\tValue " << deletedValue << " has been deleted from MyBagT.";*/
        }

        // Precondition: none.
        // Postcondition: All elements are discarded. size=0, capacity reset to 2.
        
         void clear()
         {
                delete[] data;
                capacity = 2;
                size = 0;
                data = new T[capacity];
         }

         // Precondition: T type supports operator> for comparison.
        // Postcondition: Elements are rearranged in ascending order.
          void sortAscending()
          {
                for (int i = 0; i < size - 1; i++)
                {
                    for (int j = 0; j < size - i - 1; j++) {
                        if (data[j] > data[j + 1]) {
                            T temp = data[j];
                            data[j] = data[j + 1];
                            data[j + 1] = temp;
                        }
                    }
                }
                cout << "\n\t\tMyBagT has been sorted.";
          }

          // Precondition: none.
         // Postcondition: Outputs contents of bag to stream; bag is not modified.
          friend ostream& operator<<(ostream & out, const MyBagT<T>&bag)
          {
                if (bag.size == 0) {
                    out << "\n\t\tMyBagT is empty.";
                }
                else {
                    out << "\n\tMyBagT contains these elements: \n";
                    for (int i = 0; i < bag.size; i++) {
                        out << "\n\t[" << i << "] - " << bag.data[i];
                    }
                }
                return out;
          }

            // Precondition: index must be between 0 and size-1.
            // Postcondition: Returns reference to element at index (modifiable).
            T& operator[](int index) { return data[index]; }

            // Precondition: index must be between 0 and size-1.
           // Postcondition: Returns const reference to element at index (read-only).
            const T& operator[](int index) const { return data[index]; }
        
    };

    
}
