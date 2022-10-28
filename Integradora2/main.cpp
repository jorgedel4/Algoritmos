#include <climits>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;

#include "dijkstra.hpp"
// AUX FILES: 
// Question 1
#include "optimalWiring.hpp"
// Question 2
#include "visiting.hpp"
// Question 3
#include "flux.hpp"
// Question 4
#include "assignCentral.hpp"


int main() {
  int n;
  cin >> n;
  vector<vector<int>> adjacencyMatrix(n, vector<int>(n));

  /*
  1. leer un archivo de entrada que contiene la información de un grafo
  representado en forma de una matriz de adyacencias con grafos ponderados. El
  peso de cada arista es la distancia en kilómetros entre colonia y colonia, por
  donde es factible meter cableado. El programa debe desplegar cuál es la forma
  óptima de cablear con fibra óptica conectando colonias de tal forma que se
  pueda compartir información entre cuales quiera dos colonias.

  Related File: optimalWiring.hpp
  */

  cout << endl << " ---- Question 1 ----" << endl;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> adjacencyMatrix[i][j];
    }
  }

  vector< pair<char, char> > wiring = optimalWiring(adjacencyMatrix);
  printRoute(wiring);


  /*
  2. Debido a que las ciudades apenas están entrando al mundo tecnológico, se
  requiere que alguien visite cada colonia para ir a dejar estados de cuenta
  físicos, publicidad, avisos y notificaciones impresos. por eso se quiere saber
  ¿cuál es la ruta más corta posible que visita cada colonia exactamente una vez
  y al finalizar regresa a la colonia origen? El programa debe desplegar la ruta
  a considerar, tomando en cuenta que la primera ciudad se le llamará A, a la
  segunda B, y así sucesivamente
  */
  cout << endl << " ---- Question 2 ----" << endl;
  traverseCities(adjacencyMatrix, 0);

  /*
  3. El programa también debe leer otra matriz cuadrada de N x N datos que
  representen la capacidad máxima de transmisión de datos entre la colonia i y
  la colonia j. Como estamos trabajando con ciudades con una gran cantidad de
  campos electromagnéticos, que pueden generar interferencia, ya se hicieron
  estimaciones que están reflejadas en esta matriz.

  La empresa quiere conocer el flujo máximo de información del nodo inicial al
  nodo final. Esto debe desplegarse también en la salida estándar.
  */

  cout << endl << " ---- Question 3 ----" << endl;

  vector<vector<int>> maxFluxMatrix(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> maxFluxMatrix[i][j];
    }
  }

  cout << "Flujo maximo de la colonia 0 a la colonia " << n - 1 << endl;
  cout << maxFlux(maxFluxMatrix, 0, n - 1) << endl;
  /*
  4. Teniendo en cuenta la ubicación geográfica de varias "centrales" a las que
  se pueden conectar nuevas casas, la empresa quiere contar con una forma de
  decidir, dada una nueva contratación del servicio, cuál es la central más
  cercana geográficamente a esa nueva contratación. No necesariamente hay una
  central por cada colonia. Se pueden tener colonias sin central, y colonias con
  más de una central.

  Related File: assignCentral.hpp
  */

  cout << endl<< " ---- Question 4 ----" << endl;

  vector<pair<int, int>> centralLocations(n);
  string line;
  for (int i = 0; i < n; i++) {
    cin >> line;
    centralLocations[i] = (parseCoordinates(line));
  }

  pair<int, int> newLocation;
  cin >> line;
  newLocation = parseCoordinates(line);

  int indexLocation = getClosestCentral(centralLocations, newLocation);
  cout << "La nueva ubicación debe conectarse a la central '" << indexLocation << "', ubicado en las coordenadas (" << centralLocations[indexLocation].first << ", " << centralLocations[indexLocation].second << ")" << endl;
  
}