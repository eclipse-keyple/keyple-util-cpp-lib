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

#include "keyple/core/util/cpp/exception/IllegalArgumentException.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class PatternSyntaxException : public IllegalArgumentException {
public:
    /**
     *
     */
    explicit PatternSyntaxException(const std::string& message)
    : IllegalArgumentException(message)
    {
    }

    /**
     *
     */
    PatternSyntaxException(
        const std::string& message, const std::shared_ptr<Exception> cause)
    : IllegalArgumentException(message, cause)
    {
    }
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
