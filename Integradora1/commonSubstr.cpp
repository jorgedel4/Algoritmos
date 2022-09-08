using namespace std;

// Complexity: O(n * m)
// Where n and m are the sizes of the word A and B
pair<int, int> commonSubstr(string wordA, string wordB) {
    // Create a matrix of size wordA * wordB
    int LCSubstr[wordA.size() + 1][wordB.size() + 1];
    int length = 0;
    int finalPosition = -1;

    // Fill the matrix
    for (int i = 0; i <= wordA.size(); i++)
        for (int j = 0; j <= wordB.size(); j++) {
            // Initialize values on 0 so checking previous position is within range
            if (i == 0 || j == 0) LCSubstr[i][j] = 0;

            // If there is a match, you add one + the value of the previous position
            else if (wordA[i - 1] == wordB[j - 1]) {
                LCSubstr[i][j] = 1 + LCSubstr[i-1][j-1];
                if (1 + LCSubstr[i-1][j-1] > length) {
                    length = 1 + LCSubstr[i-1][j-1];
                    finalPosition = i;
                }
            }

            // If there is no match, that position has a 0
            else LCSubstr[i][j] = 0;
        }

    return pair<int, int> (finalPosition - length, finalPosition);
}