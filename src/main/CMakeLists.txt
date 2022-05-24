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

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/exception
)

ADD_LIBRARY(
    ${LIBRARY_NAME}

    ${LIBRARY_TYPE}

    ${CMAKE_CURRENT_SOURCE_DIR}/ApduUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BerTlvUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ByteArrayUtil.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KeypleAssert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/LoggerFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/Matcher.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cpp/Pattern.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/protocol/ContactCardCommonProtocol.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/protocol/ContactlessCardCommonProtocol.cpp
)
