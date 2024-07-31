//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpsocket.h"
#include "io.h"

class TcpServer : public TcpSocket,  public ProxyIo
{
	int client_fd = 0;

public:
	explicit TcpServer(const uint16_t port = 7000);

	virtual bool   read(can_frame & frame) override;
	virtual size_t write(const can_frame & frame) override;
};

#endif
