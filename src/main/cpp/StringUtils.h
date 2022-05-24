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

#include <cstdarg>
#include <regex>
#include <string>

namespace keyple {
namespace core {
namespace util {
namespace cpp {

class StringUtils {
public:
    static inline const std::string format(const char* format, ...)
    {
        char buf[1024];
        va_list args;

        va_start(args, format);
        vsprintf(buf, format, args);
        va_end(args);

        return buf;
    }

    static inline bool contains(const std::string& s1, const std::string& s2)
    {
        return s1.find(s2) != std::string::npos;
    }

    static inline bool matches(const std::string& s, const std::string& regex)
    {
        std::regex r(regex);

        return std::regex_match(s, r);
    }

    static inline const std::vector<std::string> split(const std::string& string,
                                                       const std::string& delimiter)
    {
        std::vector<std::string> tokens;
        std::string s = string;

        size_t pos = 0;

        while ((pos = s.find(delimiter)) != std::string::npos) {
            tokens.push_back(s.substr(0, pos));
            s.erase(0, pos + delimiter.length());
        }

        return tokens;
    }
};

}
}
}
}
