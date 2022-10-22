// Programa que a partir de un grafo con pesos en sus aristas que representa un conjunto de colonias cableadas
// ejecuta diferentes algoritmos para calcular distintos valores que optimizan los procesos dentro de dicha 
// estructura de datos 

// Integrantes del equipo:
// Daniel Esteban Maldonado Espitia - A01657967
// Fernando de la Torre Rodriguez - A01174460
// Alejandro López Hernández - A01733984
// Victor Alfonso Mancera Osorio - A01733749

// Fecha de creación, modificación y finalización: 08 de noviembre de 2021

#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <cmath>
#include <algorithm> 
#include <queue>
#include <limits.h>
#include <utility>
#include <fstream>
#include <limits>
using namespace std;

//Parte 4:

//Estructura de dato que crea un Punto
struct Punto
{
    double x,y; //Valor para almacenar las coordenadas del punto.
    double distancia; //Valor para almacenar su distancia.
    char zona; //Valor para almacenar la zona a la que el punto pertenece.
};

// Parte 1:

// Función que recibe como parámetro una matriz de adyacencias que representa un grafo
// y regresa un vector de pares que representa las conexiones más óptimas del grafo.
// Para lograrlo, se usó el algoritmo de Prim para generar un MST.
// Complejidad: Orden cuadrático - O(n^2)
vector<pair<char, char>> calculoCableadoOptimo(vector<vector<int>> matrix){
    int n = matrix.size();

    // Se agrega una nueva fila con 0 al fina de la matriz 
    matrix.push_back(vector<int>(n,0));

    // Se inserta el entaro más grande soportado por un int en la última fila y 
    // primera columna de la matriz para usarlo como valor de conexión infinito
    matrix[n][0] = 2147483647;
    
    // Se crea un vector de pares que va a contener el resultado del grafo óptimo
    vector<pair<char, char>> res;

    // Se crea un Hash Set para ir guardando los nodos visitados
    unordered_set<char> visited{'A'};

    // Se crea un par el cual guardará el par de nodos con menor peso en su arista
    pair<char, char> minPair;

    // Se crea el ciclo que se recorrerá mientras no se hayan creado las conexiones 
    // necesarias en el vector res
    while(res.size() < n-1){
        
        // Se declara al minPair como el valor infinito insertado en la matriz al 
        // principio de la función
        minPair = make_pair('A'+n, 'A');

        // Se recorren los nodos visitados para evaluar sus conexiones con los demás
        for(char key: visited)
            // Por cada nodo visitado se busca el peso menor en cada una de sus aristas
            for(int i = 0; i < n; i++)
                if(matrix[key-'A'][i] != 0 && visited.find('A'+i) == visited.end() &&
                matrix[minPair.first-'A'][minPair.second-'A'] > matrix[key-'A'][i])
                    // Si el nodo no ha sido visitado y su conexión es óptima, se 
                    // redefine el valor de minPair asignandole dicha conexión
                    minPair = make_pair(key, 'A'+i);

        // Se inserta el nodo de la conexión más óptima en los visitados
        visited.insert(minPair.second);

        // Se inserta la conexión más optima en el vector resultante
        res.push_back(minPair);
    }

    return res;
}

// Función que recibe el vector de pares que representa las conexiones en el grafo
// e imprime dichas conexiones en formato numérico si inNumbers es true o imprime
// en formato alfabético si es false
// Complejidad: Orden lineal - O(n)
void printGraph(vector<pair<char, char>> graph, bool inNumbers){
    if(inNumbers)
        // Para imprimir en formato numérico, se castea el char a int y se le resta
        // la primera letra del abecedario - 1 para empezar desde 1
        for(auto p : graph)
            cout << "(" << (int)(p.first-('A'-1)) << ", " << (int)(p.second-('A'-1)) << ")\n";
    else 
        for(auto p : graph)
            cout << "(" << p.first << ", " << p.second << ")\n";
}


