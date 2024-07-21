/**************************************************************************************************
 * Copyright (c) 2024 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * This program and the accompanying materials are made available under the                       *
 * terms of the MIT License which is available at https://opensource.org/licenses/MIT.            *
 *                                                                                                *
 * SPDX-License-Identifier: MIT                                                                   *
 **************************************************************************************************/

#pragma once

#include <string>

#include "keyple/core/util/cpp/exception/Error.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class AssertionError : public Error {
public:
    /**
     *
     */
    AssertionError()
    : Error() {
    }

    /**
     *
     */
    explicit AssertionError(const std::string& msg)
    : Error(msg) {
    }
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
