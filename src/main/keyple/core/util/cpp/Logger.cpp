/**************************************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * This program and the accompanying materials are made available under the                       *
 * terms of the MIT License which is available at https://opensource.org/licenses/MIT.            *
 *                                                                                                *
 * SPDX-License-Identifier: MIT                                                                   *
 **************************************************************************************************/

#include "keyple/core/util/cpp/Logger.hpp"

#include <cstdarg>
#include <cstdio>
#include <string>

namespace keyple {
namespace core {
namespace util {
namespace cpp {

Logger::Level Logger::mLevel = Logger::Level::logDebug;

Logger::Logger(const std::string& className, std::mutex* mtx)
: className(demangle(className.c_str()))
, mtx(mtx)
{
}

std::string
Logger::getClassName()
{
    return className;
}

void
Logger::setLoggerLevel(Logger::Level level)
{
    mLevel = level;
}

const std::string
Logger::getCurrentTimestamp()
{
    using std::chrono::system_clock;
    auto currentTime = std::chrono::system_clock::now();
    char buffer1[21];
    char buffer2[26];

    auto transformed = currentTime.time_since_epoch().count() / 1000000;
    auto millis = transformed % 1000;

    std::time_t tt;
    tm ttm;
    tt = system_clock::to_time_t(currentTime);
    auto timeinfo = localtime_r(&tt, &ttm);

    strftime(buffer1, sizeof(buffer1), "%F %H:%M:%S", timeinfo);
    snprintf(buffer2, sizeof(buffer2), "%s:%03d", buffer1, static_cast<int>(millis));

    return std::string(buffer2);
}

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