//Parte 2: 

// Estrategia
// 1. Vamos a evaluar que todos los nodos estén conectados entre sí. 
// 2. Si algún nodo no posee conexión con otro nodo, entonces vamos a calcular el costo mínimo para llegar a ese nodo. 
// 3. Repetimos para todos los demás nodos. 
// 4. Tras ello, aplicamos prim desde cualquier nodo.
// 5. En cada evaluación nos preguntamos cual es el camino más corto. 
// 6. Si el camino más corto es por parte de un nodo diferente al que nos encontramos... 
// 7. Entonces, a ese camino le sumamos el costo de desplazarnos desde el nodo actual hasta ese nodo, y volvemos a evaluar. 


//Funcion que se encarga de encontrar el camino más corto entre dos nodos. 
int encontrarCaminoMasCorto(int inicio, int destino, vector<vector<int>> matriz){
  //Creamos la variable que almacena el camino más corto.
  int caminoMasCorto;  //O(1) asignación
  //Obtenemos todos los caminos disponibles para el nodo inicial.
  vector<int> caminos = matriz[inicio]; //O(1) asignación

  //Si el camino hacia nuestro destino es diferente de 0... 
  // Ese será el camino más corto. 
  if(caminos[destino] != 0){ //O(2) acceso y comparación
    return caminos[destino];
  }

  //De lo contrario, recorreremos cada uno de los vecinos que tenemos a través de nuestros caminos
  for(int vecino = 0; vecino < caminos.size(); vecino++){ //O(3) asignación, comparación & incremento. 
    //Obtenemos el coste de viajar a ese vecino.
    int costoCamino = caminos[vecino]; //O(1) asignación
    //Si el vecino es diferente al inicio, y su coste es diferente a 0...
    if (vecino != inicio && costoCamino != 0){ //O(2) comparaciones
      //Obtenemos el posible camino
      int posibleCamino = encontrarCaminoMasCorto(vecino, destino, matriz); // O(n*m) donde n es la cantidad de nodos, y m la cantidad de caminos disponibles por cada nodo.
      //Si el posible camino es menor al camino más corto actual...
      if (posibleCamino + costoCamino < caminoMasCorto) //O(2) incremento y comparación.
       //Lo actualizamos
          caminoMasCorto = posibleCamino + costoCamino; //O(2) asignación e incremento
    }
  }
  return caminoMasCorto; //Al final, regresamos el coto del camino más corto.
}


//Función que se encarga de calcular el siguiente nodo que recorreremos.
int calcularSiguienteNodo(int origen, vector<pair<pair<int,int>,int>> caminos, vector<int> visitados, vector<vector<int>> matriz){
  //Creamos un par inicial que almacenará el nodo destino y el coste del mismo
  pair<pair<int,int>, int> siguienteNodo = make_pair(make_pair(0,0), numeric_limits<int>::max()); //O(1) asignación
  //Recorremos cada par de los caminos disponibles.
  for (pair<pair<int,int>, int> nodoPeso : caminos){
    if(find(visitados.begin(), visitados.end(), nodoPeso.first.second) != visitados.end()) // O(n) donde n es equivalente a la cantidad de nodos visitados.
    {
      continue; 
    } else {
      int costo = nodoPeso.second; //O(1) asignación
      //Después nos preguntamos si el nodo de origen de este camino es el mismo que en el que nos encontramos..
      if (nodoPeso.first.first != origen){ //O(2) acceso y comparación
        //De no ser así, entonces el costo será el de desplazarnos a ese nodo, más el costo original del camino
          int costo = nodoPeso.second + matriz[origen][nodoPeso.first.first]; // O(2) asignación e incremento
      }
      //Si el costo es menor al del siguiente nodo actual...
      if (costo <  siguienteNodo.second){ //O(2) acceso y comparación
        siguienteNodo = nodoPeso;  //Lo actualizamos
      }
  }
 }
   //Regresamos el nodo siguiente. 
  return siguienteNodo.first.second; 
}

