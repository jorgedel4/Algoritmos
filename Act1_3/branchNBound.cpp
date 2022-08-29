#include <iostream>
using namespace std;
#include <vector>

// Build the final labyrinth and print it
// Complexity: O(N*M), where N and M represent the size of the labyrinth
void printBranchNBoundSolution(int x, int y, vector<pair<int, int> > bestPath, int totalMoves) {
    if (totalMoves == -1) {
        cout << "No solution" << endl;
        return;
    }
    vector<vector<int> > solutionBnB(x, vector<int>(y, 0));
    for (int i = 0; i < bestPath.size(); i++) {
        solutionBnB[bestPath[i].second][bestPath[i].first] = 1;
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cout << solutionBnB[i][j] << " ";
        }
        cout << endl;
    }
    return;
}

// Check if is inside of labyrinth bounderies and that the cell is available (1)
// Complexity: O(1)
bool isPositionValidBnB(vector<vector<int> > labyrinth, int x, int y) {
    if (x >= 0 && x < labyrinth[0].size() && y >= 0 && y < labyrinth.size() && labyrinth[y][x] == 1)
        return true;
    return false;
}

// Checks if the new move proposal has not been visited yet
// Complexity: O(N), where N is the size of visited
bool isNewPositionBnB(vector<pair<int, int> > visited, int x, int y) {
    for (auto coordinates : visited) {
        if (coordinates.first == x && coordinates.second == y){
            return false;
        }
    }
    return true;
}

// Find the next possible move within labyrinth bounderies, prioritizing right and bottom moves to get closer to the solution
// Complexity: O(N), because of isNewPositionBnB
pair<int, int> findNextMoveBnB(vector<vector<int> > labyrinth, vector<pair<int, int> > visited, int x, int y) {
    pair<int, int> nextPosition;
    if (isPositionValidBnB(labyrinth, x+1, y) && isNewPositionBnB(visited, x+1, y)) {
        nextPosition.first = x+1;
        nextPosition.second = y;
        return nextPosition;
    }
    else if (isPositionValidBnB(labyrinth, x, y+1) && isNewPositionBnB(visited, x, y+1)) {
        nextPosition.first = x;
        nextPosition.second = y+1;
        return nextPosition;
    }
    else if (isPositionValidBnB(labyrinth, x-1, y) && isNewPositionBnB(visited, x-1, y)) {
        nextPosition.first = x-1;
        nextPosition.second = y;
        return nextPosition;
    }
    else if (isPositionValidBnB(labyrinth, x, y-1) && isNewPositionBnB(visited, x, y-1)) {
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

// Determine if the next movement is reentering the best path
// Complexity: O(N), depending on the size of the bestPath
bool isReenteringBestPath(vector<pair<int, int> > bestPath, int x, int y) {
    for (auto coordinates : bestPath) {
        if (coordinates.first == x && coordinates.second == y){
            // cout << "Reentering best path: TRUE" << endl;
            return true;
        }
    }
    // cout << "Reentering Best Path: FALSE" << endl;
    return false;
}

// Find how many moves it required to get to reenter the bestPath
// Complexity: O(N), depending on bestPath.size
int getBestPathMovesOnPos(vector<pair<int, int> > bestPath, int x, int y) {
    pair<int, int> position(x, y);
    int moves = 0;
    for (int i = 0; i < bestPath.size(); i++) {
        if (bestPath[i] == position){
            // cout << "IN THE CURRENT BEST PATH IT TOOK: " << moves << " moves" << endl;
            return moves;
        }
        moves++;
    }
    return -1;
}

// Recursive method to find solution
// Complexity: O(N*M **2), representing all possible paths that must be double checked
void branchNBound(vector<vector<int> > labyrinth, vector<pair<int, int> >& visited, vector<pair<int, int> >& path, int x, int y, int& totalMoves, vector<pair<int, int> >& bestPath, bool& isDone) {
    if (isDone) return;
    // If the algorithm has arrived to a solution
    if (x == labyrinth[1].size() - 1 && y == labyrinth.size() - 1) {
        totalMoves = path.size() - 1;
        bestPath = path;
        path.pop_back();
        visited.pop_back();
        pair<int, int> lastMove = path.back();
        branchNBound(labyrinth, visited, path, lastMove.first, lastMove.second, totalMoves, bestPath, isDone);
    }
    // The algorithm is still calculating solutions
    else {
        // The current path is longer or equal in moves to a found solution
        if (totalMoves != -1 && path.size() - 1 >= totalMoves) {
            path.pop_back();
            pair<int, int> lastMove = path.back();
            branchNBound(labyrinth, visited, path, lastMove.first, lastMove.second, totalMoves, bestPath, isDone);
        }
        // Find the next move
        pair<int, int> nextMove = findNextMoveBnB(labyrinth, visited, x, y);
        // This path has come to a death end
        if ((nextMove.first == -1 && nextMove.second == -1)) {
            path.pop_back();
            pair<int, int> lastMove = path.back();
            // There are no other possible paths
            if (lastMove.first == 0 && lastMove.second == 0 && !isDone) {
                printBranchNBoundSolution(labyrinth.size(), labyrinth[1].size(), bestPath, totalMoves);
                isDone = true;
                return;
            }
            // There is still a way to go back
            else {
                branchNBound(labyrinth, visited, path, lastMove.first, lastMove.second, totalMoves, bestPath, isDone);
            }
        } 
        // Exploring deeper into the current path
        else {
            // If is back to the best found path
            // Check if is reentering the best path in the same or more moves as what was found
            if ((isReenteringBestPath(bestPath, nextMove.first, nextMove.second)) && getBestPathMovesOnPos(bestPath, nextMove.first, nextMove.second) <= (path.size())) {
                path.pop_back();
                pair<int, int> lastMove = path.back();
                branchNBound(labyrinth, visited, path, lastMove.first, lastMove.second, totalMoves, bestPath, isDone);
            }
            else {
                path.push_back(nextMove);
                visited.push_back(nextMove);
                branchNBound(labyrinth, visited, path, nextMove.first, nextMove.second, totalMoves, bestPath, isDone);
            }
        }
        return;
    }
}
