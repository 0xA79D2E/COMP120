#include <stdio.h>


void selectionSort( int array[], int size) {
    int i, j;
    int smallest;
    int temp;

    for ( i = 0; i < size - 1; ++i) {
        smallest = i;
        for (j = i+1; j < size; ++j ) {
            if (array[j] < array[smallest]) {
                smallest = j;
            }
        }

        temp = array[i];
        array[i] = array[smallest];
        array[smallest] = temp;
    }
}
int main(void) {

   int numbers[] = { 10, 2, 78, 4, 45, 32, 7, 11 };

    printf("UNSORTED: ");
    for (int i = 0; i < 8; ++i ) {
        printf("%i ", numbers[i]);
    }

    printf("\n");

    selectionSort(numbers, 8);

    printf("SORTED: ");

    for (int i = 0; i < 8; ++i) {
        printf("%i ", numbers[i]);
    }
    printf("\n");


    return 0;
}