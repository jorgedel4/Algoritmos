#include <iostream>
using namespace std;
#include <vector>

// Build the final labyrinth and print it
// Complexity: O(N*M), where N and M represent the size of the labyrinth
void printBackTrackingSolution(int x, int y, vector<pair<int, int> > path) {
    vector<vector<int> > solution(x, vector<int>(y, 0));
    for (int i = 0; i < path.size(); i++) {
        solution[path[i].second][path[i].first] = 1;
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << solution[i][j] << " ";
        }
        cout << endl;
    }
}

// Check if is inside of labyrinth bounderies and that the cell is available (1)
// Complexity: O(1)
bool isPositionValid(vector<vector<int> > labyrinth, int x, int y) {
    if (x >= 0 && x < labyrinth[0].size() && y >= 0 && y < labyrinth.size() && labyrinth[y][x] == 1)
        return true;
    return false;
}

// Checks if the new move proposal has not been visited yet
// Complexity: O(N), where N is the size of visited
bool isNewPosition(vector<pair<int, int> > visited, int x, int y) {
    for (auto coordinates : visited) {
        if (coordinates.first == x && coordinates.second == y){
            return false;
        }
    }
    return true;
}

// Find the next possible move within labyrinth bounderies, prioritizing right and bottom moves to get closer to the solution
// Complexity: O(N), because of isNewPosition
pair<int, int> findNextMove(vector<vector<int> > labyrinth, vector<pair<int, int> > visited, int x, int y) {
    pair<int, int> nextPosition;
    if (isPositionValid(labyrinth, x+1, y) && isNewPosition(visited, x+1, y)) {
        nextPosition.first = x+1;
        nextPosition.second = y;
        return nextPosition;
    }
    else if (isPositionValid(labyrinth, x, y+1) && isNewPosition(visited, x, y+1)) {
        nextPosition.first = x;
        nextPosition.second = y+1;
        return nextPosition;
    }
    else if (isPositionValid(labyrinth, x-1, y) && isNewPosition(visited, x-1, y)) {
        nextPosition.first = x-1;
        nextPosition.second = y;
        return nextPosition;
    }
    else if (isPositionValid(labyrinth, x, y-1) && isNewPosition(visited, x, y-1)) {
        nextPosition.first = x;
        nextPosition.second = y-1;
        return nextPosition;
    }
    else {
        nextPosition.first = -1;
        nextPosition.second = -1;
        return nextPosition; 
    }
}

// Recursive method to find solution
// Complexity: O(N*M), representing all possible cells
void backtracking(vector<vector<int> > labyrinth, vector<pair<int, int> >& visited, vector<pair<int, int> >& path, int x, int y) {
    // If the algorithm has arrived to the solution
    if (x == labyrinth[1].size() - 1 && y == labyrinth.size() - 1) {
        printBackTrackingSolution(labyrinth.size(), labyrinth[1].size(), path);
    }
    // The algorithm is still calculating solution
    else {
        pair<int, int> nextMove = findNextMove(labyrinth, visited, x, y);
        // This path has come to a death end
        if (nextMove.first == -1 && nextMove.second == -1) {
            path.pop_back();
            pair<int, int> lastMove = path.back();
            // There are no other possible paths
            if (lastMove.first == 0 && lastMove.second == 0) {
                cout << "No solution" << endl;
                return;
            }
            // There is still a way to go back
            else {
                backtracking(labyrinth, visited, path, lastMove.first, lastMove.second);
            }
        } else {
            // Exploring deeper into the current path
            path.push_back(nextMove);
            visited.push_back(nextMove);
            backtracking(labyrinth, visited, path, nextMove.first, nextMove.second);
        }
    }
}
