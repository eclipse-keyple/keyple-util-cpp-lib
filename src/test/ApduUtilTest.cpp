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

#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "keyple/core/util/ApduUtil.hpp"
#include "keyple/core/util/HexUtil.hpp"

using keyple::core::util::ApduUtil;
using keyple::core::util::HexUtil;

const uint8_t CLA = 0x11;
const uint8_t INS = 0x22;
const uint8_t P1 = 0x33;
const uint8_t P2 = 0x44;
const std::vector<uint8_t> DATA_IN = {0x12, 0x34, 0x56, 0x78};
const uint8_t LE = 3;

const std::vector<uint8_t> CASE1 = HexUtil::toByteArray("1122334400");
const std::vector<uint8_t> CASE2 = HexUtil::toByteArray("1122334403");
const std::vector<uint8_t> CASE3 = HexUtil::toByteArray("112233440412345678");
const std::vector<uint8_t> CASE4 = HexUtil::toByteArray("11223344041234567803");

TEST(ApduUtilTest, build_whenDataInAndLeAreNull_shouldReturnCase1)
{
    std::vector<uint8_t> apduCommand = ApduUtil::build(CLA, INS, P1, P2);

    ASSERT_EQ(apduCommand, CASE1);
}

TEST(ApduUtilTest, build_whenDataInIsNull_shouldReturnCase2)
{
    std::vector<uint8_t> apduCommand = ApduUtil::build(CLA, INS, P1, P2, LE);

    ASSERT_EQ(apduCommand, CASE2);
}

TEST(ApduUtilTest, build_whenLeIsNull_shouldReturnCase3)
{
    std::vector<uint8_t> apduCommand
        = ApduUtil::build(CLA, INS, P1, P2, DATA_IN);

    ASSERT_EQ(apduCommand, CASE3);
}

TEST(ApduUtilTest, build_whenDataInAndLeAreNotNull_shouldReturnCase4)
{
    std::vector<uint8_t> apduCommand
        = ApduUtil::build(CLA, INS, P1, P2, DATA_IN, LE);

    ASSERT_EQ(apduCommand, CASE4);
}

TEST(ApduUtilTest, isCase4_whenCase1_shouldReturnFalse)
{
    ASSERT_FALSE(ApduUtil::isCase4(CASE1));
}

TEST(ApduUtilTest, isCase4_whenCase2_shouldReturnFalse)
{
    ASSERT_FALSE(ApduUtil::isCase4(CASE2));
}

TEST(ApduUtilTest, isCase4_whenCase3_shouldReturnFalse)
{
    ASSERT_FALSE(ApduUtil::isCase4(CASE3));
}

TEST(ApduUtilTest, isCase4_whenCase4_shouldReturnFalse)
{
    ASSERT_TRUE(ApduUtil::isCase4(CASE4));
}
