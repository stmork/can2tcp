//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef CANSOCKET_H
#define CANSOCKET_H

#include <ostream>

#include "io.h"

class CanSocket : public ProxyIo
{
	int               socket_handle = 0;

public:
	explicit CanSocket(const char * device_name);
	virtual ~CanSocket();

	virtual int    poll(const std::chrono::milliseconds timeout) override;
	virtual bool   read(can_frame & frame) override;
	virtual size_t write(const can_frame & frame) override;
};

std::ostream & operator<<(std::ostream & os, const can_frame & frame);

#endif // CANSOCKET_H
