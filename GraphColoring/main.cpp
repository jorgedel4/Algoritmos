// Análisis y diseño de algoritmos avanzados 
// Actividad 3.4 Graph Coloring
// Fecha: 12/10/2022
// Miembros:
// * Karla Sanchez Olivares         (A01730545)
// * Carlos Alberto Vega Perez      (A01731416)
// * Jorge Angel Delgado Morales    (A01551955)

#include <iostream>
#include <vector>
using namespace std;

// O(a), where a = adjacencies per node
bool checkColor(vector<int> ady, vector<int> asigned, int posibleColor){
  for(int i = 0; i < ady.size();i++){
    if(asigned[ady[i]] == posibleColor) //2 3 4 
      return false;
  }
  return true;
}

// O(n² * a), where n = nodes and a = adjacencies of the node
void graphColoring(int n, vector< vector<int> > matrix){
  vector<int> asigned(n, -1); 
  vector<int> ady; 
  int posibleColor = 0;

  for(int i = 0; i < matrix.size(); i++){
    for(int j = 0; j < matrix[0].size();j++){ 
        if(matrix[i][j] == 1) 
            ady.push_back(j);
    }
    while(checkColor(ady, asigned, posibleColor) == false){
        posibleColor++;
    }
    asigned[i] = posibleColor; //posición de i el color en curso
    posibleColor = 0;  
    ady.clear();
        
  }
  for(int i = 0; i< n; i++){
    cout << "Node " << i+1 << ": " <<asigned[i] << endl;
  }
}

int main() {
  int n;
  cin >> n;  
  int temp;
  vector<vector<int> > matrix;
  for(int i=0; i<n; i++){
        vector<int> tmp;
        for(int j=0; j<n;j++){
            cin>>temp;
            tmp.push_back(temp);
        }
        matrix.push_back(tmp);
        tmp.clear();
    }

  graphColoring(n, matrix);
  return 0;
}