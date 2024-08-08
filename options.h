//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef OPTIONS_H
#define OPTIONS_H

#include <cstdint>
#include <string>

class Options
{
	uint16_t     port = 7000;
	std::string  remote_server;
	std::string  can;

public:
	Options() = delete;
	explicit Options(int argc, char * argv[]);

	const char * getCanDevice() const;
	uint16_t     getPort() const;
	const char * getRemoteServer() const;
	bool         isRemoteServer() const;
};

#endif // OPTIONS_H
