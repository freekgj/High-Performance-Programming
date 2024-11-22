#include <iostream>
#include <vector>

std::vector<int> mergeArrays(const std::vector<int>& array1, const std::vector<int>& array2) {
    // Recursively merge two arrays into one sorted array
    if (array1.empty() && array2.empty()) { // Done when both arrays are empty
        return {}; 
    } else {
        if (array1.empty()) { // If either array is empty
            int head = array2[0]; // Get the head of the second array
            std::vector<int> tail(array2.begin() + 1, array2.end()); // Get the tail of the second array
            std::vector<int> result = {head};
            std::vector<int> mergedTail = mergeArrays(array1, tail);
            result.insert(result.end(), mergedTail.begin(), mergedTail.end());
            return result;
        } else if (array2.empty()) { // Idem for the other array
            int head = array1[0]; // Get the head of the first array
            std::vector<int> tail(array1.begin() + 1, array1.end()); // Get the tail of the first array
            std::vector<int> result = {head};
            std::vector<int> mergedTail = mergeArrays(array2, tail);
            result.insert(result.end(), mergedTail.begin(), mergedTail.end());
            return result;
        } else { // When both still have elements
            int head1 = array1[0]; // Get the head of the first array
            int head2 = array2[0]; // Get the head of the second array
            
            // Select the smallest
            if (head1 < head2) {
                std::vector<int> tail1(array1.begin() + 1, array1.end()); // Get the tail of the first array
                std::vector<int> result = {head1};
                std::vector<int> mergedTail = mergeArrays(tail1, array2);
                result.insert(result.end(), mergedTail.begin(), mergedTail.end());
                return result;
            } else {
                std::vector<int> tail2(array2.begin() + 1, array2.end()); // Get the tail of the second array
                std::vector<int> result = {head2};
                std::vector<int> mergedTail = mergeArrays(tail2, array1);
                result.insert(result.end(), mergedTail.begin(), mergedTail.end());
                return result;
            }
        }
    }
}

// Recursive merge sort implementation for sorting arrays
std::vector<int> recursiveMergeSort(const std::vector<int>& data) {
    // Arrays with 1 element are sorted
    if (data.size() == 1) {
        return data; // Return the array as is
    } else {
        int middle = static_cast<int>(data.size() / 2);
        std::vector<int> first(data.begin(), data.begin() + middle);
        std::vector<int> second(data.begin() + middle, data.end());
        return mergeArrays(recursiveMergeSort(first), recursiveMergeSort(second));
    }
}

int main() {
    std::vector<int> data = {38, 27, 43, 3, 9, 82, 10};
    std::vector<int> sortedData = recursiveMerge Sort(data);

    std::cout << "Sorted array: ";
    for (int num : sortedData) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}