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
#include <string>
#include <vector>

namespace keyple {
namespace core {
namespace util {

class HexUtil final {
public:
    /**
     * Checks if a string is formed by an even number of hexadecimal digits.
     *
     * <ul>
     *   <li>{@code "1234AB"} will match.
     *   <li>{@code "1234AB2"}, {@code "12 34AB"} or {@code "x1234AB"} won't match.
     * </ul>
     *
     * @param hex The string to check.
     * @return True if the string matches the expected hexadecimal representation, false otherwise.
     * @since 2.1.0
     */
    static bool isValid(const std::string& hex);

    /**
     * Converts a hexadecimal string to a byte array.
     *
     * <p>Caution: the result may be erroneous if the string does not contain only hexadecimal
     * characters.
     *
     * @param hex The hexadecimal string to convert.
     * @return An empty byte array if the input string is empty.
     * @throw StringIndexOutOfBoundsException If the input string is made of an odd number of
     *        characters.
     * @since 2.1.0
     */
    static const std::vector<uint8_t> toByteArray(const std::string& hex);

    /**
     * Converts a hexadecimal string to a "byte".
     *
     * <p>Note: if the hexadecimal string contains more than two characters, then only the last two
     * characters will be taken into account. In this case, please note that the conversion
     * processing will be less performant.
     *
     * <p>Caution: the result may be erroneous if the string does not contain only hexadecimal
     * characters.
     *
     * @param hex The hexadecimal string to convert.
     * @return 0 if the input string is empty.
     * @since 2.1.0
     */
    static uint8_t toByte(const std::string& hex);

    /**
     * Converts a hexadecimal string to a "short".
     *
     * <p>Note: if the hexadecimal string contains more than four characters, then only the last
     * four characters will be taken into account. In this case, please note that the conversion
     * processing will be less performant.
     *
     * <p>Caution: the result may be erroneous if the string does not contain only hexadecimal
     * characters.
     *
     * @param hex The hexadecimal string to convert.
     * @return 0 if the input string is empty.
     * @throws NullPointerException If the input string is null.
     * @since 2.1.0
     */
    static uint16_t toShort(const std::string& hex);

    /**
     * Converts a hexadecimal string to an "integer".
     *
     * <p>Note: if the hexadecimal string contains more than eight characters, then only the last
     * eight characters will be taken into account. In this case, please note that the conversion
     * processing will be less performant.
     *
     * <p>Caution: the result may be erroneous if the string does not contain only hexadecimal
     * characters.
     *
     * @param hex The hexadecimal string to convert.
     * @return 0 if the input string is empty.
     * @since 2.1.0
     */
    static uint32_t toInt(const std::string& hex);

    /**
     * Converts a hexadecimal string to a "long".
     *
     * <p>Note: if the hexadecimal string contains more than sixteen characters, then only the last
     * sixteen characters will be taken into account. In this case, please note that the conversion
     * processing will be less performant.
     *
     * <p>Caution: the result may be erroneous if the string does not contain only hexadecimal
     * characters.
     *
     * @param hex The hexadecimal string to convert.
     * @return 0 if the input string is empty.
     * @since 2.1.0
     */
    static uint64_t toLong(const std::string& hex);

    /**
     * Converts a byte array to a hexadecimal string.
     *
     * @param tab The byte array to convert.
     * @return A string with a size equal to (2 * size of the input array).
     * @since 2.1.0
     */
    static const std::string toHex(const std::vector<uint8_t>& tab);

    /**
     * Converts a "byte" to a hexadecimal string.
     *
     * @param val The byte to convert.
     * @return A string containing 2 characters.
     * @since 2.1.0
     */
    static const std::string toHex(const uint8_t val);

    /**
     * Converts a "short" to a hexadecimal string.
     *
     * <p>Note: the returned string has an even length and is left truncated if necessary to keep
     * only the significant characters.
     *
     * @param val The short to convert.
     * @return A string containing 2 or 4 characters.
     * @since 2.1.0
     */
    static const std::string toHex(const uint16_t val);

    /**
     * Converts an "integer" to a hexadecimal string.
     *
     * <p>Note: the returned string has an even length and is left truncated if necessary to keep
     * only the significant characters.
     *
     * @param val The integer to convert.
     * @return A string containing 2, 4, 6 or 8 characters.
     * @since 2.1.0
     */
    static const std::string toHex(const uint32_t val);

    /**
     * Converts a "long" to a hexadecimal string.
     *
     * <p>Note: the returned string has an even length and is left truncated if necessary to keep
     * only the significant characters.
     *
     * @param val The long to convert.
     * @return A string containing 2, 4, 6, 8, 10, 12, 14 or 16 characters.
     * @since 2.1.0
     */
    static const std::string toHex(const uint64_t val);

private:
    /**
     * Byte to hex string conversion table
     */
    static const std::vector<std::string> mByteToHex;

    /**
     * Hex digit to nibble conversion table
     */
    static const std::vector<uint8_t> mHexToNibble;

    /**
     *
     */
    HexUtil();
};

}
}
}
