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

#include "keyple/core/util/cpp/exception/IOException.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class FileNotFoundException : public IOException {
public:
    /**
     *
     */
    explicit FileNotFoundException(const std::string& message)
    : IOException(message)
    {
    }

    /**
     *
     */
    FileNotFoundException(const std::string& message, const std::exception cause)
    : IOException(message, cause)
    {
    }
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
