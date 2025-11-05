#include <cstdlib>
#include <climits>
#include <fstream>
#include <string>

struct MinHeapNode {
    int element;
    int i;
};
class MinHeap {
    MinHeapNode* harr;
    int heap_size;
    public:
        MinHeap(MinHeapNode a[], int size) {
            heap_size = size;
            harr = a;
            int i = (heap_size - 1) / 2;
            while (i >= 0) {
                MinHeapify(i);
                i--;
            }
        };
        void MinHeapify(int i) {
            int l = left(i);
            int r = right(i);
            int smallest = i;
            if (l < heap_size && harr[l].element < harr[i].element) {
                smallest = l;
            }
            if (r < heap_size && harr[r].element < harr[smallest].element) {
                smallest = r;
            }
            if (smallest != i) {
                std::swap(harr[i], harr[smallest]);
                MinHeapify(smallest);
            }
        };
        int left(int i) { return (2 * i + 1); }
        int right(int i) { return (2 * i + 2); }
        MinHeapNode getMin() { return harr[0]; }
        void replaceMin(MinHeapNode x) {
            harr[0] = x;
            MinHeapify(0);
        }
};
void mergeSort(int* arr, int left, int right) {
    if (left >= right) { return; }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}
void mergeFiles(char* output_file, int n, int k) {
    std::fstream* in = new std::fstream[k];
    for (int i = 0; i < k; i++) {
        in[i] = std::fstream(std::to_string(i), std::ios::in);
    }
    std::fstream out(output_file, std::ios::out);
    MinHeapNode* harr = new MinHeapNode[k];
    int i;
    for (i = 0; i < k; i++) {
        if (!(in[i] >> harr[i].element)) {
            break;
        }
        harr[i].i = i;
    }
    MinHeap hp(harr, i);
    int count = 0;
    while (count != i) {
        MinHeapNode root = hp.getMin();
        out << root.element << "\n";
        if (!(in[root.i] >> root.element)) {
            root.element = INT_MAX;
            count++;
        }
        hp.replaceMin(root);
    }
    for (int j = 0; j < k; j++) {
        in[j].close();
        std::remove(std::to_string(j).c_str());
    }
    out.close();
    delete[] in;
    delete[] harr;
}
void createInitialRuns(char* input_file, int run_size, int num_ways) {
    std::fstream in(input_file, std::ios::in);
    std::fstream* out = new std::fstream[num_ways];
    char fileName[16];
    for (int i = 0; i < num_ways; i++) {
        out[i] = std::fstream(std::to_string(i), std::ios::out);
    }
    int* arr = (int*)malloc(run_size * sizeof(int));
    bool more_input = true;
    int next_output_file = 0;
    int i;
    while (more_input) {
        for (i = 0; i < run_size; i++) {
            if (!(in >> arr[i])) {
                more_input = false;
                break;
            }
        }
        if (i > 0) {
            mergeSort(arr, 0, i - 1);
            for (int j = 0; j < i; j++) {
                out[next_output_file] << arr[j] << "\n";
            }
            next_output_file++;
        }
    }
    free(arr);
    in.close();
    for (int i = 0; i < num_ways; i++) {
        out[i].close();
    }
    delete[] out;
}
void externalSort(char* input_file, char* output_file, int num_ways, int run_size) {
    createInitialRuns(input_file, run_size, num_ways);
    mergeFiles(output_file, run_size, num_ways);
}
int main() {
    int num_ways = 4;
    int run_size = 25;
    char input_file[] = "..//../input1.txt";
    char output_file[] = "..//..//output.txt";
    externalSort(input_file, output_file, num_ways, run_size);
    return 0;
}