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

#include <exception>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace keyple {
namespace core {
namespace util {
namespace cpp {
namespace exception {

class Exception : public std::exception {
public:
    /**
     *
     */
    Exception() {}

    /**
     *
     */
    Exception(const Exception& o) : mMessage(o.mMessage), mCause(o.mCause) {}

    /**
     *
     */
    Exception(const std::string& message) : mMessage(message), mCause(nullptr) {}

    /**
     *
     */
    Exception(const std::string& message, const std::shared_ptr<Exception> cause)
    : mMessage(message), mCause(cause) {}

    /**
     * Returns the detail message string of this exception.
     */
    const std::string& getMessage() const
    {
        return mMessage;
    }

    /**
     * Returns the cause of the exception.
     */
    const std::shared_ptr<Exception> getCause() const
    {
        return mCause;
    }

    /**
     *
     */
    friend std::ostream& operator<<(std::ostream& os, const Exception& e)
    {
        os << "EXCEPTION: {"
           << "MESSAGE = " << e.mMessage;
    
        if (e.mCause != nullptr) {
            os << ", CAUSE = " << e.mCause->what();
        }
    
        os << "}";

        return os;
    }

    /**
     *
     */
    bool operator==(const Exception& o) const
    {
        return mMessage == o.mMessage &&
               mCause== o.mCause;
    }

private:
    /**
     *
     */
    const std::string mMessage;

    /**
     *
     */
    const std::shared_ptr<Exception> mCause;
};

}
}
}
}
}
