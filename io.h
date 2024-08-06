//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef IO_H
#define IO_H

#include <cstddef>
#include <chrono>
#include <functional>

#include <linux/can/raw.h>

using namespace std::chrono_literals;

class ProxyIo
{
public:
	bool proxy(ProxyIo & writer);

	virtual int    poll(const std::chrono::milliseconds timeout = 100ms) = 0;
	virtual bool   read(can_frame & frame) = 0;
	virtual size_t write(const can_frame & frame) = 0;
};

#endif
