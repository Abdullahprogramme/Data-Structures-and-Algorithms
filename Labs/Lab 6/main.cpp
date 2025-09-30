#include "Svector.hpp"
#include <iostream>

using namespace std;

int main() {
    Svector v1, v2;
    v1.set(1, 3.0); v1.set(3, 4.0); v1.set(10, 5.0);
    cout << "v1 = "; v1.print();
    v2.set(1, 2.0); v2.set(2, 7.0); v2.set(3, 1.0);
    cout << "v2 = "; v2.print();

    cout << "v1.get(2) = " << v1.get(2) << " (should be 0)\n";
    cout << "v1 . v2 = " << v1.dot(v2) << "\n";
    cout << "||v1|| = " << v1.norm() << "\n";

    Svector v3 = v1.add(v2); cout << "v1 + v2 = "; v3.print();
    v1.scale(2.0);
    cout << "2 * v1 = "; v1.print();
    
    // test removing entry by setting to 0
    v1.set(3, 0.0);
    cout << "After setting v1[3] = 0: "; v1.print();
    return 0;
}