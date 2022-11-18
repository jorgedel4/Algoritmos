#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
using namespace std;

float getDistance(int finalPosition, int x, int y) {
    return sqrt( pow(finalPosition-y, 2) + pow(finalPosition-x, 2));
}

bool isValid(const vector< vector<int> >& matrix, int x, int y, pair<int, int> lastPosition) {
    if (x < 0 || x >= matrix.size()) return false;
    if (y < 0 || y >= matrix.size()) return false;
    if (x == lastPosition.first && y == lastPosition.second) return false;
    // cout << "matrix at: " << x << ", " << y << " = " << matrix[x][y] << endl;
    return matrix[x][y];
}

char addDirection(int x) {
    if (x == 0) return 'R';
    else if (x == 1) return 'D';
    else if (x == 2) return 'L';
    return 'U';
}

string createPaths(
                const vector< vector<int> >& matrix,
                int x, 
                int y, 
                string currentStr,
                pair<int, int> lastPosition
                ) {

    cout << "Current pos: (" << x << ", " << y << ")" << endl;
    // cout << currentStr << endl;
    int n = matrix.size() - 1;
    if (x == n && y == n) {
        return (currentStr);
    }

    vector<pair<int, int>> movements = { pair(0, 1), pair(1, 0), pair(0, -1), pair(-1, 0)};
    vector<pair<int, int>> validNeighbors;
    vector<int> direction; // 0 = R, 1 = D, 2 = L, 3 = U
    vector<float> distances;
    for (int i = 0; i < movements.size(); i++) {
        if (isValid(matrix, x + movements[i].first, y + movements[i].second, lastPosition)) {
            int newX = x + movements[i].first;
            int newY = y + movements[i].second;
            validNeighbors.push_back(pair(newX, newY));
            distances.push_back(getDistance(n, newX, newY));
            direction.push_back(i);
        }
    }
    // cout << "VALID NEIGHBORS" << endl;
    // for (int i = 0; i < validNeighbors.size(); i++) {
    //     cout << validNeighbors[i].first << " " << validNeighbors[i].second << endl;
    // }

    int indexNextMove = 0;
    int minimumDistance = distances[0];
    for (int i = 1; i < validNeighbors.size(); i++) {
        if (distances[i] < minimumDistance) {
            indexNextMove = i;
            minimumDistance = distances[i];
        }
    }
    currentStr += addDirection(direction[indexNextMove]);
    pair<int, int> nextMove = pair(validNeighbors[indexNextMove].first, validNeighbors[indexNextMove].second);
    // cout << "Next move: " << nextMove.first << " " << nextMove.second << endl;
    return createPaths(matrix, nextMove.first, nextMove.second, currentStr, pair(x, y));
}

string aStar(const vector< vector<int> >& matrix) {
    string s = "";
    return createPaths(matrix, 0, 0, s, pair(0, 0));
}