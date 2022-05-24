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
 * Utils around byte arrays
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
     * @param hexString A string.
     * @return true if the string matches the expected hexadecimal representation, false otherwise.
     */
    static bool isValidHexString(const std::string& hexString);

    /**
     * Create a byte array from an hexadecimal string made of consecutive even number of digits in
     * the range {0..9,a..f,A..F}.
     *
     * <p>No checks are performed on the input string, except for nullity, zero length and length
     * parity.
     *
     * @param hex An hexadecimal string.
     * @return A reference of not empty of byte array.
     * @throw IllegalArgumentException If the provided string is null, empty or made of an odd
     *        number of characters.
     * @see #isValidHexString(String)
     * @since 2.0.0
     */
    static std::vector<uint8_t> fromHex(const std::string& hex);

    /**
     * Represents the byte array in a hexadecimal string.
     *
     * @param byteArray The byte array to represent in hexadecimal.
     * @return An hexadecimal string representation of byteArray, an empty string of if the byte
     *         array is null.
     * @since 2.0.0
     */
    static std::string toHex(const std::vector<char>& byteArray);

    /**
     * Represents the byte array in a hexadecimal string.
     *
     * @param byteArray The byte array to represent in hexadecimal.
     * @return An hexadecimal string representation of byteArray, an empty string of if the byte
     *         array is null.
     * @since 2.0.0
     */
    static std::string toHex(const std::vector<uint8_t>& byteArray);

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
    static const std::vector<std::string> byteToHex;

    /**
     *
     */
    static const std::string HEXA_REGEX;

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
