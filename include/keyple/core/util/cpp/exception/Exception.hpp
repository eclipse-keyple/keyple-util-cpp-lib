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

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

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
    Exception() = default;

    /**
     *
     */
    ~Exception() = default;

    /**
     * Constructor.
     */
    explicit Exception(const std::string& message)
    : mMessage(message)
    {
    }

    /**
     * Constructor.
     */
    Exception(const std::string& message, const Exception& cause)
    : mMessage(message)
    , mCause(std::unique_ptr<Exception>(new Exception(cause)))
    {
    }

    /**
     * Move constructor.
     */
    Exception(Exception&& other) noexcept
    : mMessage(std::move(other.mMessage))
    , mCause(std::move(other.mCause))
    {
    }

    /**
     * Copy constructor.
     */
    Exception(const Exception& other)
    : mMessage(other.mMessage)
    {
        if (other.mCause) {
            mCause = std::unique_ptr<Exception>(new Exception(*other.mCause));
        }
    }

    /**
     * Returns the detail message string of this exception.
     */
    const std::string&
    getMessage() const
    {
        return mMessage;
    }

    /**
     * Returns the cause of the exception.
     */
    Exception*
    getCause() const
    {
        return (mCause == nullptr) ? nullptr : mCause.get();
    }

    /**
     *
     */
    friend std::ostream&
    operator<<(std::ostream& os, const Exception& e)
    {
        os << "EXCEPTION: {"
           << "MESSAGE = " << e.mMessage << ", "
           << "CAUSE = " << (e.mCause ? e.mCause->getMessage() : "null") << "}";

        return os;
    }

    /**
     *
     */
    bool
    operator==(const Exception& o) const
    {
        return mMessage == o.mMessage
               && mCause->getMessage() == o.mCause->getMessage();
    }

private:
    /**
     *
     */
    std::string mMessage;

    /**
     *
     */
    std::unique_ptr<Exception> mCause;
};

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
