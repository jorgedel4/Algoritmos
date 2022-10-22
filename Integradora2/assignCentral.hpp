// File related to question 4

// TC : O(n), where n = size of line
pair<int, int> parseCoordinates(std::string line) {
    int x, y, divider;

    line = line.substr(1, line.length() - 2);

    divider = line.find(',');

    x = stoi(line.substr(0, divider));
    y = stoi(line.substr(divider + 1, line.length() - divider - 1));

    return {x, y};
}

// TC : O(1)
double getDistance(const pair<int, int>& central, const pair<int, int>& newLocation) {
    int xDif = central.first - newLocation.first;
    int yDif = central.second - newLocation.second;
    return sqrt( pow(xDif, 2) + pow(yDif, 2) );
}

// TC : O(n), where n = size of centralLocations
int getClosestCentral(const vector<pair<int, int>>& centralLocations, const pair<int, int>& newLocation) {
    int closestIndex = 0;
    double closestDistance = getDistance(centralLocations[0], newLocation);
    for (int i = 1; i < centralLocations.size(); i++) {
        double distance = getDistance(centralLocations[i], newLocation);
        if (distance < closestDistance) {
            closestIndex = i;
            closestDistance = distance;
        }
    }
    return closestIndex;
}

