#include <iostream>
#include <vector>

using namespace std;

// 세 값의 메디안을 찾는 함수
int medianOfThree(vector<int>& a, int left, int right) {
  int mid = left + (right - left) / 2;  // 중간 인덱스 계산

  // 세 값의 메디안 찾기
  if (a[left] > a[mid]) swap(a[left], a[mid]);
  if (a[left] > a[right]) swap(a[left], a[right]);
  if (a[mid] > a[right]) swap(a[mid], a[right]);

  // 메디안은 중간 값이므로 mid를 반환
  return mid;
}

int quickSortCallCount = 0;

// 퀵 정렬 함수
void quickSort(vector<int>& a, int left, int right) {
  quickSortCallCount++;
  if (left < right) {
    // 메디안 피벗 선택
    int pivotIndex = medianOfThree(a, left, right);
    int pivotValue = a[pivotIndex];
    swap(a[pivotIndex], a[right]);  // 피벗을 오른쪽 끝으로 이동

    int i = left;  // 피벗보다 작은 값의 인덱스

    // 분할 과정
    for (int j = left; j < right; j++) {
      if (a[j] < pivotValue) {
        swap(a[i], a[j]);
        i++;
      }
    }
    swap(a[i], a[right]);  // 피벗을 올바른 위치로 이동

    // 재귀 호출
    quickSort(a, left, i - 1);   // 왼쪽 부분 배열 정렬
    quickSort(a, i + 1, right);  // 오른쪽 부분 배열 정렬
  }
}

int main() {
  vector<int> arr = {26, 5, 37, 1, 61, 11, 59, 15, 48, 19};
  int n = arr.size();

  quickSort(arr, 0, n - 1);

  cout << "Sorted array: ";
  for (int num : arr) {
    cout << num << " ";
  }
  cout << endl;
  cout << "Sort function call count : " << quickSortCallCount;
  return 0;
}