//Función que se encarga de recorrer cada una de las ciudades de la forma más óptima
void recorrerTodasLasCiudades(int origen, vector<vector<int>> matriz){
  //Recorremos todos los nodos y sus respectivos caminos. 
  for(int nodoActual = 0; nodoActual < matriz.size(); nodoActual++){ //O(3) asingación, comparación e incremento
    for(int nodoSiguiente = 0; nodoSiguiente < matriz[nodoActual].size(); nodoSiguiente++){ //O(3) asingación, comparación e incremento
      //Obtenemos el costo de cada camino
      int costo = matriz[nodoActual][nodoSiguiente]; //O(1) asignación
      //Si el costo es de 0, y este es para otro nodo diferente al actual...
      if(costo == 0 && nodoActual != nodoSiguiente){ //O(2) comparación
        //Calcula su nuevo costo...
        int nuevoCosto = encontrarCaminoMasCorto(nodoActual, nodoSiguiente, matriz);  // O(n*m)  donde n es la cantidad de nodos, y m la cantidad de caminos disponibles por cada nodo.
        //Se lo asignamos
        matriz[nodoActual][nodoSiguiente] = nuevoCosto; //O(1) asignación
        //Esto se realiza para aquellos nodos que no tienen conexiones directas.
      }
    }
  }
  
  //Creamos un vector que almacenará a todos los elementos visitados.
  vector<int> visitados;  //O(1) asignación
  //Creamos un vector de pares que representan los caminos disponibles.
  vector<pair<pair<int,int>,int>> caminosDisponibles; // O(1) asignación
  //Establecemos un nodo actual y final. 
  int nodoActual = origen; // O(1) asignación
  int nodoAnterior = origen; // O(1) asignación
  
  //Mientras no hayamos recorrido todos los nodos...
  while (visitados.size() < matriz.size()-1){ //O(n) donde n es la cantidad de elementos en la matriz
    //Añadimos a visitados al nodo actual. 
    visitados.push_back(nodoActual); //O(1) añadido
    //Creamos un vector de caminos de acuerdo a los caminos actuales.
    vector<int> caminos = matriz[nodoActual]; // O(1) asignación
    //Recorremos cada camino
    for(int nodoSiguiente = 0; nodoSiguiente < caminos.size(); nodoSiguiente++){ //O(3) asignación, comparación e incremento
      //Si el camino nos lleva a un nodo que hayamos visitado...
      if(find(visitados.begin(), visitados.end(), nodoSiguiente) != visitados.end()) { //O(n) donde n es la cantidad de elementos analizados. 
        continue;  //No lo tomamos en cuenta
      } else { //Por otra parte...
      //Obtenemos su respectivo peso 
        int peso = caminos[nodoSiguiente];  // O(1) asignación
        //Creamos un par en donde establecemos: origen, destino y peso. 
        pair<pair<int,int>, int> nodoPeso = {{nodoActual, nodoSiguiente}, peso}; //O(1) asignación
        //Lo añadimos a nuestro vector de caminos disponibles. 
        caminosDisponibles.push_back(nodoPeso); //O(1) añadido
      }
    }
    //Establecemos que nuestro nuevo nodo será el resultado de la función calcularSiguienteNodo
    int nuevoNodo = calcularSiguienteNodo(nodoActual, caminosDisponibles,visitados, matriz);// O(n) donde n es la cantidad de caminos a evaluar. 
    //Imprimimos la transición
    cout << nodoActual << " -> " << nuevoNodo << "\n" ;
    //Actualizamos los nodos. 
    nodoAnterior = nodoActual; //O(1) asignacion
    nodoActual = nuevoNodo;//O(1) asignacion
  }
  cout << nodoActual << " -> " << origen << endl;
}

