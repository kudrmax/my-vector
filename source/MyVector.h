#include <initializer_list>
#include <iostream>

//template <typename T>
class MyVector {
public:
    // конструкторы
    MyVector() = default;
    MyVector(size_t size) : m_size(size), m_vec(new int[size]) {};
    MyVector(size_t size, int num) : MyVector(size) {
        for (size_t i = 0; i < m_size; i++)
            m_vec[i] = num;
    };
    MyVector(std::initializer_list<int> list) : MyVector(list.size()) {
        for (auto it = list.begin(); it != list.end(); it++)
            m_vec[std::distance(list.begin(), it)] = *it;
    }

    // деструктор
    ~MyVector() {
        delete[] m_vec;
        m_vec = nullptr;
    }

    // конструктор копирования
    MyVector(const MyVector& other_vec) : MyVector(other_vec.m_size) {
        for (int i = 0; i < other_vec.m_size; i++)
            m_vec[i] = *(other_vec.m_vec + i);
    }

    // конструктор перемещения
    MyVector(MyVector&& other_vec) {
        std::swap(other_vec.m_size, m_size);
        std::swap(other_vec.m_vec, m_vec);
    }
public:
//    size_t size() { return m_size; }
    void print() {
        std::cout << "vec: ";
        for (size_t i = 0; i < m_size; i++)
            std::cout << m_vec[i];
        std::cout << std::endl;
    }
private:
    int* m_vec;
    size_t m_size;
};
