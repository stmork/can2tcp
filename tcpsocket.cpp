//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <sys/socket.h>
#include <unistd.h>

#include "exception.h"
#include "tcpsocket.h"

TcpSocket::TcpSocket(const in_addr_t ip4_addr, const uint16_t port)
{
	socket_handle = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_handle < 0)
	{
		throw Exception("TCP failed", errno);
	}

	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = ip4_addr;
	addr.sin_port        = htons(port);
}

TcpSocket::~TcpSocket()
{
	close(socket_handle);
}
