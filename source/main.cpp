#include "MyVector.h"

int main() {
    MyVector vec = { 1, 2, 3, 4, 5 };
    (vec++).print();
    (--vec).print();
    const MyVector temp = { 5, 5, 5 };
    return 0;
}
