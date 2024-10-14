#ifdef __cplusplus
extern "C" {
#endif

#include "ecc.h"

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <stdint.h>

int main(){
    const uint8_t data[3] = {0b11010101, 0b11010100, 0b11010111};
    const uint32_t d_length = 3;
    uint8_t r_data[9];
    const uint32_t r_length = 9;

    uint8_t rr_data[3];
    const uint32_t rr_length = 3;

    printf("Data: {");
    for (uint32_t i = 0; i < d_length; i++)
    {
            printBinary(data[i], 7);
            printf(" ");
    }
    printf("}\n");


    int64_t encoded = ecc_encode(data, d_length, r_data, r_length);
    
    if (encoded > 0)
    {
        printf("ECC encoded: {");
        for (uint32_t i = 0; i < encoded; i++)
        {
            printBinary(r_data[i], 7);
            printf(" ");
        }
        printf("}\n");
    }
    else
    {
        printf("ERROR CODE: %lld \n", encoded);
    }
    
    int64_t decoded = ecc_decode(r_data, r_length, rr_data, rr_length);
    
    if (decoded > 0)
    {    
        printf("ECC decoded: {");
        for (uint32_t i = 0; i < decoded; i++)
        {
            printBinary(rr_data[i], 7);
            printf(" ");
        }
        printf("}\n");
    }
    else
    {
        printf("ERROR CODE: %lld \n", encoded);
    }

    return 0;
}
