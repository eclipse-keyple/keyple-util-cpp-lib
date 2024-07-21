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

std::shared_ptr<Pattern>
Pattern::compile(const std::string& regularExpression, const int flags) const
{
    /* Compiler hack */
    (void)mFlags;

    try {
        return std::make_shared<Pattern>(regularExpression, flags);

    } catch (const std::exception& e) {
        throw PatternSyntaxException(e.what());
    }
}

std::shared_ptr<Pattern>
Pattern::compile(const std::string& pattern)
{
    try {
        return std::make_shared<Pattern>(pattern, 0);

    } catch (const std::exception& e) {
        throw PatternSyntaxException(e.what());
    }
}

std::shared_ptr<Matcher>
Pattern::matcher(const std::string& input) const
{
    return std::make_shared<Matcher>(this, input);
}

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
