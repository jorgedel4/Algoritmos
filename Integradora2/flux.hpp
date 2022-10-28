#include <vector>
#include <queue>
using namespace std;

// TC: O(n ^ 2) donde n es el numero de nodos
bool BFS(vector< vector<int> > residualGraph, int start, int end, int* path) {
    int n = residualGraph.size();

    bool visited[n];
    for(int i = 0; i < n; ++i)
        visited[i] = false; 

    queue<int> auxQueue;
    auxQueue.push(start);

    visited[start] = true;
    path[start] = -1;

    int current;
    while(!auxQueue.empty()) {
        current = auxQueue.front();
        auxQueue.pop();

        for(int i = 0; i < n; ++i) {
            if(!visited[i] && residualGraph[current][i] > 0) {
                if(end == i) {
                    path[i] = current;
                    return true;
                }
                auxQueue.push(i);
                path[i] = current;
                visited[i] = true;
            }
        }
    }

    return false;
}

// TC: O(n ^ 5) donde n es el numero de nodos
int maxFlux(vector< vector<int> > fluxMatrix, int start, int end){
    vector< vector<int> > residualGraph = fluxMatrix;
    int n = fluxMatrix.size();

    int path[n];
    int maxFlux = 0;

    int i, j;
    // TC: O(n ^ 3) donde n es el numero de nodos
    while(BFS(residualGraph, start, end, path)) {
        int fluxPath = INT_MAX;

        // TC: O(n ^ 2) donde n es el numero de nodos
        for(j = end; j != start; j = path[j]) {
            i = path[j];
            fluxPath = min(fluxPath, residualGraph[i][j]);
        }

        for(j = end; j != start; j = path[j]) {
            i = path[j];
            residualGraph[i][j] -= fluxPath;
        }
        maxFlux += fluxPath;
    }
    return maxFlux;
}