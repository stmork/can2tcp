//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <iostream>

#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>

#include "exception.h"
#include "tcpserver.h"

TcpServer::TcpServer(const uint16_t port) : TcpSocket(INADDR_ANY, port)
{
	if (bind(socket_handle, (struct sockaddr *)&addr, sizeof(addr)) != 0)
	{
		throw Exception("Bind failed", errno);
	}

	if (listen(socket_handle, 1) != 0)
	{
		throw Exception("Listen failed", errno);
	}

	std::cout << "TCP server listening." << std::endl;
}

TcpServer::~TcpServer()
{
	close(client_fd);
}

void TcpServer::acceptClient()
{
	sockaddr_in newSockAddr{};
	socklen_t   newSockAddrSize = sizeof(newSockAddr);

	client_fd = accept(socket_handle, (sockaddr *)&newSockAddr, &newSockAddrSize);
	if (client_fd < 0)
	{
		throw Exception("Accept failed", errno);
	}
	std::cout << "TCP client accepted." << std::endl;
}

void TcpServer::closeClient()
{
	close(client_fd);
	client_fd = -1;
}

int TcpServer::poll(const std::chrono::milliseconds timeout)
{
	struct pollfd descriptor {};

	descriptor.events  = POLLIN;
	descriptor.revents = 0;
	descriptor.fd      = client_fd;

	return ::poll(&descriptor, 1, timeout.count());
}

bool TcpServer::read(can_frame & frame)
{
	return recv(client_fd, &frame, sizeof(can_frame), 0) == sizeof(can_frame);
}

size_t TcpServer::write(const can_frame & frame)
{
	return send(client_fd, &frame, sizeof(can_frame), 0);
}
