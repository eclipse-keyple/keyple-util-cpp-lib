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

#include <cstdarg>

#include "Logger.h"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

Logger::Level Logger::mLevel = Logger::Level::logDebug;

Logger::Logger(const std::string& className, std::mutex* mtx)
: className(demangle(className.c_str())), mtx(mtx) {}

std::string Logger::getClassName()
{
    return className;
}

void Logger::setLoggerLevel(Logger::Level level)
{
    mLevel = level;
}

const std::string Logger::getCurrentTimestamp()
{
    using std::chrono::system_clock;
    auto currentTime = std::chrono::system_clock::now();
    char buffer1[21];
    char buffer2[26];

    auto transformed = currentTime.time_since_epoch().count() / 1000000;
    auto millis = transformed % 1000;

    std::time_t tt;
    tt = system_clock::to_time_t(currentTime);
    auto timeinfo = localtime(&tt);

    strftime(buffer1, sizeof(buffer1), "%F %H:%M:%S", timeinfo);
    sprintf(buffer2, "%s:%03d", buffer1, (int)millis);

    return std::string(buffer2);
}

}
}
}
}
