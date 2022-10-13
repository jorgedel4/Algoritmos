#include <iostream>
#include <vector>
using namespace std;


bool checkColor(vector<int> ady, vector<int> asigned, int posibleColor){
  for(int i = 0; i < ady.size();i++){
    if(asigned[ady[i]] == posibleColor) //2 3 4 
      return false;
  }
  return true;
}

void graphColoring(int n, vector< vector<int> > matrix){
  //vector<int> colors = {0,1,2,3,4}; //es vec porque se van añadiendo
  vector<int> asigned(n, -1); //año fijo igual al num de nodos
  vector<int> ady; //stack de adyacencias(?) 
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
  vector<vector<int>> matrix;
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