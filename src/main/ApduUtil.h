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

#include <cstdint>
#include <vector>

/* Keyple Core Util */
#include "KeypleUtilExport.h"

namespace keyple {
namespace core {
namespace util {

/**
 * Util to build APDUs and check case 4.
 *
 * @since 2.0.0
 */
class KEYPLEUTIL_API ApduUtil final {
public:
    /**
     * Builds an APDU request from its elements as defined by the ISO 7816 standard.
     *
     * @param cla The class byte.
     * @param ins The instruction byte.
     * @param p1 The parameter 1.
     * @param p2 The parameter 2.
     * @param dataIn The data field of the command (optional).
     * @param le The maximum number of bytes expected in the data field of the response to the command
     *     (optional).
     * @return A byte array containing the resulting apdu command data.
     * @since 2.0.0
     */
    static const std::vector<uint8_t> build(const uint8_t cla,
                                            const uint8_t ins,
                                            const uint8_t p1,
                                            const uint8_t p2,
                                            const std::vector<uint8_t>& dataIn,
                                            const uint8_t le);

    /**
     * Builds an APDU request from its elements as defined by the ISO 7816 standard.
     *
     * @param cla The class byte.
     * @param ins The instruction byte.
     * @param p1 The parameter 1.
     * @param p2 The parameter 2.
     * @param dataIn The data field of the command (optional).
     * @return A byte array containing the resulting apdu command data.
     * @since 2.0.0
     */
    static const std::vector<uint8_t> build(const uint8_t cla,
                                            const uint8_t ins,
                                            const uint8_t p1,
                                            const uint8_t p2,
                                            const std::vector<uint8_t>& dataIn);

    /**
     * Builds an APDU request from its elements as defined by the ISO 7816 standard.
     *
     * @param cla The class byte.
     * @param ins The instruction byte.
     * @param p1 The parameter 1.
     * @param p2 The parameter 2.
     * @param le The maximum number of bytes expected in the data field of the response to the command
     *     (optional).
     * @return A byte array containing the resulting apdu command data.
     * @since 2.0.0
     */
    static const std::vector<uint8_t> build(const uint8_t cla,
                                            const uint8_t ins,
                                            const uint8_t p1,
                                            const uint8_t p2,
                                            const uint8_t le);

    /**
     * Builds an APDU request from its elements as defined by the ISO 7816 standard.
     *
     * @param cla The class byte.
     * @param ins The instruction byte.
     * @param p1 The parameter 1.
     * @param p2 The parameter 2.
     * @return A byte array containing the resulting apdu command data.
     * @since 2.0.0
     */
    static const std::vector<uint8_t> build(const uint8_t cla,
                                            const uint8_t ins,
                                            const uint8_t p1,
                                            const uint8_t p2);

    /**
     * (private)<br>
     * Returns a byte array having the expected length according the APDU construction rules.
     *
     * @param data Data array
     * @param le Expected outgoing length
     * @return A new byte array.
     */
    static std::vector<uint8_t> allocateBuffer(const std::vector<uint8_t>& data, const uint8_t le);

    /**
     * (private)<br>
     * Returns a byte array having the expected length according the APDU construction rules.
     *
     * @param data Data array
     * @return A new byte array.
     */
    static std::vector<uint8_t> allocateBuffer(const std::vector<uint8_t>& data);

    /**
     * (private)<br>
     * Returns a byte array having the expected length according the APDU construction rules.
     *
     * @param le Expected outgoing length
     * @return A new byte array.
     */
    static std::vector<uint8_t> allocateBuffer(const uint8_t le);

    /**
     * (private)<br>
     * Returns a byte array having the expected length according the APDU construction rules.
     *
     * @return A new byte array.
     */
    static std::vector<uint8_t> allocateBuffer();

    /**
     * Indicates if the provided byte array contains a case4 APDU command.
     *
     * <p>The ISO7816 case for data in a command-response pair is determined from the provided
     * arguments:
     *
     * <ul>
     *   <li><code>dataIn &nbsp;= null, le &nbsp;= null</code>&nbsp;&nbsp;&rarr;&nbsp;&nbsp;case 1:
     *       no command data, no response data expected.
     *   <li><code>dataIn &nbsp;= null, le != null</code>&nbsp;&nbsp;&rarr;&nbsp;&nbsp;case 2: no
     *       command data, expected response data.
     *   <li><code>dataIn != null, le &nbsp;= null</code>&nbsp;&nbsp;&rarr;&nbsp;&nbsp;case 3:
     *       command data, no response data expected.
     *   <li><code>dataIn != null, le &nbsp;= 0&nbsp;&nbsp;&nbsp;</code>
     *       &nbsp;&nbsp;&rarr;&nbsp;&nbsp;case 4: command data, expected response data.
     * </ul>
     *
     * Only the indication for case 4 is retained in the end.<br>
     * In this case (incoming and outgoing data for the card), Le is set to 0, letting the lower
     * layer (see API plugin) take care of recovering the exact length of the outgoing data.
     *
     * @param apduCommand The apduCommand to check.
     * @return true the APDU command is case 4.
     * @since 2.0.0
     */
    static bool isCase4(const std::vector<uint8_t>& apduCommand);

private:
    /**
     * private<br>
     * Constructor
     */
    ApduUtil();
};

}
}
}
