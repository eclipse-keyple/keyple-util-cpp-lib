/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association                                                *
 * https://www.calypsonet-asso.org/                                                               *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "BerTlvUtil.h"

/* Keyple Core Util */
#include "Arrays.h"
#include "ByteArrayUtil.h"
#include "IllegalArgumentException.h"

using namespace testing;

using namespace keyple::core::util;
using namespace keyple::core::util::cpp;
using namespace keyple::core::util::cpp::exception;

const std::string TLV1 =
    "6F238409315449432E49434131A516BF0C13C708000000001122334453070A3C2005141001";
const std::string TLV2 =
    "6F23A516BF0C1353070A3C2005141001C70800000000112233448409315449432E49434131";

// static bool mapContainsEntry(const std::map<int, std::vector<uint8_t>>& m,  const int tag)
// {
//     const auto it = m.find(tag);
//     if (it != m.end()) {
//         return true;
//     }

//     return false;
// }

static bool mapContainsEntry(const std::map<int, std::vector<uint8_t>>& m, 
                             const int tag, 
                             const std::vector<uint8_t>& value)
{
    const auto it = m.find(tag);
    if (it != m.end() && it->second == value) {
        return true;
    }

    return false;
}

TEST(BerTlvUtilTest, parse_whenStructureIsValidAndPrimitiveOnlyIsFalse_shouldProvideAllTags)
{
    const auto tlvs = BerTlvUtil::parseSimple(ByteArrayUtil::fromHex(TLV1), false);

    ASSERT_EQ(tlvs.size(), 6);
    ASSERT_TRUE(mapContainsEntry(tlvs, 0x6F, ByteArrayUtil::fromHex("8409315449432E49434131A516BF0C13C708000000001122334453070A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0x84, ByteArrayUtil::fromHex("315449432E49434131")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0xA5, ByteArrayUtil::fromHex("BF0C13C708000000001122334453070A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0xBF0C, ByteArrayUtil::fromHex("C708000000001122334453070A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0x53, ByteArrayUtil::fromHex("0A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0xC7, ByteArrayUtil::fromHex("0000000011223344")));
}

TEST(BerTlvUtilTest, 
     parse_whenStructureIsValidAndPrimitiveOnlyIsTrue_shouldProvideOnlyPrimitiveTags)
{
    const auto tlvs = BerTlvUtil::parseSimple(ByteArrayUtil::fromHex(TLV1), true);

    ASSERT_EQ(tlvs.size(), 3);
    ASSERT_TRUE(mapContainsEntry(tlvs, 0x84, ByteArrayUtil::fromHex("315449432E49434131")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0x53, ByteArrayUtil::fromHex("0A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0xC7, ByteArrayUtil::fromHex("0000000011223344")));
}

TEST(BerTlvUtilTest, parse_whenTagsOrderChange_shouldProvideTheSameTags)
{
    const auto tlvs1 = BerTlvUtil::parseSimple(ByteArrayUtil::fromHex(TLV1), true);
    const auto tlvs2 = BerTlvUtil::parseSimple(ByteArrayUtil::fromHex(TLV2), true);

    ASSERT_EQ(tlvs1, tlvs2);
}

TEST(BerTlvUtilTest, parse_whenTagsIdIs3Bytes_shouldProvideTheTag)
{
    const auto tlvs = BerTlvUtil::parseSimple(ByteArrayUtil::fromHex("6F258409315449432E49434131A518BF0C15DFEF2C08000000001122334453070A3C2005141001"), true);
    
    ASSERT_EQ(tlvs.size(), 3);
    ASSERT_TRUE(mapContainsEntry(tlvs, 0x84, ByteArrayUtil::fromHex("315449432E49434131")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0x53, ByteArrayUtil::fromHex("0A3C2005141001")));
    ASSERT_TRUE(mapContainsEntry(tlvs, 0xDFEF2C, ByteArrayUtil::fromHex("0000000011223344")));
}

TEST(BerTlvUtilTest, parse_whenStructureIsInvalid_shouldIAE)
{
    EXPECT_THROW(BerTlvUtil::parseSimple(ByteArrayUtil::fromHex("6F23A5"), true),
                 IllegalArgumentException);
}

TEST(BerTlvUtilTest, parse_whenLengthFieldIsInvalid_shouldIAE)
{
    EXPECT_THROW(BerTlvUtil::parseSimple(ByteArrayUtil::fromHex("6F83A5"), true),
                 IllegalArgumentException);
}

TEST(BerTlvUtilTest, parse_whenLengthIsZero_shouldReturnEmptyValue)
{
    const auto tlvs = BerTlvUtil::parseSimple(ByteArrayUtil::fromHex("8400"), false);
    const auto it = tlvs.find(0x84);

    ASSERT_NE(it, tlvs.end());
    ASSERT_EQ(static_cast<int>(it->second.size()), 0);
}

TEST(BerTlvUtilTest, parse_whenLengthIsTwoBytes_shouldValue)
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

TEST(BerTlvUtilTest, parse_whenLengthIsThreeBytes_shouldValue) 
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
    EXPECT_THROW(BerTlvUtil::isConstructed(0x1000000), IllegalArgumentException);
}
