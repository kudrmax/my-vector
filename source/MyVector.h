#include <initializer_list>
#include <exception>
#include <iostream>

template<typename T>
class MyVector {
public:
    MyVector() = default; // конструктор по умолчанию
    explicit MyVector(size_t size); // конструктор от одного аргумента
    MyVector(size_t size, T num); // конструктор от двух аргументов
    MyVector(std::initializer_list<T> list); // конструктор от std::initializer_list
    MyVector(const MyVector& obj); // конструктор копирования
    MyVector(MyVector&& obj) noexcept; // конструктор перемещения
    ~MyVector(); // деструктор
public:
    MyVector& operator=(const MyVector& obj); // оператор копирующего присваивания
    MyVector& operator=(MyVector&& obj) noexcept; // оператор move присваивания
    MyVector& operator+=(const MyVector& obj);
    MyVector& operator++(); // постфиксный оператор ++
    MyVector& operator--(); // постфиксный оператор ++
    const MyVector operator++(int); // префиксный оператор ++
    const MyVector operator--(int); // префиксный оператор ++
    const MyVector operator+(const MyVector& obj);
public:
    bool operator==(const MyVector& obj) const noexcept;
    bool operator!=(const MyVector& obj) const noexcept;
    bool operator<(const MyVector& obj) const noexcept;
    bool operator>(const MyVector& obj) const noexcept;
public:
    MyVector operator*() const { return *m_arr; };
    T* operator->() const { return m_arr; };
    explicit operator int() const { return m_size; };
//    friend std::ostream& operator<<(std::ostream& out, const MyVector<T>& vec);
public:
    T& operator[](int index);
    T& at(int index);
    const T& operator[](int index) const;
    const T& at(int index) const;
public:
//    size_t size() { return m_size; }
    void print() const {
        std::cout << "vec: ";
        for (size_t i = 0; i < m_size; i++)
            std::cout << m_arr[i];
        std::cout << std::endl;
    }
private:
    T* m_arr;
    size_t m_size;
};

template<typename T>
MyVector<T>::MyVector(size_t size) : m_size(size), m_arr(new T[size]) {};

template<typename T>
MyVector<T>::MyVector(size_t size, T num) : MyVector(size) {
    for (size_t i = 0; i < m_size; i++)
        m_arr[i] = num;

}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> list) : MyVector(list.size()) {
    for (auto it = list.begin(); it != list.end(); it++)
        m_arr[std::distance(list.begin(), it)] = *it;
}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] m_arr;
    m_arr = nullptr;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& obj) : MyVector(obj.m_size) {
    for (size_t i = 0; i < obj.m_size; i++)
        m_arr[i] = *(obj.m_arr + i);
}

template<typename T>
MyVector<T>::MyVector(MyVector&& obj) noexcept {
    std::swap(obj.m_size, m_size);
    std::swap(obj.m_arr, m_arr);
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& obj) {
    if (&obj == this)
        return *this;
    delete[] m_arr;
    m_size = obj.m_size;
    m_arr = new T[m_size];
    for (size_t i = 0; i < m_size; i++)
        m_arr[i] = obj.m_arr[i];
    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& obj) noexcept {
    if (&obj == this)
        return *this;
    delete[] m_arr;
    std::swap(obj.m_size, m_size);
    std::swap(obj.m_arr, m_arr);
    return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator+=(const MyVector& obj) {
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

template<typename T>
MyVector<T>& MyVector<T>::operator++() {
    for (size_t i = 0; i < m_size; i++)
        ++m_arr[i];
    return *this;
}

template<typename T>
const MyVector<T> MyVector<T>::operator++(int) {
    MyVector temp(*this);
    ++*this;
    return temp;
}

template<typename T>
MyVector<T>& MyVector<T>::operator--() {
    for (size_t i = 0; i < m_size; i++)
        --m_arr[i];
    return *this;
}

template<typename T>
const MyVector<T> MyVector<T>::operator--(int) {
    MyVector temp(*this);
    --*this;
    return temp;
}

template<typename T>
bool MyVector<T>::operator==(const MyVector& obj) const noexcept {
    if (m_arr == obj.m_arr)
        return true;
    if (m_size != obj.m_size)
        return false;
    for (size_t i = 0; i < m_size; i++)
        if (m_arr[i] != obj.m_arr[i])
            return false;
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector& obj) const noexcept {
    return !(*this == obj);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& obj) const noexcept {
    for (size_t i = 0; i < std::min(m_size, obj.m_size); i++) {
        if (m_arr[i] < obj.m_arr[i])
            return true;
        if (m_arr[i] > obj.m_arr[i])
            return false;
    }
    if (m_size < obj.m_size)
        return true;
    return false;
}

template<typename T>
bool MyVector<T>::operator>(const MyVector& obj) const noexcept {
    return !(*this < obj) && !(*this == obj);
}

template<typename T>
const MyVector<T> MyVector<T>::operator+(const MyVector& obj) {
    MyVector temp(*this);
    temp += obj;
    return temp;
}

template<typename T>
T& MyVector<T>::operator[](int index) {
    return m_arr[index];
}

template<typename T>
const T& MyVector<T>::operator[](int index) const {
    return m_arr[index];
}

template<typename T>
T& MyVector<T>::at(int index) {
    if (!(0 <= index && index < m_size))
        throw std::runtime_error("Out of range!");
    return operator[](index);
}

template<typename T>
const T& MyVector<T>::at(int index) const {
    if (!(0 <= index && index < m_size))
        throw std::runtime_error("Out of range!");
    return operator[](index);
}

//template<typename T>
//std::ostream& operator<<(std::ostream& out, const MyVector<T>& vec) {
////    for (int i = 0; i < vec.m_size; i++)
////        out << vec.m_arr[i];
//    out << 111;
//    return out;
//}