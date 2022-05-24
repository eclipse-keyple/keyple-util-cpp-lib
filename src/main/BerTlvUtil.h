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

#include <map>
#include <vector>

namespace keyple {
namespace core {
namespace util {

/**
 * Helper class to decode BER-TLV encoded data.
 *
 * <p>This class offers a tradeoff between complexity and efficiency adapted to the TLV structures
 * encountered in smart card data, it has the following limitations:
 *
 * <ul>
 *   <li>The tag ID fields must not exceed 3 bytes.
 *   <li>The length fields must not exceed 3 bytes.
 *   <li>Tags present several times in the same TLV structure require special attention (see {@link
 *       #parseSimple(byte[], boolean)}).
 * </ul>
 *
 * @since 2.0.0
 */
class BerTlvUtil {
public:
    /**
     * Parse the provided TLV structure and place all or only primitive tags found in a map. The key
     * is an integer representing the tag Id (e.g. 0x84 for the DF name tag), the value is the tag
     * value as an array of bytes.
     *
     * <p><b>Note:</b>This method of extracting tags is deliberately simplified.<br>
     * If the provided TLV structure contains several identical tags then only one will be reported in
     * the returned Map.<br>
     * To overcome this limitation it is recommended to re-parse the constructed tags known to contain
     * other tags.
     *
     * @param tlvStructure The input TLV structure.
     * @param primitiveOnly True if only primitives tags are to be placed in the map.
     * @return A not null map.
     * @throw IllegalArgumentException If the parsing of the provided structure failed.
     * @since 2.0.0
     */
    static const std::map<const int, const std::vector<uint8_t>> parseSimple(
        const std::vector<uint8_t>& tlvStructure, const bool primitiveOnly);

    /**
     * Indicates if the provided tag ID corresponds to a constructed tag.
     *
     * @param tagId A positive int less than FFFFFFh.
     * @return True if the tag is constructed.
     * @throw IllegalArgumentException If the tag Id is out of range.
     * @since 2.0.0
     */
    static bool isConstructed(const int tagId);

private:
    /**
     * (private)
     */
    BerTlvUtil();

    /**
     * (private)<br>
     * Parse the provided TLV structure from the provided offset and place all or only primitive tags
     * found in a map.
     *
     * @param tlvStructure The input TLV structure.
     * @param primitiveOnly True if only primitives tags are to be placed in the map.
     * @return A not null map.
     */
    static const std::map<const int, const std::vector<uint8_t>> parseBuffer(
        const std::vector<uint8_t> tlvStructure, const bool primitiveOnly);

    /**
     * (private)<br>
     * Gets the tag field size.
     *
     * @param tlvStructure The input TLV structure.
     * @param offset The starting offset in the structure.
     * @return An int.
     * @throw IllegalArgumentException If the tag field is invalid.
     * @throw IndexOutOfBoundsException If offset is out of range for the provided tlvStructure.
     */
    static int getTagSize(const std::vector<uint8_t>& tlvStructure, const int offset);

    /**
     * (private)<br>
     * Gets, as an integer, the tag of the provided size present at the designated location.
     *
     * @param tlvStructure The input TLV structure.
     * @param offset The starting offset in the structure.
     * @param size The tag size.
     * @return An int representing the tag value.
     * @throw IllegalArgumentException If the size is wrong.
     * @throw IndexOutOfBoundsException If offset is out of range for the provided tlvStructure.
     */
    static int getTag(const std::vector<uint8_t>& tlvStructure, const int offset, const int size);

    /**
     * (private)<br>
     * Gets the length field size.
     *
     * @param tlvStructure The input TLV structure.
     * @param offset The starting offset in the structure.
     * @return An int between 1 and 3.
     * @throw IllegalArgumentException If the length field is invalid.
     * @throw IndexOutOfBoundsException If offset is out of range for the provided tlvStructure.
     */
    static int getLengthSize(const std::vector<uint8_t>& tlvStructure, const int offset);

    /**
     * (private)<br>
     * Gets, as an integer, the length of the provided size present at the designated location.
     *
     * @param tlvStructure The input TLV structure.
     * @param offset The starting offset in the structure.
     * @param size The tag size.
     * @return An int representing the length value.
     * @throw IllegalArgumentException If the size is wrong.
     * @throw IndexOutOfBoundsException If offset is out of range for the provided tlvStructure.
     */
    static int getLength(const std::vector<uint8_t>& tlvStructure,
                         const int offset,
                         const int size);
};

}
}
}
