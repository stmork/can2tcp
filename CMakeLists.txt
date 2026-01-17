#
#  SPDX-License-Identifier: MIT
#  SPDX-FileCopyrightText: Copyright (C) 2024 - 2026  Steffen A. Mork
#

cmake_minimum_required(VERSION 3.14)

project(can2tcp LANGUAGES CXX)

add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wsuggest-override)
add_compile_options(-fstack-protector-strong)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	main.cpp
	exception.cpp
	io.cpp
	cansocket.cpp
	options.cpp
	tcpconnection.cpp
	tcpclient.cpp
	tcpserver.cpp
	tcpsocket.cpp
)

set(HEADERS
	cansocket.h
	exception.h
	io.h
	options.h
	tcpconnection.h
	tcpclient.h
	tcpserver.h
	tcpsocket.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(can2tcp)

add_custom_target(astyle
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND astyle --options=.astylerc ${SOURCES} ${HEADERS}
)

add_custom_target(cppcheck
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND cppcheck ${SOURCES} ${HEADERS} --language=c++ --std=c++14 -q --xml-version=2 --force 2>cppcheck.xml
)

set_property(
	TARGET cppcheck
	APPEND
	PROPERTY ADDITIONAL_CLEAN_FILES ${CMAKE_SOURCE_DIR}/cppcheck.xml
)

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION /usr/bin
)

install(
	FILES ${PROJECT_SOURCE_DIR}/LICENSE
	DESTINATION /usr/share/doc/morknet-${PROJECT_NAME}/
	RENAME copyright
)

set(CPACK_GENERATOR "DEB")

set(CPACK_PACKAGE_NAME "morknet-${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "MORKNet")
set(CPACK_PACKAGE_CONTACT "linux-dev@morknet.de")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CAN over TCP client/server tool")

if(DEFINED ENV{BUILD_NUMBER})
	set(JENKINS_BUILD_NUMBER $ENV{BUILD_NUMBER})
else()
	set(JENKINS_BUILD_NUMBER 0)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR   ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR   ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH   ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION         ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_RELEASE  ${JENKINS_BUILD_NUMBER})

# Debian-spezifisch
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Steffen A. Mork")
set(CPACK_DEBIAN_PACKAGE_SECTION    "system")
set(CPACK_DEBIAN_PACKAGE_PRIORITY   "optional")
set(CPACK_DEBIAN_PACKAGE_DEPENDS    "can-utils")
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)

include(CPack)
