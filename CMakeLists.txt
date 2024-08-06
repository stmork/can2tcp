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

add_executable(can2tcp ${SOURCES} ${HEADERS}
)

target_link_libraries(can2tcp)

add_custom_target(astyle
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND astyle --options=.astylerc ${SOURCES} ${HEADERS}
)

add_custom_target(cppcheck
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
	COMMAND cppcheck ${SOURCES} ${HEADERS} --language=c++ --std=c++14 -q --xml-version=2 --force 2>cppcheck.xml
)
