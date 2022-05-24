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

#pragma once

#include <memory>
#include <mutex>
#include <typeinfo>
#include <vector>

/* Util */
#include "KeypleUtilExport.h"
#include "Logger.h"

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

}
}
}
}
