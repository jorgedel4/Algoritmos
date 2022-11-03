// Análisis y diseño de algoritmos avanzados 
// Actividad 4.4 Implementación Randomized Binary Search
// Fecha: 03/11/2022
// Miembros:
// * Karla Sanchez Olivares         (A01730545)
// * Carlos Alberto Vega Perez      (A01731416)
// * Jorge Angel Delgado Morales    (A01551955)

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#include "binarySearch.hpp"

// Apply format to transform line into vector of ints
// TC: O(n), where n = line.size()
vector<int> splitInput(string line) {
    vector<int> results;
    string number = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] != ' ' && line[i] != ',') {
            number += line[i];
        } else if (number != "") {
            results.push_back(stoi(number));
            number = "";
        }
    }
    if (number != "") results.push_back(stoi(number));
    return results;
}


int main() {
    int target;
    string line;

    // Read Input
    getline(cin, line);
    target = stoi(line);
    getline(cin, line);

    // TC: O(n), where n = line.size()
    vector<int> values = splitInput(line);
    // TC: O(n), where n = values.size()
    int index = randomBinarySearch(values, 0, values.size()-1, target);

    if (index == -1) {
        cout << "El elemento no esta presente en el arreglo" << endl;
    } else {
        cout << "El elemento esta presente en el indice: " << index << endl;
    }
}