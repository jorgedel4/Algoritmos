#include <climits>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

void updateCosts(vector<int>& costs, int current, const vector<int>& row) {
  for(int i = 0; i < row.size(); ++i)
    if(row[i] > 0)
      costs[i] = min(costs[i], row[i] + costs[current]);
}

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

void printDijkstra(const vector<int>& costs, int start) {
    for (int i = 0; i < costs.size(); i++) {
        if (costs[i] != 0) {
            cout << "node " << start+1 << " to node " << i+1 << " : " << costs[i] << endl;
        }
    }
}

vector<int> dijkstra(int start, vector<vector<int>> matrix) {
  int n = matrix.size();
  set<int> visited;
  int current = start;
  vector<int> costs(n, INT_MAX);
  costs[start] = 0;
  while(visited.size() || current != -1) {
    updateCosts(costs, current, matrix[current]);
    visited.insert(current);
    updateCurrent(costs, current, visited);
  }
  printDijkstra(costs, start);
  return costs;
}

int main() {
  int n;
  cin >> n;

  vector<vector<int>> matrix(n, vector<int>(n));

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      cin >> matrix[i][j];

  return 0;
}