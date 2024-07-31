//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef CANSOCKET_H
#define CANSOCKET_H

#include "io.h"

class CanSocket : public ProxyIo
{
	int               socket_handle = 0;

public:
	explicit CanSocket(const char * device_name);
	virtual ~CanSocket();

	virtual bool   read(can_frame & frame) override;
	virtual size_t write(const can_frame & frame) override;
};

#endif // CANSOCKET_H
