/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/* Util */
#include "Pattern.h"

/* Core */
#include "KeypleUtilExport.h"

namespace keyple {
namespace core {
namespace util {

/**
 * Utility class around byte arrays.
 */
class KEYPLEUTIL_API ByteArrayUtil {
public:
      /**
     * Extracts "nbBytes" bytes from the "bitOffset" index (<b>in bits</b>) from a byte array.
     *
     * @param src The source byte array.
     * @param bitOffset The offset (<b>in bits</b>).
     * @param nbBytes The number of bytes to extract.
     * @return A not null byte array.
     * @throws ArrayIndexOutOfBoundsException If "bitOffset" or "nbBytes" is out of range.
     * @throws NegativeArraySizeException If "nbBytes" is negative.
     * @since 2.1.0
     */
    static const std::vector<uint8_t> extractBytes(const std::vector<uint8_t>& src,
                                                   const int bitOffset,
                                                   const int nbBytes);


    /**
     * Converts "nbBytes" bytes located at the "offset" provided in a source byte array into an
     * integer.
     *
     * <p>Caution: the result may be erroneous if "nbBytes" is not in range [1..4].
     *
     * @param src The source byte array.
     * @param offset The offset (in bytes).
     * @param nbBytes The number of bytes to extract.
     * @param isSigned True if the resulting integer is "signed" (relevant only if "nbBytes" is in
     *     range [1..3]).
     * @return An int.
     * @throws ArrayIndexOutOfBoundsException If "offset" is not in range [0..(src.length-nbBytes)]
     * @since 2.1.0
     */
    static uint32_t extractInt(const std::vector<uint8_t>& src,
                               const int offset,
                               const int nbBytes,
                               const bool isSigned);

    /**
     * Checks if the provided string is formed by an even number of hexadecimal digits. <br>
     *
     * <ul>
     *   <li>{@code "1234AB"} will match.
     *   <li>{@code "1234AB2"}, {@code "12 34AB"} or {@code "x1234AB"} won't match.
     * </ul>
     *
     * @param hex A string.
     * @return true if the string matches the expected hexadecimal representation, false otherwise.
     * @since 2.0.0
     * @deprecated Use {@link HexUtil#isValid(String)} method instead.
     */
    static bool isValidHexString(const std::string& hex);

    /**
     * Normalizes the input hex string by padding on the left by a zero if necessary.
     *
     * @param hex The hex string to normalize.
     * @return A not null string.
     * @throws NullPointerException If the input string is null.
     * @since 2.0.0
     * @deprecated To be removed.
     */
    static const std::string normalizeHexString(const std::string& hex);

    /**
     * Create a byte array from an hexadecimal string made of consecutive even number of digits in
     * the range {0..9,a..f,A..F}.
     *
     * <p>No checks are performed on the input string, except for nullity, zero length and length
     * parity.
     *
     * @param hex The hexadecimal string to convert.
     * @return A not empty byte array.
     * @throw IllegalArgumentException If the provided string is null, empty or made of an odd
     *        number of characters.
     * @see isValidHexString(const std::string&)
     * @since 2.0.0
     * @deprecated Use HexUtil::toByteArray(const std::string&) method instead.
     */
    static std::vector<uint8_t> fromHex(const std::string& hex);

    /**
     * Converts the provided byte array into a hexadecimal string.
     *
     * @param src The byte array to convert.
     * @return An empty string if the byte array is null or empty.
     * @since 2.0.0
     * @deprecated Use HexUtil::toHex(const std::vector<uint8_t>&) method instead.
     */
    static const std::string toHex(const std::vector<uint8_t>& src);

