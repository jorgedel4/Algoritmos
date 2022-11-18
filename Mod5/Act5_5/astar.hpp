#include <iostream>
#include <vector>
using namespace std;

void createPaths(const vector< vector<int8_t> >& matrix, vector<string>& paths, vector< vector<bool> >& visited, const pair<int, int>& end, int x, int y, string& currentStr) {

    string copy = currentStr.substr(0, currentStr.size() - 1);
    if (x == end.first && y == end.second) {
        paths.push_back(currentStr);
        currentStr = "";
        return;
    }

    visited[x][y] = true;

    if (!(x < 0 || x >= matrix.size() || y < 0 || y >= matrix.size()) && matrix[x][y]) {
        if (x - 1 >= 0 && !visited[x - 1][y]) {
            currentStr += "U";
            cout << "--------Moving up--------" << endl;
            cout << currentStr << endl;
            cout << x << ", " << y << endl;
            createPaths(matrix, paths, visited, end, x - 1, y, currentStr);
        }

        if (x + 1 < matrix.size() && !visited[x + 1][y]) {
            currentStr += "D";
            cout << "-------Moving down----------" << endl;
            cout << currentStr << endl;
            cout << x << ", " << y << endl;
            createPaths(matrix, paths, visited, end, x + 1, y, currentStr);
        }

        if (y - 1 >= 0 && !visited[x][y - 1]) {
            currentStr += "L";
            cout << "-------Moving left--------" << endl;
            cout << currentStr << endl;
            cout << x << ", " << y << endl;
            createPaths(matrix, paths, visited, end, x, y - 1, currentStr);
        }

        if (y + 1 < matrix.size() && !visited[x][y + 1]) {
            currentStr += "R";
            cout << "---------Moving right----------" << endl;
            cout << currentStr << endl;
            cout << x << ", " << y << endl;
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