#include <iostream>
#include <vector>
using namespace std;
#include "Point.hpp"

Point parseLine(string line) {
    size_t divisor = line.find(", ");
    int x, y;
    x = stoi(line.substr(0, divisor));
    y = stoi(line.substr(divisor + 2, line.length() - divisor - 2));

    return Point(x, y);
}

int main() {
    int n;
    string nStr;
    getline(cin, nStr);
    n = stoi(nStr);
    vector<Point> points(n);
    cout << n << endl;
    string line;
    
    for(int i = 0; i < n; ++i) {
        getline(cin, line);
        points[i] = parseLine(line);
    }

    for(Point point : points) {
        point.print();
    }

    return 0;
}