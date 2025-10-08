#include <iostream>

void combSort(int* arr, int n) {
	const double factor = 1.2473309;
	int step = n - 1;
	while (step >= 1) {
		for (int i = 0; i + step < n; i++) {
			if (arr[i] > arr[i + step]) {
				std::swap(arr[i], arr[i + step]);
			}
		}
		step /= factor;
	}
}

const int n = 5;
int arr[n] = {2, 3, 1, 6, 4};

int main() {
    combSort(arr, n);
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}