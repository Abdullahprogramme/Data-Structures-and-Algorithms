#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include "Point2D.hpp"
#include "RectHV.hpp"

using namespace std;

int main() {
    // Test constructor and getters
    Point2D p1(3.0, 4.0);

    assert(p1.x() == 3.0);
    assert(p1.y() == 4.0);

    // Test distanceSquaredTo
    Point2D p2(1.0, 1.0);
    assert(p1.distanceSquaredTo(p2) == 13.0);

    // Test equality operators
    Point2D p3(3.0, 4.0);
    assert(p1 == p3);
    assert(p1 != p2);
    
    // Test < operator
    Point2D p4(1.0, 4.0);
    assert(p2 < p3);
    assert(p2 < p4);
    // Test output stream operator
    cout << p1 << endl; // Should print something like "(3, 4)"

    map<Point2D, int> pointMap;

    // Insert some points and their corresponding values
    pointMap[Point2D(1.0, 2.0)] = 10;
    pointMap[Point2D(3.0, 4.0)] = 20;
    pointMap[Point2D(1.0, 2.0)] = 30; // Overwrites the previous value

    cout << "Accessing values in pointMap, expecting 30\n";
    cout << "Value for (1.0, 2.0): " << pointMap[Point2D(1.0, 2.0)] << endl;

    cout << "iterating over pointMap, expecting 3 key value pairs\n";
    for (const auto& pair : pointMap) {
        cout << "Point: " << pair.first << ", Value: " << pair.second << endl;
    }

    // Create a RectHV object
    RectHV rect1(1.0, 2.0, 3.0, 4.0);

    cout << "Testing RectHV\n";

    cout << "Test getter methods\n";
    cout << "xmin: " << rect1.xmin() << endl;
    cout << "ymin: " << rect1.ymin() << endl;
    cout << "xmax: " << rect1.xmax() << endl;
    cout << "ymax: " << rect1.ymax() << endl;

    cout << "Test contains method: true, false expected\n";
    Point2D p11(1.5, 2.5);
    Point2D p12(4.0, 5.0);
    cout << "Contains p11: " << rect1.contains(p11) << endl;
    cout << "Contains p12: " << rect1.contains(p12) << endl;

    cout << "Test intersects method: true, false expected\n";
    RectHV rect2(2.5, 3.5, 4.5, 5.5);
    RectHV rect3(0.0, 0.0, 1.0, 1.0);
    cout << "Intersects rect2: " << rect1.intersects(rect2) << endl;
    cout << "Intersects rect3: " << rect1.intersects(rect3) << endl;

    cout << "Test distanceSquaredTo method: 5 expected\n";
    Point2D p13(0.0, 0.0);
    cout << "Distance squared to p13: " << rect1.distanceSquaredTo(p13) << endl;

    cout << "Test operator==: true, false expected\n";
    RectHV rect4(1.0, 2.0, 3.0, 4.0);
    RectHV rect5(2.0, 3.0, 4.0, 5.0);
    cout << "rect1 == rect4: " << (rect1 == rect4) << endl;
    cout << "rect1 == rect5: " << (rect1 == rect5) << endl;

    cout << "Test operator<<: [1,3] x [2,4] expected\n";
    cout << "rect1: " << rect1 << endl;

    return 0;
}
