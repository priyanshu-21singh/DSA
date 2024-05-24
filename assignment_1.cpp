#include <bits/stdc++.h>
using namespace std;

// Define the DynamicArray class
class DynamicArray {
private:
    int* data;
    int capacity;
    int size;
    int resize_factor;

    void resize(int new_capacity) {
        int* new_data = new int[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    DynamicArray(int initial_capacity = 2, int resize_factor = 2)
        : capacity(initial_capacity), size(0), resize_factor(resize_factor) {
        data = new int[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void insert(int index, int element) {
        if (index < 0 || index > size) {
            throw std::out_of_range("index out of size");
        }
        if (size == capacity) {
            resize(capacity * resize_factor);
        }
        // this willshift elemrnt to right ...
        for (int i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = element;
        ++size;
    }

    void erase(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("index out of size");
        }
        // this shift the arrayt  to left.... it will fill gap 
        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
        if (size < capacity / resize_factor) {
            resize(capacity / resize_factor);
        }
    }

    int get_size() const {
        return size;
    }

    bool is_empty() const {
        return size == 0;
    }

    void rotate(int k) {
        if (size == 0) return;
        k = k % size;
        std::reverse(data, data + size);
        std::reverse(data, data + k);
        std::reverse(data + k, data + size);
    }

    void reverse() {
        std::reverse(data, data + size);
    }

    void append(int element) {
        if (size == capacity) {
            resize(capacity * resize_factor);
        }
        data[size++] = element;
    }

    void prepend(int element) {
        insert(0, element);
    }

    void merge(const DynamicArray& other) {
        for (int i = 0; i < other.size; ++i) {
            append(other.data[i]);
        }
    }

    DynamicArray interleave(const DynamicArray& other) const {
        DynamicArray new_array;
        int i = 0, j = 0;
        while (i < size || j < other.size) {
            if (i < size) {
                new_array.append(data[i++]);
            }
            if (j < other.size) {
                new_array.append(other.data[j++]);
            }
        }
        return new_array;
    }

    int get_middle_element() const {
        if (size == 0) {
            throw std::out_of_range("Empty array");
        }
        return data[size / 2];
    }

    int index_of(int element) const {
        for (int i = 0; i < size; ++i) {
            if (data[i] == element) {
                return i;
            }
        }
        return -1;
    }

    std::pair<DynamicArray, DynamicArray> split(int index) const {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of bounds");
        }
        DynamicArray first_half;
        DynamicArray second_half;
        for (int i = 0; i < index; ++i) {
            first_half.append(data[i]);
        }
        for (int i = index; i < size; ++i) {
            second_half.append(data[i]);
        }
        return std::make_pair(first_half, second_half);
    }

    void print() const {
        for (int i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Main function to test the DynamicArray class
int main() {
    DynamicArray array;
    array.append(1);
    array.append(2);
    array.append(3);
    array.prepend(0);
    array.insert(2, 1.5);
    std::cout << "Array: ";
    array.print();
    std::cout << "Size: " << array.get_size() << std::endl;
    std::cout << "Is empty: " << (array.is_empty() ? "Yes" : "No") << std::endl;
    array.erase(2);
    std::cout << "Array after deletion: ";
    array.print();
    array.rotate(2);
    std::cout << "Array after rotation: ";
    array.print();
    array.reverse();
    std::cout << "Array after reversal: ";
    array.print();
    DynamicArray other;
    other.append(4);
    other.append(5);
    array.merge(other);
    std::cout << "Array after merge: ";
    array.print();
    std::cout << "Middle element: " << array.get_middle_element() << std::endl;
    std::cout << "Index of 3: " << array.index_of(3) << std::endl;
    
    // Unpack the split result without structured bindings
    std::pair<DynamicArray, DynamicArray> split_result = array.split(3);
    DynamicArray first_half = split_result.first;
    DynamicArray second_half = split_result.second;

    std::cout << "First half: ";
    first_half.print();
    std::cout << "Second half: ";
    second_half.print();

    return 0;
}
