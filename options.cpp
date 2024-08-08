//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "options.h"

Options::Options(int argc, char * argv[]) : can("vcan0")
{
	int opt;

	while ((opt = getopt(argc, argv, "p:d:s:")) != -1)
	{
		switch (opt)
		{
		case 'p':
			port = atoi(optarg);
			break;
		case 'd':
			can.assign(optarg);
			break;
		case 's':
			remote_server.assign(optarg);
			break;

		default:
			std::cerr << "Usage: " << argv[0] <<
				" [-p port]" <<
				" [-d CAN-device]" <<
				" [-s remote-host]" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}

uint16_t Options::getPort() const
{
	return port;
}

const char * Options::getCanDevice() const
{
	return can.c_str();
}

const char * Options::getRemoteServer() const
{
	return remote_server.c_str();
}

bool Options::isRemoteServer() const
{
	return remote_server.empty();
}
