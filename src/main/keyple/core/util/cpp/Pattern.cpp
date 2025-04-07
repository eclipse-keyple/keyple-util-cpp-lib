/**************************************************************************************************
 * Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * This program and the accompanying materials are made available under the                       *
 * terms of the MIT License which is available at https://opensource.org/licenses/MIT.            *
 *                                                                                                *
 * SPDX-License-Identifier: MIT                                                                   *
 **************************************************************************************************/

#include "keyple/core/util/cpp/Pattern.hpp"

#include <memory>
#include <string>

#include "keyple/core/util/cpp/exception/PatternSyntaxException.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

using keyple::core::util::cpp::exception::PatternSyntaxException;

Pattern::Pattern(const std::string& pattern, const int flags)
: mPattern(pattern)
, mFlags(flags)
{
}

std::unique_ptr<Pattern>
Pattern::compile(const std::string& regularExpression, const int flags) const
{
    /* Compiler hack */
    (void)mFlags;

    try {
        return std::unique_ptr<Pattern>(new Pattern(regularExpression, flags));
    } catch (const std::exception& e) {
        throw PatternSyntaxException(e.what());
    }
}

std::unique_ptr<Pattern>
Pattern::compile(const std::string& pattern)
{
    try {
        return std::unique_ptr<Pattern>(new Pattern(pattern, 0));
    } catch (const std::exception& e) {
        throw PatternSyntaxException(e.what());
    }
}

std::unique_ptr<Matcher>
Pattern::matcher(const std::string& input) const
{
    return std::unique_ptr<Matcher>(new Matcher(this, input));
}

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
