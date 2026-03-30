#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Function to print the current state of the array to STDOUT
void printArray(const std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << (i == arr.size() - 1 ? "" : ",");
    }
    std::cout << std::endl;
}

// 1. Bubble Sort
void bubbleSort(std::vector<int> arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                printArray(arr);
            }
        }
    }
}

// 2. Selection Sort
void selectionSort(std::vector<int> arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }
        std::swap(arr[min_idx], arr[i]);
        printArray(arr);
    }
}

// 3. Insertion Sort
void insertionSort(std::vector<int> arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            printArray(arr);
        }
        arr[j + 1] = key;
        printArray(arr);
    }
}

// 4. Quick Sort Helpers
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            printArray(arr);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    printArray(arr);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 5. Merge Sort Helpers
void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { arr[k] = L[i]; i++; }
        else { arr[k] = R[j]; j++; }
        k++; printArray(arr);
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; printArray(arr); }
    while (j < n2) { arr[k] = R[j]; j++; k++; printArray(arr); }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main(int argc, char* argv[]) {
    // 1. Basic safety check
    if (argc < 3) return 1; 

    // 2. Capture the algorithm name (Don't use stoi on this!)
    std::string algo = argv[1]; 
    
    std::vector<int> arr;
    
    // 3. START AT i = 2 (This skips the program name AND the algorithm name)
    for (int i = 2; i < argc; i++) {
        try {
            arr.push_back(std::stoi(argv[i]));
        } catch (...) {
            // This prevents the crash if someone types a letter by mistake
            continue; 
        }
    }

    // 4. Logic to choose the sort
    if (algo == "Bubble") bubbleSort(arr);
    else if (algo == "Selection") selectionSort(arr);
    else if (algo == "Insertion") insertionSort(arr);
    else if (algo == "Quick") quickSort(arr, 0, arr.size() - 1);
    else if (algo == "Merge") mergeSort(arr, 0, arr.size() - 1);

    return 0;
}