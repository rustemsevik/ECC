#include <stdio.h>
#include <stdint.h>

void printBinary(uint32_t num, uint8_t width){
    width += 1;
    int i;

    for ( i = width - 1; i >= 0; i--)
    {
        uint32_t mask = 1 << i;
        if (num & mask)
        {
            printf("1");
        }
        else 
        {
            printf("0");
        }
    }
}
