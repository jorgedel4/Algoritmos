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