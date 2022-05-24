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

#include "ContactCardCommonProtocol.h"

namespace keyple {
namespace core {
namespace util {
namespace protocol {

const ContactCardCommonProtocol ContactCardCommonProtocol::ISO_7816_3(
    "ISO_7816_3");
const ContactCardCommonProtocol ContactCardCommonProtocol::ISO_7816_3_T0(
    "ISO_7816_3_T0");
const ContactCardCommonProtocol ContactCardCommonProtocol::ISO_7816_3_T1(
    "ISO_7816_3_T1");
const ContactCardCommonProtocol ContactCardCommonProtocol::INNOVATRON_HIGH_SPEED_PROTOCOL_SAM(
    "INNOVATRON_HIGH_SPEED_PROTOCOL_SAM");

ContactCardCommonProtocol::ContactCardCommonProtocol(const std::string& name) : mName(name) {}

const std::string& ContactCardCommonProtocol::getName() const
{
    return mName;
}

}
}
}
}
