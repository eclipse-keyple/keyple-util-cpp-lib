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

#include <memory>
#include <string>

#include "keyple/core/util/KeypleUtilExport.hpp"
#include "keyple/core/util/cpp/Matcher.hpp"

namespace keyple {
namespace core {
namespace util {
namespace cpp {

class KEYPLEUTIL_API Pattern {
public:
    /**
     *
     */
    const std::regex mPattern;

    /**
     * Constructor
     */
    Pattern(const std::string& pattern, const int flags);

    /**
     * Returns a compiled form of the given regular expression, as modified by
     * the given flags.
     *
     * @throws PatternSyntexException
     */
    std::shared_ptr<Pattern>
    compile(const std::string& regularExpression, const int flags) const;

    /**
     * Equivalent to Pattern::compile(pattern, 0)
     */
    static std::shared_ptr<Pattern> compile(const std::string& pattern);

    /*
     * Returns a Matcher for this pattern applied to the given input. The
     * Matcher can be used to match the Pattern against the whole input, find
     * occurences of the Pattern in the input, or replace parts of the input.
     */
    std::shared_ptr<Matcher> matcher(const std::string& input) const;

private:
    /**
     *
     */
    const int mFlags;
};

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
