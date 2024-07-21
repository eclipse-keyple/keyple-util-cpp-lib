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
#include <mutex>
#include <typeinfo>
#include <vector>

#include "keyple/core/util/KeypleUtilExport.hpp"
#include "keyple/core/util/cpp/Logger.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

class KEYPLEUTIL_API LoggerFactory {
public:
    /**
     * Mutex for critical sections (std::cout usage)
     */
    static std::mutex mtx;

    /**
     *
     */
    static std::unique_ptr<Logger> getLogger(const std::type_info& type);
};

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
