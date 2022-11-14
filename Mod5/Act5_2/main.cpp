#include <iostream>
#include <vector>
using namespace std;
#include "findWays.cpp"

// Apply format to transform line into vector of ints
// TC: O(n), where n = line.size()
vector<int> parseLine(string line) {
    vector<int> results;
    string number = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] != ' ') {
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
    int people;
    string line;

    // --- Read input ---
    getline(cin, line);
    people = stoi(line);
    vector<vector<int>> hats(people);
    for (int i = 0; i < people; i++) {
        getline(cin, line);
        hats[i] = parseLine(line);
    }

    cout << numberOfWays(hats) << endl;
}