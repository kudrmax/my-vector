#include <initializer_list>
#include <iostream>

//template <typename T>
class MyVector {
public:
    MyVector() = default; // конструктор по умолчанию
    explicit MyVector(size_t size); // конструктор от одного аргумента
    MyVector(size_t size, int num); // конструктор от двух аргументов
    MyVector(std::initializer_list<int> list); // конструктор от std::initializer_list
    MyVector(const MyVector& other_vec); // конструктор копирования
    MyVector(MyVector&& other_vec) noexcept; // конструктор перемещения
    ~MyVector(); // деструктор
public:
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

MyVector::MyVector(size_t size) : m_size(size), m_vec(new int[size]) {};

MyVector::MyVector(size_t size, int num) : MyVector(size) {
    for (size_t i = 0; i < m_size; i++)
        m_vec[i] = num;
}

MyVector::MyVector(std::initializer_list<int> list) : MyVector(list.size()) {
    for (auto it = list.begin(); it != list.end(); it++)
        m_vec[std::distance(list.begin(), it)] = *it;
}

MyVector::~MyVector() {
    delete[] m_vec;
    m_vec = nullptr;
}

MyVector::MyVector(const MyVector& other_vec) : MyVector(other_vec.m_size) {
    for (int i = 0; i < other_vec.m_size; i++)
        m_vec[i] = *(other_vec.m_vec + i);
}

MyVector::MyVector(MyVector&& other_vec) noexcept {
    std::swap(other_vec.m_size, m_size);
    std::swap(other_vec.m_vec, m_vec);
}