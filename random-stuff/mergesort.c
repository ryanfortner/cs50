#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Merge two sorted subarrays into one sorted subarray
void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0; // Index for left subarray
    int j = 0; // Index for right subarray
    int k = 0; // Index for merged subarray

    // Merge elements from left and right subarrays into the merged subarray
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Copy the remaining elements from the left subarray, if any
    while (i < leftSize) {
        arr[k++] = left[i++];
    }

    // Copy the remaining elements from the right subarray, if any
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

// Merge Sort function
void mergeSort(int arr[], int size) {
    if (size < 2) {
        return; // Base case: If the array has 0 or 1 element, it is already sorted
    }

    int mid = size / 2; // Find the middle index of the array

    // Create left and right subarrays
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((size - mid) * sizeof(int));

    // Populate left and right subarrays
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    // Recursively sort the left and right subarrays
    mergeSort(left, mid);
    mergeSort(right, size - mid);

    // Merge the sorted left and right subarrays
    merge(arr, left, mid, right, size - mid);

    // Free the dynamically allocated memory
    free(left);
    free(right);
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Not enough arguments\n");
        return 0;
    }

    if ((!strcasecmp(argv[1], "--help")) || (!strcasecmp(argv[1], "-h"))) {
        printf("Sort Numbers via Merge Sort Algorithm\nProvide 2 or more numbers to sort\nExample command: ./mergesort 12 34 1 4 141\n");
        return 0;
    } 

    // put cli arguments into array elements
    int arr[argc - 1];

    for (int i = 0; i < argc - 1; i++) {
        arr[i] = strtof(argv[i + 1], NULL);
    }

    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, size);

    mergeSort(arr, size);

    printf("Sorted array: ");
    printArray(arr, size);

    return 0;
}
