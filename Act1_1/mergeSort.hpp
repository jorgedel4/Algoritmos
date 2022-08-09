void merge(double array[], int left, int mid, int right){
    int n1, n2;
    // tamano de subarray 1
    n1 = mid - left + 1;
    // tamano de subarray 2
    n2 = right - mid;
 
    // creacion de subarrays temporales
    double *leftArray = new double[n1];
    double *rightArray = new double[n2];
 
    // se llenan los subarrays con los valores correspondientes del array original
    for (int i = 0; i < n1; i++)
        leftArray[i] = array[left + i];
    for (auto i = 0; i < n2; i++)
        rightArray[i] = array[mid + 1 + i];

    int i1, i2, iMerged;
    // indices actuales del subarray 1 y 2
    i1 = 0;
    i2 = 0;
    // indice actual de que parte ha sido mergeada del array original
    iMerged = left;
 
    // mientras aun no se haya recorrido por completo ambos subarrays
    while (i1 < n1 && i2 < n2) {
        if (leftArray[i1] >= rightArray[i2]) {
            array[iMerged] = leftArray[i1];
            i1++;
        }
        else {
            array[iMerged] = rightArray[i2];
            i2++;
        }
        iMerged++;
    }

    // en caso de que se haya pasado ya por todo el segundo subarray
    while (i1 < n1) {
        array[iMerged] = leftArray[i1];
        i1++;
        iMerged++;
    }

    // en caso de que se haya pasado ya por todo el primer subarray
    while (i2 < n2) {
        array[iMerged] = rightArray[i2];
        i2++;
        iMerged++;
    }

    // liberar la memoria usada para los subarrays temporales
    delete[] leftArray;
    delete[] rightArray;
}
 
void mergeSort(double arr[], int left, int right){
    // caso base
    if (left >= right) return; 
 
    int mid = left + (right - left) / 2;
    
    // llamadas recursivas con ambas mitades
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}