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

#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <ostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#ifdef __GNUG__  // gnu C++ compiler
#include <cxxabi.h>
#endif

#include "keyple/core/util/KeypleUtilExport.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

class KEYPLEUTIL_API Logger {
public:
    /**
     *
     */
    enum class Level {
        logNone = 0,
        logError,
        logWarn,
        logInfo,
        logDebug,
        logTrace
    };

    /**
     * Constructor
     */
    Logger(const std::string& className, std::mutex* mtx);

    /**
     *
     */
    std::string getClassName();

    /**
     *
     */
    static void setLoggerLevel(Level level);

    /**
     *
     */
    template <typename... Args>
    void
    trace(const std::string& format, Args... args)
    {
        if (mLevel >= Level::logTrace)
            log("TRACE", format, std::forward<Args>(args)...);
    }

    /**
     *
     */
    template <typename... Args>
    void
    debug(const std::string& format, Args... args)
    {
        if (mLevel >= Level::logDebug)
            log("DEBUG", format, std::forward<Args>(args)...);
    }

    /**
     *
     */
    template <typename... Args>
    void
    warn(const std::string& format, Args... args)
    {
        if (mLevel >= Level::logWarn)
            log("WARN", format, std::forward<Args>(args)...);
    }

    /**
     *
     */
    template <typename... Args>
    void
    info(const std::string& format, Args... args)
    {
        if (mLevel >= Level::logInfo)
            log("INFO", format, std::forward<Args>(args)...);
    }

    /**
     *
     */
    template <typename... Args>
    void
    error(const std::string& format, Args... args)
    {
        if (mLevel >= Level::logError)
            log("ERROR", format, std::forward<Args>(args)...);
    }

private:
    /**
     *
     */
    static Level mLevel;

    /**
     *
     */
    const size_t maxClassNameLength = 100;

    /**
     *
     */
    const std::string className;

    /**
     *
     */
    std::mutex* mtx;

    /**
     *
     */
    static const std::string getCurrentTimestamp();

    /**
     *
     */
#ifdef __GNUG__  // gnu C++ compiler
    std::string
    demangle(const char* mangled_name)
    {
        std::size_t len = 0;
        int status = 0;
        std::unique_ptr<char, decltype(&std::free)> ptr(
            __cxxabiv1::__cxa_demangle(mangled_name, nullptr, &len, &status),
            &std::free);
        std::string s(ptr.get());
        if (s.size() > maxClassNameLength)
            s.resize(maxClassNameLength);
        return s;
    }
#else
    std::string
    demangle(const char* name)
    {
        std::string s(name);
        if (s.size() > maxClassNameLength)
            s.resize(maxClassNameLength);
        return s;
    }
#endif  // _GNUG_

    void
    printf(std::ostringstream& os, const char* s)
    {
        while (s && *s) {
            if (*s == '%' && *(s + 1) != '%')
                throw std::runtime_error("invalid format: missing arguments");
            os << *s++;
        }
    }

    template <typename T, typename... Args>
    void
    printf(std::ostringstream& os, const char* s, T& value, Args... args)
    {
        while (s && *s) {
            if (*s == '%' && *(s + 1) != '%') {
                os << value;
                return printf(os, ++s, args...);
            }
            os << *s++;
        }
        throw std::runtime_error("extra arguments provided to printf");
    }

    template <typename T, typename... Args>
    void
    printf(std::ostringstream& os, const char* s, const T* value, Args... args)
    {
        while (s && *s) {
            if (*s == '%' && *(s + 1) != '%') {
                os << *value;
                return printf(os, ++s, args...);
            }
            os << *s++;
        }
        throw std::runtime_error("extra arguments provided to printf");
    }

    /**
     * Because of variadic templates usage, the function must be declared and
     * defined in the header file.
     */
    template <typename... Args>
    void
    log(const std::string& label, const std::string& format, Args... args)
    {
        const std::lock_guard<std::mutex> lock(*mtx);

        /* Header */
        std::string name = className;
        name.resize(70);
        std::printf(
            "[%s]   [%5s]   [%-70s]   ",
            getCurrentTimestamp().c_str(),
            label.c_str(),
            name.c_str());

        /* Actual log */
        std::ostringstream os;
        printf(os, format.c_str(), args...);
        const std::string& str = os.str();
        std::printf("%s", str.c_str());
    }
};

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
