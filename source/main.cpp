#include "MyVector.h"

int main() {
    MyVector vec1 = { 1, 2, 3, 4, 5 };
    MyVector vec2 = vec1;
    MyVector vec3(vec1);

    vec1.print();
    vec2.print();
    vec3.print();
    return 0;
}
