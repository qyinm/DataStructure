#include "MergeSort.h"

void divisionArray(int *arr, int left, int right) {
    int mid = (left + right) / 2;

    if (left < right) {
        divisionArray(arr, left, mid);
        divisionArray(arr, mid + 1, right);

        mergeArray(arr, left, right, mid);
    }
}

void mergeArray(int *arr, int left, int right, int mid) {
    int lidx = left;
    int ridx = mid + 1;

    int sidx = lidx;
    int *temp = new int[right + 1];

    while (lidx <= mid && ridx <= right) {
        if (arr[lidx] <= arr[ridx]) {
            temp[sidx] = arr[lidx++];
        } else {
            temp[sidx] = arr[ridx++];
        }
        ++sidx;
    }
    for (; lidx <= mid; lidx++) {
        temp[sidx++] = arr[lidx];
    }
    for (; ridx <= right; ridx++) {
        temp[sidx++] = arr[ridx];
    }
    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
    delete[] temp;
}
