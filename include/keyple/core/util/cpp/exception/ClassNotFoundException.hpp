/**************************************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * This program and the accompanying materials are made available under the                       *
 * terms of the MIT License which is available at https://opensource.org/licenses/MIT.            *
 *                                                                                                *
 * SPDX-License-Identifier: MIT                                                                   *
 **************************************************************************************************/

#pragma once

#include <string>

#include "Exception.h"

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class ClassNotFoundException : public Exception {
public:
    /**
     *
     */
    explicit ClassNotFoundException(const std::string& message)
    : Exception(message)
    {
    }

    /**
     *
     */
    ClassNotFoundException(const std::string& message, const std::exception cause)
    : Exception(message, cause)
    {
    }
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
