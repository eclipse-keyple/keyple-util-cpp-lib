# *****************************************************************************
# Copyright (c) 2025 Calypso Networks Association https://calypsonet.org/     *
#                                                                             *
# This program and the accompanying materials are made available under the    *
# terms of the MIT License which is available at                              *
# https://opensource.org/licenses/MIT.                                        *
#                                                                             *
# SPDX-License-Identifier: MIT                                                *
# *****************************************************************************/

SET(EXECUTABLE_NAME keypleutilcpplib_ut)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DKEYPLEUTIL_EXPORT")

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

ADD_EXECUTABLE(
    ${EXECUTABLE_NAME}

    ${CMAKE_CURRENT_SOURCE_DIR}/ApduUtilTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BerTlvUtilTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ByteArrayUtilTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HexUtilTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
)

# Add Google Test
INCLUDE(CMakeLists.txt.googletest)

TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} gtest gmock keypleutilcpplib)
