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

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <regex>
#include <string>
#include <vector>

#include "keyple/core/util/cpp/exception/PatternSyntaxException.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

using keyple::core::util::cpp::exception::PatternSyntaxException;

class StringUtils {
public:
    static inline const std::string
    format(const char* format, ...)
    {
        char buf[1024];
        va_list args;

        va_start(args, format);
        vsnprintf(buf, sizeof(buf), format, args);
        va_end(args);

        return buf;
    }

    static inline bool
    contains(const std::string& s1, const std::string& s2)
    {
        return s1.find(s2) != std::string::npos;
    }

    static inline bool
    matches(const std::string& s, const std::string& regex)
    {
        try {
            std::regex r(regex);
            return std::regex_match(s, r);

        } catch (const std::regex_error& e) {
            throw PatternSyntaxException(e.what());
        }
    }

    static inline const std::vector<std::string>
    split(const std::string& s, const std::string& delimiter)
    {
        std::vector<std::string> tokens;
        std::string _s = s;

        size_t pos = 0;

        while ((pos = _s.find(delimiter)) != std::string::npos) {
            tokens.push_back(_s.substr(0, pos));
            _s.erase(0, pos + delimiter.length());
        }

        return tokens;
    }

    static inline const std::string
    tolower(const std::string& s)
    {
        std::string copy = s;
        std::transform(
            copy.begin(), copy.end(), copy.begin(), [](unsigned char c) {
                return static_cast<char>(std::tolower(c));
            });

        return copy;
    }

    static inline const std::string
    toupper(const std::string& s)
    {
        std::string copy = s;
        std::transform(
            copy.begin(), copy.end(), copy.begin(), [](unsigned char c) {
                return static_cast<char>(std::toupper(c));
            });

        return copy;
    }

    static inline bool
    startsWith(const std::string& s, const std::string& start)
    {
        return s.rfind(start, 0) == 0;
    }
};

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
