#include <iostream>
#include <vector>
#include <cmath>  // for pow

using namespace std;

// Get the digit of number at position `pos` (from the right)
int digit(int number, int pos, int base) {
    return (number / static_cast<int>(pow(base, pos))) % base;
}

int radixSort(vector<int>& a, vector<int>& link, int d, int r, int n) {
    vector<int> front(r, -1), rear(r, -1);  // Corrected size of rear to match r
    int i, bin, current, first, last;

    // Initialize the linked list
    first = 0; // first should start from the 0th index in C++ arrays
    for (i = 0; i < n - 1; i++) link[i] = i + 1;
    link[n - 1] = -1;  // End of the linked list is marked with -1

    // Perform d passes, where d is the number of digits
    for (i = 0; i < d; i++) {
        // Initialize bins
        for (bin = 0; bin < r; bin++) {
            front[bin] = -1;
            rear[bin] = -1;
        }

        // Distribute elements into bins
        for (current = first; current != -1; current = link[current]) {
            bin = digit(a[current], i, r);  // Get the digit for this bin
            if (front[bin] == -1) {
                front[bin] = current;
            } else {
                link[rear[bin]] = current;
            }
            rear[bin] = current;
        }

        // Reassemble the linked list from bins
        first = -1;
        for (bin = 0; bin < r; bin++) {
            if (front[bin] != -1) {
                if (first == -1) first = front[bin];
                else link[last] = front[bin];
                last = rear[bin];
            }
        }
        link[last] = -1;  // Mark the end of the list
    }

    return first;
}

int main() {
    // Input data
    vector<int> a = {329, 457, 657, 839, 436, 720, 355};
    int n = a.size();
    vector<int> link(n);

    int d = 3; // Number of digits in the largest number
    int r = 10; // Radix (decimal system)

    // Perform radix sort
    int first = radixSort(a, link, d, r, n);

    // Reassemble sorted array using the linked list
    vector<int> sorted(n);
    int index = 0;
    while (first != -1) {
        sorted[index++] = a[first];
        first = link[first];
    }

    // Output sorted array
    cout << "Sorted array: ";
    for (int num : sorted) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}