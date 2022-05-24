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

#include "ApduUtil.h"

/* Util */
#include "System.h"

namespace keyple {
namespace core {
namespace util {

using namespace keyple::core::util::cpp;

ApduUtil::ApduUtil() {}

const std::vector<uint8_t> ApduUtil::build(const uint8_t cla,
                                           const uint8_t ins,
                                           const uint8_t p1,
                                           const uint8_t p2,
                                           const std::vector<uint8_t>& dataIn,
                                           const uint8_t le)
{
    std::vector<uint8_t> apduCommand;

    /* Buffer allocation */
    apduCommand = allocateBuffer(dataIn, le);

    /* Build APDU buffer from provided arguments */
    apduCommand[0] = cla;
    apduCommand[1] = ins;
    apduCommand[2] = p1;
    apduCommand[3] = p2;

    /* ISO7618 case determination and Le management */
    if (dataIn.size() != 0) {
        /* Append Lc and ingoing data */
        apduCommand[4] = static_cast<uint8_t>(dataIn.size());
        System::arraycopy(dataIn, 0, apduCommand, 5, static_cast<int>(dataIn.size()));
        apduCommand[apduCommand.size() - 1] = le;
    } else {
        /* Case2: outgoing data only */
        apduCommand[4] = le;
    }

    return apduCommand;
}

const std::vector<uint8_t> ApduUtil::build(const uint8_t cla,
                                           const uint8_t ins,
                                           const uint8_t p1,
                                           const uint8_t p2,
                                           const std::vector<uint8_t>& dataIn)
{
    std::vector<uint8_t> apduCommand;

    /* Buffer allocation */
    apduCommand = allocateBuffer(dataIn);

    /* Build APDU buffer from provided arguments */
    apduCommand[0] = cla;
    apduCommand[1] = ins;
    apduCommand[2] = p1;
    apduCommand[3] = p2;

    /* ISO7618 case determination and Le management */
    if (dataIn.size() != 0) {
        /* append Lc and ingoing data */
        apduCommand[4] = static_cast<uint8_t>(dataIn.size());
        System::arraycopy(dataIn, 0, apduCommand, 5, static_cast<int>(dataIn.size()));
        /* Case3: ingoing data only, no Le */
    } else {
        /* Case1: no ingoing, no outgoing data, P3/Le = 0 */
        apduCommand[4] = 0x00;
    }
    return apduCommand;
}

const std::vector<uint8_t> ApduUtil::build(const uint8_t cla,
                                           const uint8_t ins,
                                           const uint8_t p1,
                                           const uint8_t p2,
                                           const uint8_t le)
{
    std::vector<uint8_t> apduCommand;

    /* Buffer allocation */
    apduCommand = allocateBuffer(le);

    /* Build APDU buffer from provided arguments */
    apduCommand[0] = cla;
    apduCommand[1] = ins;
    apduCommand[2] = p1;
    apduCommand[3] = p2;

    /* ISO7618 case determination and Le management */
    /* Case2: outgoing data only */
    apduCommand[4] = le;

    return apduCommand;
}

const std::vector<uint8_t> ApduUtil::build(const uint8_t cla,
                                           const uint8_t ins,
                                           const uint8_t p1,
                                           const uint8_t p2)
{
    std::vector<uint8_t> apduCommand;

    /* Buffer allocation */
    apduCommand = allocateBuffer();

    /* Build APDU buffer from provided arguments */
    apduCommand[0] = cla;
    apduCommand[1] = ins;
    apduCommand[2] = p1;
    apduCommand[3] = p2;

    /* ISO7618 case determination and Le management */
    /* Case1: no ingoing, no outgoing data, P3/Le = 0 */
    apduCommand[4] = 0x00;

    return apduCommand;
}

std::vector<uint8_t> ApduUtil::allocateBuffer(const std::vector<uint8_t>& data, const uint8_t le)
{
    (void)le;

    int length = 4;                              // Header

    length += static_cast<int>(data.size() + 1); // Lc + data
    length += 1;                                 // Le

    return std::vector<uint8_t>(length);
}

std::vector<uint8_t> ApduUtil::allocateBuffer(const std::vector<uint8_t>& data)
{
    int length = 4;                              // Header

    length += static_cast<int>(data.size() + 1); // Lc + data

    return std::vector<uint8_t>(length);
}

std::vector<uint8_t> ApduUtil::allocateBuffer(const uint8_t le)
{
    (void)le;

    int length = 4;            // Header

    length += 1;               // Le

    return std::vector<uint8_t>(length);
}

std::vector<uint8_t> ApduUtil::allocateBuffer()
{
    int length = 4;            // Header

    /* Case 1: 5-byte apdu, le=0 */
    length += 1;               // Le

    return std::vector<uint8_t>(length);
}

bool ApduUtil::isCase4(const std::vector<uint8_t>& apduCommand)
{
    if (apduCommand.size() > 4) {
        return apduCommand[4] == apduCommand.size() - 6;
    }

    return false;
}

}
}
}
