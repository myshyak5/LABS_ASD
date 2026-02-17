#include <iostream>

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_ind = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_ind]) {
                min_ind = j;
            }
        }
        if (min_ind != i) {
            std::swap(arr[min_ind], arr[i]);
        }
    }
}

const int n = 5;
int arr[n] = {2, 3, 1, 6, 4};

int main() {
    selectionSort(arr, n);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}