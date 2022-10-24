#include <vector>
#include <queue>
using namespace std;

bool BFS(vector< vector<int> > residualGraph, int start, int end, int* path) {
    int n = residualGraph.size();

    bool visited[n];
    for(int i = 0; i < n; ++i)
        visited[i] = false; 

    queue<int> auxQueue;
    auxQueue.push(start);

    visited[start];
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

int maxFlux(vector< vector<int> > fluxMatrix, int start, int end){
    vector< vector<int> > residualGraph = fluxMatrix;
    int n = fluxMatrix.size();

    int path[n];
    int maxFlux = 0;

    int i, j;
    while(BFS(residualGraph, start, end, path)) {
        int fluxPath = INT_MAX;

        for(j = end; j != start; j = path[i]) {
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