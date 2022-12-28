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

#include "HexUtil.h"

/* Keyple Core Util */
#include "Arrays.h"
#include "StringIndexOutOfBoundsException.h"

using namespace testing;

using namespace keyple::core::util;
using namespace keyple::core::util::cpp;
using namespace keyple::core::util::cpp::exception;

TEST(HexUtilTest, isValid_whenHexIsValid_shouldReturnTrue)
{
    ASSERT_TRUE(HexUtil::isValid("0123456789ABCDEF"));
}

TEST(HexUtilTest, isValid_whenHexHasOddLength_shouldReturnFalse)
{
    ASSERT_FALSE(HexUtil::isValid("0123456789ABCDE"));
}

TEST(HexUtilTest, isValid_whenHexContainsEmptySpaces_shouldReturnFalse)
{
    ASSERT_FALSE(HexUtil::isValid("01 23456789ABCDEF"));
}

TEST(HexUtilTest, isValid_whenHexContainsNotHexDigits_shouldReturnFalse)
{
    ASSERT_FALSE(HexUtil::isValid("0123456789ABCDEG"));
}

TEST(HexUtilTest, toByteArray_whenHexIsEmpty_shouldReturnEmptyArray)
{
    ASSERT_EQ(static_cast<int>(HexUtil::toByteArray("").size()), 0);
}

TEST(HexUtilTest, toByteArray_whenHexIsOddLength_shouldThrowSIOOBE)
{
    EXPECT_THROW(HexUtil::toByteArray("1"), StringIndexOutOfBoundsException);
}

TEST(HexUtilTest, toByteArray_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_TRUE(Arrays::equals(HexUtil::toByteArray("ABCDEFabcdef"),
                              {0xAB, 0xCD, 0xEF, 0xAB, 0xCD, 0xEF}));
}

TEST(HexUtilTest, toByte_whenHexIsEmpty_shouldReturn0)
{
    ASSERT_EQ(HexUtil::toByte(""), 0);
}

TEST(HexUtilTest, toByte_whenHexLengthIsGreaterThan2_shouldTruncateLeft)
{
    ASSERT_EQ(HexUtil::toByte("1234"), 0x34);
}

TEST(HexUtilTest, toByte_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_EQ(HexUtil::toByte("1"), 0x1);
    ASSERT_EQ(HexUtil::toByte("AB"), 0xAB);
    ASSERT_EQ(HexUtil::toByte("CD"), 0xCD);
    ASSERT_EQ(HexUtil::toByte("EF"), 0xEF);
    ASSERT_EQ(HexUtil::toByte("ab"), 0xAB);
    ASSERT_EQ(HexUtil::toByte("cd"), 0xCD);
    ASSERT_EQ(HexUtil::toByte("ef"), 0xEF);
}

TEST(HexUtilTest, toShort_whenHexIsEmpty_shouldReturn0)
{
    ASSERT_EQ(HexUtil::toShort(""), 0);
}

TEST(HexUtilTest, toShort_whenHexLengthIsGreaterThan4_shouldTruncateLeft)
{
    ASSERT_EQ(HexUtil::toShort("123456"), 0x3456);
}

TEST(HexUtilTest, toShort_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_EQ(HexUtil::toShort("1"), 0x1);
    ASSERT_EQ(HexUtil::toShort("ABCD"), 0xABCD);
    ASSERT_EQ(HexUtil::toShort("EF"), 0xEF);
    ASSERT_EQ(HexUtil::toShort("abcd"), 0xABCD);
    ASSERT_EQ(HexUtil::toShort("ef"), 0xEF);
}

TEST(HexUtilTest, toInt_whenHexIsEmpty_shouldReturn0)
{
    ASSERT_EQ(HexUtil::toInt(""), 0);
}

TEST(HexUtilTest, toInt_whenHexLengthIsGreaterThan8_shouldTruncateLeft)
{
    ASSERT_EQ(HexUtil::toInt("123456789A"), 0x3456789A);
}

