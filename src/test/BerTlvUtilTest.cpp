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

#include <map>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "keyple/core/util/BerTlvUtil.hpp"
#include "keyple/core/util/HexUtil.hpp"
#include "keyple/core/util/cpp/Arrays.hpp"
#include "keyple/core/util/cpp/exception/IllegalArgumentException.hpp"

using keyple::core::util::BerTlvUtil;
using keyple::core::util::HexUtil;
using keyple::core::util::cpp::Arrays;
using keyple::core::util::cpp::exception::IllegalArgumentException;

const char* TLV1 = "6F238409315449432E49434131A516BF0C13C7080000000011223344530"
                   "70A3C2005141001";
const char* TLV2 = "6F23A516BF0C1353070A3C2005141001C70800000000112233448409315"
                   "449432E49434131";

static bool
mapContainsEntry(
    const std::map<const int, const std::vector<uint8_t>>& m,
    const int tag,
    const std::vector<uint8_t>& value)
{
    const auto it = m.find(tag);
    if (it != m.end() && it->second == value) {
        return true;
    }

    return false;
}

static bool
mapContainsOnlyKeys(
    const std::map<const int, std::vector<std::vector<uint8_t>>>& m,
    const std::vector<int>& values)
{
    return std::all_of(m.begin(), m.end(), [&](const auto& entry) {
        return Arrays::contains(values, entry.first);
    });
}

static bool
vectorContainsExactly(
    std::vector<std::vector<uint8_t>>& v,
    const std::vector<std::vector<uint8_t>>& values)
{
    if (v.size() != values.size()) {
        return false;
    }

    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!Arrays::equals(v[i], values[i])) {
            return false;
        }
    }

    return true;
}

static bool
vectorContainsExactly(
    std::vector<std::vector<uint8_t>>& v, const std::vector<uint8_t>& value)
{
    if (v.size() != 1) {
        return false;
    }

    return Arrays::equals(v[0], value);
}

TEST(
    BerTlvUtilTest,
    parse_whenStructureIsValidAndPrimitiveOnlyIsFalse_shouldProvideAllTags)
{
    auto tlvs = BerTlvUtil::parse(HexUtil::toByteArray(TLV1), false);

    ASSERT_TRUE(
        mapContainsOnlyKeys(tlvs, {0x6F, 0x84, 0xA5, 0xBF0C, 0x53, 0xC7}));

    ASSERT_TRUE(vectorContainsExactly(
        tlvs[0x6F],
        HexUtil::toByteArray("8409315449432E49434131A516BF0C13C708000"
                             "000001122334453070A3C2005141001")));
    ASSERT_TRUE(vectorContainsExactly(
        tlvs[0x84], HexUtil::toByteArray("315449432E49434131")));
    ASSERT_TRUE(vectorContainsExactly(
        tlvs[0xA5],
        HexUtil::toByteArray("BF0C13C708000000001122334453070A3C2005141001")));
    ASSERT_TRUE(vectorContainsExactly(
        tlvs[0xBF0C],
        HexUtil::toByteArray("C708000000001122334453070A3C2005141001")));
    ASSERT_TRUE(vectorContainsExactly(
        tlvs[0x53], HexUtil::toByteArray("0A3C2005141001")));
    ASSERT_TRUE(vectorContainsExactly(
        tlvs[0xC7], HexUtil::toByteArray("0000000011223344")));
}

TEST(
    BerTlvUtilTest,
    parse_whenStructureIsValidAndPrimitiveOnlyIsFalse_shouldProvideAllTags2)
{
    auto tlvs = BerTlvUtil::parse(
        HexUtil::toByteArray(
            "E030C106200107021D01C106202009021D04C106206919091D0"
            "1C106201008041D03C10620401D021D01C10620501E021D01"),
        false);

    ASSERT_TRUE(mapContainsOnlyKeys(tlvs, {0xE0, 0xC1}));
    ASSERT_TRUE(vectorContainsExactly(
        tlvs[0xE0],
        HexUtil::toByteArray(
            "C106200107021D01C106202009021D04C106206919091D01C10"
            "6201008041D03C10620401D021D01C10620501E021D01")));
    ASSERT_TRUE(vectorContainsExactly(
        tlvs[0xC1],
        {HexUtil::toByteArray("200107021D01"),
         HexUtil::toByteArray("202009021D04"),
         HexUtil::toByteArray("206919091D01"),
         HexUtil::toByteArray("201008041D03"),
         HexUtil::toByteArray("20401D021D01"),
         HexUtil::toByteArray("20501E021D01")}));
}

