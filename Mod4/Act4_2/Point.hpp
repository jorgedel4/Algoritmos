class Point {
    public:
        int x, y;
        
        Point();
        Point(int x, int y);
};

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x, int y) {
    this -> x = x;
    this -> y = y;
}

