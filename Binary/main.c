#include <stdio.h>

int iterativeBinarySearch(int array[], int length, int target) {

    int low;
    int mid;
    int high;


    low = 0;

    high = length - 1;



    while (high >= low) {
        mid = (high + low) / 2;

        if (array[mid] < target) {
            low = mid + 1;
        }

    else   if (array[mid] > target) {
            high = mid - 1;
        }


        else return mid;
    }
    return -1;
}


int recursiveBinarySearch(int* array, int size, int key) {


    int low, mid, high;

    low = 0;
    high = size-1;

    while (high >= low) {
        mid = (high + low) / 2;
        if (array[mid] == key) return mid;

        if (array[mid] > key) {
            return recursiveBinarySearch(array, mid + 1, key);
        }

        return recursiveBinarySearch(array, mid - 1, key);

    }
}

int main(void) {

    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};


    int index = recursiveBinarySearch(array, sizeof(array), 9);


    if (index == -1) printf("Element not found.\n");
    else printf("Element found at index = %d\n", index);


    return 0;
}