#ifdef __cplusplus
extern "C" {
#endif

#include "ecc.h"

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


int main(){
    uint8_t data[16384];
    uint32_t d_length = 16384;    
    
    uint8_t r_data[49152];
    uint32_t r_length = 49152;

    uint8_t rr_data[16384];
    uint32_t rr_length = 16384;

    // Create random data
    srand(time(NULL));
    for (uint16_t i = 0; i < 16384; i++)
    {
        data[i] = rand();
    }

    // Write data to a file
    FILE* d_file;
    errno_t err = fopen_s(&d_file, "data.txt", "wb");
    if (err == 0) {
        size_t written = fwrite(data, sizeof(uint8_t), sizeof(data), d_file);
        if (written != sizeof(data))
        {
            printf("Error writing to file\n");
        }
        fclose(d_file);
        printf("Data written to file \"data.txt\".\n");
    } else {
        printf("Failed to open file for writing.\n");
    }

    int64_t encoded = ecc_encode(data, d_length, r_data, r_length);
    if (encoded > 0)
    {
        printf("Encoding successful. \n");
    }
    else
    {
        printf("Encoding failed. Error Code: %lld\n", encoded);
    }

    int64_t decoded = ecc_decode(r_data, r_length, rr_data, rr_length);
    if (decoded > 0)
    {
        printf("Decoding successful. \n");
    }
    else
    {
        printf("Decoding failed. Error Code: %lld\n", decoded);
    }

    // Write decoded data to a file
    FILE* r_file;
    err = fopen_s(&r_file, "decoded_data.txt", "wb");
    if (err == 0) {
        size_t written = fwrite(data, sizeof(uint8_t), sizeof(data), r_file);
        if (written != sizeof(data))
        {
            printf("Error writing to file\n");
        }
        fclose(r_file);
        printf("Decoded data written to file \"decoded_data.txt\". \n");
    } else {
        printf("Failed to open file for writing.\n");
    }

    return 0;
}