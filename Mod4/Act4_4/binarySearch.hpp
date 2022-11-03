// Find a random valid index
// TC: O(1)
int getRandom(int min, int max) {
    int range = max - min + 1;
    int num = rand() % range + min;
    return num;
}

// Find a number using a random valid index
// TC: O(n), where n = values.size()
int randomBinarySearch(vector<int> values, int start, int end, int target) {
    if (start == end) {
        return values[start] == target ? start : -1;
    } else if (start > end) {
        return -1;
    }

    int random = getRandom(start, end);
    if (values[random] == target) {
        return random;
    }
    else if (values[random] < target) {
        return randomBinarySearch(values, random+1, end, target);
    }
    return randomBinarySearch(values, start, random-1, target);
}