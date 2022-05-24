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

#include <string>

/* Keyple Core Util */
#include "KeypleUtilExport.h"

namespace keyple {
namespace core {
namespace util {
namespace protocol {

/**
 * This enum contains a non-exhaustive list of contactless smartcard communication protocols.
 *
 * @since 2.0.0
 */
class KEYPLEUTIL_API ContactlessCardCommonProtocol {
public:
    /**
     * Contactless standard
     */
    static const ContactlessCardCommonProtocol ISO_14443_4;

    /* Contactless NFC compliant */
    static const ContactlessCardCommonProtocol NFC_A_ISO_14443_3A;
    static const ContactlessCardCommonProtocol NFC_B_ISO_14443_3B;
    static const ContactlessCardCommonProtocol NFC_F_JIS_6319_4;
    static const ContactlessCardCommonProtocol NFC_V_ISO_15693;

    /* Other contactless proprietary protocols */
    static const ContactlessCardCommonProtocol INNOVATRON_B_PRIME_CARD;

    /**
     *
     */
    const std::string& getName() const;

private:
    /**
     *
     */
    const std::string mName;

    /**
     *
     */
    ContactlessCardCommonProtocol(const std::string& name);
};

}
}
}
}
