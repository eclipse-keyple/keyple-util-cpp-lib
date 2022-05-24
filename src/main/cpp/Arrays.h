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

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

/* Keyple Core Util */
#include "IndexOutOfBoundsException.h"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

using namespace keyple::core::util::cpp::exception;

class Arrays {
public:
    static bool equals(const std::vector<char>& a1, const std::vector<char>& a2)
    {
        if (a1.size() != a2.size()) {
            return false;
        }

        for (auto i1 = a1.begin(), i2 = a2.begin(); i1 != a1.end();
            i1++, i2++) {
            if (*i1 != *i2)
                return false;
        }

        return true;
    }

    static bool equals(const std::vector<uint8_t>& a1, const std::vector<uint8_t>& a2)
    {
        if (a1.size() != a2.size()) {
            return false;
        }

        for (auto i1 = a1.begin(), i2 = a2.begin(); i1 != a1.end();
            i1++, i2++) {
            if (*i1 != *i2)
                return false;
        }

        return true;
    }

    static int hashCode(const std::vector<char> a)
    {
        int hash = 0;

        for (auto i = a.begin(); i != a.end(); i++)
            hash ^= *i;

        return hash;
    }

    static int hashCode(const std::vector<uint8_t> a)
    {
        int hash = 0;

        for (auto i = a.begin(); i != a.end(); i++)
            hash ^= *i;

        return hash;
    }

    static std::vector<char> copyOfRange(const std::vector<char>& original,
                                         const int from,
                                         const int to)
    {
        if ((to - from) > static_cast<int>(original.size())) {
            throw IndexOutOfBoundsException("index out of bound");
        }

        std::vector<char> vec;
        std::copy(original.begin() + from, original.begin() + to, std::back_inserter(vec));

        return vec;
    }

    static std::vector<uint8_t> copyOfRange(const std::vector<uint8_t>& original,
                                            const int from,
                                            const int to)
    {
        if ((to - from) > static_cast<int>(original.size())) {
            throw IndexOutOfBoundsException("index out of bound");
        }

        std::vector<uint8_t> vec;
        std::copy(original.begin() + from, original.begin() + to, std::back_inserter(vec));

        return vec;
    }

    template <typename T>
    static bool contains(const std::vector<T>& a, const T b)
    {
        for (const auto& v : a) {
            if (v == b) {
                return true;
            }
        }

        return false;
    }

    template <typename T>
    static bool containsAll(std::vector<T> a, std::vector<T> b)
    {
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());

        return std::includes(a.begin(), a.end(), b.begin(), b.end());
    }

    template <typename T>
    static bool containsOnly(const std::vector<T>& a, const T b)
    {
        for (const auto& v : a) {
            if (v != b) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    static int indexOf(const std::vector<T>& a, const T b)
    {
        auto it = std::find(a.begin(), a.end(), b);
        if (it != a.end()) {
            return static_cast<int>(it - a.begin());
        }

        return -1;
    }

    template <typename T, typename U>
    static bool addAll(std::vector<std::shared_ptr<T>>& a, const std::vector<std::shared_ptr<U>>& b)
    {
        if (b.size() == 0) {
            return false;
        }

        for (const auto& u : b) {
            a.push_back(std::dynamic_pointer_cast<T>(u));
        }

        return true;
    }

    template <typename T>
    static void remove(std::vector<std::shared_ptr<T>>& a, const std::shared_ptr<T>& b)
    {
        const auto it = std::find(a.begin(), a.end(), b);
        if (it != a.end()) {
            /* Value is present */
            a.erase(it);
        }
    }

    template <typename T, typename U>
    static bool removeAll(std::vector<std::shared_ptr<T>>& a, const std::vector<std::shared_ptr<U>>& b)
    {
        bool ret = false;

        if (b.size() == 0) {
            return false;
        }

        for (const auto& u : b) {
            const auto t = std::dynamic_pointer_cast<T>(u);
            const auto it = std::find(a.begin(), a.end(), t);
            if (it != a.end()) {
                /* Value is present, remove it and set ret to true */
                a.erase(it);
                ret = true;
            }
        }

        return ret;
    }

    template <typename T>
    static void fill(std::vector<T>& a, int from_Index, int to_Index, T val)
    {
        for (int i = from_Index; i < to_Index; i++) {
            a[i] = val;
        }
    }
};

}
}
}
}
