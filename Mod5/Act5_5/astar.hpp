#include <iostream>
#include <vector>
using namespace std;

void createPaths(const vector< vector<int8_t> >& matrix, vector<string>& paths, vector< vector<bool> >& visited, const pair<int, int>& end, int x, int y, string& currentStr) {
    if (x == end.first && y == end.second) {
        paths.push_back(currentStr);
        currentStr = "";
        return;
    }

    visited[x][y] = true;
    string copy = currentStr;

    if (!(x < 0 || x >= matrix.size() || y < 0 || y >= matrix.size()) && matrix[x][y]) {
        if (x - 1 >= 0 && !visited[x - 1][y]) {
            currentStr += "U";
            cout << 1 << endl;
            createPaths(matrix, paths, visited, end, x - 1, y, currentStr);
        }

        if (x + 1 < matrix.size() && !visited[x + 1][y]) {
            currentStr += "D";
            cout << 2 << endl;
            createPaths(matrix, paths, visited, end, x + 1, y, currentStr);
        }

        if (y - 1 >= 0 && !visited[x][y - 1]) {
            currentStr += "L";
            cout << 3 << endl;

            createPaths(matrix, paths, visited, end, x, y - 1, currentStr);
        }

        if (y + 1 < matrix.size() && !visited[x][y + 1]) {
            currentStr += "R";
            cout << 4 << endl;

            createPaths(matrix, paths, visited, end, x, y + 1, currentStr);
        }
    }

    currentStr = copy;
    visited[x][y] = false;
}

vector<string> aStar(const vector< vector<int8_t> >& matrix, pair<int, int> start, pair<int, int> end) {
    // validar que no sea una matriz vacia, y que tanto como el inicio y fin sean celdas accesibles
    if (!(matrix.size()) || !(matrix[start.first][start.second]) || !(matrix[end.first][end.second]))
        return {};

    // todos los caminos posibles de inicio a fin
    vector<string> paths;
    vector< vector<bool> > visited(matrix.size(), vector<bool>(matrix.size(), false));

    string s;
    createPaths(matrix, paths, visited, end, start.first, start.second, s);

    return paths;
}