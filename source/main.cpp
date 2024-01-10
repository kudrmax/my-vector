#include "MyVector.h"

int main() {
    MyVector vec1 = { 1, 2, 3, 4 };
    MyVector vec2 = { 1, 2, 3 };
    std::cout << (vec1 > vec2) << std::endl;
    return 0;
}