TEST(HexUtilTest, toInt_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_EQ(HexUtil::toInt("1"), 0x1);
    ASSERT_EQ(HexUtil::toInt("FE"), 0xFE);
    ASSERT_EQ(HexUtil::toInt("FEF7"), 0xFEF7);
    ASSERT_EQ(HexUtil::toInt("FEF712"), 0xFEF712);
    ASSERT_EQ(HexUtil::toInt("FEF71234"), 0xFEF71234);
    ASSERT_EQ(HexUtil::toInt("ABCDEF"), 0xABCDEF);
    ASSERT_EQ(HexUtil::toInt("abcdef"), 0xABCDEF);
}

TEST(HexUtilTest, toLong_whenHexIsEmpty_shouldReturn0)
{
    ASSERT_EQ(HexUtil::toLong(""), 0);
}

TEST(HexUtilTest, toLong_whenHexLengthIsGreaterThan16_shouldTruncateRight)
{
    ASSERT_EQ(HexUtil::toLong("123456789ABCDEF012"), 0x3456789ABCDEF012L);
}

TEST(HexUtilTest, toLong_whenHexIsValid_shouldBeSuccessful)
{
    ASSERT_EQ(HexUtil::toLong("1"), 0x1L);
    ASSERT_EQ(HexUtil::toLong("FE"), 0xFEL);
    ASSERT_EQ(HexUtil::toLong("FEF7"), 0xFEF7L);
    ASSERT_EQ(HexUtil::toLong("FEF712"), 0xFEF712L);
    ASSERT_EQ(HexUtil::toLong("FEF71234"), 0xFEF71234L);
    ASSERT_EQ(HexUtil::toLong("FEF7123456"), 0xFEF7123456L);
    ASSERT_EQ(HexUtil::toLong("FEF712345678"), 0xFEF712345678L);
    ASSERT_EQ(HexUtil::toLong("FEF7123456789A"), 0xFEF7123456789AL);
    ASSERT_EQ(HexUtil::toLong("FEF7123456789ABC"), 0xFEF7123456789ABCL);
    ASSERT_EQ(HexUtil::toLong("ABCDEF"), 0xABCDEFL);
    ASSERT_EQ(HexUtil::toLong("abcdef"), 0xABCDEFL);
}

TEST(HexUtilTest, toHex_byte_array)
{
    ASSERT_EQ(HexUtil::toHex(static_cast<uint8_t>(0xFE)), "FE");
}

TEST(HexUtilTest, toHex_byte)
{
    ASSERT_EQ(HexUtil::toHex(static_cast<uint8_t>(0xFE)), "FE");
}

TEST(HexUtilTest, toHex_short)
{
    ASSERT_EQ(HexUtil::toHex(static_cast<uint16_t>(0xFE)), "FE");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint16_t>(0xFE34)), "FE34");
}

TEST(HexUtilTest, toHex_int)
{
    ASSERT_EQ(HexUtil::toHex(static_cast<uint32_t>(0xFE)), "FE");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint32_t>(0xFE34)), "FE34");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint32_t>(0xFE3456)), "FE3456");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint32_t>(0xFE345678)), "FE345678");
}

TEST(HexUtilTest, toHex_long)
{
    ASSERT_EQ(HexUtil::toHex(static_cast<uint64_t>(0xFEL)), "FE");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint64_t>(0xFE34L)), "FE34");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint64_t>(0xFE3456L)), "FE3456");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint64_t>(0xFE345678L)), "FE345678");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint64_t>(0xFE3456789AL)), "FE3456789A");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint64_t>(0xFE3456789ABCL)), "FE3456789ABC");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint64_t>(0xFE3456789ABCDEL)), "FE3456789ABCDE");
    ASSERT_EQ(HexUtil::toHex(static_cast<uint64_t>(0xFE3456789ABCDEF0L)), "FE3456789ABCDEF0");
}
