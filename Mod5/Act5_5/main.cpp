#include <iostream>
#include <vector>
#include "astar.hpp"
using namespace std;

int main() {
    int n;
    cin >> n;
    // Se ocupa tiny int ya que solo necesitamos guardar 0s y 1s, y esta variable usa 1 byte en vez de los 4 que usa un int normal
    vector< vector<int8_t> > matrix(n, vector<int8_t>(n));

    // Lectura de matriz, TC de O(n ** 2)
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            cin >> matrix[i][i];

    // Celda inicial y final del recorrido del robot 
    pair<int, int> start = {0, 0}; // (Esquina superior izquierda)
    pair<int, int> end = {n - 1, n - 1}; // (Esquina inferior derecha)

    vector<string> paths = aStar(matrix, start, end);
    if (paths.size() == 0) {
        cout << "No existen caminos" << endl;
    }
    else {
        cout << paths.size() << endl;
        for(string path : paths)
            cout << path << endl;
    }
    return 0;
}