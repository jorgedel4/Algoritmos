// Análisis y diseño de algoritmos avanzados 
// Actividad 3.2 Implementación de "Dijkstra and Floyd"
// Fecha: 28/09/2022
// Miembros:
// * Karla Sanchez Olivares         (A01730545)
// * Carlos Alberto Vega Perez      (A01731416)
// * Jorge Angel Delgado Morales    (A01551955)

#include <climits>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

// Time complexity: O(n), where n is the number of nodes in the graph
void updateCosts(vector<int>& costs, int current, const vector<int>& row) {
  for(int i = 0; i < row.size(); ++i) {
    if (row[i] > 0) {
      costs[i] = min(costs[i], row[i] + costs[current]);
    }
  }
}

// Time complexity: O(n), where n is the number of nodes in the graph
void updateCurrent(const vector<int>& costs, int& current, const set<int>& visited) {
    int index = -1;
    int minValue = INT_MAX;
    for (int i = 0; i < costs.size(); i++) {
        if (costs[i] < minValue && visited.find(i) == visited.end()) {
            minValue = costs[i];
            index = i;
        }
    }
    current = index;
}

// Time complexity: O(n), where n is the number of nodes in the graph
void printDijkstra(const vector<int>& costs, int start) {
    for (int i = 0; i < costs.size(); i++) {
        if (costs[i] != 0) {
            cout << "node " << start+1 << " to node " << i+1 << " : " << costs[i] << endl;
        }
    }
    cout << endl;
}

// Time complexity: O(n), where n is the number of nodes in the graph
void correctCosts(vector<int>& costs) {
  for (int i = 0; i < costs.size(); i++) {    
    if (costs[i] == INT_MAX) {
      costs[i] = -1;
    }
  }
}

// Time complexity: O(n ˆ 2), where n is the number of nodes in the graph
vector<int> dijkstra(int start, vector<vector<int>> matrix) {
  int n = matrix.size();
  set<int> visited;
  int current = start;
  vector<int> costs(n, INT_MAX);
  costs[start] = 0;
  // TC: O(n ˆ 2) 
  while(visited.size() <= n && current != -1) { 
    updateCosts(costs, current, matrix[current]); // TC: 0(n)
    visited.insert(current);
    updateCurrent(costs, current, visited); // TC: O(n)
  }
  correctCosts(costs); // TC: O(n)
  printDijkstra(costs, start); // TC: O(n)
  return costs;
}

// Complexity: O(n ˆ 2), where n is the number of nodes in the graph
void printFloyd(const vector<vector<int>>& floyd) {
  cout << "Floyd :" << endl;
  for (auto i : floyd) {
    for (auto j : i) {
      cout << j << " ";
    }
    cout << endl;
  }
}

int main() {
  int n;
  cin >> n;

  vector<vector<int>> matrix(n, vector<int>(n));
  vector<vector<int>> floyd;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> matrix[i][j];

  for (int i = 0; i < n; i++) {
    floyd.push_back(dijkstra(i, matrix));
  }

  printFloyd(floyd);

  return 0;
}