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

#include <cstdint>
#include <string>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "keyple/core/util/HexUtil.hpp"
#include "keyple/core/util/cpp/KeypleStd.hpp"
#include "keyple/core/util/cpp/Logger.hpp"
#include "keyple/core/util/cpp/LoggerFactory.hpp"

using keyple::core::util::HexUtil;
using keyple::core::util::cpp::Logger;
using keyple::core::util::cpp::LoggerFactory;

class LoggerTest { };

TEST(LoggerTest, debug)
{
    auto logger(LoggerFactory::getLogger(typeid(LoggerTest)));

    logger->debug("This is a int: %\n", static_cast<int>(27));
    logger->debug("This is a uint8_t: %\n", static_cast<uint8_t>(27));
    logger->debug("This is a C++ string: %\n", std::string("C++ style string"));
    std::vector<uint8_t> vec = {0x01, 0x02, 0xFF, 0x04};
    logger->debug("This is a vector: %\n", vec);
}
