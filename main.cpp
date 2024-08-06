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
#include "exception.h"
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

			if (host == nullptr)
			{
				throw Exception("TCP server not found", errno);
			}

			struct in_addr * addr_list = (struct in_addr *) host->h_addr;

			std::cout << "Connecting to: " << inet_ntoa(*addr_list) << std::endl;
			TcpClient tcp(addr_list->s_addr, options.getPort());
			bool      can2tcp_loop = true;
			bool      tcp2can_loop = true;

			std::thread can2tcp([&]()
			{
				do
				{
					can2tcp_loop = can.proxy(tcp);
				}
				while (can2tcp_loop && tcp2can_loop);
			});

			std::thread tcp2can([&]()
			{
				do
				{
					tcp2can_loop = tcp.proxy(can);
				}
				while (can2tcp_loop && tcp2can_loop);
			});

			can2tcp.join();
			tcp2can.join();
		}
		else
		{
			// Server
			TcpServer tcp(options.getPort());
			bool      can2tcp_loop = true;
			bool      tcp2can_loop = true;

			tcp.acceptClient();
			std::thread can2tcp([&]()
			{
				do
				{
					can2tcp_loop = can.proxy(tcp);
				}
				while (can2tcp_loop && tcp2can_loop);
			});

			std::thread tcp2can([&]()
			{
				do
				{
					tcp2can_loop = tcp.proxy(can);
				}
				while (can2tcp_loop && tcp2can_loop);
			});

			can2tcp.join();
			tcp2can.join();
			tcp.closeClient();
		}

		return EXIT_SUCCESS;
	}
	catch (std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
}
