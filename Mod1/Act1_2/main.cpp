// Análisis y diseño de algoritmos avanzados 
// Actividad 1.2 Implementación de la técnica de programación "Programación dinámica" y "algoritmos avaros" 
// Fecha: 15/8/2022
// Jorge Angel Delgado Morales A01551955
// Karla Sánchez Olivares A01730545
// Carlos Alberto Vega Perez A0173

#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#include "changeDynamic.hpp"
#include "changeGreedy.hpp"

int main() {
  int n, p, q, cambio;
  cin >> n;
  vector<int> currencies(n);
  for (int i = 0; i < n; i++) {
    cin >> currencies[i];
  }

  sort(currencies.begin(), currencies.end());

  cin >> p; // precio
  cin >> q; // pago
  cambio = q - p;
  cout << endl;
  vector<int> dynamicVector = changeDynamic(cambio, currencies);
  vector<int> greedyVector = changeGr(cambio, currencies);

  reverse(currencies.begin(), currencies.end());

  for (int i = 0; i < currencies.size(); i++) {
    cout << dynamicVector[i] << " de monedas de " << currencies[i] << endl;
  }
  cout << endl;

  for (int i = 0; i < currencies.size(); i++) {
    cout << greedyVector[i] << " de monedas de " << currencies[i] << endl;
  }
}