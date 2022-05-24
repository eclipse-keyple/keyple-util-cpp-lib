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

#include "KeypleAssert.h"

namespace keyple {
namespace core {
namespace util {

const std::string Assert::ARGUMENT        = "Argument [";
const std::string Assert::CONDITION       = "Condition [";
const std::string Assert::HAS_A_VALUE     = "] has a value [";
const std::string Assert::LESS_THAN       = "] less than [";
const std::string Assert::GREATER_THAN    = "] greater than [";
const std::string Assert::IS_NULL         = "] is null.";
const std::string Assert::IS_EMPTY        = "] is empty.";
const std::string Assert::IS_FALSE        = "] is false.";
const std::string Assert::NOT_EQUAL_TO    = "] not equal to [";
const std::string Assert::CLOSING_BRACKET = "].";

Assert::Assert() {}

Assert& Assert::getInstance()
{
    static Assert INSTANCE;

    return INSTANCE;
}

Assert& Assert::notEmpty(const std::string& obj, const std::string& name)
{

    if (obj == "") {
        throw IllegalArgumentException(ARGUMENT + name + IS_EMPTY);
    }

    return *this;
}

Assert& Assert::notEmpty(const std::vector<uint8_t>& obj, const std::string& name)
{
    if (obj.size() == 0) {
        throw IllegalArgumentException(ARGUMENT + name + IS_EMPTY);
    }

    return *this;
}

Assert& Assert::isTrue(const bool condition, const std::string& name)
{
    if (!condition) {
        throw IllegalArgumentException(CONDITION + name + IS_FALSE);
    }

    return *this;
}

Assert& Assert::greaterOrEqual(const int number, const int minValue, const std::string& name)
{
    if (number < minValue) {
        throw IllegalArgumentException(ARGUMENT +
                                       name +
                                       HAS_A_VALUE +
                                       std::to_string(number) +
                                       LESS_THAN +
                                       std::to_string(minValue) +
                                       CLOSING_BRACKET);
    }

    return *this;
}

Assert& Assert::isEqual(const int number, const int value, const std::string& name)
{
    if (number != value) {
        throw IllegalArgumentException(ARGUMENT +
                                       name +
                                       HAS_A_VALUE +
                                       std::to_string(number) +
                                       NOT_EQUAL_TO +
                                       std::to_string(value) +
                                       CLOSING_BRACKET);
    }

    return *this;
}

Assert& Assert::isInRange(const int number,
                          const int minValue,
                          const int maxValue,
                          const std::string& name)
{
    if (number < minValue) {
       throw IllegalArgumentException(ARGUMENT +
                                      name +
                                      HAS_A_VALUE +
                                      std::to_string(number) +
                                      LESS_THAN +
                                      std::to_string(minValue) +
                                      CLOSING_BRACKET);
    } else if (number > maxValue) {
        throw IllegalArgumentException(ARGUMENT +
                                       name +
                                       HAS_A_VALUE +
                                       std::to_string(number) +
                                       GREATER_THAN +
                                       std::to_string(maxValue) +
                                       CLOSING_BRACKET);
    }

    return *this;
}

}
}
}
