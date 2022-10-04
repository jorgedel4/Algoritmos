// Análisis y diseño de algoritmos avanzados 
// Actividad 3.3 Implementacion de Knapsack problem
// Fecha: 3/10/2022
// Miembros:
// * Karla Sanchez Olivares         (A01730545)
// * Carlos Alberto Vega Perez      (A01731416)
// * Jorge Angel Delgado Morales    (A01551955)

#include <iostream>
#include <vector>
using namespace std;

struct item {
    int value;
    int weight;
    float relation;
    item() {
        value = 1;
        weight = 1;
    }
    item(int value, int weight)  {
        this->value = value;
        this->weight = weight;
        relation = (float)value / (float)weight;
    }
    void setValue(int value) {
        this->value = value;
        relation = (float)this->value / (float)this->weight;
    }

    void setWeight(int weight) {
        this->weight = weight;
        relation = (float)this->value / (float)this->weight;
    }

    void printItem() {
        cout << "Value: " << this->value << endl;
        cout << "Weight: " << this->weight << endl;
        cout << "Relation: " << this->relation << endl;
        cout << endl;
    }
};

// TC: O(1)
bool itemAIsBigger(item a, item b) {
    if (a.relation > b.relation) return true;
    else if (a.relation == b.relation) {
        if (a.weight < b.weight) return true;
        else if (a.weight > b.weight) return false;
        
        if (a.value > b.value) return true;
        else return false;
    }
    else return false;
}

// TC: O(n logn) - donde n es el numero de elementos en el vector
void merge(vector<item>& vec, int start, int end, int middle) {
    vector<item> aux(end-start+1);
    int i = start, j = middle+1, k = start;
    while (i <= middle && j <= end) {
        if (itemAIsBigger(vec[i], vec[j])){
            aux[k-start] = vec[i];
            i++;
            k++;
        } else {
            aux[k-start] = vec[j];
            j++;
            k++;
        }
    }
    while (i <= middle) {
        aux[k-start] = vec[i];
        i++;
        k++;
    }
    while (j <= end) {
        aux[k-start] = vec[j];
        j++;
        k++;
    }
    for (int k = start; k <= end-start; k++) {
        vec[k] = aux[k-start];
    }
}

// TC: O(n logn)
void mergeSort(vector<item>& vec, int start, int end) {
    if (start >= end) return;
    int middle = (start+end)/2;
    mergeSort(vec, start, middle);
    mergeSort(vec, middle+1, end);
    merge(vec, start, end, middle);
}

// TC: O(s) - Donde s es el tamano disponible
int insertIntoBackpack(vector<item> available, int maxWeight) {
    int weightCounter = 0;
    int valueCounter = 0;
    for (int i = 0; i < available.size(); i++) {
        if (available[i].weight + weightCounter <= maxWeight) {
            weightCounter += available[i].weight;
            valueCounter += available[i].value;
        }
    }
    return valueCounter;
}

int main() {
    int n, num, maxWeight;
    cin >> n;
    vector<item> available (n, item());
    // TC: O(n)
	for (int i = 0; i < n; i++) {
        cin >> num;
        available[i].setValue(num);
    }
	// TC: O(n)
    for (int i = 0; i < n; i++) {
        cin >> num;
        available[i].setWeight(num);
    }
    cin >> maxWeight;

	// TC: O(n)
    for (int i = 0; i < n; i++) {
        cin >> num;
        available[i].printItem();
    }
	// TC: O(n logn)
    mergeSort(available, 0, n-1);
	// TC: O(n), dado a que available es de tamano n
    cout << insertIntoBackpack(available, maxWeight) << endl;
}