//Parte 3
//recorrido bfs al grafo representado en la matriz, si es un recorrido valido de origen a destino
//retorna true, de lo contrairo retorna false
bool BFS(vector<vector<int>> grafoResidual, int origen, int destino, int path[]){
    int sizeOfMatrix = grafoResidual.size();
    //inicia el arreglo de visitados y se llena de false con memset
    // bool visited[sizeOfMatrix] = {0};
    vector<bool> visited(sizeOfMatrix, 0); // Esto hace lo mismo
    // memset(visited, 0, sizeof(visited));
    //cola para guardar los indices del recorrido, iniciando con el origen
    queue<int> myQueue;
    myQueue.push(origen);
    visited[origen] = true;
    path[origen] = -1;
    //mientras que la cola tenga algo
    while (!myQueue.empty()){
        //guardar el index del frente de la cola y eliminarlo
        int indexActual = myQueue.front();
        myQueue.pop();
        //ciclo for para recorrer la fila de la matriz
        for (int x = 0; x < sizeOfMatrix; x++){
            //si no ha sido visitado y su valor en matriz es mayor a cero
            if (!visited[x] && grafoResidual[indexActual][x] > 0){
                //si el indice en x es el destino retorna true primero añadiendose al path
                if ( x == destino){
                    path[x] = indexActual;
                    return true;
                }
                //se añade el indice a la cola y al path, tambien se verifica en visited
                myQueue.push(x);
                path[x] = indexActual;
                visited[x] = true;
            }
        }
    }
    //si no fue un recorrido valido, retorna false
    return false;
}
int getFlujoMaximo(vector<vector<int>> matrizDatos, int origen, int destino){
    //iteradores
    int i, j;
    //copia de la matriz que modificara los pesos de acuerdo al flujo
    vector<vector<int>> grafoResidual = matrizDatos;
    int sizeOfMatrix = grafoResidual.size();
    //inicializacion del path
    int path[sizeOfMatrix];
    int flujoMaximo = 0;
    //mientras que el bfs encuentre un camino valido de acuerdo al origen y el destino
    while (BFS(grafoResidual, origen, destino, path)){
        int flujoPath = INT_MAX;
        //recorrer todo lo encontrado en el path de destino a origen
        for(j = destino; j != origen; j = path[j]){
            i = path[j];
            //comparar y obtener el nuevo flujo minimo del path
            flujoPath = min (flujoPath, grafoResidual[i][j]);
        }
        //restar a todos los nodos del recorrido el flujo encontrado
        for (j = destino; j != origen; j = path[j]){
            i = path[j];
            grafoResidual[i][j] -= flujoPath;
        }
        //sumar el flujo encontrado al flujo maximo
        flujoMaximo += flujoPath;
    }
    return flujoMaximo;
}

//Parte 4.1

//Función que realiza la comparación entre dos puntos dados para realizar el ordenamiento de las distancias.
bool comparacion(Punto a, Punto b)
{
    return (a.distancia < b.distancia); //Se retorna de manera ordenada las distancias.
}

//Función que determina a que colonia pertenece cada central ingresada del usuario.
void determinarCentral(Punto arr[],int n, Punto p)
{
    //Se recorre de manera iterativa la cantidad de elementos (colonias), ingresadas por el usuario.
    for(int i=0;i<n;i++)
    {
        arr[i].distancia = sqrt((arr[i].x - p.x)*(arr[i].x - p.x)+(arr[i].y - p.y)*(arr[i].y - p.y)); //Mediante la formula se calcula cuál es la distancia entre ambos puntos.
    }

    sort( arr , arr + n , comparacion ); //Se realiza un sort para acomodar el arreglo de distancia del más pequeño al más grande.
    
    cout << "La zona a la que pertenece es: " << arr[0].zona << endl; //Se imprime el resultado con la zona a la que pertenece cada colonia.
    
}

