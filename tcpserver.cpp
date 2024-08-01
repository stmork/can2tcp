//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <iostream>
#include <stdexcept>

#include <netinet/in.h>
#include <unistd.h>

#include "tcpserver.h"

TcpServer::TcpServer(const uint16_t port) : TcpSocket(INADDR_ANY, port)
{
	if (bind(socket_handle, (struct sockaddr *)&addr, sizeof(addr)) != 0)
	{
		throw std::runtime_error("Bind failed.");
	}

	if (listen(socket_handle, 1) != 0)
	{
		throw std::runtime_error("Listen failed!");
	}

	std::cout << "TCP server listening." << std::endl;
}

void TcpServer::acceptClient()
{
	sockaddr_in newSockAddr{};
	socklen_t   newSockAddrSize = sizeof(newSockAddr);

	client_fd = accept(socket_handle, (sockaddr *)&newSockAddr, &newSockAddrSize);
	if (client_fd < 0)
	{
		throw std::runtime_error("Accept failed!");
	}
	std::cout << "TCP client accepted." << std::endl;
}

bool TcpServer::read(can_frame & frame)
{
	return recv(client_fd, &frame, sizeof(can_frame), 0) == sizeof(can_frame);
}

size_t TcpServer::write(const can_frame & frame)
{
	return send(client_fd, &frame, sizeof(can_frame), 0);
}
