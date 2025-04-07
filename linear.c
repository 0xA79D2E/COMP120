#include <stdio.h>

int linearSearch(int* array, int length, int target) {

for (int i = 0; i < length; ++i) {
if (array[i] == target) return i;
} return -1;

}


int main() {

int array[] = {9,7,4,8,2,6,1,3,5};

int x = linearSearch(array, sizeof(array), 6);

if (x == -1) printf("Element not found.\n");
else printf("Element found at index = %x\n", x);

return 0;
}