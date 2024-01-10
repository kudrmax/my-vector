#include "MyVector.h"

int main() {
    MyVector vec1 = { 1, 2, 3, 4, 5 };
    MyVector vec2;
    vec2 = vec1;


    vec1.print();
    vec2.print();

    return 0;
}
