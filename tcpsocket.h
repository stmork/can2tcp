//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <cstdint>

#include <netinet/in.h>

class TcpSocket
{
protected:
	int               socket_handle = -1;
	sockaddr_in       addr{};

public:
	explicit TcpSocket(const in_addr_t ip4_addr, const uint16_t port = 7000);
	virtual ~TcpSocket();
};

#endif
