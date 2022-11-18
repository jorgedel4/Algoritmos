#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// Complejidad O(1)
bool validate(int x, int y, int N) {
  return !(x < 0 || y < 0 || x >= N || y >= N);
}

// Complejidad O(n)
void nPaths(vector<vector<int>> const &maze, int x, int y, pair<int, int> &dest, vector<vector<bool>> &visited, int& count, vector<string> &res, string &str)
{
  string tmp = str.substr(0, str.size()-1);

  // Si se llega a la casilla destino
  if (x == dest.first && y == dest.second){
    res.push_back(str);
    str.clear();
    count++;
    return;
  }

  // cambiar bool como visitado
  visited[x][y] = 1;

  int N = maze.size();


  // En caso de que la celda sea valida
  if (validate(x, y, N) && maze[x][y]){
    // Down (x, y) ——> (x + 1, y)
    if (x + 1 < N && !visited[x + 1][y]) {
      str += "D";
      nPaths(maze, x + 1, y, dest, visited, count, res, str);
    }

    // Up (x, y) ——> (x - 1, y)
    if (x - 1 >= 0 && !visited[x - 1][y]) {
      str += "U";
      nPaths(maze, x - 1, y, dest, visited, count, res, str);
    }

    // Right (x, y) ——> (x, y + 1)
    if (y + 1 < N && !visited[x][y + 1]) {
      str += "R";     
      nPaths(maze, x, y + 1, dest, visited, count, res, str);
    }

    // Left (x, y) ——> (x, y - 1)
    if (y - 1 >= 0 && !visited[x][y - 1]) {
      str += "L";      
      nPaths(maze, x, y - 1, dest, visited, count, res, str);
    }
  }

  // Backtracking
  str = tmp;
  visited[x][y] = 0;
}
 
// Complejidad O(1)
int findCount(vector<vector<int>> const &maze, pair<int, int> &src, pair<int, int> &dest, vector<string> &res)
{
  // `N × N` matrix
  int N = maze.size();
  string str;

  // base case
  if (N == 0 || maze[src.first][src.second] == 0 ||maze[dest.first][dest.second] == 0) 
    return 0;

  // stores number of unique paths from source to destination
  int count = 0;

  // 2D matrix to keep track of cells involved in the current path
  vector<vector<bool>> visited;
  visited.resize(N, vector<bool>(N));

  // start from source cell
  nPaths(maze, src.first, src.second, dest, visited, count, res, str);

  return count;
}

// Complejidad O(n^2)
void fillMaze(vector<vector<int>> &maze, int N){
  int num;
  for (int i = 0; i < N; i++) {
    vector<int> tmp;
    for (int j = 0; j < N; j++) {
      cin >> num;
      tmp.push_back(num);
    }
    maze.push_back(tmp);
    tmp.clear();
  }
}

// Complejidad O(n*m)
int main(){
  int N;
  cin >> N;
  vector<string> resultado;
  vector<vector<int>> maze;
  fillMaze(maze, N);    

  // source cell
  pair<int,int> src = make_pair(0, 0);

  // destination cell
  pair<int,int> dest = make_pair(N-1, N-1);
  
  int nPath = findCount(maze, src, dest, resultado);
  if(nPath != 0){
    cout << nPath << endl;
    for(auto path : resultado)
      cout<<path<<endl;
  }else{
    cout << "Invalid Maze\n";
  }

  return 0;
}