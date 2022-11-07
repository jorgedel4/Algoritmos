// A divide and conquer program in C++ to find the smallest distance from a
// given set of points.

#include <iostream>
#include <float.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;

// A structure to represent a Point in 2D plane
struct Point
{
	int x, y;
    Point() : x(0), y(0) {};
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

 
// A utility function to find the distance between two points
float dist(Point p1, Point p2) {
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                (p1.y - p2.y)*(p1.y - p2.y)
            );
}

// A Brute Force method to return the smallest distance between two points
// in P[] of size n
float bruteForce(vector<Point> P, int n)
{
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i)
		for (int j = i+1; j < n; ++j)
			if (dist(P[i], P[j]) < min)
				min = dist(P[i], P[j]);
	return min;
}

// Apply format to transform line into Point
// TC: O(1)
Point parseLine(string line) {
    size_t divisor = line.find(", ");
    int x, y;
    x = stoi(line.substr(0, divisor));
    y = stoi(line.substr(divisor + 2, line.length() - divisor - 2));

    return Point(x, y);
}

// Driver program to test above functions
int main() {

    string line;
    getline(cin, line);
    int n = stoi(line);

    vector<Point> points;
    for(int i = 0; i < n; ++i) {
        getline(cin, line);
        points.push_back(parseLine(line));
    }

	cout << "[CORRECT] La distancia mas corta es: " << bruteForce(points, n) << endl;
	return 0;
}
