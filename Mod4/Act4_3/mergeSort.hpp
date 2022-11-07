
// TC: O(n)
void merge(vector<Point>& points, int start, int end, int middle) {
    vector<Point> aux(end-start+1);
    int i = start, j = middle+1, k = start;
    while (i <= middle && j <= end) {
        if (points[i] < points[j]) {
            aux[k-start] = points[i];
            i++;
        } else {
            aux[k-start] = points[j];
            j++;
        }
        k++;
    }
    while (i <= middle) {
        aux[k-start] = points[i];
        i++;
        k++;
    }
    while (j <= end) {
        aux[k-start] = points[j];
        j++;
        k++;
    }
    for (int k = start; k <= end; k++) {
        points[k] = aux[k-start];
    }
}

// TC: O(n log n)
void mergeSort(vector<Point>& points, int start, int end) {
    if (start >= end) return;
    int middle = (start + end) / 2;
    mergeSort(points, start, middle);
    mergeSort(points, middle+1, end);
    merge(points, start, end, middle);
}