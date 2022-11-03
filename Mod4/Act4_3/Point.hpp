#include <math.h>
#include <cmath>

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {};
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    float getDistanceTo(Point b) {
        return (sqrt( pow(this->x - b.x , 2) + pow(this->y - b.y, 2)));
    }
    void print() {
        cout << "(" << this->x << ", " << this->y << ")" << endl;
    }
};

// Sobrecarga del operador <
bool operator <(const Point& p1, const Point& p2) {
    if (p1.y < p2.y) return true;
    else if (p1.y > p2.y) return false;

    if (p1.x < p2.x) return true;
    return false;
}

// Sobrecarga del operador >
bool operator >(const Point& p1, const Point& p2) {
    if (p1.y < p2.y) return false;
    else if (p1.y > p2.y) return true;

    if (p1.x < p2.x) return false;
    return true;
}