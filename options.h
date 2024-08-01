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
	std::string  server;
	std::string  can;

public:
	Options() = delete;
	explicit Options(int argc, char * argv[]);

	uint16_t getPort() const;
	const char * getCanDevice() const;
	const char * getServer() const;
	bool isServer() const;
};

#endif // OPTIONS_H
