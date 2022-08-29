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

/* Keyple Core Util */
#include "Arrays.h"
#include "ArrayIndexOutOfBoundsException.h"
#include "IllegalArgumentException.h"
#include "NegativeArraySizeException.h"

using namespace testing;

using namespace keyple::core::util;
using namespace keyple::core::util::cpp;
using namespace keyple::core::util::cpp::exception;

const std::string HEXSTRING_ODD  = "0102030";
const std::string HEXSTRING_BAD  = "010203ABGH8+";
const std::string HEXSTRING_GOOD = "1234567890ABCDEFFEDCBA0987654321";
const std::vector<uint8_t> BYTEARRAY_LEN_0 = {};
const std::vector<uint8_t> BYTEARRAY_LEN_1 = {0x12};
const std::vector<uint8_t> BYTEARRAY_LEN_2 = {0x12, 0x34};
const std::vector<uint8_t> BYTEARRAY_LEN_3 = {0x12, 0x34, 0x56};
const std::vector<uint8_t> BYTEARRAY_LEN_4 = {0x12, 0x34, 0x56, 0x78};
const std::vector<uint8_t> BYTEARRAY_LEN_16 = {
    0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x09, 0x87, 0x65, 0x43, 0x21
};


TEST(ByteArrayUtilTest, extractBytes_whenBitOffsetIsOutOfRange_shouldThrowAIOOBE)
{
    EXPECT_THROW(ByteArrayUtil::extractBytes(std::vector<uint8_t>(1), 16, 1),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractBytes_whenBitOffsetIsOutOfRange_shouldThrowAIOOBE2)
{
    EXPECT_THROW(ByteArrayUtil::extractBytes(std::vector<uint8_t>(1), 9, 1),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractBytes_whenBitOffsetIsNegative_shouldThrowAIOOBE)
{
    EXPECT_THROW(ByteArrayUtil::extractBytes(std::vector<uint8_t>(1), -8, 1),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractBytes_whenBitOffsetIsNegative_shouldThrowAIOOBE2)
{
    EXPECT_THROW(ByteArrayUtil::extractBytes(std::vector<uint8_t>(1), -1, 1),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractBytes_whenNbBytesIsOutOfRange_shouldThrowAIOOBE)
{
    EXPECT_THROW(ByteArrayUtil::extractBytes(std::vector<uint8_t>(1), 0, 2),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractBytes_whenNbBytesIsOutOfRange_shouldThrowAIOOBE2)
{
    EXPECT_THROW(ByteArrayUtil::extractBytes(std::vector<uint8_t>(1), 1, 2),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractBytes_whenNbBytesIsNegative_shouldThrowAIOOBE)
{
    EXPECT_THROW(ByteArrayUtil::extractBytes(std::vector<uint8_t>(1), 0, -1),
                 NegativeArraySizeException);
}

TEST(ByteArrayUtilTest, extractBytes_whenNbBytesIsNegative_shouldThrowAIOOBE2)
{
    EXPECT_THROW(ByteArrayUtil::extractBytes(std::vector<uint8_t>(1), 1, -1),
                 NegativeArraySizeException);
}


TEST(ByteArrayUtilTest, extractBytes_whenBitOffsetIsMultipleOf8_shouldBeSuccessful)
{
    const std::vector<uint8_t> src = {0xF1, 0xF2, 0xF3};

    ASSERT_TRUE(Arrays::equals(ByteArrayUtil::extractBytes(src, 8, 1), {0xF2}));
    ASSERT_TRUE(Arrays::equals(ByteArrayUtil::extractBytes(src, 8, 2), {0xF2, 0xF3}));
}

TEST(ByteArrayUtilTest, extractBytes_whenBitOffsetIsNotMultipleOf8_shouldBeSuccessful)
{
    const std::vector<uint8_t> src = {0xF1, 0xF2, 0xF3};

    ASSERT_TRUE(Arrays::equals(ByteArrayUtil::extractBytes(src, 6, 1), {0x7C}));
    ASSERT_TRUE(Arrays::equals(ByteArrayUtil::extractBytes(src, 6, 2), {0x7C, 0xBC}));
    ASSERT_TRUE(Arrays::equals(ByteArrayUtil::extractBytes(src, 3, 1), {0x8F}));
}

TEST(ByteArrayUtilTest, extractInt_whenOffsetIsNegative_shouldThrowAIOOBE)
{
    EXPECT_THROW(ByteArrayUtil::extractInt(std::vector<uint8_t>(1), -1, 1, true),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractInt_whenOffsetIsGreaterThanSrcLengthMinusNbBytes_shouldThrowAIOOBE)
{
    EXPECT_THROW(ByteArrayUtil::extractInt(std::vector<uint8_t>(1), 1, 1, true),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractInt_whenNbBytesIsTooBig_shouldThrowAIOOBE)
{
    EXPECT_THROW(ByteArrayUtil::extractInt(std::vector<uint8_t>(1), 0, 2, true),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, extractInt_whenInputIsOk_shouldBeSuccessful)
{
    const std::vector<uint8_t> src = {0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6};

    ASSERT_EQ(ByteArrayUtil::extractInt(src, 1, 1, true), 0xFFFFFFF2);
    ASSERT_EQ(ByteArrayUtil::extractInt(src, 1, 1, false), 0xF2);
    ASSERT_EQ(ByteArrayUtil::extractInt(src, 1, 2, true), 0xFFFFF2F3);
    ASSERT_EQ(ByteArrayUtil::extractInt(src, 1, 2, false), 0xF2F3);
    ASSERT_EQ(ByteArrayUtil::extractInt(src, 1, 3, true), 0xFFF2F3F4);
    ASSERT_EQ(ByteArrayUtil::extractInt(src, 1, 3, false), 0xF2F3F4);
    ASSERT_EQ(ByteArrayUtil::extractInt(src, 1, 4, true), 0xF2F3F4F5);
    ASSERT_EQ(ByteArrayUtil::extractInt(src, 1, 4, false), 0xF2F3F4F5);
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


TEST(ByteArrayUtilTest, toHex_empty)
{
    const std::vector<uint8_t> bytes = std::vector<uint8_t>(0);
    const std::string hex = ByteArrayUtil::toHex(bytes);

    ASSERT_EQ(static_cast<int>(hex.size()), 0);
}

TEST(ByteArrayUtilTest, toHex_bytearray_good)
{
    const std::string hex = ByteArrayUtil::toHex(BYTEARRAY_LEN_16);

    ASSERT_EQ(hex, HEXSTRING_GOOD);
}

TEST(ByteArrayUtilTest, twoBytesToInt_negative_offset)
{
    EXPECT_THROW(ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_16, -1),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, twoBytesToInt_too_short_buffer_1)
{
    EXPECT_THROW(ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_1, 0),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, twoBytesToInt_too_short_buffer_2)
{
    EXPECT_THROW(ByteArrayUtil::twoBytesToInt(BYTEARRAY_LEN_3, 2),
                 ArrayIndexOutOfBoundsException);
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

TEST(ByteArrayUtilTest, threeBytesToInt_negative_offset)
{
    EXPECT_THROW(ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_16, -1),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, threeBytesToInt_too_short_buffer_1)
{
    EXPECT_THROW(ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_2, 0),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, threeBytesToInt_too_short_buffer_2)
{
    EXPECT_THROW(ByteArrayUtil::threeBytesToInt(BYTEARRAY_LEN_3, 1),
                 ArrayIndexOutOfBoundsException);
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

TEST(ByteArrayUtilTest, fourBytesToInt_negative_offset)
{
    EXPECT_THROW(ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_16, -1),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, fourBytesToInt_too_short_buffer_1)
{
    EXPECT_THROW(ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_3, 0),
                 ArrayIndexOutOfBoundsException);
}

TEST(ByteArrayUtilTest, fourBytesToInt_too_short_buffer_2)
{
    EXPECT_THROW(ByteArrayUtil::fourBytesToInt(BYTEARRAY_LEN_4, 1),
                 ArrayIndexOutOfBoundsException);
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
