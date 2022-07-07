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

#include "ByteArrayUtil.h"

/* Keyple Core Util */
#include "Character.h"
#include "IllegalArgumentException.h"
#include "KeypleAssert.h"
#include "Pattern.h"
#include "StringBuilder.h"

namespace keyple {
namespace core {
namespace util {

using namespace keyple::core::util::cpp;
using namespace keyple::core::util::cpp::exception;

const std::vector<std::string> ByteArrayUtil::mByteToHex = {
    "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F",
    "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1A", "1B", "1C", "1D", "1E", "1F",
    "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "2A", "2B", "2C", "2D", "2E", "2F",
    "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3A", "3B", "3C", "3D", "3E", "3F",
    "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4A", "4B", "4C", "4D", "4E", "4F",
    "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5A", "5B", "5C", "5D", "5E", "5F",
    "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6A", "6B", "6C", "6D", "6E", "6F",
    "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7A", "7B", "7C", "7D", "7E", "7F",
    "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8A", "8B", "8C", "8D", "8E", "8F",
    "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9A", "9B", "9C", "9D", "9E", "9F",
    "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "AA", "AB", "AC", "AD", "AE", "AF",
    "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "BA", "BB", "BC", "BD", "BE", "BF",
    "C0", "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "CA", "CB", "CC", "CD", "CE", "CF",
    "D0", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "DA", "DB", "DC", "DD", "DE", "DF",
    "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "EA", "EB", "EC", "ED", "EE", "EF",
    "F0", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "FA", "FB", "FC", "FD", "FE", "FF"
};

const std::vector<uint8_t> ByteArrayUtil::mHexToNibble = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

bool ByteArrayUtil::isValidHexString(const std::string& hex)
{
    if (hex.length() == 0 || hex.length() % 2 != 0) {
        return false;
    }

    for (int i = 0; i < static_cast<int>(hex.length()); i++) {
        if (static_cast<char>(mHexToNibble[hex.at(i)]) < 0) {
            return false;
        }
    }

    return true;
}

const std::string ByteArrayUtil::normalizeHexString(const std::string& hex)
{
    if (hex.length() % 2 != 0) {
        return "0" + hex;
    }

    return hex;
}

std::vector<uint8_t> ByteArrayUtil::fromHex(const std::string& hex)
{
    Assert::getInstance().notEmpty(hex, "hex").isEqual(hex.length() % 2, 0, "hex");
    std::vector<uint8_t> tab(hex.length() / 2);

    for (int i = 0; i < (int)hex.length(); i += 2) {
        tab[i / 2] = ((mHexToNibble[hex.at(i)] << 4) + (mHexToNibble[hex.at(i + 1)] & 0xFF));
    }

    return tab;
}

uint8_t ByteArrayUtil::hexToByte(const std::string& hex)
{
    Assert::getInstance().notEmpty(hex, "hex").isEqual(hex.length(), 2, "hex");

    return ((mHexToNibble[hex.at(0)] << 4) + (mHexToNibble[hex.at(1)] & 0xFF));
}

uint16_t ByteArrayUtil::hexToShort(const std::string& hex)
{
    Assert::getInstance().notEmpty(hex, "hex")
                         .isEqual(hex.length() % 2, 0, "hex")
                         .isTrue(hex.length() <= 4, "hex");

    uint16_t val = 0;
    for (int i = 0; i < static_cast<int>(hex.length()); i++) {
        val <<= 4;
        val |= (mHexToNibble[hex.at(i)] & 0xFF);
    }

    return val;
}

uint32_t ByteArrayUtil::hexToInt(const std::string& hex)
{
    Assert::getInstance().notEmpty(hex, "hex")
                         .isEqual(hex.length() % 2, 0, "hex")
                         .isTrue(hex.length() <= 8, "hex");
    uint32_t val = 0;
    for (int i = 0; i < static_cast<int>(hex.length()); i++) {
        val <<= 4;
        val |= (mHexToNibble[hex.at(i)] & 0xFF);
    }

    return val;
}

uint64_t ByteArrayUtil::hexToLong(const std::string& hex)
{
    Assert::getInstance().notEmpty(hex, "hex")
                         .isEqual(hex.length() % 2, 0, "hex")
                         .isTrue(hex.length() <= 16, "hex");
    uint64_t val = 0;
    for (int i = 0; i < static_cast<int>(hex.length()); i++) {
        val <<= 4;
        val |= (mHexToNibble[hex.at(i)] & 0xFF);
    }

    return val;
}

std::string ByteArrayUtil::toHex(const std::vector<char>& tab)
{
    if (tab.empty()) {
        return "";
    }

    auto sb = std::make_shared<StringBuilder>();
    for (const auto& b : tab) {
        sb->append(mByteToHex[b & 0xFF]);
    }

    return sb->toString();
}

std::string ByteArrayUtil::toHex(const std::vector<uint8_t>& tab)
{
    if (tab.empty()) {
        return "";
    }

    auto sb = std::make_shared<StringBuilder>();
    for (const auto& b : tab) {
        sb->append(mByteToHex[b & 0xFF]);
    }

    return sb->toString();
}

const std::string ByteArrayUtil::toHex(const uint8_t val)
{
    return mByteToHex[val & 0xFF];
}

const std::string ByteArrayUtil::toHex(const uint16_t val)
{
    if ((val & 0xFF00) == 0) {
        return mByteToHex[val & 0xFF];

    } else {
        return mByteToHex[val >> 8 & 0xFF] +
               mByteToHex[val & 0xFF];
    }
}

const std::string ByteArrayUtil::toHex(const uint32_t val)
{
    if ((val & 0xFFFFFF00) == 0) {
        return mByteToHex[val & 0xFF];

    } else if ((val & 0xFFFF0000) == 0) {
        return mByteToHex[val >> 8 & 0xFF] +
               mByteToHex[val & 0xFF];

    } else if ((val & 0xFF000000) == 0) {
        return mByteToHex[val >> 16 & 0xFF] +
               mByteToHex[val >> 8 & 0xFF] +
               mByteToHex[val & 0xFF];

    } else {
        return mByteToHex[val >> 24 & 0xFF] +
               mByteToHex[val >> 16 & 0xFF] +
               mByteToHex[val >> 8 & 0xFF] +
               mByteToHex[val & 0xFF];
    }
}

const std::string ByteArrayUtil::toHex(const uint64_t val)
{
    if ((val & 0xFFFFFFFFFFFFFF00L) == 0) {
        return mByteToHex[(int) (val & 0xFF)];

    } else if ((val & 0xFFFFFFFFFFFF0000L) == 0) {
        return mByteToHex[(int) (val >> 8 & 0xFF)] +
               mByteToHex[(int) (val & 0xFF)];

    } else if ((val & 0xFFFFFFFFFF000000L) == 0) {
        return mByteToHex[(int) (val >> 16 & 0xFF)] +
               mByteToHex[(int) (val >> 8 & 0xFF)] +
               mByteToHex[(int) (val & 0xFF)];

    } else if ((val & 0xFFFFFFFF00000000L) == 0) {
        return mByteToHex[(int) (val >> 24 & 0xFF)] +
               mByteToHex[(int) (val >> 16 & 0xFF)] +
               mByteToHex[(int) (val >> 8 & 0xFF)] +
               mByteToHex[(int) (val & 0xFF)];

    } else if ((val & 0xFFFFFF0000000000L) == 0) {
        return mByteToHex[(int) (val >> 32 & 0xFF)] +
               mByteToHex[(int) (val >> 24 & 0xFF)] +
               mByteToHex[(int) (val >> 16 & 0xFF)] +
               mByteToHex[(int) (val >> 8 & 0xFF)] +
               mByteToHex[(int) (val & 0xFF)];

    } else if ((val & 0xFFFF000000000000L) == 0) {
        return mByteToHex[(int) (val >> 40 & 0xFF)] +
               mByteToHex[(int) (val >> 32 & 0xFF)] +
               mByteToHex[(int) (val >> 24 & 0xFF)] +
               mByteToHex[(int) (val >> 16 & 0xFF)] +
               mByteToHex[(int) (val >> 8 & 0xFF)] +
               mByteToHex[(int) (val & 0xFF)];

    } else if ((val & 0xFF00000000000000L) == 0) {
        return mByteToHex[(int) (val >> 48 & 0xFF)] +
               mByteToHex[(int) (val >> 40 & 0xFF)] +
               mByteToHex[(int) (val >> 32 & 0xFF)] +
               mByteToHex[(int) (val >> 24 & 0xFF)] +
               mByteToHex[(int) (val >> 16 & 0xFF)] +
               mByteToHex[(int) (val >> 8 & 0xFF)] +
               mByteToHex[(int) (val & 0xFF)];

    } else {
        return mByteToHex[(int) (val >> 56 & 0xFF)] +
               mByteToHex[(int) (val >> 48 & 0xFF)] +
               mByteToHex[(int) (val >> 40 & 0xFF)] +
               mByteToHex[(int) (val >> 32 & 0xFF)] +
               mByteToHex[(int) (val >> 24 & 0xFF)] +
               mByteToHex[(int) (val >> 16 & 0xFF)] +
               mByteToHex[(int) (val >> 8 & 0xFF)] +
               mByteToHex[(int) (val & 0xFF)];
    }
}

void ByteArrayUtil::checkBytesToIntConversionParams(const int size,
                                                    const std::vector<uint8_t>& bytes,
                                                    const int offset)
{
    if (!bytes.size()) {
        throw IllegalArgumentException("bytes");
    } else if ((int)bytes.size() < offset + size) {
        throw IllegalArgumentException("length");
    } else if (offset < 0) {
        throw IllegalArgumentException("offset");
    }
}

int ByteArrayUtil::twoBytesToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    checkBytesToIntConversionParams(2, bytes, offset);

