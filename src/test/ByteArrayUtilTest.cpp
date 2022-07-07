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

#include "ByteArrayUtil.h"

/* Util */
#include "IllegalArgumentException.h"

using namespace testing;

using namespace keyple::core::util;
using namespace keyple::core::util::cpp;
using namespace keyple::core::util::cpp::exception;

const std::string HEXSTRING_ODD  = "0102030";
const std::string HEXSTRING_BAD  = "010203ABGH8+";
const std::string HEXSTRING_GOOD = "1234567890ABCDEFFEDCBA0987654321";
const std::vector<uint8_t> BYTEARRAY_LEN_16 = {
0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x09, 0x87, 0x65, 0x43, 0x21
};

const std::vector<uint8_t> BYTEARRAY_LEN_0 = {};
const std::vector<uint8_t> BYTEARRAY_LEN_1 = {0x12};
const std::vector<uint8_t> BYTEARRAY_LEN_2 = {0x12, 0x34};
const std::vector<uint8_t> BYTEARRAY_LEN_3 = {0x12, 0x34, 0x56};
const std::vector<uint8_t> BYTEARRAY_LEN_4 = {0x12, 0x34, 0x56, 0x78};

TEST(ByteArrayUtilTest, isValidHexString_null)
{
    ASSERT_FALSE(ByteArrayUtil::isValidHexString(""));
}

TEST(ByteArrayUtilTest, isValidHexString_valid)
{
    ASSERT_TRUE(ByteArrayUtil::isValidHexString("0123456789ABCDEF"));
}

TEST(ByteArrayUtilTest, isValidHexString_invalid)
{
    ASSERT_FALSE(ByteArrayUtil::isValidHexString("0123456789ABCDE"));
    ASSERT_FALSE(ByteArrayUtil::isValidHexString("01 23456789ABCDEF"));
    ASSERT_FALSE(ByteArrayUtil::isValidHexString("0123456789ABCDEG"));
}

