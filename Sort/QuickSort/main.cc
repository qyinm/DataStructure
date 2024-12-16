#include <iostream>

using namespace std;

int quickSortCallCount = 0;

void quickSort(vector<int>& a, int left, int right) {
  quickSortCallCount++;
  int pivot, i, j;
  if (left < right) {
    i = left;
    j = right + 1;
    pivot = a[left];
    do {
      do i++;
      while (a[i] < pivot);
      do j--;
      while (a[j] > pivot);
      if (i < j) swap(a[i], a[j]);
    } while (i < j);
    swap(a[left], a[j]);
    quickSort(a, left, j - 1);
    quickSort(a, j + 1, right);
  }
}

int main() {
  vector<int> arr = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
  int n = arr.size();
  quickSort(arr, 0, n - 1);

  cout << "Sorted array : ";
  for (const auto& a : arr) {
    cout << a << " ";
  }
  cout << endl;

  cout << "Sort function call count : " << quickSortCallCount;
  return 0;
}