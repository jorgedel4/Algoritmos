#include <iostream>
#include <vector>
using namespace std;
#include "Point.hpp"

int main() {
    Point a = Point(10, 5);
    Point b = Point(12, 7);
    cout << "a < b ? " << (a > b) << endl;
}