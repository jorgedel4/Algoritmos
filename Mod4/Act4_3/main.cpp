#include <iostream>
#include <vector>
using namespace std;
#include "Point.hpp"
#include "mergeSort.hpp"

// Apply format to transform line into Point
// TC: O(1)
Point parseLine(string line) {
    size_t divisor = line.find(", ");
    int x, y;
    x = stoi(line.substr(0, divisor));
    y = stoi(line.substr(divisor + 2, line.length() - divisor - 2));

    return Point(x, y);
}

int main() {
    string line;
    getline(cin, line);
    int n = stoi(line);

    vector<Point> points;
    for(int i = 0; i < n; ++i) {
        getline(cin, line);
        points.push_back(parseLine(line));
    }

    mergeSort(points, 0, points.size()-1);

    for (Point i : points) {
        i.print();
    }
}