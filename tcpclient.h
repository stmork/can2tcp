//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "tcpsocket.h"
#include "io.h"

class TcpClient : public TcpSocket,  public ProxyIo
{
public:
	explicit TcpClient(const in_addr_t ip_addr, const uint16_t port = 7000);

	virtual bool   read(can_frame & frame) override;
	virtual size_t write(const can_frame & frame) override;
};

#endif
