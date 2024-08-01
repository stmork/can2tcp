//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <cstdlib>
#include <iostream>
#include <thread>

#include <netdb.h>
#include <arpa/inet.h>

#include "cansocket.h"
#include "options.h"
#include "tcpclient.h"
#include "tcpserver.h"

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
			struct hostent * host      = gethostbyname(options.getServer());
			struct in_addr * addr_list = (struct in_addr *) host->h_addr;

			std::cout << "Connecting to: " << inet_ntoa(*addr_list) << std::endl;
			TcpClient tcp(addr_list->s_addr, options.getPort());

			std::thread can2tcp([&]()
			{
				do
				{
					can.proxy(std::bind(&TcpClient::write, &tcp, _1));
				}
				while (true);
			});

			std::thread tcp2can([&]()
			{
				do
				{
					tcp.proxy(std::bind(&CanSocket::write, &can, _1));
				}
				while (true);
			});

			can2tcp.join();
			tcp2can.join();
		}
		else
		{
			// Server
			TcpServer tcp(options.getPort());

			tcp.acceptClient();
			std::thread can2tcp([&]()
			{
				do
				{
					can.proxy(std::bind(&TcpServer::write, &tcp, _1));
				}
				while (true);
			});

			std::thread tcp2can([&]()
			{
				do
				{
					tcp.proxy(std::bind(&CanSocket::write, &can, _1));
				}
				while (true);
			});

			can2tcp.join();
			tcp2can.join();
		}

		return EXIT_SUCCESS;
	}
	catch (std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
}
