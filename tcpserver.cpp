//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

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
}

bool TcpServer::read(can_frame & frame)
{
	return recv(client_fd, &frame, sizeof(can_frame), 0) == sizeof(can_frame);
}

size_t TcpServer::write(const can_frame & frame)
{
	return send(client_fd, &frame, sizeof(can_frame), 0);
}
