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
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "keyple/core/util/cpp/exception/IllegalArgumentException.hpp"
#include "keyple/core/util/cpp/exception/IndexOutOfBoundsException.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

using keyple::core::util::cpp::exception::IllegalArgumentException;
using keyple::core::util::cpp::exception::IndexOutOfBoundsException;

class Arrays {
public:
    static bool
    equals(const std::vector<char>& a1, const std::vector<char>& a2)
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

    static bool
    equals(const std::vector<uint8_t>& a1, const std::vector<uint8_t>& a2)
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

    static int
    hashCode(const std::vector<char>& a)
    {
        int hash = 0;

        std::for_each(a.begin(), a.end(), [&](const char i) { hash ^= i; });

        return hash;
    }

    static int
    hashCode(const std::vector<uint8_t>& a)
    {
        int hash = 0;

        std::for_each(a.begin(), a.end(), [&](const uint8_t i) { hash ^= i; });

        return hash;
    }

    /**
     * Copies the specified array, truncating or padding with false (if
     * necessary) so the copy has the specified length.
     */
    static std::vector<uint8_t>
    copyOf(const std::vector<uint8_t>& original, const size_t size)
    {
        std::vector<uint8_t> vec;
        std::copy(
            original.begin(), original.begin() + size, std::back_inserter(vec));

        return vec;
    }

    static std::vector<char>
    copyOfRange(
        const std::vector<char>& original, const size_t from, const size_t to)
    {
        if ((to - from) > original.size()) {
            throw IndexOutOfBoundsException("index out of bound");
        }

        std::vector<char> vec;
        std::copy(
            original.begin() + from,
            original.begin() + to,
            std::back_inserter(vec));

        return vec;
    }

    static std::vector<uint8_t>
    copyOfRange(
        const std::vector<uint8_t>& original,
        const size_t from,
        const size_t to)
    {
        if (from > original.size()) {
            throw IndexOutOfBoundsException("from > original.size()");
        }

        if (from > to) {
            throw IllegalArgumentException("from > to");
        }

        std::vector<uint8_t> vec;

        if (to <= original.size()) {
            std::copy(
                original.begin() + from,
                original.begin() + to,
                std::back_inserter(vec));
        } else {
            std::copy(
                original.begin() + from,
                original.begin() + original.size(),
                std::back_inserter(vec));
            vec.resize(to - from, 0);
        }

        return vec;
    }

    template <typename T>
    static bool
    contains(const std::vector<T>& a, const T b)
    {
        return std::any_of(a.begin(), a.end(), [&](T i) { return i == b; });
    }

    template <typename T>
    static bool
    containsAll(std::vector<T> a, std::vector<T> b)
    {
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());

        return std::includes(a.begin(), a.end(), b.begin(), b.end());
    }

    template <typename T>
    static bool
    containsOnly(const std::vector<T>& a, const T b)
    {
        return std::all_of(a.begin(), a.end(), [&](T i) { return i == b; });
    }

    template <typename T>
    static bool
    startsWith(const std::vector<T>& a, const std::vector<T>& b)
    {
        if (b.size() > a.size()) {
            return false;
        }

        for (size_t i = 0; i < b.size(); i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    static bool
    endsWith(const std::vector<T>& a, const std::vector<T>& b)
    {
        if (b.size() > a.size()) {
            return false;
        }

        const size_t offset = a.size() - b.size();

        for (size_t i = 0; i < b.size(); i++) {
            if (a[offset + i] != b[i]) {
                return false;
            }
        }

        return true;
    }

    template <typename T>
    static int
    indexOf(const std::vector<T>& a, const T b)
    {
        auto it = std::find(a.begin(), a.end(), b);
        if (it != a.end()) {
            return static_cast<int>(it - a.begin());
        }

        return -1;
    }

    template <typename T>
    static bool
    addAll(std::vector<T>& a, const std::vector<T>& b)
    {
        if (b.size() == 0) {
            return false;
        }

        std::copy(b.begin(), b.end(), std::back_inserter(a));

        return true;
    }

    template <typename T>
    static bool
    addAll(
        std::vector<std::shared_ptr<T>>& a,
        const std::vector<std::shared_ptr<T>>& b)
    {
        if (b.size() == 0) {
            return false;
        }

        std::copy(b.begin(), b.end(), std::back_inserter(a));

        return true;
    }

    template <typename T, typename U>
    static bool
    addAll(
        std::vector<std::shared_ptr<T>>& a,
        const std::vector<std::shared_ptr<U>>& b)
    {
        if (b.size() == 0) {
            return false;
        }

        std::copy(b.begin(), b.end(), std::back_inserter(a));

        return true;
    }

    template <typename T>
    static void
    remove(std::vector<std::shared_ptr<T>>& a, const std::shared_ptr<T>& b)
    {
        const auto it = std::find(a.begin(), a.end(), b);
        if (it != a.end()) {
            /* Value is present */
            a.erase(it);
        }
    }

    template <typename T, typename U>
    static bool
    removeAll(
        std::vector<std::shared_ptr<T>>& a,
        const std::vector<std::shared_ptr<U>>& b)
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
    static void
    fill(
        std::vector<T>& a,
        const size_t from_Index,
        const size_t to_Index,
        T val)
    {
        for (size_t i = from_Index; i < to_Index; i++) {
            a[i] = val;
        }
    }
};

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
