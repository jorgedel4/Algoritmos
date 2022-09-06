/* Análisis y diseño de algoritmos avanzados 
Actividad 1.3 Implementación de la técnica de programación "backtracking" y "ramificación y poda"
Fecha: 28/8/2022
- Jorge Angel Delgado Morales // A01551955
- Karla Sánchez Olivares // A01730545
- Carlos Alberto Vega Perez // A01731416
*/

#include <iostream>
using namespace std;
#include <vector>
#include "backtracking.cpp"
#include "branchNBound.cpp"


int main() {

    // Create labyrinth
    // Complexity: O(N*M)
    int M, N;
    cin >> M >> N;

    vector<vector<int> > labyrinth(M);
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int block;
            cin >> block;
            labyrinth[i].push_back(block);
        }
    }

    // Catch basic cases
    
    // If initial and final are not valid cells
    // Complexity: O(1)
    if (labyrinth[0][0] == 0 || labyrinth[M-1][N-1] == 0) {
        cout << "No solution" << endl;
        return 0;
    }
    // If M or N are lower or equal to 0
    // Complexity: O(1)
    if (M <= 0 || N <= 0) {
        cout << "No solution" << endl;
        return 0;
    }

    // Backtracking
    vector<pair<int, int> > visitedBT(1, make_pair(0, 0)), pathBT(1, make_pair(0, 0));
    backtracking(labyrinth, visitedBT, pathBT, 0, 0);

    cout << endl;

    // Branch N Bound
    int totalMoves = -1;
    bool isDone = false;
    vector<pair<int, int> > visitedBnB(1, make_pair(0, 0)), pathBnB(1, make_pair(0, 0)), bestPath;
    branchNBound(labyrinth, visitedBnB, pathBnB, 0, 0, totalMoves, bestPath, isDone);

    return 0;
}