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
    FileNotFoundException(
        const std::string& message, const std::exception cause)
    : IOException(message, cause)
    {
    }
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
