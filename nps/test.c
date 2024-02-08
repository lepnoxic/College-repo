#include <stdio.h>
#define CRC_POLYNOMIAL 0x80F


void printBinary(int num) {
    printf("0b");
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

int main() {
	unsigned char current[] = { 0b010101000, '\0' };
    current[0] = current[0] << 3;
    printBinary(current[0]);
	return 0;
}