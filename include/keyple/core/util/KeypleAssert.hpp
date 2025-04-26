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

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "keyple/core/util/KeypleUtilExport.hpp"
#include "keyple/core/util/cpp/exception/IllegalArgumentException.hpp"

namespace keyple {
namespace core {
namespace util {

using keyple::core::util::cpp::exception::IllegalArgumentException;

/**
 * Exposes useful methods for testing method call parameters and raising a
 * IllegalArgumentException unchecked exception.
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
    Assert&
    notNull(const std::shared_ptr<T> obj, const std::string& name)
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
    template <typename T>
    Assert&
    notEmpty(const std::vector<T>& obj, const std::string& name)
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
     * Assert that an integer is not null and is greater than or equal to
     * minValue.
     *
     * @param number the number to check
     * @param minValue the min accepted value
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if number is null or has a value less
     * than minValue.
     * @since 2.0.0
     */
    Assert& greaterOrEqual(
        const size_t number, const size_t minValue, const std::string& name);

    /**
     * Assert that an integer is equal to value.
     *
     * @param number the number to check
     * @param value the expected value
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if number is null or has a value less
     * than minValue.
     * @since 2.0.0
     */
    Assert&
    isEqual(const size_t number, const size_t value, const std::string& name);

    /**
     * Assert that an integer is not null and is in the range minValue,
     * maxValue.
     *
     * @param number the number to check
     * @param minValue the min accepted value
     * @param maxValue the max accepted value
     * @param name the object name
     * @return the current instance
     * @throw IllegalArgumentException if number is null or is out of range.
     * @since 2.0.0
     */
    Assert& isInRange(
        const size_t number,
        const size_t minValue,
        const size_t maxValue,
        const std::string& name);

    /**
     * Assert that a string has a valid hexadecimal format.
     *
     * @param hex The string to check.
     * @param name The object name.
     * @return The current instance.
     * @throw IllegalArgumentException If the provided string is null, empty or
     * has not a valid hexadecimal format.
     * @since 2.1.0
     */
    Assert& isHexString(const std::string& hex, const std::string& name);

private:
    /**
     *
     */
    static const char* ARGUMENT;
    static const char* CONDITION;
    static const char* HAS_A_VALUE;
    static const char* LESS_THAN;
    static const char* GREATER_THAN;
    static const char* IS_NULL;
    static const char* IS_EMPTY;
    static const char* IS_FALSE;
    static const char* IS_NOT_HEX;
    static const char* NOT_EQUAL_TO;
    static const char* CLOSING_BRACKET;

    /**
     * Private Constructor
     */
    Assert();
};

} /* namespace util */
} /* namespace core */
} /* namespace keyple */