int main(){
  cout << "Bievenidos al programa!\n";

  // Vector de vectores que permite almacenar la matriz de adyacencias
  vector<vector<int>> matrix1;

  // Variables para leer los datos de entrada
  int nColonias, distance;
  
  // Creamos la variable de entrada input y le asignamos el archivo 'input.txt'
  ifstream input("input.txt");

  // Leemos la primera línea que corresponde al número de nodos que tiene el grafo
  input >> nColonias;

  // Leemos el peso de cada arista en el grafo y lo agregamos a la matriz
  for(int i = 0; i < nColonias; i++){
      matrix1.push_back({});
      for(int j = 0; j < nColonias; j++){
          input >> distance;
          matrix1[i].push_back(distance);
      }
  }

  // --- Parte 1 ---
  // Mandamos a llamar la función de cableado optimo de las colonias y almacenamos su resutado en un ector de pares
  vector<pair<char, char>> cableadoColonias = calculoCableadoOptimo(matrix1);

  cout << "\n- PARTE 1 -\nForma de cablear las colonias con fibra (lista de arcos de la forma (A,B)):\n";

  // Imprimimos el resultado del cableado optimo
  printGraph(cableadoColonias, 0);

  // --- Parte 2 ---
  cout << "\n- PARTE 2 -\nRuta a seguir por el personal que reparte correspondencia:\n";
  recorrerTodasLasCiudades(0, matrix1);
  
  // --- Parte 3 ---
  vector<vector<int>> matrix2;

  // Leemos el peso de cada arista en el grafo y lo agregamos a la matriz
  for(int i = 0; i < nColonias; i++){
      matrix2.push_back({});
      for(int j = 0; j < nColonias; j++){
          input >> distance;
          matrix2[i].push_back(distance);
      }
  }

  int flujoMaximo = getFlujoMaximo(matrix2,0,3);

  cout << "\n- PARTE 3 -\nFlujo máximo de información del nodo inicial al nodo final: " << flujoMaximo << "\n";

  // --- Parte 4 ---
    
    int x, y, n = 0; //Variables de las coordenadas para las colonias y las centrales (x, y) y n la cantidad de colonias y centrales que habrá
    char id = 'A'; // Identificador de cada punto
    
    cout << "\n- PARTE 4 -\nIngresa la cantidad de colonias: " << endl;
    cin >> n;
    
    Punto arr[n]; //Arreglo donde se almacenan los puntos pertenecientes a las colonias (con su coordenada en x e y; así como su zona y distancia)
    
    //Se itera a partir del número de coloninas que el usuario solicita
    for (int i = 0; i < n; i++, id++){
        cout << "Ingresa las coordenadas, (primeramente x luego y)" << endl;
        cin >> x >> y; // Se almacenan los valores de las coordenadas x e y
        arr[i].x = x; //Se coloca el valor de x en el struct de x de Punto
        arr[i].y = y; //Se coloca el valor de y en el struct de y de Punto
        arr[i].zona = id; //Se coloca el valor de la zona en el struct de zona de Punto
    }
    
    int nC = 0; //Variable que representa el número de centrales que ingresa el usuario
    
    cout << "Ingrese la cantidad de centrales: " << endl; 
    
    cin >> nC;
    
    //Se recorre de manera iterativa la cantidad de centrales
    for(int i=0; i < nC; i++){
        cout << "Ingresa las coordenadas de la central (de la forma x y): " << endl;
        cin >> x >> y; //Se almacenan los valores de las coordenadas x e y de las centrales.
        Punto p; //Se crea un punto que representa la central buscada
        p.x = x; //Se coloca el valor de x en el struct de x de Punto
        p.y = y; //Se coloca el valor de y en el struct de y de Punto
        determinarCentral(arr,n,p); //Se llama a la función determinarCentral, dando de parámetros; el arreglo que contiene las colonias, el número de colonias y el punto a evaluar siendo este la central.
    }

  // Cerramos el archivo de texto
  input.close();

  return 0;
}