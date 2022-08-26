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
#include "HexUtil.h"
#include "IllegalArgumentException.h"
#include "KeypleAssert.h"
#include "NegativeArraySizeException.h"
#include "Pattern.h"
#include "StringBuilder.h"
#include "System.h"

namespace keyple {
namespace core {
namespace util {

using namespace keyple::core::util::cpp;
using namespace keyple::core::util::cpp::exception;

const std::vector<uint8_t> ByteArrayUtil::extractBytes(const std::vector<uint8_t>& src,
                                                       const int bitOffset,
                                                       const int nbBytes)
{
    if (bitOffset < 0) {
        throw ArrayIndexOutOfBoundsException("negative index");
    }

    if (nbBytes < 0) {
        throw NegativeArraySizeException("negative array size");
    }

    const int byteOffset = bitOffset / 8;
    int lBitOffset = bitOffset % 8;

    if (byteOffset >= static_cast<int>((src.size() - (lBitOffset ? 1 : 0)))) {
        throw ArrayIndexOutOfBoundsException("pos + offset > src size");
    }

    std::vector<uint8_t> dest(nbBytes);

    if (lBitOffset == 0) {
        System::arraycopy(src, byteOffset, dest, 0, nbBytes);
    } else {
        const int rightShift = 8 - bitOffset;
        for (int i = 0, j = byteOffset; j < byteOffset + nbBytes; i++, j++) {
            dest[i] = ((src[j] << lBitOffset) | ((src[j + 1] & 0xFF) >> rightShift));
        }
    }

    return dest;
}

uint32_t ByteArrayUtil::extractInt(const std::vector<uint8_t>& src,
                                   const int offset,
                                   const int nbBytes,
                                   const bool isSigned)
{
    if (offset < 0) {
        throw ArrayIndexOutOfBoundsException("negative offset");
    }

    if ((offset + nbBytes) > static_cast<int>(src.size())) {
        throw ArrayIndexOutOfBoundsException("offset + nbBytes > src size");
    }

    /* C++ - doesn't make sense to have nbBytes > int size */
    if (nbBytes > 4) {
        throw IllegalArgumentException("nbBytes can't be bigger than 4");
    }

    uint32_t val = 0;
    uint32_t complement = 0xFFFFFFFF;
    int lOffset = offset;
    int lNbBytes = nbBytes;
    bool negative = false;

    /* Get value */
    while (lNbBytes > 0) {
        /* Check MSB byte negativeness */
        negative = negative ? true : ((src[lOffset] & 0xFF) > 0x7F ? true : false);
        val |= ((src[lOffset++] & 0xFF) << (8 * (--lNbBytes)));
        complement &= ~(0xFF << 8 * lNbBytes);
    }

    /* If signed, add complement */
    if (isSigned && negative) {
        val |= complement;
    }

    return (uint32_t)val;
}

bool ByteArrayUtil::isValidHexString(const std::string& hex)
{
    return HexUtil::isValid(hex);
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
    Assert::getInstance().notEmpty(hex, "hex").isEqual(hex.length() % 2, 0, "hex size");

    return HexUtil::toByteArray(hex);
}

const std::string ByteArrayUtil::toHex(const std::vector<uint8_t>& src)
{
    if (src.empty()) {
        return "";
    }

    return HexUtil::toHex(src);
}

int ByteArrayUtil::twoBytesToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    return extractInt(bytes, offset, 2, false);
}

int ByteArrayUtil::twoBytesSignedToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    return extractInt(bytes, offset, 2, true);
}

int ByteArrayUtil::threeBytesToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    return extractInt(bytes, offset, 3, false);
}

int ByteArrayUtil::threeBytesSignedToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    return extractInt(bytes, offset, 3, true);
}

int ByteArrayUtil::fourBytesToInt(const std::vector<uint8_t>& bytes, const int offset)
{
    return extractInt(bytes, offset, 4, true);
}

}
}
}
