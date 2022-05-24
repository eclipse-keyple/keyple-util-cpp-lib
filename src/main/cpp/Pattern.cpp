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

#include "Pattern.h"

/* Keyple Core Utils */
#include "PatternSyntaxException.h"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

using namespace keyple::core::util::cpp::exception;

Pattern::Pattern(const std::string& pattern, const int flags) : mPattern(pattern), mFlags(flags) {}

std::unique_ptr<Pattern> Pattern::compile(const std::string& regularExpression, const int flags)
    const
{
    /* Compiler hack */
    (void)mFlags;

    try {
        return std::unique_ptr<Pattern>(new Pattern(regularExpression, flags));
    } catch (const std::exception& e) {
        throw PatternSyntaxException(e.what());
    }
}

std::unique_ptr<Pattern> Pattern::compile(const std::string& pattern)
{
    try {
        return std::unique_ptr<Pattern>(new Pattern(pattern, 0));
    } catch (const std::exception& e) {
        throw PatternSyntaxException(e.what());
    }
}

std::unique_ptr<Matcher> Pattern::matcher(const std::string& input) const
{
    return std::unique_ptr<Matcher>(new Matcher(this, input));
}

}
}
}
}
