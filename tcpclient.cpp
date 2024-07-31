//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <stdexcept>

#include "tcpclient.h"

TcpClient::TcpClient(const in_addr_t ip_addr, const uint16_t port) :
	TcpSocket(ip_addr, port)
{
	if (connect(socket_handle, (sockaddr *) &addr, sizeof(addr)) < 0)
	{
		throw std::runtime_error("TCP connection failed.");
	}
}

bool TcpClient::read(can_frame & frame)
{
	return recv(socket_handle, &frame, sizeof(can_frame), 0) == sizeof(can_frame);
}

size_t TcpClient::write(const can_frame & frame)
{
	return send(socket_handle, &frame, sizeof(can_frame), 0);
}
