/**
 * @file ecc.h
 * @brief 3-bit ECC implementation for error correction on little-endian systems
 * @author M. Rustem Sevik
 * @date [current date]
 * @attention For use on little-endian systems only
 */

#ifndef ECC_H_
#define ECC_H_

#include <stdint.h>
#include "ecc_util.h"
#include "ecc_err.h"

/**
 * @brief Encodes the source data using 3-bit ECC
 * @remark The size of the destination buffer should be at least src_size * 3
 * @remark The source length should be less than 2^32 - 2
 * @param [in] src_data - source buffer that contains raw data
 * @param [in] src_length - length of the source data
 * @param [inout] dst_data - destination buffer to store the encoded data
 * @param [in] dst_length - length of the destination buffer
 * @return error code if failed, otherwise used length of the destination buffer
 */
int64_t ecc_encode(const uint8_t *src_data, const uint32_t src_length, uint8_t *dst_data, const uint32_t dst_length);

/**
 * @brief Decodes the source data using 3-bit ECC
 * @remark The size of the destination buffer should be at least src_size / 3
 * @remark The source length should be less than 2^32 - 2
 * @param [in] src_data - source buffer that contains the encoded data
 * @param [in] src_length - length of the source data
 * @param [inout] dst_data - destination buffer to store the decoded data
 * @param [in] dst_length - length of the destination buffer
 * @return error code if failed, otherwise used length of the destination buffer
 */
int64_t ecc_decode(const uint8_t *src_data, const uint32_t src_length, uint8_t *dst_data, const uint32_t dst_length);

#endif //ECC_H_