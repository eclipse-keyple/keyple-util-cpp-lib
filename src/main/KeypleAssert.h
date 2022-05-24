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

#include <memory>
#include <string>
#include <vector>

/* Util */
#include "KeypleUtilExport.h"
#include "IllegalArgumentException.h"

namespace keyple {
namespace core {
namespace util {

using namespace keyple::core::util::cpp::exception;

/**
 * Exposes useful methods for testing method call parameters and raising a IllegalArgumentException
 * unchecked exception.
 *
 * @since 2.0.0
 */
class KEYPLEUTIL_API Assert final {
public:
    /**
     * Gets the unique instance.
     *
     * @return the instance
     */
    static Assert& getInstance();

    /**
     * Assert that the input object is not null.
     *
     * @param obj the object to check
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if object is null
     * @since 2.0
     */
    template <typename T>
    Assert& notNull(const std::shared_ptr<T> obj, const std::string& name)
    {
        if (obj == nullptr) {
            throw IllegalArgumentException(ARGUMENT + name + IS_NULL);
        }

        return *this;
    }

    /**
     * Assert that the input string is not null and not empty.
     *
     * @param obj the object to check
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if object is null or empty
     * @since 2.0.0
     */
    Assert& notEmpty(const std::string& obj, const std::string& name);

    /**
     * Assert that a collection of objects is not null and not empty.
     *
     * @param obj the object to check
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if object is null or empty
     * @since 2.0.0
     */
    template<typename T>
    Assert& notEmpty(const std::vector<T>& obj, const std::string& name)
    {
        if (obj.empty()) {
            throw IllegalArgumentException(ARGUMENT + name + IS_EMPTY);
        }

        return *this;
    }

    /**
     * Assert that a byte array is not null and not empty.
     *
     * @param obj the object to check
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if object is null or empty
     * @since 2.0.0
     */
    Assert& notEmpty(const std::vector<uint8_t>& obj, const std::string& name);

    /**
     * Assert that a condition is true.
     *
     * @param condition the condition to check
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if condition is null or false
     * @since 2.0.0
     */
    Assert& isTrue(const bool condition, const std::string& name);

    /**
     * Assert that an integer is not null and is greater than or equal to minValue.
     *
     * @param number the number to check
     * @param minValue the min accepted value
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if number is null or has a value less than minValue.
     * @since 2.0.0
     */
    Assert& greaterOrEqual(const int number, const int minValue, const std::string& name);

    /**
     * Assert that an integer is equal to value.
     *
     * @param number the number to check
     * @param value the expected value
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if number is null or has a value less than minValue.
     * @since 2.0.0
     */
    Assert& isEqual(const int number, const int value, const std::string& name);

    /**
     * Assert that an integer is not null and is in the range minValue, maxValue.
     *
     * @param number the number to check
     * @param minValue the min accepted value
     * @param maxValue the max accepted value
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if number is null or is out of range.
     * @since 2.0.0
     */
    Assert& isInRange(const int number,
                      const int minValue,
                      const int maxValue,
                      const std::string& name);

private:
    /**
     *
     */
    static const std::string ARGUMENT;
    static const std::string CONDITION;
    static const std::string HAS_A_VALUE;
    static const std::string LESS_THAN;
    static const std::string GREATER_THAN;
    static const std::string IS_NULL;
    static const std::string IS_EMPTY;
    static const std::string IS_FALSE;
    static const std::string NOT_EQUAL_TO;
    static const std::string CLOSING_BRACKET;

    /**
     * Private Constructor
     */
    Assert();
};

}
}
}
