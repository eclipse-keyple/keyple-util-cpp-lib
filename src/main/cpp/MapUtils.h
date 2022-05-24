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

#include <map>
#include <vector>

namespace keyple {
namespace core {
namespace util {
namespace cpp {

using namespace keyple::core::util::cpp::exception;

class MapUtils {
public:
    template <typename K, typename V>
    static const std::vector<K> getKeySet(const std::map<const K, const V>& m)
    {
        std::vector<K> v;

        for (const auto& e : m) {
            v.push_back(e.first);
        }

        return v;
    }

    template <typename K, typename V>
    static const std::vector<V> getValueSet(const std::map<const K, const V>& m)
    {
        std::vector<V> v;

        for (const auto& e : m) {
            v.push_back(e.second);
        }

        return v;
    }
};

}
}
}
}
