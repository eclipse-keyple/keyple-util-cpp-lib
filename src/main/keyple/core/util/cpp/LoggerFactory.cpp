/**************************************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * This program and the accompanying materials are made available under the                       *
 * terms of the MIT License which is available at https://opensource.org/licenses/MIT.            *
 *                                                                                                *
 * SPDX-License-Identifier: MIT                                                                   *
 **************************************************************************************************/

#include "keyple/core/util/cpp/LoggerFactory.hpp"

#include <memory>

namespace keyple {
namespace core {
namespace util {
namespace cpp {

std::mutex LoggerFactory::mtx;

std::unique_ptr<Logger>
LoggerFactory::getLogger(const std::type_info& type)
{
    return std::unique_ptr<Logger>(new Logger(type.name(), &mtx));
}

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
