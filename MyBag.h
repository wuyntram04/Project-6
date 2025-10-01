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
    
    bool isEmpty() const
    {
        return size == 0;
    }

    // resize to new capacity
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

    void insert(int value)
    {
        if (size == capacity)
        {
            resize(capacity + 1);
        }

        data[size] = value;
        size++;
    }

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

    void clear()
    {
        delete[] data;
        capacity = 0;
        size = 0;
        data = new int[capacity];
    }

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
