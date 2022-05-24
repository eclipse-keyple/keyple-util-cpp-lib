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

#include "ContactlessCardCommonProtocol.h"

namespace keyple {
namespace core {
namespace util {
namespace protocol {

const ContactlessCardCommonProtocol ContactlessCardCommonProtocol::ISO_14443_4(
    "ISO_14443_4");
const ContactlessCardCommonProtocol ContactlessCardCommonProtocol::NFC_A_ISO_14443_3A(
    "NFC_A_ISO_14443_3A");
const ContactlessCardCommonProtocol ContactlessCardCommonProtocol::NFC_B_ISO_14443_3B(
    "NFC_B_ISO_14443_3B");
const ContactlessCardCommonProtocol ContactlessCardCommonProtocol::NFC_F_JIS_6319_4(
    "NFC_F_JIS_6319_4");
const ContactlessCardCommonProtocol ContactlessCardCommonProtocol::NFC_V_ISO_15693(
    "NFC_V_ISO_15693");
const ContactlessCardCommonProtocol ContactlessCardCommonProtocol::INNOVATRON_B_PRIME_CARD(
    "INNOVATRON_B_PRIME_CARD");

ContactlessCardCommonProtocol::ContactlessCardCommonProtocol(const std::string& name)
: mName(name) {}

const std::string& ContactlessCardCommonProtocol::getName() const
{
    return mName;
}

}
}
}
}
