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

#include <iostream>
#include <string>

#include "keyple/core/util/HexUtil.hpp"

int
main()
{
    /* Calls into the actual compiled library (not just a header), proving
     * the binary resolved and linked correctly through Conan/CMake. */
    const std::string hex
        = keyple::core::util::HexUtil::toHex(static_cast<uint8_t>(0xAB));
    std::cout << "Keyple::Util package resolved and linked correctly (0xAB -> "
              << hex << ")" << std::endl;
    return hex == "AB" ? 0 : 1;
}
