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
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <ostream>
#include <regex>
#include <set>
#include <vector>

namespace std {

#if !defined(_WIN32)
template <typename To, typename From>
inline std::shared_ptr<To> reinterpret_pointer_cast(std::shared_ptr<From> const & ptr) noexcept
{
    return std::shared_ptr<To>(ptr, reinterpret_cast<To *>(ptr.get()));
}
#endif

inline std::ostream& operator<<(std::ostream& os, const uint8_t v)
{
    os << static_cast<int>(v)
       << "(0x" << std::hex << std::setfill('0') << std::setw(2)
       << static_cast<int>(v) << ")";

    return os;
}

inline std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t>& v)
{
    for (int i = 0; i < static_cast<int>(v.size()); i++)
        os << std::hex << std::setfill('0') << std::setw(2)
           << static_cast<int>(v[i]);

    return os;
}

inline std::ostream& operator<<(std::ostream& os, const std::vector<int>& v)
{
    for (int i = 0; i < static_cast<int>(v.size()); i++)
        os << std::hex << std::setfill('0') << std::setw(8)
           << static_cast<int>(v[i]);

    return os;
}

inline std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v)
{
    os << "{";
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        if (it != v.begin())
            os << ", ";
        os << *it;
    }
    os << "}";

    return os;
}

inline std::ostream& operator<<(std::ostream& os, const std::set<std::string>& s)
{
    os << "{";
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        if (it != s.begin())
            os << ", ";
        os << *it;
    }
    os << "}";

    return os;
}

template<class A, class B>
inline
std::ostream& operator<<(std::ostream& os, const std::map<A, B>& s)
{
    os << "MAP: {";
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        if (it != s.begin())
            os << ", ";
        os << "{" << it->first << ", " << it->second << "}";
    }
    os << "}";

    return os;
}

template <typename out>
inline void split(const std::string &s, const std::regex& re, out result)
{
    std::sregex_token_iterator d(s.begin(), s.end(), re, -1);
    std::sregex_token_iterator end;

    while (d != end) {
        *result++ = *d++;
    }
}

/* Trim from left */
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));

    return s;
}

/* Trim from right */
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);

    return s;
}

/* Trim from left & right */
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

}
