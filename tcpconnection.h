//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "io.h"

class Connection
{
	ProxyIo & first;
	ProxyIo & second;

	bool      l2r_loop = false;
	bool      r2l_loop = false;

public:
	Connection() = delete;
	Connection(ProxyIo & left, ProxyIo & right);

	void loop();
	void stop();
};

#endif // TCPCONNECTION_H
