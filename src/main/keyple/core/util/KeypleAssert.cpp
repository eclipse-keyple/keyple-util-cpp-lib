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

#include "keyple/core/util/KeypleAssert.hpp"

#include <string>
#include <vector>

#include "keyple/core/util/HexUtil.hpp"

namespace keyple {
namespace core {
namespace util {

const char* Assert::ARGUMENT = "Argument [";
const char* Assert::CONDITION = "Condition [";
const char* Assert::HAS_A_VALUE = "] has a value [";
const char* Assert::LESS_THAN = "] less than [";
const char* Assert::GREATER_THAN = "] greater than [";
const char* Assert::IS_NULL = "] is null.";
const char* Assert::IS_EMPTY = "] is empty.";
const char* Assert::IS_FALSE = "] is false.";
const char* Assert::IS_NOT_HEX = "] is not a hex string.";
const char* Assert::NOT_EQUAL_TO = "] not equal to [";
const char* Assert::CLOSING_BRACKET = "].";

Assert::Assert()
{
}

Assert&
Assert::getInstance()
{
    static Assert INSTANCE;

    return INSTANCE;
}

Assert&
Assert::notEmpty(const std::string& obj, const std::string& name)
{
    if (obj == "") {
        throw IllegalArgumentException(ARGUMENT + name + IS_EMPTY);
    }

    return *this;
}

Assert&
Assert::notEmpty(const std::vector<uint8_t>& obj, const std::string& name)
{
    if (obj.size() == 0) {
        throw IllegalArgumentException(ARGUMENT + name + IS_EMPTY);
    }

    return *this;
}

Assert&
Assert::isTrue(const bool condition, const std::string& name)
{
    if (!condition) {
        throw IllegalArgumentException(CONDITION + name + IS_FALSE);
    }

    return *this;
}

Assert&
Assert::greaterOrEqual(
    const size_t number, const size_t minValue, const std::string& name)
{
    if (number < minValue) {
        throw IllegalArgumentException(
            ARGUMENT + name + HAS_A_VALUE + std::to_string(number) + LESS_THAN
            + std::to_string(minValue) + CLOSING_BRACKET);
    }

    return *this;
}

Assert&
Assert::isEqual(
    const size_t number, const size_t value, const std::string& name)
{
    if (number != value) {
        throw IllegalArgumentException(
            ARGUMENT + name + HAS_A_VALUE + std::to_string(number)
            + NOT_EQUAL_TO + std::to_string(value) + CLOSING_BRACKET);
    }

    return *this;
}

Assert&
Assert::isInRange(
    const size_t number,
    const size_t minValue,
    const size_t maxValue,
    const std::string& name)
{
    if (number < minValue) {
        throw IllegalArgumentException(
            ARGUMENT + name + HAS_A_VALUE + std::to_string(number) + LESS_THAN
            + std::to_string(minValue) + CLOSING_BRACKET);
    } else if (number > maxValue) {
        throw IllegalArgumentException(
            ARGUMENT + name + HAS_A_VALUE + std::to_string(number)
            + GREATER_THAN + std::to_string(maxValue) + CLOSING_BRACKET);
    }

    return *this;
}

Assert&
Assert::isHexString(const std::string& hex, const std::string& name)
{
    if (!HexUtil::isValid(hex)) {
        throw IllegalArgumentException(ARGUMENT + name + IS_NOT_HEX);
    }

    return *this;
}

} /* namespace util */
} /* namespace core */
} /* namespace keyple */
