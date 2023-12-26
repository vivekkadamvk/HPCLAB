#include <iostream>
#include <omp.h>

using namespace std;

void parallelBubbleSort(int arr[], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n-1; i++) {
        // Last i elements are already sorted, so we don't need to check them
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    const int size = 10;
    int arr[size] = {64, 34, 25, 12, 22, 11, 90, 88, 45, 76};

    cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    parallelBubbleSort(arr, size);

    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
