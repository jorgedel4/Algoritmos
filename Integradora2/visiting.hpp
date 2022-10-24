#include <iostream>
#include <set>
#include <vector>//Parte 2: 
#include <limits>
#include <algorithm>
using namespace std;

// Estrategia
// 1. Vamos a evaluar que todos los nodos estén conectados entre sí. 
// 2. Si algún nodo no posee conexión con otro nodo, entonces vamos a calcular el costo mínimo para llegar a ese nodo. 
// 3. Repetimos para todos los demás nodos. 
// 4. Tras ello, aplicamos prim desde cualquier nodo.
// 5. En cada evaluación nos preguntamos cual es el camino más corto. 
// 6. Si el camino más corto es por parte de un nodo diferente al que nos encontramos... 
// 7. Entonces, a ese camino le sumamos el costo de desplazarnos desde el nodo actual hasta ese nodo, y volvemos a evaluar. 


//Funcion que se encarga de encontrar el camino más corto entre dos nodos. 
int shortestPathFun(vector<vector<int>> matrix, int start, int final){
  //Creamos la variable que almacena el camino más corto.
  int shortestPath;  //O(1) asignación
  //Obtenemos todos los caminos disponibles para el nodo inicial.
  vector<int> avPaths = matrix[start]; //O(1) asignación

  //Si el camino hacia nuestro destino es diferente de 0... 
  // Ese será el camino más corto. 
  if(avPaths[final] != 0){ //O(2) acceso y comparación
    return avPaths[final];
  }

  //De lo contrario, recorreremos cada uno de los vecinos que tenemos a través de nuestros caminos
  for(int i = 0; i < avPaths.size(); i++){ //O(3) asignación, comparación & incremento. 
    //Obtenemos el coste de viajar a ese vecino.
    int cost = avPaths[i]; //O(1) asignación
    //Si el vecino es diferente al start, y su coste es diferente a 0...
    if (i != start && cost != 0){ //O(2) comparaciones
      //Obtenemos el posible camino
      int possible = shortestPathFun(matrix, i, final); // O(n*m) donde n es la cantidad de nodos, y m la cantidad de caminos disponibles por cada nodo.
      //Si el posible camino es menor al camino más corto actual...
      if (possible + cost < shortestPath) //O(2) incremento y comparación.
       //Lo actualizamos
          shortestPath = possible + cost; //O(2) asignación e incremento
    }
  }
  return shortestPath; //Al final, regresamos el coto del camino más corto.
}


//Función que se encarga de calcular el siguiente nodo que recorreremos.
int nextVertex(int origen, vector<pair<pair<int,int>,int>> avPaths, vector<int> visited, vector<vector<int>> matrix){
  //Creamos un par inicial que almacenará el nodo destino y el coste del mismo
  pair<pair<int,int>, int> nextVertex = make_pair(make_pair(0,0), numeric_limits<int>::max()); //O(1) asignación
  //Recorremos cada par de los caminos disponibles.
  for (pair<pair<int,int>, int> nodoPeso : avPaths){
    if(find(visited.begin(), visited.end(), nodoPeso.first.second) != visited.end()) // O(n) donde n es equivalente a la cantidad de nodos visitados.
    {
      continue; 
    } else {
      int costo = nodoPeso.second; //O(1) asignación
      //Después nos preguntamos si el nodo de origen de este camino es el mismo que en el que nos encontramos..
      if (nodoPeso.first.first != origen){ //O(2) acceso y comparación
        //De no ser así, entonces el costo será el de desplazarnos a ese nodo, más el costo original del camino
          int costo = nodoPeso.second + matrix[origen][nodoPeso.first.first]; // O(2) asignación e incremento
      }
      //Si el costo es menor al del siguiente nodo actual...
      if (costo <  nextVertex.second){ //O(2) acceso y comparación
        nextVertex = nodoPeso;  //Lo actualizamos
      }
  }
 }
   //Regresamos el nodo siguiente. 
  return nextVertex.first.second; 
}

//Función que se encarga de recorrer cada una de las ciudades de la forma más óptima
void recorrerTodasLasCiudades(int origen, vector<vector<int>> matrix){
  //Recorremos todos los nodos y sus respectivos caminos. 
  for(int current = 0; current < matrix.size(); current++){ //O(3) asingación, comparación e incremento
    for(int nodoSiguiente = 0; nodoSiguiente < matrix[current].size(); nodoSiguiente++){ //O(3) asingación, comparación e incremento
      //Obtenemos el costo de cada camino
      int costo = matrix[current][nodoSiguiente]; //O(1) asignación
      //Si el costo es de 0, y este es para otro nodo diferente al actual...
      if(costo == 0 && current != nodoSiguiente){ //O(2) comparación
        //Calcula su nuevo costo...
        int nuevoCosto = shortestPathFun(matrix, current, nodoSiguiente);  // O(n*m)  donde n es la cantidad de nodos, y m la cantidad de caminos disponibles por cada nodo.
        //Se lo asignamos
        matrix[current][nodoSiguiente] = nuevoCosto; //O(1) asignación
        //Esto se realiza para aquellos nodos que no tienen conexiones directas.
      }
    }
  }
  
  //Creamos un vector que almacenará a todos los elementos visitados.
  vector<int> visited;  //O(1) asignación
  //Creamos un vector de pares que representan los caminos disponibles.
  vector<pair<pair<int,int>,int>> unvisiPaths; // O(1) asignación
  //Establecemos un nodo actual y final. 
  int current = origen; // O(1) asignación
  int previous = origen; // O(1) asignación
  
  //Mientras no hayamos recorrido todos los nodos...
  while (visited.size() < matrix.size()-1){ //O(n) donde n es la cantidad de elementos en la matrix
    //Añadimos a visitados al nodo actual. 
    visited.push_back(current); //O(1) añadido
    //Creamos un vector de caminos de acuerdo a los caminos actuales.
    vector<int> avPaths = matrix[current]; // O(1) asignación
    //Recorremos cada camino
    for(int i = 0; i < avPaths.size(); i++){ //O(3) asignación, comparación e incremento
      //Si el camino nos lleva a un nodo que hayamos visitado...
      if(find(visited.begin(), visited.end(), i) != visited.end()) { //O(n) donde n es la cantidad de elementos analizados. 
        continue;  //No lo tomamos en cuenta
      } else { //Por otra parte...
      //Obtenemos su respectivo peso 
        int edge = avPaths[i];  // O(1) asignación
        //Creamos un par en donde establecemos: origen, destino y peso. 
        pair<pair<int,int>, int> edgeValue = {{current, i}, edge}; //O(1) asignación
        //Lo añadimos a nuestro vector de caminos disponibles. 
        unvisiPaths.push_back(edgeValue); //O(1) añadido
      }
    }
    //Establecemos que nuestro nuevo nodo será el resultado de la función calcularSiguienteNodo
    int newNode = nextVertex(current, unvisiPaths,visited, matrix);// O(n) donde n es la cantidad de caminos a evaluar. 
    //Imprimimos la transición
    cout << current << " -> " << newNode << "\n" ;
    //Actualizamos los nodos. 
    previous = current; //O(1) asignacion
    current = newNode;//O(1) asignacion
  }
  cout << current << " -> " << origen << endl;
}