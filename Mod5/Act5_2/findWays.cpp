#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Used to determine if everyone is wearing a different mask
// will have n bits in 1
int allUsedMask;


//
int countWays(int people, int hatTypes, int hatIndex, int bitmask, vector<vector<int>>& dp, unordered_map<int, vector<int>> personPerHat) {
    cout << "===================" << endl;
    cout << "hatIndex: " << hatIndex << endl;
    cout << "bitmask: " << bitmask << endl;
    // All people are wearing unique hats
    if (bitmask == allUsedMask) {
        cout << "All people are wearing caps!" << endl;
        return 1;
    }

    // There is not another hat to process
    if (hatIndex > hatTypes) return 0;

    // Return a recorded record of the answer
    if (dp[bitmask][hatIndex] != -1) {
        cout << "Repeated pattern found at " << bitmask << " " << hatIndex << endl;
        return dp[bitmask][hatIndex];

    }

    // ---- FIRST OPTION ----
    // This cap is skipped
    int ways = countWays(people, hatTypes, hatIndex+1, bitmask, dp, personPerHat);

    // ---- SECOND OPTION ----
    // Allow this cap to a person
    for (int person : personPerHat[hatIndex]) {
        // Check that current person is not wearing a mask
        if ( ((1 << person) & bitmask) == 0) {
            int newMask = bitmask | (1 << person);
            cout << "newMask: " << newMask << endl;
            ways += countWays(people, hatTypes, hatIndex+1, newMask, dp, personPerHat);
        }
    }
    dp[bitmask][hatIndex] = ways;
    // cout << "found ways: " << ways << endl;
    return ways;

}

// hatsPerPerson indicates which person [i] likes which hat [i][j]
// personPerHat indicates which hat [i] can be used by which person [i][j]
// TC: O(h), where h = number of hats
int numberOfWays(vector<vector<int>> hatsPerPerson) {
    int people = hatsPerPerson.size();
    allUsedMask = (1 << people) - 1;
    int hatTypes = 100;

    unordered_map<int, vector<int>> personPerHat;

    for (int person = 0; person < people; person++) {
        for (int hat : hatsPerPerson[person]) {
            personPerHat[hat].push_back(person);
        }
    }

    // Create vector for storing results, starting as -1 indicating no results yet on that value
    // dp[i][j], where i = bitmask and j = hatIndex
    vector<vector<int> > dp(1 << people, vector<int>(hatTypes+1, -1));
    return countWays(people, hatTypes, 1, 0, dp, personPerHat);
}