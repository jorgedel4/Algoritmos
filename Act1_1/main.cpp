// Análisis y diseño de algoritmos avanzados 
// Actividad 1.1 - Implementación de la técnica de programación "divide y vencerás"
// Fecha: 
// Miembros:
// * Jorge Angel Delgado Morales (A01551955)
// *
// * 

#include <iostream>
#include "mergeSort.hpp"

int main(){
    uint n;
    int val;
    std::cin >> n;

    double arr[n];

    for(int i = 0; i < n; ++i)
        std::cin >> arr[i];

    mergeSort(arr, 0, n - 1);

    for(int i = 0; i < n; ++i)
        std::cout << arr[i] << std::endl;
    
    return 0;
}