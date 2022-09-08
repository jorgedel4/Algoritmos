using namespace std;
#include <vector>

// Complexity: O(n + m), where
// n is the size of the pattern
// m is the size of the text
vector<int> functionZ(string pattern, string text) {
    string word = pattern + "$" + text;
    vector<int> zArray(text.size());
    int left = 0, right, matches;
    // [DEBUGGING] Print chars of the text
    for (int i = 0; i < text.size(); i++) cout << text[i] << " ";
    cout << endl;

    // Start to iterate where text starts
    for (int i = pattern.size() + 1; i < word.size(); i++) {
        right = i;
        left = 0;
        matches = 0;
        while (word[left] == word[right] && right < word.size()) {
            matches++;
            left++;
            right++;
        }
        // Set value of array corresponding to position of the text
        zArray[i - pattern.size() - 1] = matches;
        // [DEBUGGING] Print number of matches
        cout << matches << " ";
    }
    cout << endl;
    return zArray;
}

// Complexity: O(N), where N is the size of the arrayZ
void checkMatch(vector<int> arrayZ, int patternSize) {
    bool isFound = false;
    for (int i = 0; i < arrayZ.size(); i++) {
        if (arrayZ[i] == patternSize) {
            if (!isFound) {
                cout << "true ";
                isFound = true;
            }
            cout << i << " ";
        }
    }
    if (!isFound) cout << "false" << endl;
    else cout << endl;
    return;
}