// TC: O(n**3), where n = adyMatrix.size()
vector< pair<char, char> > optimalWiring(vector< vector<int> > adyMatrix) {
    vector< pair<char, char> > wiringRoute;
    unordered_set<char> visited;
    int n = adyMatrix.size();

    adyMatrix.push_back(vector<int>(n, 0));
    adyMatrix[n][0] = INT_MAX;
    visited.insert('A');

    pair<char, char> optimalConnection;

    // TC: O(n), where n = adyMatriz.size()
    while (wiringRoute.size() < n - 1) {
        optimalConnection.first = 'A' + n;
        optimalConnection.second = 'A';
        // TC: O(n), where n = adyMatriz.size()
        for (char v : visited) {
            // TC: O(n), where n = adyMatriz.size()
            for (int i = 0; i < n; i++) {
                if (adyMatrix[v - 'A'][i] != 0 &&
                    visited.find('A' + i) == visited.end() &&
                    adyMatrix[optimalConnection.first - 'A'][optimalConnection.second - 'A'] > adyMatrix[v - 'A'][i]
                ) {
                    optimalConnection.first = v;
                    optimalConnection.second = 'A' + i;
                }
            }
        }

        visited.insert(optimalConnection.second);

        wiringRoute.push_back(optimalConnection);
    }

    return wiringRoute;
}

void printRoute(vector< pair<char, char> > route) {
    for(pair<char, char> r : route) {
        cout << "(" << r.first << ", " << r.second << ")" << endl;
    }
}