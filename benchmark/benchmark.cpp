#ifdef __cplusplus
extern "C" {
#endif

#include "ecc.h"

#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <stdint.h>
#include <windows.h>

// @todo rdtsc
// stdin - 0, stdout - 1, stderr - 2
// .text, .bss, .stack, .heap (malloc), .data, .static

int main() {    
    uint8_t data[16384];
    uint8_t r_data[49152];
    uint8_t rr_data[16384];
    uint32_t d_length[3] = {1024, 2048, 16384};
    uint32_t r_length[3] = {3072, 6144, 49152};
    uint32_t rr_length[3] = {1024, 2048, 16384};

    for (uint16_t i = 0; i < 16384; i++)
    {
        data[i] = 0b11011010; // filled with a magic number
    }

    for (uint8_t i = 0; i < 3; i++)
    {
        LARGE_INTEGER frequency;
        LARGE_INTEGER start_time, end_time;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start_time);
        const int64_t encoded = ecc_encode(data, d_length[i], r_data, r_length[i]);
        QueryPerformanceCounter(&end_time);
    
        if (encoded > 0)
        {
            double time_taken = (double)(end_time.QuadPart - start_time.QuadPart) * 1e9 /frequency.QuadPart;
            printf("Encoding Execution Time for Data Size %d: %0.2f nanoseconds\n", d_length[i], time_taken);
        }
        else
        {
            printf("Execution terminated. Error Code: %lld\n", encoded);
        }
         
        QueryPerformanceCounter(&start_time);
        const int64_t decoded = ecc_decode(r_data, r_length[i], rr_data, rr_length[i]);
        QueryPerformanceCounter(&end_time);

        if (decoded > 0)
        {
            double time_taken = (double)(end_time.QuadPart - start_time.QuadPart) * 1e9 /frequency.QuadPart;
            printf("Decoding Execution Time for Data Size %d: %.2f nanoseconds\n", d_length[i], time_taken);

        }
        else
        {
            printf("Execution terminated. Error Code: %lld\n", decoded);
        }
    }
    
    return 0;
}