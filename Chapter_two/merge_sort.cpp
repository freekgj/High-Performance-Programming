#include <iostream>
#include <vector>

// Merge function that combines two sorted halves into one
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;  // Size of the left half
    int n2 = right - mid;      // Size of the right half

    // Create temporary vectors to hold the two halves
    std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    // Merge the two halves back into the original array
    int i = 0, j = 0, k = left;

    // Compare elements from both halves and merge them in sorted order
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {    
            arr[k++] = rightArr[j++];
        }
    }

    // Copy remaining elements from leftArr, if any
    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    // Copy remaining elements from rightArr, if any
    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
}

// Recursive function to perform Merge Sort
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) { // when left >= right, the array is already sorted
        int mid = left + (right - left) / 2; // Find the midpoint

        // Recursively sort the left and right halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    // Input array to be sorted
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};

    // Print the original array
    std::cout << "Original Array: ";
    for (const auto& val : arr) std::cout << val << " ";
    std::cout << std::endl;

    // Perform Merge Sort
    mergeSort(arr, 0, arr.size() - 1);

    // Print the sorted array
    std::cout << "Sorted Array: ";
    for (const auto& val : arr) std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}
