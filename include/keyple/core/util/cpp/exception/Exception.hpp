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
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

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
    Exception() {
    }

    /**
     *
     */
    Exception(const Exception& o)
    : mMessage(o.mMessage)
    , mCause(o.mCause) {
    }

    /**
     *
     */
    explicit Exception(const std::string& message)
    : mMessage(message)
    , mCause(nullptr) {
    }

    /**
     *
     */
    Exception(const std::string& message, const std::shared_ptr<Exception> cause)
    : mMessage(message)
    , mCause(cause) {
    }

    /**
     * Returns the detail message string of this exception.
     */
    const std::string&
    getMessage() const {
        return mMessage;
    }

    /**
     * Returns the cause of the exception.
     */
    const std::shared_ptr<Exception>
    getCause() const {
        return mCause;
    }

    /**
     *
     */
    const char*
    what() const noexcept override {
        return mMessage.c_str();
    }

    /**
     *
     */
    friend std::ostream&
    operator<<(std::ostream& os, const Exception& e) {
        os << "EXCEPTION: {" << "MESSAGE = " << e.mMessage;

        if (e.mCause != nullptr) {
            os << ", CAUSE = " << e.mCause->what();
        }

        os << "}";

        return os;
    }

    /**
     *
     */
    bool
    operator==(const Exception& o) const {
        return mMessage == o.mMessage && mCause == o.mCause;
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

} /* namespace exception */
} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
