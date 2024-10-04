#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <stdexcept>

using namespace std;

// Function to print the bucketsorting
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to get highest value of array
int getMaxValue(int arr[], int n) {
    if (arr == nullptr || n <= 0) {
        throw std::invalid_argument("Array is null or size is non-positive");
    }
    return *std::max_element(arr, arr+n);
}

// Bucket sort function per unit
void bucketSortPerDigit(int arr[], int n, int exp){
    
    // Create an array of buckets with numbers from 0-9
    vector<int> buckets[10];

    // Divide the values over the buckets based on current digit variable exp (distribution pass)
    for (int i = 0; i < n; i++) {
        int bucket_index = (arr[i] / exp) % 10;
        buckets[bucket_index].push_back(arr[i]);
    }

    // rebuild the array based on the current buckets (Gathering pass)
    int index = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

// Function that covers all numbers of all units inside
void radixSort(int arr[], int n) {

    // Early return if array is empty
    if (n <= 0) return;

    int maxVal = getMaxValue(arr, n);

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        bucketSortPerDigit(arr, n, exp);
    }
}

// Function to handle negative numbers in bucket sort
void bucketSortNegativePositive(int arr[], int n) {
    // Separate positive and negative numbers
    vector<int> positiveNumbers;
    vector<int> negativeNumbers;

    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            negativeNumbers.push_back(-arr[i]); // Store negatives as positive for sorting
        } else {
            positiveNumbers.push_back(arr[i]);
        }
    }

    // Sort the positive numbers using radix sort
    if(!positiveNumbers.empty()){
        radixSort(positiveNumbers.data(), positiveNumbers.size());
    }

    // Sort the negative numbers (reverse to get them back to negative)
    if (!negativeNumbers.empty()){
        radixSort(negativeNumbers.data(), negativeNumbers.size());
    }

    // Combine sorted negative and positive numbers back into the original array
    int index = 0;

    // Fill in the negative numbers first in reversed order
    for (int j = negativeNumbers.size() - 1; j >= 0; j--) {
        arr[index++] = -negativeNumbers[j];
    }

    // Fill in the positive numbers
    for (int j = 0; j < positiveNumbers.size(); j++) {
        arr[index++] = positiveNumbers[j];
    }
}

int main() {
    vector<int> ns = {3}; // , 100, 1000, 10000};

    // make a ffile for output in CSV format
    ofstream outputFile("sorting_times.csv");

    // Write the CSV header
    outputFile << "ArraySize, TimeMicroseconds\n";

    for (int n : ns) {
        // Generate a random vector to sort
        std::random_device rnd_device;
        std::mt19937 mersenne_engine {rnd_device()};
        std::uniform_int_distribution<int> dist {1, 1000};

        auto gen = [&dist, &mersenne_engine]() {
                        return dist(mersenne_engine);
        };
    
        std::vector<int> arr(n);

        generate(begin(arr), end(arr), gen);

        int n_arr = arr.size(); // Size of the array

        cout << "Before bucketsort: " << endl;
        printArray(arr.data(), n_arr);

        // Start timing
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();        

        bucketSortNegativePositive(arr.data(), n_arr);

        cout << "After bucketsort" << endl;
        printArray(arr.data(), n_arr);

        // Stop timing
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        
        // Calculate and print time
        int time_ms = chrono::duration_cast<chrono::microseconds>(end - begin).count();
        std::cout << n << ", " << time_ms << std::endl;

        // Write array size and time to CSV file
        outputFile << n << "," << time_ms << "\n";
    }
    
    // Close the file
    outputFile.close();

    return 0;
}