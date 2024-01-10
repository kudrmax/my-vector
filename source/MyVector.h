#include <initializer_list>
#include <iostream>

//template <typename T>
class MyVector {
public:
    // конструкторы
    MyVector() = default;
    MyVector(size_t size) : m_size(size), arr(new int[size]) {};
    MyVector(size_t size, int num) : MyVector(size) {
        for (size_t i = 0; i < m_size; i++)
            arr[i] = num;
    };
    MyVector(std::initializer_list<int> list) : MyVector(list.size()) {
        for (auto it = list.begin(); it != list.end(); it++)
            arr[std::distance(list.begin(), it)] = *it;
    }

    // деструктор
    ~MyVector() {
        delete[] arr;
        arr = nullptr;
    }

    // конструктор копирования
    MyVector(const MyVector& other_arr) : MyVector(other_arr.m_size) {
        for (int i = 0; i < other_arr.m_size; i++)
            arr[i] = *(other_arr.arr + i);
    }
public:
//    size_t size() { return m_size; }
    void print() {
        for (size_t i = 0; i < m_size; i++)
            std::cout << arr[i];
        std::cout << std::endl;
    }
private:
    int* arr;
    size_t m_size;
};
