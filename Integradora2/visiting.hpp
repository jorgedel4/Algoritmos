#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

//O(n) where n is the numper of remaining available Paths
int shortestPathFun(vector<vector<int>> matrix, int start, int final){
  int shortestPath, cost, possible;  
  vector<int> avPaths = matrix[start]; 
  if(avPaths[final] != 0){ 
    return avPaths[final];
  }

  for(int i = 0; i < avPaths.size(); i++){ 
    cost = avPaths[i]; 
    if (i != start && cost != 0){ 
      possible = shortestPathFun(matrix, i, final);
      if (possible + cost < shortestPath)
          shortestPath = possible + cost;
    }
  }
  return shortestPath; 
}

//O(n) where n the number of possible paths
int nextVertex(int origen, vector<pair<pair<int,int>,int>> avPaths, vector<int> visited, vector<vector<int>> matrix){
  pair<pair<int,int>, int> nextVertex = make_pair(make_pair(0,0), numeric_limits<int>::max()); 
  for (pair<pair<int,int>, int> vertexValue : avPaths){
    if(find(visited.begin(), visited.end(), vertexValue.first.second) != visited.end()) {
      continue; 
    } else {
      int cost = vertexValue.second; 
      if (vertexValue.first.first != origen) 
          int costo = vertexValue.second + matrix[origen][vertexValue.first.first]; 
      if (cost <  nextVertex.second){ 
        nextVertex = vertexValue; 
      }
  }
 }
  return nextVertex.first.second; 
}

//O(n^2) where n is the number of nodes/vertex
void traverseCities(vector<vector<int>> matrix, int start ){
  int cost, updatedCost;
  int current = start, previous = start; 
  vector<int> visited;  
  vector<pair<pair<int,int>,int>> unvisiPaths; 
  for(int i = 0; i < matrix.size(); i++){
    for(int j = 0; j < matrix[i].size(); j++){ 
      cost = matrix[i][j]; 
      if(cost == 0 && i != j){
        int updatedCost = shortestPathFun(matrix, i, j);  
        matrix[i][j] = updatedCost; 
      }
    }
  }
  
  
  while (visited.size() < matrix.size()-1){ 
    visited.push_back(current);
    vector<int> avPaths = matrix[current]; 
    for(int i = 0; i < avPaths.size(); i++){ 
      if(find(visited.begin(), visited.end(), i) != visited.end()) {  
        continue;  
      } else { 
        int edge = avPaths[i]; 
        pair<pair<int,int>, int> edgeValue = {{current, i}, edge}; 
        unvisiPaths.push_back(edgeValue); 
      }
    }
    int newNode = nextVertex(current, unvisiPaths,visited, matrix); 
    cout << current << " -> " << newNode << "\n" ;
    previous = current; 
    current = newNode;
  }
  cout << current << " -> " << start << endl;
}