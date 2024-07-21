# *************************************************************************************************
# Copyright (c) 2021 Calypso Networks Association http://calypsonet.org/                          *
#                                                                                                 *
# See the NOTICE file(s) distributed with this work for additional information regarding          *
# copyright ownership.                                                                            *
#                                                                                                 *
# This program and the accompanying materials are made available under the terms of the Eclipse   *
# Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                   *
#                                                                                                 *
# SPDX-License-Identifier: EPL-2.0                                                                *
# *************************************************************************************************/

SET(LIBRARY_NAME keypleutilcpplib)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKEYPLEUTIL_EXPORT")

ADD_LIBRARY(
    ${LIBRARY_NAME}

    ${LIBRARY_TYPE}

    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/ApduUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/BerTlvUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/ByteArrayUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/HexUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/KeypleAssert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/cpp/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/cpp/LoggerFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/cpp/Matcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/cpp/Pattern.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/protocol/ContactCardCommonProtocol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/keyple/core/util/protocol/ContactlessCardCommonProtocol.cpp
)

TARGET_INCLUDE_DIRECTORIES(
    ${LIBRARY_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

ADD_LIBRARY(Keyple::Util ALIAS ${LIBRARY_NAME})
