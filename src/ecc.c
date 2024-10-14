#include <stdint.h>
#include "ecc.h"
#include "ecc_util.h"
#include "ecc_err.h"

int64_t ecc_encode(const uint8_t *src_data, const uint32_t src_length, uint8_t *dst_data, const uint32_t dst_length){
    if (!src_data || !dst_data)
    {
        return NULLITY_ERROR;
    }
    
    if ((dst_length < 3*src_length ) || (src_length < 1))
    {
        return LENGTH_ERROR;
    }
    
    uint32_t used_dst_length = 3*src_length; 
    uint32_t src_byte_expanded;

    for (uint32_t i = 0; i < src_length; i++)
    {
        src_byte_expanded = 0;

        for (uint8_t j = 0; j < 8; j++)
        {
            _Bool bit = (src_data[i] >> (7 - j)) & 1; // most significant bit
            src_byte_expanded <<= 3;
            if (bit)
            {
                src_byte_expanded += 7; // src_byte_expanded += 0b111
            }        
        }
        for (uint8_t k = 0; k < 3; k++)
        {
            dst_data[3*i + (2-k)] = src_byte_expanded & 255; // src_byte_expanded & 0b11111111;
            src_byte_expanded >>= 8;
        }
    }
    return used_dst_length;
}

int64_t ecc_decode(const uint8_t *src_data, const uint32_t src_length, uint8_t *dst_data, const uint32_t dst_length){
    if (!src_data || !dst_data)
    {
        return NULLITY_ERROR;
    }
    
    if ((dst_length < src_length / 3) || (src_length < 3))
    {
        return LENGTH_ERROR;
    }
    
    uint32_t used_dst_length = src_length / 3;
    
    uint8_t bitSum = 0;
    uint32_t united = 0;

    for (uint32_t i = 0; i < used_dst_length; i++)
    {
        for (uint8_t j = 0; j < 3; j++)
        {
            united <<= 8;
            united = united ^ src_data[3*i+j];
        }
        
        for (uint8_t j = 0; j < 8; j++)
        {
            for (uint8_t k = 0; k < 3; k++) // 3 bit ecc
            {   
                bitSum += united & 1; // least significant bit
                united >>= 1;
            }

            dst_data[i] >>= 1;

            if (bitSum >=2)
            {
                dst_data[i] ^= 128; // dst_data[i] ^= 0b10000000
            }
            
            bitSum = 0;
        }
    }
    return used_dst_length;
}