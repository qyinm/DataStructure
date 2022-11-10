#include <iostream>
#include "MergeSort.h"
using namespace std;
int main() {
    int arr[8] = {8, 2, 3, 7, 1, 5, 4, 6};
    divisionArray(arr, 0, 7);

    for (int i = 0; i < 8; i++) {
        cout << arr[i] << " ";
    }
    return 0;
}
