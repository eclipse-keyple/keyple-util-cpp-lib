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
 * Utility class around byte arrays
 */
class KEYPLEUTIL_API ByteArrayUtil {
public:
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
     */
    static bool isValidHexString(const std::string& hex);

    /**
     * Normalizes the input hex string by padding on the left by a zero if necessary.
     *
     * @param hex The hex string to normalize.
     * @return A not null string.
     * @throws NullPointerException If the input string is null.
     * @since 2.0.0
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
     * @see #isValidHexString(String)
     * @since 2.0.0
     */
    static std::vector<uint8_t> fromHex(const std::string& hex);

    /**
     * Converts the provided hexadecimal string into a byte.
     *
     * <p>No checks are performed on the input string, except for nullity, zero length and length
     * parity.
     *
     * @param hex The hexadecimal string to convert.
     * @return The value.
     * @throw IllegalArgumentException If the provided string is null, empty or made of an odd
     *        number of characters.
     * @see #isValidHexString(String)
     * @since 2.1.0
     */
    static uint8_t hexToByte(const std::string& hex);

    /**
     * Converts the provided hexadecimal string into a short.
     *
     * <p>No checks are performed on the input string, except for nullity, zero length and length
     * parity.
     *
     * @param hex The hexadecimal string to convert.
     * @return The value.
     * @throw IllegalArgumentException If the provided string is null, empty or made of an odd
     *        number of characters.
     * @see #isValidHexString(String)
     * @since 2.1.0
     */
    static uint16_t hexToShort(const std::string& hex);

    /**
     * Represents the byte array in a hexadecimal string.
     * Converts the provided hexadecimal string into an integer.
     *
     * @param byteArray The byte array to represent in hexadecimal.
     * @return An hexadecimal string representation of byteArray, an empty string of if the byte
     *         array is null.
     * <p>No checks are performed on the input string, except for nullity, zero length and length
     * parity.
     *
     * @param hex The hexadecimal string to convert.
     * @return The value.
     * @throw IllegalArgumentException If the provided string is null, empty or made of an odd
     *        numberof characters.
     * @see #isValidHexString(String)
     * @since 2.1.0
     */
    static uint32_t hexToInt(const std::string& hex);

    /**
     * Converts the provided hexadecimal string into a long.
     *
     * <p>No checks are performed on the input string, except for nullity, zero length and length
     * parity.
     *
     * @param hex The hexadecimal string to convert.
     * @return The value.
     * @throw IllegalArgumentException If the provided string is null, empty or made of an odd
     *        number of characters.
     * @see #isValidHexString(String)
     * @since 2.1.0
     */
    static uint64_t hexToLong(const std::string& hex);

    /**
     * Converts the provided byte array into a hexadecimal string.
     *
     * @param tab The byte array to convert.
     * @return An empty string if the byte array is null or empty.
     * @since 2.0.0
     */
    static std::string toHex(const std::vector<char>& tab);

    /**
     * Converts the provided byte array into a hexadecimal string.
     *
     * @param tab The byte array to convert.
     * @return An empty string if the byte array is null or empty.
     * @since 2.0.0
     */
    static std::string toHex(const std::vector<uint8_t>& tab);

    /**
     * Converts the provided byte into a hexadecimal string.
     *
     * @param val The value to convert.
     * @return A not empty string.
     * @since 2.1.0
     */
    static const std::string toHex(const uint8_t val);

    /**
     * Converts the provided short into a hexadecimal string.
     *
     * @param val The value to convert.
     * @return A not empty string.
     * @since 2.1.0
     */
    static const std::string toHex(const uint16_t val);

    /**
     * Converts the provided integer into a hexadecimal string.
     *
     * @param val The value to convert.
     * @return A not empty string.
     * @since 2.1.0
     */
    static const std::string toHex(const uint32_t val);

    /**
     * Converts the provided long into a hexadecimal string.
     *
     * @param val The value to convert.
     * @return A not empty string.
     * @since 2.1.0
     */
    static const std::string toHex(const uint64_t val) ;

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
     * @throw IllegalArgumentException If the buffer has a bad length or the offset is negative.
     * @since 2.0.0
     */
    static int twoBytesToInt(const std::vector<uint8_t>& bytes, const int offset);

    /**
     * Converts 2 bytes located at the offset provided in the byte array into an <b>signed</b>
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
     * @throw IllegalArgumentException If the buffer has a bad length or the offset is negative.
     * @since 2.0.0
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
     * @throw IllegalArgumentException if the buffer has a bad length
     * @since 2.0.0
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
     * @throw IllegalArgumentException if the buffer has a bad length
     * @since 2.0.0
     */
    static int threeBytesSignedToInt(const std::vector<uint8_t>& bytes, const int offset);

    /**
     * Converts 4 bytes located at the offset provided in the byte array into an <b>unsigned</b>
     * integer.
     *
     * <p>The 4 bytes are assumed to be in the of the most significant byte first order (aka 'network
     * order' or 'big-endian' or 'MSB').
     *
     * @param bytes A byte array.
     * @param offset The position of the 4 bytes in the array.
     * @return A positive int.
     * @throw IllegalArgumentException if the buffer has a bad length
     * @since 2.0.0
     */
    static int fourBytesToInt(const std::vector<uint8_t>& bytes, const int offset);

private:
    /**
     * Byte to hex string conversion table
     */
    static const std::vector<std::string> mByteToHex;

    /**
     * Hex digit to nibble conversion
     */
    static const std::vector<uint8_t> mHexToNibble;

    /**
     * (private)
     */
    static void checkBytesToIntConversionParams(const int size,
                                                const std::vector<uint8_t>& bytes,
                                                const int offset);
};

}
}
}
