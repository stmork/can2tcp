//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <cstdlib>
#include <iostream>

#include <netdb.h>
#include <arpa/inet.h>

#include "cansocket.h"
#include "exception.h"
#include "options.h"
#include "tcpclient.h"
#include "tcpserver.h"
#include "tcpconnection.h"

using namespace std::placeholders;

int main(int argc, char * argv[])
{
	try
	{
		Options   options(argc, argv);
		CanSocket can(options.getCanDevice());

		if (!options.isServer())
		{

			// Client
			struct hostent * host = gethostbyname(options.getServer());

			if (host == nullptr)
			{
				throw Exception("TCP server not found", errno);
			}

			struct in_addr * addr_list = (struct in_addr *) host->h_addr;

			std::cout << "Connecting to: " << inet_ntoa(*addr_list) << std::endl;
			TcpClient  tcp(addr_list->s_addr, options.getPort());
			Connection connection(can, tcp);

			connection.loop();
		}
		else
		{
			// Server
			TcpServer tcp(options.getPort());

			do
			{
				Connection connection(can, tcp);

				tcp.acceptClient();
				connection.loop();
				tcp.closeClient();
			}
			while (true);
		}

		return EXIT_SUCCESS;
	}
	catch (std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
}
