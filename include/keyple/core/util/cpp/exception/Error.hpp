/**************************************************************************************************
 * Copyright (c) 2024 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * This program and the accompanying materials are made available under the                       *
 * terms of the MIT License which is available at https://opensource.org/licenses/MIT.            *
 *                                                                                                *
 * SPDX-License-Identifier: MIT                                                                   *
 **************************************************************************************************/

#pragma once

#include <exception>
#include <string>

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class Error : public std::exception {
public:
    /**
     *
     */
    Error()
    : mMessage("")
    {
    }

    /**
     *
     */
    explicit Error(const std::string& msg)
    : mMessage(msg)
    {
    }

private:
    /**
     *
     */
    const std::string mMessage;
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
