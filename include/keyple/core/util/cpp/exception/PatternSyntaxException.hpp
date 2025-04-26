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