TEST(ByteArrayUtilTest, fromHex_empty)
{
    EXPECT_THROW(ByteArrayUtil::fromHex(""), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, fromHex_odd_length)
{
    EXPECT_THROW(ByteArrayUtil::fromHex(HEXSTRING_ODD), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, fromHex_bad_hex)
{
    /* No verification is being carried out at the moment */
    const std::vector<uint8_t> bytes = ByteArrayUtil::fromHex(HEXSTRING_BAD);
    /* Just check that the conversion is wrong */
    const std::string hex = ByteArrayUtil::toHex(bytes);

    ASSERT_NE(hex, HEXSTRING_BAD);
}

TEST(ByteArrayUtilTest, fromHex_good_hex)
{
    /* No verification is being carried out at the moment */
    const std::vector<uint8_t> bytes = ByteArrayUtil::fromHex(HEXSTRING_GOOD);

    ASSERT_EQ(bytes, BYTEARRAY_LEN_16);
}

TEST(ByteArrayUtilTest, hexToByte_whenHexIsEmpty_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToByte(""), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToByte_whenHexLengthIsOdd_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToByte("1"), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToByte_whenHexLengthIsGreaterThan2_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToByte("1234"), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToByte_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_EQ(ByteArrayUtil::hexToByte("AB"),  0xAB);
    ASSERT_EQ(ByteArrayUtil::hexToByte("CD"),  0xCD);
    ASSERT_EQ(ByteArrayUtil::hexToByte("EF"),  0xEF);
    ASSERT_EQ(ByteArrayUtil::hexToByte("ab"),  0xAB);
    ASSERT_EQ(ByteArrayUtil::hexToByte("cd"),  0xCD);
    ASSERT_EQ(ByteArrayUtil::hexToByte("ef"),  0xEF);
}

TEST(ByteArrayUtilTest, hexToShort_whenHexIsEmpty_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToShort(""), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToShort_whenHexLengthIsOdd_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToShort("1"), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToShort_whenHexLengthIsGreaterThan4_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToShort("123456"), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToShort_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_EQ(ByteArrayUtil::hexToShort("ABCD"), 0xABCD);
    ASSERT_EQ(ByteArrayUtil::hexToShort("EF"), 0xEF);
    ASSERT_EQ(ByteArrayUtil::hexToShort("abcd"), 0xABCD);
    ASSERT_EQ(ByteArrayUtil::hexToShort("ef"), 0xEF);
}

TEST(ByteArrayUtilTest, hexToInt_whenHexIsEmpty_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToInt(""), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToInt_whenHexLengthIsOdd_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToInt("1"), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToInt_whenHexLengthIsGreaterThan8_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToInt("123456789A"), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToInt_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_EQ(ByteArrayUtil::hexToInt("FE"), 0xFE);
    ASSERT_EQ(ByteArrayUtil::hexToInt("FEF7"), 0xFEF7);
    ASSERT_EQ(ByteArrayUtil::hexToInt("FEF712"), 0xFEF712);
    ASSERT_EQ(ByteArrayUtil::hexToInt("FEF71234"), 0xFEF71234);
    ASSERT_EQ(ByteArrayUtil::hexToInt("ABCDEF"), 0xABCDEF);
    ASSERT_EQ(ByteArrayUtil::hexToInt("abcdef"), 0xABCDEF);
}

TEST(ByteArrayUtilTest, hexToLong_whenHexIsEmpty_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToLong(""), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToLong_whenHexLengthIsOdd_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToLong("1"), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToLong_whenHexLengthIsGreaterThan16_shouldThrowIAE)
{
    EXPECT_THROW(ByteArrayUtil::hexToLong("123456789ABCDEF012"), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, hexToLong_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_EQ(ByteArrayUtil::hexToLong("FE"), 0xFEL);
    ASSERT_EQ(ByteArrayUtil::hexToLong("FEF7"), 0xFEF7L);
    ASSERT_EQ(ByteArrayUtil::hexToLong("FEF712"), 0xFEF712L);
    ASSERT_EQ(ByteArrayUtil::hexToLong("FEF71234"), 0xFEF71234L);
    ASSERT_EQ(ByteArrayUtil::hexToLong("FEF7123456"), 0xFEF7123456L);
    ASSERT_EQ(ByteArrayUtil::hexToLong("FEF712345678"), 0xFEF712345678L);
    ASSERT_EQ(ByteArrayUtil::hexToLong("FEF7123456789A"), 0xFEF7123456789AL);
    ASSERT_EQ(ByteArrayUtil::hexToLong("FEF7123456789ABC"), 0xFEF7123456789ABCL);
    ASSERT_EQ(ByteArrayUtil::hexToLong("ABCDEF"), 0xABCDEFL);
    ASSERT_EQ(ByteArrayUtil::hexToLong("abcdef"), 0xABCDEFL);
}

TEST(ByteArrayUtilTest, toHex_empty)
{
    const std::vector<uint8_t> bytes;
    const std::string hex = ByteArrayUtil::toHex(bytes);

    ASSERT_EQ(static_cast<int>(hex.size()), 0);
}

TEST(ByteArrayUtilTest, toHex_bytearray_good)
{
    const std::string hex = ByteArrayUtil::toHex(BYTEARRAY_LEN_16);

    ASSERT_EQ(hex, HEXSTRING_GOOD);
}

TEST(ByteArrayUtilTest, toHex_byte)
{
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint8_t>(0xFE)), "FE");
}

TEST(ByteArrayUtilTest, toHex_short)
{
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint16_t>(0xFE)), "FE");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint16_t>(0xFE34)), "FE34");
}

TEST(ByteArrayUtilTest, toHex_int)
{
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint32_t>(0xFE)), "FE");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint32_t>(0xFE34)), "FE34");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint32_t>(0xFE3456)), "FE3456");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint32_t>(0xFE345678)), "FE345678");
}

TEST(ByteArrayUtilTest, toHex_long)
{
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint64_t>(0xFEL)), "FE");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint64_t>(0xFE34L)), "FE34");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint64_t>(0xFE3456L)), "FE3456");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint64_t>(0xFE345678L)), "FE345678");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint64_t>(0xFE3456789AL)), "FE3456789A");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint64_t>(0xFE3456789ABCL)), "FE3456789ABC");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint64_t>(0xFE3456789ABCDEL)), "FE3456789ABCDE");
    ASSERT_EQ(ByteArrayUtil::toHex(static_cast<uint64_t>(0xFE3456789ABCDEF0L)), "FE3456789ABCDEF0");
}

TEST(ByteArrayUtilTest, twoBytesToInt_empty)
{
    EXPECT_THROW(ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_0, 0), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, twoBytesToInt_negative_offset)
{
    EXPECT_THROW(ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_16, -1), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, twoBytesToInt_too_short_buffer_1)
{
    EXPECT_THROW(ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_1, 0), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, twoBytesToInt_too_short_buffer_2)
{
    EXPECT_THROW(ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_3, 2), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, twoBytesToInt_buffer_ok_1)
{
    const int value = ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_3, 0);

    ASSERT_EQ(value, 0x1234);
}

