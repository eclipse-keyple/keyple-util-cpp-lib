/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#include "LoggerFactory.h"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

std::mutex LoggerFactory::mtx;

std::unique_ptr<Logger> LoggerFactory::getLogger(const std::type_info& type)
{
    return std::unique_ptr<Logger>(new Logger(type.name(), &mtx));
}

}
}
}
}
