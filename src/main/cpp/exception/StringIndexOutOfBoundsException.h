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

#include "IndexOutOfBoundsException.h"

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class StringIndexOutOfBoundsException : public IndexOutOfBoundsException {
public:
    /**
     *
     */
    StringIndexOutOfBoundsException(const std::string& message)
    : IndexOutOfBoundsException(message) {}

    /**
     *
     */
    StringIndexOutOfBoundsException(const std::string& message,
                                    const std::shared_ptr<Exception> cause)
    : IndexOutOfBoundsException(message, cause) {}
};

}
}
}
}
}