    /**
     * Converts 2 bytes located at the offset provided in the byte array into an <b>unsigned</b>
     * integer.
     *
     * <p>The 2 bytes are assumed to be in the of the most significant byte first order (aka
     * 'network order' or 'big-endian' or 'MSB').
     *
     * @param bytes A byte array.
     * @param offset The position of the 2 bytes in the array.
     * @return A positive int.
     * @throw ArrayIndexOutOfBoundsException If "offset" is not in range [0..(bytes.length-2)]
     * @since 2.0.0
     * @deprecated Use extractInt(const std::vector<uint8_t>&, int, int, boolean) method instead
     *             with "nbBytes = 2" and "isSigned = false".
     */
    static int twoBytesToInt(const std::vector<uint8_t>& bytes, const int offset);

    /**
     * Converts 2 bytes located at the offset provided in the byte array into a <b>signed</b>
     * integer.
     *
     * <p>The 2 bytes are assumed to be in the of the most significant byte first order (aka
     * 'network order' or 'big-endian' or 'MSB').
     *
     * <p>The number is also considered as signed. That is, if the MSB (first left bit) is 1, then
     * the number is negative and the conversion is done accordingly with the usual binary
     * arithmetic.
     *
     * @param bytes A byte array.
     * @param offset The position of the 2 bytes in the array.
     * @return A negative or positive int.
     * @throw ArrayIndexOutOfBoundsException If "offset" is not in range [0..(bytes.length-3)]
     * @since 2.0.0
     * @deprecated Use extractInt(const std::vector<uint8_t>&, int, int, boolean) method instead
     *             with "nbBytes = "2" and "isSigned = true".
     */
    static int twoBytesSignedToInt(const std::vector<uint8_t>& bytes, const int offset);

    /**
     * Converts 3 bytes located at the offset provided in the byte array into an <b>unsigned</b>
     * integer.
     *
     * <p>The 3 bytes are assumed to be in the of the most significant byte first order (aka
     * 'network order' or 'big-endian' or 'MSB').
     *
     * @param bytes A byte array.
     * @param offset The position of the 3 bytes in the array.
     * @return A positive int.
     * @throw ArrayIndexOutOfBoundsException If "offset" is not in range [0..(bytes.length-3)]
     * @since 2.0.0
     * @deprecated Use extractInt(const std::vector<uint8_t>&, int, int, boolean) method instead
     *             with "nbBytes = 3" and "isSigned = false".
     */
    static int threeBytesToInt(const std::vector<uint8_t>& bytes, const int offset);

    /**
     * Converts 3 bytes located at the offset provided in the byte array into an <b>signed</b>
     * integer.
     *
     * <p>The 3 bytes are assumed to be in the of the most significant byte first order (aka
     * 'network order' or 'big-endian' or 'MSB').
     *
     * <p>The number is also considered as signed. That is, if the MSB (first left bit) is 1, then
     * the number is negative and the conversion is done accordingly with the usual binary
     * arithmetic.
     *
     * @param bytes A byte array.
     * @param offset The position of the 3 bytes in the array.
     * @return A positive int.
     * @throw ArrayIndexOutOfBoundsException If "offset" is not in range [0..(bytes.length-3)]
     * @since 2.0.0
     * @deprecated Use extractInt(const std::vector<uint8_t>&, int, int, boolean) method instead
     *             with "nbBytes = "3" and "isSigned = true".
     */
    static int threeBytesSignedToInt(const std::vector<uint8_t>& bytes, const int offset);

    /**
     * Converts 4 bytes located at the offset provided in the byte array into an <b>unsigned</b>
     * integer.
     *
     * <p>The 4 bytes are assumed to be in the of the most significant byte first order (aka
     * 'network order' or 'big-endian' or 'MSB').
     *
     * @param bytes A byte array.
     * @param offset The position of the 4 bytes in the array.
     * @return A positive int.
     * @throw ArrayIndexOutOfBoundsException If "offset" is not in range [0..(bytes.length-3)]
     * @since 2.0.0
     * @deprecated Use extractInt(const std::vector<uint8_t>&, int, int, boolean) method instead
     *             with "nbBytes = 4" and "isSigned = true|false".
     */
    static int fourBytesToInt(const std::vector<uint8_t>& bytes, const int offset);
};

}
}
}