TEST(
    BerTlvUtilTest,
    parseSimple_whenStructureIsValidAndPrimitiveOnlyIsFalse_shouldProvideAllTags)  // NOLINT
{
    const auto tlvs
        = BerTlvUtil::parseSimple(HexUtil::toByteArray(TLV1), false);

    ASSERT_EQ(tlvs.size(), 6);
    ASSERT_TRUE(mapContainsEntry(
        tlvs,
        0x6F,
        HexUtil::toByteArray(
            "8409315449432E49434131A516BF0C13C708000000001122334"
            "453070A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(
        tlvs, 0x84, HexUtil::toByteArray("315449432E49434131")));
    ASSERT_TRUE(mapContainsEntry(
        tlvs,
        0xA5,
        HexUtil::toByteArray("BF0C13C708000000001122334453070A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(
        tlvs,
        0xBF0C,
        HexUtil::toByteArray("C708000000001122334453070A3C2005141001")));
    ASSERT_TRUE(
        mapContainsEntry(tlvs, 0x53, HexUtil::toByteArray("0A3C2005141001")));
    ASSERT_TRUE(
        mapContainsEntry(tlvs, 0xC7, HexUtil::toByteArray("0000000011223344")));
}

TEST(
    BerTlvUtilTest,
    parse_whenStructureIsValidAndPrimitiveOnlyIsTrue_shouldProvideOnlyPrimitiveTags)  // NOLINT
{
    const auto tlvs = BerTlvUtil::parseSimple(HexUtil::toByteArray(TLV1), true);

    ASSERT_EQ(tlvs.size(), 3);
    ASSERT_TRUE(mapContainsEntry(
        tlvs, 0x84, HexUtil::toByteArray("315449432E49434131")));
    ASSERT_TRUE(
        mapContainsEntry(tlvs, 0x53, HexUtil::toByteArray("0A3C2005141001")));
    ASSERT_TRUE(
        mapContainsEntry(tlvs, 0xC7, HexUtil::toByteArray("0000000011223344")));
}

TEST(BerTlvUtilTest, parseSimple_whenTagsOrderChange_shouldProvideTheSameTags)
{
    const auto tlvs1
        = BerTlvUtil::parseSimple(HexUtil::toByteArray(TLV1), true);
    const auto tlvs2
        = BerTlvUtil::parseSimple(HexUtil::toByteArray(TLV2), true);

    ASSERT_EQ(tlvs1, tlvs2);
}

TEST(BerTlvUtilTest, parseSimple_whenTagsIdIs3Bytes_shouldProvideTheTag)
{
    const auto tlvs = BerTlvUtil::parseSimple(
        HexUtil::toByteArray(
            "6F258409315449432E49434131A518BF0C15DFEF2C080000000"
            "01122334453070A3C2005141001"),
        true);

    ASSERT_EQ(tlvs.size(), 3);
    ASSERT_TRUE(mapContainsEntry(
        tlvs, 0x84, HexUtil::toByteArray("315449432E49434131")));
    ASSERT_TRUE(
        mapContainsEntry(tlvs, 0x53, HexUtil::toByteArray("0A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(
        tlvs, 0xDFEF2C, HexUtil::toByteArray("0000000011223344")));
}

TEST(BerTlvUtilTest, parseSimple_whenStructureIsInvalid_shouldIAE)
{
    EXPECT_THROW(
        BerTlvUtil::parseSimple(HexUtil::toByteArray("6F23A5"), true),
        IllegalArgumentException);
}

TEST(BerTlvUtilTest, parseSimple_whenLengthFieldIsInvalid_shouldIAE)
{
    EXPECT_THROW(
        BerTlvUtil::parseSimple(HexUtil::toByteArray("6F83A5"), true),
        IllegalArgumentException);
}

TEST(BerTlvUtilTest, parseSimple_whenLengthIsZero_shouldReturnEmptyValue)
{
    const auto tlvs
        = BerTlvUtil::parseSimple(HexUtil::toByteArray("8400"), false);
    const auto it = tlvs.find(0x84);

    ASSERT_NE(it, tlvs.end());
    ASSERT_EQ(static_cast<int>(it->second.size()), 0);
}

TEST(BerTlvUtilTest, parseSimple_whenLengthIsTwoBytes_shouldValue)
{
    /* Length 250 */
    std::vector<uint8_t> tlv(253);

    tlv[0] = 0x84;
    tlv[1] = 0x81;
    tlv[2] = 250;
    for (int i = 3; i < 253; i++) {
        tlv[i] = 0xA5;
    }

    const auto tlvs = BerTlvUtil::parseSimple(tlv, false);
    const auto it = tlvs.find(0x84);

    ASSERT_NE(it, tlvs.end());
    ASSERT_EQ(static_cast<int>(it->second.size()), 250);
    ASSERT_TRUE(Arrays::containsOnly(it->second, static_cast<uint8_t>(0xA5)));
}

TEST(BerTlvUtilTest, parseSimple_whenLengthIsThreeBytes_shouldValue)
{
    /* Length 260 */
    std::vector<uint8_t> tlv(264);

    tlv[0] = 0x84;
    tlv[1] = 0x82;
    tlv[2] = 0x01;
    tlv[3] = 0x04;
    for (int i = 4; i < 264; i++) {
        tlv[i] = 0xA5;
    }

    const auto tlvs = BerTlvUtil::parseSimple(tlv, false);
    const auto it = tlvs.find(0x84);
    ASSERT_NE(it, tlvs.end());
    ASSERT_EQ(static_cast<int>(it->second.size()), 260);
    ASSERT_TRUE(Arrays::containsOnly(it->second, static_cast<uint8_t>(0xA5)));
}

TEST(BerTlvUtilTest, isConstructed_when1ByteTagIsConstructed_shouldReturnTrue)
{
    ASSERT_TRUE(BerTlvUtil::isConstructed(0x6F));
}

TEST(BerTlvUtilTest, isConstructed_when1ByteTagIsPrimitive_shouldReturnFalse)
{
    ASSERT_FALSE(BerTlvUtil::isConstructed(0x84));
}

TEST(BerTlvUtilTest, isConstructed_when2ByteTagIsConstructed_shouldReturnTrue)
{
    ASSERT_TRUE(BerTlvUtil::isConstructed(0xBC0C));
}

TEST(BerTlvUtilTest, isConstructed_when2ByteTagIsPrimitive_shouldReturnFalse)
{
    ASSERT_FALSE(BerTlvUtil::isConstructed(0x9F0C));
}

TEST(BerTlvUtilTest, isConstructed_when3ByteTagIsConstructed_shouldReturnTrue)
{
    ASSERT_TRUE(BerTlvUtil::isConstructed(0x6FEF2C));
}

TEST(BerTlvUtilTest, isConstructed_when3ByteTagIsPrimitive_shouldReturnFalse)
{
    ASSERT_FALSE(BerTlvUtil::isConstructed(0xDFEF2C));
}

TEST(BerTlvUtilTest, isConstructed_whenTagIsNegative_shouldIAE)
{
    EXPECT_THROW(BerTlvUtil::isConstructed(-1), IllegalArgumentException);
}

TEST(BerTlvUtilTest, isConstructed_whenTagIsTooLarge_shouldIAE)
{
    EXPECT_THROW(
        BerTlvUtil::isConstructed(0x1000000), IllegalArgumentException);
}
