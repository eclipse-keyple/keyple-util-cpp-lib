/******************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#pragma once

#include <memory>
#include <string>

#include "keyple/core/util/cpp/exception/RuntimeException.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class IndexOutOfBoundsException : public RuntimeException {
public:
    /**
     *
     */
    explicit IndexOutOfBoundsException(const std::string& message)
    : RuntimeException(message)
    {
    }

    /**
     *
     */
    IndexOutOfBoundsException(
        const std::string& message, const std::shared_ptr<Exception> cause)
    : RuntimeException(message, cause)
    {
    }
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
