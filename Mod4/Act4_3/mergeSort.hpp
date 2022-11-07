
#include "Point.h"

// TC: O(n)
void mergeX(vector<Point>& points, int start, int end, int middle) {
    vector<Point> aux(end-start+1);
    int i = start, j = middle+1, k = start;
    while (i <= middle && j <= end) {
        if (points[i].x < points[j].x) {
            aux[k-start] = points[i].x;
            i++;
        } else {
            aux[k-start] = points[j].x;
            j++;
        }
        k++;
    }
    while (i <= middle) {
        aux[k-start] = points[i].x;
        i++;
        k++;
    }
    while (j <= end) {
        aux[k-start] = points[j].x;
        j++;
        k++;
    }
    for (int k = start; k <= end; k++) {
        points[k] = aux[k-start];
    }
}

void mergeY(vector<Point>& points, int start, int end, int middle) {
    vector<Point> aux(end-start+1);
    int i = start, j = middle+1, k = start;
    while (i <= middle && j <= end) {
        if (points[i].y < points[j].y) {
            aux[k-start] = points[i].y;
            i++;
        } else {
            aux[k-start] = points[j].y;
            j++;
        }
        k++;
    }
    while (i <= middle) {
        aux[k-start] = points[i].y;
        i++;
        k++;
    }
    while (j <= end) {
        aux[k-start] = points[j].y;
        j++;
        k++;
    }
    for (int k = start; k <= end; k++) {
        points[k].y = aux[k-start];
    }
}


// TC: O(n log n)
void mergeSort(vector<Point>& points, int start, int end, char par) {
    if (start >= end) return;
    int middle = (start + end) / 2;
    mergeSort(points, start, middle);
    mergeSort(points, middle+1, end);
    parameter == 'x' ? mergeX(points, start, end, middle) : mergeY(points, start, end, middle)
}