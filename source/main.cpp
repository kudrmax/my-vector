#include "MyVector.h"

int main() {
    MyVector vec1 = { 1, 2, 3 };
    MyVector vec2 = { 4, 5 };
    auto temp = vec1 + vec2;
    temp.print();
    return 0;
}
