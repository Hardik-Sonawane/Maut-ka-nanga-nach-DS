#include <iostream>
using namespace std;

// Sift-up for Max Heap
void maxHeapifyUp(int a[], int i) {
    while (i > 0 && a[i] > a[(i - 1) / 2]) {
        swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Sift-up for Min Heap
void minHeapifyUp(int a[], int i) {
    while (i > 0 && a[i] < a[(i - 1) / 2]) {
        swap(a[i], a[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Insert element into Max Heap
void insertMax(int a[], int& n, int value) {
    a[n] = value;
    maxHeapifyUp(a, n);
    n++;
}

// Insert element into Min Heap
void insertMin(int a[], int& n, int value) {
    a[n] = value;
    minHeapifyUp(a, n);
    n++;
}

// Print heap
void printHeap(const string& label, int a[], int n) {
    cout << label << ": ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    int maxHeap[10] = {50, 30, 20, 15, 10, 8, 5}; // Example Max Heap
    int minHeap[10] = {5, 10, 8, 15, 20, 30, 50}; // Example Min Heap
    int maxSize = 7, minSize = 7;  // Initial sizes of heaps

    // Insert elements into Max Heap and Min Heap
    insertMax(maxHeap, maxSize, 25);  // Insert 25 into Max Heap
    insertMin(minHeap, minSize, 25);  // Insert 25 into Min Heap

    // Display both heaps
    printHeap("Max Heap", maxHeap, maxSize);
    printHeap("Min Heap", minHeap, minSize);

    return 0;
}
