/* Análisis y diseño de algoritmos avanzados 
Actividad 2.2 Suffix Array 
Fecha: 7/9/2022
Miembros:
* Karla Sanchez Olivares         (A01730545)
* Carlos Alberto Vega Perez      (A01731416)
* Jorge Angel Delgado Morales    (A01551955)

Escribe un programa en C++ que dado un string, 
se calcule el arreglo de substrings y lo muestre ordenado alfabéticamente 
*/

#include <iostream>
#include <vector>
using namespace std;

// Complexity: O(N), where N is the size of the word
vector<string> findSuffix(string word) {
    vector<string> suffixes;
    int end = word.size();
    for (int i = end - 1; i >= 0; i--) {
        suffixes.push_back(word.substr(i, end));
    }
    return suffixes;
}

// Complexity: O(N), where N is the size of the smallest word
// if (first < second) true
bool compareString(string first, string second) {
    bool isFirstBigger = first.size() >= second.size();
    if (isFirstBigger) {
        for (int i = 0; i < second.size(); i++) {
            if (first[i] < second[i]) return true;
            else if (first[i] > second[i]) return false;
        }
        return false;
    }
    else {
        for (int i = 0; i < first.size(); i++) {
            if (first[i] < second[i]) return true;
            else if (first[i] > second[i]) return false;
        }
        return true;
    }
}

// Complexity: O(N), where N is the size of the vector
void merge(vector<string>& suffix, int initial, int final, int middle) {
    vector<string> aux(final + 1);
    // Check iteration over left side
    int i = initial;
    // Check iteration over right side
    int j = middle + 1;
    // To place items in the right index
    int k = initial; 
    // Fill aux vector
    while (i <= middle && j <= final) {
        if (compareString(suffix[i], suffix[j])) {
            aux[k] = suffix[i];
            i++;
        }
        else {
            aux[k] = suffix[j];
            j++;
        }
        k++;
    }
    // Terminate aux vector with remaining value
    while (i <= middle) {
        aux[k] = suffix[i];
        i++;
        k++;
    }
    while (j <= final) {
        aux[k] = suffix[j];
        j++;
        k++;
    }
    // Reflect changes on original vector
    for (int i = initial; i <= final; i++) {
        suffix[i] = aux[i];
    }
    return;
}

// Complexity: O(N log N), where N is the size of the array 
void mergeSort(vector<string>& suffix, int initial, int final) {
    if (initial < final) {
        int middle = (initial + final) / 2;
        mergeSort(suffix, initial, middle);
        mergeSort(suffix, middle + 1, final);
        merge(suffix, initial, final, middle);
    }
}

// Complexity: O(N), where N is the size of the vector
void printVector(vector<string> solution) {
    for (int i = 0; i < solution.size(); i++) {
        cout << solution[i] << " ";
    }
    cout << endl;
}

int main() {
    string word;
    cin >> word;
    
    vector<string> suffixes = findSuffix(word);
    mergeSort(suffixes, 0, suffixes.size() - 1);

    printVector(suffixes);

}