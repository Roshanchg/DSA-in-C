#include<stdio.h>
#include<stdlib.h>

int get_partition(int arr[], int start, int end) {
    int pivot = arr[start];  // Set the pivot element as the first element.
    int left = start + 1;  // Start the left pointer just after the pivot.
    int right = end;  // Start the right pointer at the end of the array.
    int temp;

    while (left <= right) {
        // Move left pointer to the right while elements are less than or equal to pivot.
        while (left <= end && arr[left] <= pivot) {
            left++;
        }
        // Move right pointer to the left while elements are greater than or equal to pivot.
        while (arr[right] > pivot) {
            right--;
        }

        // If left is still less than right, swap the elements.
        if (left < right) {
            temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
        }
    }
    // Swap the pivot with the element at the right pointer.
    temp = arr[start];
    arr[start] = arr[right];
    arr[right] = temp;

    return right;  // Return the partition index.
}

void quicksort(int arr[], int start, int end) {
    if (start < end) {
        int pivotIndex = get_partition(arr, start, end);  // Get the partition index.
        quicksort(arr, start, pivotIndex - 1);  // Recursively sort the left part.
        quicksort(arr, pivotIndex + 1, end);  // Recursively sort the right part.
    }
}

int main() {
    int size;
    printf("\nEnter size of Array: ");
    scanf("%d", &size);
    size = (size < 0) ? abs(size) : size;  // Ensure the size is positive.

    if (size < 1) {
        printf("Invalid size!\n");
        exit(0);
    }

    int array[size];  // Declare the array.

    for (int i = 0; i < size; i++) {
        printf("\nIndex %d: ", i);
        scanf("%d", &array[i]);  // Take user input for each element of the array.
    }

    quicksort(array, 0, size - 1);  // Call quicksort to sort the entire array.

    printf("\nSorted Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);  // Display the sorted array.
    }
    printf("\n");

    return 0;
}
