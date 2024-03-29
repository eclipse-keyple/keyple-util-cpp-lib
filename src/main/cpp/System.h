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

#include <math.h>
#include <vector>
#include <memory>

#if defined(_WIN32)
#include <windows.h>
#endif

/* Keyple Core Util */
#include "ArrayIndexOutOfBoundsException.h"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

using namespace keyple::core::util::cpp::exception;

class System {
public:
    /**
     *
     */
    static unsigned long long nanoTime()
    {
#if defined(WIN32)
        SYSTEMTIME time;
        GetSystemTime(&time);
        return static_cast<long long>((time.wHour * 3600 * 1000 +
                                       time.wMinute * 60 * 1000 +
                                       time.wSecond * 1000 +
                                       time.wMilliseconds) * pow(10, 6));
#else
        timespec ts;
        // clock_gettime(CLOCK_MONOTONIC, &ts); // Works on FreeBSD
        clock_gettime(CLOCK_REALTIME, &ts);
        return ts.tv_sec * pow(10, 9) + ts.tv_nsec;
#endif
    }

    /**
     *
     */
    static void arraycopy(const std::vector<char>& src, size_t srcPos,
                          std::vector<char>& dest, size_t destPos, size_t length)
    {
        for (size_t i = 0; i < length; i++) {
            dest[destPos + i] = src[srcPos + i];
        }
    }

    /**
     *
     */
    static void arraycopy(const std::vector<uint8_t>& src, size_t srcPos,
                          std::vector<char>& dest, size_t destPos, size_t length)
    {
        if ((srcPos + length) >= src.size()) {
            throw ArrayIndexOutOfBoundsException("pos + offset > src size");
        }

        if ((srcPos + length) >= src.size()) {
            throw ArrayIndexOutOfBoundsException("pos + offset > dest size");
        }

        for (size_t i = 0; i < length; i++) {
            dest[destPos + i] = static_cast<char>(src[srcPos + i]);
        }
    }

    static void arraycopy(const std::vector<uint8_t>& src, size_t srcPos,
                          std::vector<uint8_t>& dest, size_t destPos, size_t length)
    {
        if ((srcPos + length) > src.size()) {
            throw ArrayIndexOutOfBoundsException("pos + offset > src size");
        }

        if ((destPos + length) > dest.size()) {
            throw ArrayIndexOutOfBoundsException("pos + offset > dest size");
        }

        for (size_t i = 0; i < length; i++) {
            dest[destPos + i] = src[srcPos + i];
        }
    }

    /**
     *
     */
    static unsigned long long currentTimeMillis()
    {
        return (unsigned long long)(nanoTime() / pow(10, 6));
    }

    /**
     *
     */
    template<typename T>
    static unsigned int identityHashCode(const std::shared_ptr<T> t)
    {
        if (t == nullptr) {
            return 0;
        }

        return static_cast<int>(reinterpret_cast<unsigned long long>(t.get()));
    }
};

}
}
}
}
