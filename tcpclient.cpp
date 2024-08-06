//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <iostream>

#include <poll.h>

#include "exception.h"
#include "tcpclient.h"

TcpClient::TcpClient(const in_addr_t ip_addr, const uint16_t port) :
	TcpSocket(ip_addr, port)
{
	if (connect(socket_handle, (sockaddr *) &addr, sizeof(addr)) < 0)
	{
		throw Exception("TCP connection failed", errno);
	}
	std::cout << "TCP client connected." << std::endl;
}

int TcpClient::poll(const std::chrono::milliseconds timeout)
{
	struct pollfd descriptor {};

	descriptor.events  = POLLIN;
	descriptor.revents = 0;
	descriptor.fd      = socket_handle;

	return ::poll(&descriptor, 1, timeout.count());
}

bool TcpClient::read(can_frame & frame)
{
	return recv(socket_handle, &frame, sizeof(can_frame), 0) == sizeof(can_frame);
}

size_t TcpClient::write(const can_frame & frame)
{
	return send(socket_handle, &frame, sizeof(can_frame), 0);
}