    return (bytes[offset] & 0xFF) << 8 | (bytes[offset + 1] & 0xFF);
}

int ByteArrayUtil::twoBytesSignedToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    checkBytesToIntConversionParams(2, bytes, offset);

    if (static_cast<int8_t>(bytes[offset]) >= 0) {
        /* Positive number */
        return (bytes[offset] & 0xFF) << 8 | (bytes[offset + 1] & 0xFF);
    } else {
        /* Negative number */
        return 0xFFFF0000 | (bytes[offset] & 0xFF) << 8 | (bytes[offset + 1] & 0xFF);
    }
}

int ByteArrayUtil::threeBytesToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    checkBytesToIntConversionParams(3, bytes, offset);

    return ((static_cast<int>(bytes[offset    ])) << 16) +
           ((static_cast<int>(bytes[offset + 1])) <<  8) +
            (static_cast<int>(bytes[offset + 2]));
}

int ByteArrayUtil::threeBytesSignedToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    checkBytesToIntConversionParams(3, bytes, offset);

    if (static_cast<int8_t>(bytes[offset]) >= 0) {
        /* Positive number */
        return (bytes[offset    ] & 0xFF) << 16 |
               (bytes[offset + 1] & 0xFF) <<  8 |
               (bytes[offset + 2] & 0xFF);
    } else {
        /* Negative number */
        return 0xFF000000                       |
               (bytes[offset    ] & 0xFF) << 16 |
               (bytes[offset + 1] & 0xFF) <<  8 |
               (bytes[offset + 2] & 0xFF);
    }
}

int ByteArrayUtil::fourBytesToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    checkBytesToIntConversionParams(4, bytes, offset);

    return (bytes[offset    ] & 0xFF) << 24 |
           (bytes[offset + 1] & 0xFF) << 16 |
           (bytes[offset + 2] & 0xFF) <<  8 |
           (bytes[offset + 3] & 0xFF);
}

}
}
}
