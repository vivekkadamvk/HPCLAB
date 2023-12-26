#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

int parallelBinarySearch(const vector<int>& arr, int key, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid;
        }

        if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1; // key not found
}

int main() {
    const int size = 10;
    vector<int> arr = {11, 22, 34, 45, 64, 76, 88, 90, 91, 99};

    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int keys[] = {34, 76, 99};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    #pragma omp parallel for
    for (int i = 0; i < num_keys; i++) {
        int key = keys[i];

        int result = parallelBinarySearch(arr, key, 0, size - 1);

        #pragma omp critical
        {
            if (result != -1) {
                cout << "Key " << key << " found at index " << result << endl;
            } else {
                cout << "Key " << key << " not found" << endl;
            }
        }
    }

    return 0;
}
