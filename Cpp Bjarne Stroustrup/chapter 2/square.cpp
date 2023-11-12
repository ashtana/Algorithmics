#include <iostream>
using namespace std; // видимость имён из std без std::

double square(double x) { // возвести в квадрат число типа double
    return x*x;
}

void print_square(double x) {
    cout << "the square of " << x << " is " << square(x) << "\n";
}

int main() {
    print_square(1.234); // печать: квадрат 1.234 есть 1.52276
}
