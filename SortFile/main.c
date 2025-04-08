/**
 * Reads a file containing a set of up to 1000 integers, sorts in ascending order it with selection sort, and overwrites file with sorted sequence.
 *
 */
#include <stdio.h>


void selectionSort(int array[], int size) {
    int i, j, smallest, temp;
    

    for (i = 0; i < size - 1; ++i) {
        smallest = i;

        for (j = i + 1; j < size; ++j) {
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
    fprintf(stdout, "Enter file path (without quotes): ");

    char path[256];

    fscanf(stdin, "%s", path);

    FILE *inFile = NULL;

    // FILE* outFile = NULL;


    int num;

    inFile = fopen(path, "r+");
    // outFile = fopen("C:\\Users\\Admin\\Desktop\\num_sorted.txt", "w");

    if (inFile == NULL) {
        printf("Could not open input file. \n");
        return -1;
    }

    // if (outFile == NULL) {
    //     printf("Could not open output file. \n");
    //     return -1;
    // }


    int array[1000];

    int i = 0;
    fscanf(inFile, "%d", &num);
    array[i++] = num;
    while (i < 1000 && fscanf(inFile, "%d", &num) == 1 && num != -1) {
        array[i++] = num;
    }

    fclose(inFile);

    for (int j = 0; j < i; ++j) {
        printf("%d ", array[j]);
    }


    printf("\n\n");


    selectionSort(array, i);

    for (int j = 0; j < i; ++j) {
        printf("%d ", array[j]);
    }


    FILE *outFile = NULL;

    outFile = fopen(path, "w");

    if (outFile == NULL) {
        printf("Unable to open output file.\n");
        return -1;
    }

    for (int j = 0; j < i; ++j) {
        fprintf(outFile, "%d\n", array[j]);
    }

    fprintf(outFile, "-1");


    fclose(outFile);

    return 0;
}
