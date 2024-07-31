cmake_minimum_required(VERSION 3.14)

project(can2tcp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	main.cpp
	io.cpp
	cansocket.cpp
	tcpclient.cpp
	tcpserver.cpp
	tcpsocket.cpp
)

set(HEADERS
	cansocket.h
	io.h
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
