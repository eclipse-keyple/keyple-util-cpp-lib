/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * See the NOTICE file(s) distributed with this work for additional           *
 * information regarding copyright ownership.                                 *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the Eclipse Public License 2.0 which is available at              *
 * http://www.eclipse.org/legal/epl-2.0                                       *
 *                                                                            *
 * SPDX-License-Identifier: EPL-2.0                                           *
 ******************************************************************************/

#include "keyple/core/util/BerTlvUtil.hpp"

#include <map>
#include <vector>

#include "keyple/core/util/cpp/Arrays.hpp"
#include "keyple/core/util/cpp/exception/IllegalArgumentException.hpp"
#include "keyple/core/util/cpp/exception/IndexOutOfBoundsException.hpp"

namespace keyple {
namespace core {
namespace util {

using keyple::core::util::cpp::Arrays;
using keyple::core::util::cpp::exception::IllegalArgumentException;
using keyple::core::util::cpp::exception::IndexOutOfBoundsException;

BerTlvUtil::BerTlvUtil()
{
}

const std::map<const int, const std::vector<uint8_t>>
BerTlvUtil::parseSimple(
    const std::vector<uint8_t>& tlvStructure, const bool primitiveOnly)
{
    try {
        return parseBufferSimple(tlvStructure, primitiveOnly);
    } catch (const IndexOutOfBoundsException& e) {
        (void)e;
        throw IllegalArgumentException("Invalid TLV structure.");
    }
}

const std::map<const int, std::vector<std::vector<uint8_t>>>
BerTlvUtil::parse(
    const std::vector<uint8_t>& tlvStructure, const bool primitiveOnly)
{
    try {
        return parseBuffer(tlvStructure, primitiveOnly);
    } catch (const IndexOutOfBoundsException& e) {
        (void)e;
        throw IllegalArgumentException("Invalid TLV structure.");
    }
}

bool
BerTlvUtil::isConstructed(const int tagId)
{
    if (tagId < 0 || tagId > 0xFFFFFF) {
        throw IllegalArgumentException("Tag Id out of range.");
    }

    if (tagId <= 0xFF) {
        return (tagId & 0x20) != 0;
    }

    if (tagId <= 0xFFFF) {
        return (tagId & 0x2000) != 0;
    }

    return (tagId & 0x200000) != 0;
}

const std::map<const int, const std::vector<uint8_t>>
BerTlvUtil::parseBufferSimple(
    const std::vector<uint8_t>& tlvStructure, const bool primitiveOnly)
{
    std::map<const int, const std::vector<uint8_t>> tlvs;
    int offset = 0;

    do {
        const int tagSize = getTagSize(tlvStructure, offset);
        const std::vector<uint8_t> tagBytes
            = Arrays::copyOfRange(tlvStructure, offset, offset + tagSize);
        const int tag = getTag(tlvStructure, offset, tagSize);
        const int lengthSize = getLengthSize(tlvStructure, offset + tagSize);
        const int valueSize
            = getLength(tlvStructure, offset + tagSize, lengthSize);
        const std::vector<uint8_t> value = Arrays::copyOfRange(
            tlvStructure,
            offset + tagSize + lengthSize,
            offset + tagSize + lengthSize + valueSize);

        offset += tagSize + lengthSize + valueSize;

        if ((tagBytes[0] & 0x20) != 0) {
            /* Tag is constructed */
            if (!primitiveOnly) {
                tlvs.insert({tag, value});
            }

            const std::map<const int, const std::vector<uint8_t>> parse
                = parseSimple(value, primitiveOnly);
            tlvs.insert(parse.begin(), parse.end());
        } else {
            /* Tag is primitive */
            tlvs.insert({tag, value});
        }
    } while (offset < static_cast<int>(tlvStructure.size()));

    return tlvs;
}

const std::map<const int, std::vector<std::vector<uint8_t>>>
BerTlvUtil::parseBuffer(
    const std::vector<uint8_t>& tlvStructure, const bool primitiveOnly)
{
    std::map<const int, std::vector<std::vector<uint8_t>>> tlvs;
    int offset = 0;

    do {
        const int tagSize = getTagSize(tlvStructure, offset);
        const std::vector<uint8_t> tagBytes
            = Arrays::copyOfRange(tlvStructure, offset, offset + tagSize);
        const int tag = getTag(tlvStructure, offset, tagSize);
        const int lengthSize = getLengthSize(tlvStructure, offset + tagSize);
        const int valueSize
            = getLength(tlvStructure, offset + tagSize, lengthSize);
        const std::vector<uint8_t> value = Arrays::copyOfRange(
            tlvStructure,
            offset + tagSize + lengthSize,
            offset + tagSize + lengthSize + valueSize);

        offset += tagSize + lengthSize + valueSize;

        if ((tagBytes[0] & 0x20) != 0) {
            /* Tag is constructed */
            if (!primitiveOnly) {
                std::vector<std::vector<uint8_t>>& values
                    = getOrInitTagValues(tlvs, tag);
                values.push_back(value);
            }

            std::map<const int, std::vector<std::vector<uint8_t>>> tlvs2
                = parse(value, primitiveOnly);

            for (const auto& entry : tlvs2) {
                std::vector<std::vector<uint8_t>>& values
                    = getOrInitTagValues(tlvs, entry.first);
                Arrays::addAll(values, entry.second);
            }
        } else {
            /* Tag is primitive */
            std::vector<std::vector<uint8_t>>& values
                = getOrInitTagValues(tlvs, tag);
            values.push_back(value);
        }
    } while (offset < static_cast<int>(tlvStructure.size()));

    return tlvs;
}

std::vector<std::vector<uint8_t>>&
BerTlvUtil::getOrInitTagValues(
    std::map<const int, std::vector<std::vector<uint8_t>>>& tlvs, const int tag)
{
    const auto it = tlvs.find(tag);

    if (it == tlvs.end()) {
        std::vector<std::vector<uint8_t>> values;
        tlvs.insert({tag, values});
    }

    /* Look again and return reference */
    return tlvs.find(tag)->second;
}

int
BerTlvUtil::getTagSize(
    const std::vector<uint8_t>& tlvStructure, const int offset)
{
    /* C++: prevent accessing unexisting values */
    if (offset >= static_cast<int>(tlvStructure.size())) {
        throw IndexOutOfBoundsException("Invalid index");
    }

    if ((tlvStructure[offset] & 0x1F) == 0x1F) {
        if ((tlvStructure[offset + 1] & 0x80) == 0) {
            return 2;
        } else {
            if ((tlvStructure[offset + 2] & 0x80) != 0) {
                throw IllegalArgumentException("Invalid tag.");
            }
        }

        return 3;
    } else {
        return 1;
    }
}

int
BerTlvUtil::getTag(
    const std::vector<uint8_t>& tlvStructure, const int offset, const int size)
{
    switch (size) {
    case 1:
        return tlvStructure[offset] & 0xFF;
    case 2:
        return ((tlvStructure[offset] & 0xFF) << 8)
               + (tlvStructure[offset + 1] & 0xFF);
    case 3:
        return ((tlvStructure[offset] & 0xFF) << 16)
               + ((tlvStructure[offset + 1] & 0xFF) << 8)
               + (tlvStructure[offset + 2] & 0xFF);
    default:
        throw IllegalArgumentException("Bad tag size.");
    }
}

int
BerTlvUtil::getLengthSize(
    const std::vector<uint8_t>& tlvStructure, const int offset)
{
    int firstByteLength = tlvStructure[offset] & 0xff;

    switch (firstByteLength) {
    case 0x82:
        return 3;
    case 0x81:
        return 2;
    default:
        if (firstByteLength >= 0x80) {
            throw IllegalArgumentException("Invalid length.");
        }

        return 1;
    }
}

int
BerTlvUtil::getLength(
    const std::vector<uint8_t>& tlvStructure, const int offset, const int size)
{
    switch (size) {
    case 1:
        return tlvStructure[offset] & 0x7F;
    case 2:
        return tlvStructure[offset + 1] & 0xFF;
    case 3:
        return ((tlvStructure[offset + 1] & 0xFF) << 8)
               + (tlvStructure[offset + 2] & 0xFF);
    default:
        throw IllegalArgumentException("Bad length size.");
    }
}

} /* namespace util */
} /* namespace core */
} /* namespace keyple */
