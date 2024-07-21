/**************************************************************************************************
 * Copyright (c) 2024 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * This program and the accompanying materials are made available under the                       *
 * terms of the MIT License which is available at https://opensource.org/licenses/MIT.            *
 *                                                                                                *
 * SPDX-License-Identifier: MIT                                                                   *
 **************************************************************************************************/

#pragma once

#include <map>
#include <vector>

namespace keyple {
namespace core {
namespace util {
namespace cpp {

class MapUtils {
public:
    template <typename K, typename V>
    static const std::vector<K>
    getKeySet(const std::map<const K, const V>& m) {
        std::vector<K> v;

        std::for_each(m.begin(), m.end(), [&](const auto& e) { v.push_back(e.first); });

        return v;
    }

    template <typename K, typename V>
    static const std::vector<V>
    getValueSet(const std::map<const K, const V>& m) {
        std::vector<V> v;

        std::for_each(m.begin(), m.end(), [&](const auto& e) { v.push_back(e.second); });

        return v;
    }
};

} /* namespace cpp */
} /* namespace util */
} /* namespace core */
} /* namespace keyple */
