/**************************************************************************************************
 * Copyright (c) 2024 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * This program and the accompanying materials are made available under the                       *
 * terms of the MIT License which is available at https://opensource.org/licenses/MIT.            *
 *                                                                                                *
 * SPDX-License-Identifier: MIT                                                                   *
 **************************************************************************************************/

#pragma once

#include <memory>
#include <string>

#include "keyple/core/util/cpp/exception/IndexOutOfBoundsException.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class StringIndexOutOfBoundsException : public IndexOutOfBoundsException {
public:
    /**
     *
     */
    explicit StringIndexOutOfBoundsException(const std::string& message)
    : IndexOutOfBoundsException(message) {
    }

    /**
     *
     */
    StringIndexOutOfBoundsException(
        const std::string& message, const std::shared_ptr<Exception> cause)
    : IndexOutOfBoundsException(message, cause) {
    }
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
