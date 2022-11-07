// TC: O(1)
float min(float a, float b) {
    return (a < b) ? a : b;
}

// TC: O(n²), where n = points.size()
float stripClosest(vector<Point> points, float minDistance) {
    float min = minDistance;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i+1; j < points.size(); j++) {
            if (points[i].getDistanceTo(points[j]) < min) {
                min = points[i].getDistanceTo(points[j]);
            }
        }
    }
    return min;
}

// TC: O(n), where n = points.size()
float closestDistance(vector<Point> points) {
    if (points.size() == 2) {
        return points[0].getDistanceTo(points[1]);
    } 
    else if (points.size() <= 1) {
        return numeric_limits<float>::max();
    }

    int middle = points.size()/2;
    Point middlePoint = points[middle];

    vector<Point> left;
    vector<Point> right;
    for (int i = 0; i < points.size(); i++) {
        if (i <= middle) left.push_back(points[i]);
        else right.push_back(points[i]);
    }

    float leftDistance = closestDistance(left);
    float rightDistance = closestDistance(right);
    float minDistance = min(leftDistance, rightDistance);

    vector<Point> strip;
    for (int i = 0; i < points.size(); i++) {
        if (abs(points[i].x - middlePoint.x) < minDistance ) {
            strip.push_back(points[i]);
        }
    }
    return stripClosest(strip, minDistance);
}