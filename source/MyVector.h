#include <initializer_list>
#include <iostream>

//template <typename T>
class MyVector {
public:
    MyVector() = default; // конструктор по умолчанию
    explicit MyVector(size_t size); // конструктор от одного аргумента
    MyVector(size_t size, int num); // конструктор от двух аргументов
    MyVector(std::initializer_list<int> list); // конструктор от std::initializer_list
    MyVector(const MyVector& obj); // конструктор копирования
    MyVector(MyVector&& obj) noexcept; // конструктор перемещения
    ~MyVector(); // деструктор
public:
    MyVector& operator=(const MyVector& obj); // оператор копирующего присваивания
    MyVector& operator=(MyVector&& obj) noexcept; // оператор move присваивания
    MyVector& operator+=(const MyVector& obj); // оператор +=
    MyVector& operator-();
    MyVector& operator++();
    const MyVector operator++(int);
public:
    bool operator==(const MyVector& obj) const noexcept;
    bool operator!=(const MyVector& obj) const noexcept;
public:
    MyVector& operator[](size_t index);
    const MyVector& operator[](size_t index) const;
public:
//    size_t size() { return m_size; }
    void print() {
        std::cout << "obj: ";
        for (size_t i = 0; i < m_size; i++)
            std::cout << m_arr[i];
        std::cout << std::endl;
    }
private:
    int* m_arr;
    size_t m_size;
};

MyVector::MyVector(size_t size) : m_size(size), m_arr(new int[size]) {};

MyVector::MyVector(size_t size, int num) : MyVector(size) {
    for (size_t i = 0; i < m_size; i++)
        m_arr[i] = num;
}

MyVector::MyVector(std::initializer_list<int> list) : MyVector(list.size()) {
    for (auto it = list.begin(); it != list.end(); it++)
        m_arr[std::distance(list.begin(), it)] = *it;
}

MyVector::~MyVector() {
    delete[] m_arr;
    m_arr = nullptr;
}

MyVector::MyVector(const MyVector& obj) : MyVector(obj.m_size) {
    for (int i = 0; i < obj.m_size; i++)
        m_arr[i] = *(obj.m_arr + i);
}

MyVector::MyVector(MyVector&& obj) noexcept {
    std::swap(obj.m_size, m_size);
    std::swap(obj.m_arr, m_arr);
}

MyVector& MyVector::operator=(const MyVector& obj) {
    if (&obj == this)
        return *this;
    delete[] m_arr;
    m_size = obj.m_size;
    m_arr = new int[m_size];
    for (size_t i = 0; i < m_size; i++)
        m_arr[i] = obj.m_arr[i];
    return *this;
}

MyVector& MyVector::operator=(MyVector&& obj) noexcept {
    if (&obj == this)
        return *this;
    delete[] m_arr;
    std::swap(obj.m_size, m_size);
    std::swap(obj.m_arr, m_arr);
    return *this;
}

MyVector& MyVector::operator+=(const MyVector& obj) {
    auto temp = new MyVector(m_size + obj.m_size);
    for (size_t i = 0; i < m_size; i++)
        temp->m_arr[i] = m_arr[i];
    for (size_t i = m_size; i < m_size + obj.m_size; i++)
        temp->m_arr[i] = obj.m_arr[i - m_size];
    delete[] m_arr;
    m_arr = temp->m_arr;
    m_size = temp->m_size;
    return *this;
}