TEST(ByteArrayUtilTest, twoBytesToInt_buffer_ok_2)
{
    const int value = ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_16, 0);

    ASSERT_EQ(value, 0x1234);
}

TEST(ByteArrayUtilTest, twoBytesToInt_buffer_ok_3)
{
    const int value = ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_16, 1);

    ASSERT_EQ(value, 0x3456);
}

TEST(ByteArrayUtilTest, twoBytesToInt_buffer_ok_4)
{
    const int value = ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_16, 4);

    ASSERT_EQ(value, 0x90AB);
}

TEST(ByteArrayUtilTest, twoBytesToInt_buffer_ok_5)
{
    const int value = ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_16, 14);

    ASSERT_EQ(value, 0x4321);
}

TEST(ByteArrayUtilTest, twoBytesSignedToInt_buffer_ok_1)
{
    const int value = ByteArrayUtil::twoBytesSignedToInt(BYTEARRAY_LEN_16, 0);

    ASSERT_EQ(value, 0x1234);
}

TEST(ByteArrayUtilTest, twoBytesSignedToInt_buffer_ok_2)
{
    const int value = ByteArrayUtil::twoBytesSignedToInt(BYTEARRAY_LEN_16, 4);

    /* 0x90AB{2 bytes} = -28501 */
    ASSERT_EQ(value, -28501);
}

TEST(ByteArrayUtilTest, threeBytesToInt_empty)
{
    EXPECT_THROW(ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_0, 0), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, threeBytesToInt_negative_offset)
{
    EXPECT_THROW(ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_16, -1), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, threeBytesToInt_too_short_buffer_1)
{
    EXPECT_THROW(ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_2, 0), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, threeBytesToInt_too_short_buffer_2)
{
    EXPECT_THROW(ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_3, 1), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, threeBytesToInt_buffer_ok_1)
{
    const int value = ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_3, 0);

    ASSERT_EQ(value, 0x123456);
}

TEST(ByteArrayUtilTest, threeBytesToInt_buffer_ok_2)
{
    const int value = ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_16, 0);

    ASSERT_EQ(value, 0x123456);
}

TEST(ByteArrayUtilTest, threeBytesToInt_buffer_ok_3)
{
    const int value = ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_16, 1);

    ASSERT_EQ(value, 0x345678);
}

TEST(ByteArrayUtilTest, threeBytesToInt_buffer_ok_4)
{
    const int value = ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_16, 4);

    ASSERT_EQ(value, 0x90ABCD);
}

TEST(ByteArrayUtilTest, threeBytesToInt_buffer_ok_5)
{
    const int value = ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_16, 13);

    ASSERT_EQ(value, 0x654321);
}

TEST(ByteArrayUtilTest, threeBytesSignedToInt_buffer_ok_1)
{
    const int value = ByteArrayUtil::threeBytesSignedToInt(BYTEARRAY_LEN_16, 0);

    ASSERT_EQ(value, 0x123456);
}

TEST(ByteArrayUtilTest, threeBytesSignedToInt_buffer_ok_2)
{
    const int value = ByteArrayUtil::threeBytesSignedToInt(BYTEARRAY_LEN_16, 4);

    /* 0xFF90ABCD{4 bytes} = -7296051 */
    ASSERT_EQ(value, -7296051);
}

TEST(ByteArrayUtilTest, fourBytesToInt_empty)
{
    EXPECT_THROW(ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_0, 0), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, fourBytesToInt_negative_offset)
{
    EXPECT_THROW(ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_16, -1), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, fourBytesToInt_too_short_buffer_1)
{
    EXPECT_THROW(ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_3, 0), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, fourBytesToInt_too_short_buffer_2)
{
    EXPECT_THROW(ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_4, 1), IllegalArgumentException);
}

TEST(ByteArrayUtilTest, fourBytesToInt_buffer_ok_1)
{
    const int value = ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_4, 0);

    ASSERT_EQ(value, 0x12345678);
}

TEST(ByteArrayUtilTest, fourBytesToInt_buffer_ok_2)
{
    const int value = ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_16, 0);

    ASSERT_EQ(value, 0x12345678);
}

TEST(ByteArrayUtilTest, fourBytesToInt_buffer_ok_3)
{
    const int value = ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_16, 1);

    ASSERT_EQ(value, 0x34567890);
}

TEST(ByteArrayUtilTest, fourBytesToInt_buffer_ok_4)
{
    const int value = ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_16, 4);

    ASSERT_EQ(value, 0x90ABCDEF);
}

TEST(ByteArrayUtilTest, fourBytesToInt_buffer_ok_5)
{
    const int value = ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_16, 12);

    ASSERT_EQ(value, 0x87654321);
}
