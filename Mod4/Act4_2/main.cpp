#include <iostream>
#include <vector>
#include <stack>
#include <math.h>
#include "Point.hpp"
using namespace std;

// Use a global variable for the lowest point in y and x
Point p0;


// Given two points, find the distance
// TC: O(1)
int getDistance(Point p1, Point p2) {
    return (pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}


// Orientation defined as follows:
// 0 if colinear, 1 if clockwise, 2 if counterclockwise
// TC: O(1)
int getOrientation(Point p, Point p1, Point p2) {
    int val = (p1.y - p.y) * (p2.x - p1.x) - (p1.x - p.x) * (p2.y - p1.y);
    if (val == 0) return 0;  // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}



// Función utilizada por "qsort" para poder ordenar los puntos
// Complejidad: orden constante - O(1)
int compare(const void *_p1, const void *_p2) {
    //Soliticamos los puntos y los casteamos
    Point *p1 = (Point *) _p1;
    Point *p2 = (Point *) _p2;

    // Encontramos su orientacion
    int o = getOrientation(p0, *p1, *p2);
    switch (o) {
        case 0: {
            return (getDistance(p0, *p2) >= getDistance(p0, *p1)) ? -1 : 1;
        } break;
        case 1: {
            return 1;
        } break;
        case 2: {
            return -1;
        } break;
    }
    return 0;
}

// Change the position of two points
// TC: O(1)
void swapPoints(Point& p1, Point& p2){
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

// Get next to top point in a stack
// TC: O(1)
Point nextToTop(stack<Point>& S) {
    Point top = S.top();
    S.pop();
    Point next = S.top();
    S.push(top);
    return next;
}


// Print all points that create the polygon
// TC: O(n), where n = Stack.size()
void printResults(stack<Point> S) {
    cout << "Se unen los puntos en el siguiente orden: " << endl;
    while (!S.empty()) {
        Point p = S.top();
        cout << "Punto en coordenadas (" << p.x << ", " << p.y << ")" << endl;
        S.pop();
    }
}



void Graham(vector<Point> points) {
    int lowestYPoint = points[0].y;
    int minPointIndex = 0;
    int y;

    // Find the lowest point in y (using lowest in x as tie-breaker)
    for (int i = 1; i < points.size(); i++) {
        y = points[i].y;
        if ((y < lowestYPoint) || (lowestYPoint == y && points[i].x < points[minPointIndex].x)) {
            lowestYPoint = points[i].y;
            minPointIndex = i;
        }
    }

    // Change the position of the first element with the lowest in y
    swapPoints(points[0], points[minPointIndex]);

    for (auto point : points) {
        cout << point.x << " " << point.y << endl;
    }
    cout << "------" << endl;

    p0 = points[0];
    qsort(&points[1], points.size()-1, sizeof(Point), compare);

    for (auto point : points) {
        cout << point.x << " " << point.y << endl;
    }
    cout << "------" << endl;

    stack<Point> polygonPath;

    // Add the first three elements to the polygon path (minimum number of points to create a polygon)
    polygonPath.push(points[0]);
    polygonPath.push(points[1]);
    polygonPath.push(points[2]);

    // Check all remaining points. If the orientation is not possible, remove the pro
    for (int i = 3; i < points.size(); i++) {
        while (
            getOrientation(
                nextToTop(polygonPath), 
                polygonPath.top(), 
                points[i]
            ) != 2
        ) {
            // Delete point because there is no convex
            polygonPath.pop();
        } 
        polygonPath.push(points[i]);
    }

    printResults(polygonPath);
}




int main() {
    int n;
    cin >> n;
    vector<Point> points;
    int x, y;
    for(int i = 0; i < n; i++){
        cin >> x;
        cin >> y;
        points.push_back(Point(x, y));
    }
    Graham(points);
}