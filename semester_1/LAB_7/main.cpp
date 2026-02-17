#include <iostream>

void shellSort(int* arr, int n) {
	for (int step = n / 2; step > 0; step /= 2) {
		for (int i = step; i < n; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= step && arr[j - step] > temp; j -= step) {
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}
	}
}

const int n = 5;
int arr[n] = {2, 3, 1, 6, 4};

int main() {
    shellSort(arr, n);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}