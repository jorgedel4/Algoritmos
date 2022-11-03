#include <iostream>
#include <vector>
using namespace std;
#include "Point.hpp"

// Apply format to transform line into vector of ints
// TC: O(n), where n = line.size()
Point createPointFromInput(string line) {
    vector<int> numbers;
    string number = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] != ' ' && line[i] != ',') {
            number += line[i];
        } else if (number != "") {
            numbers.push_back(stoi(number));
            number = "";
        }
    }
    if (number != "") numbers.push_back(stoi(number));
    return Point(numbers[0], numbers[1]);
}

int main() {
    Point a = Point(10, 5);
    Point b = Point(12, 7);
    cout << "a < b ? " << (a > b) << endl;

    string line;
    getline(cin, line);
    int n = stoi(line);

    vector<Point> points;
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        points.push_back(createPointFromInput(line));
    }

    for (Point i : points) {
        i.print();
    }
}