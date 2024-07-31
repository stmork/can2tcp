//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <cstdlib>
#include <thread>

#include <netdb.h>

#include "cansocket.h"
#include "tcpclient.h"
#include "tcpserver.h"

using namespace std::placeholders;

int main(int argc, char *argv[])
{
	CanSocket can("vcan0");

	if (argc > 1)
	{
		// Client
		struct hostent*  host      = gethostbyname(argv[1]);
		struct in_addr * addr_list = (struct in_addr *) host->h_addr;

		TcpClient tcp(addr_list->s_addr, 7000);

		std::thread can2tcp([&]()
		{
			do
			{
				can.proxy(std::bind(&TcpClient::write, &tcp, _1));
			}
			while(true);
		});

		std::thread tcp2can([&]()
		{
			do
			{
				tcp.proxy(std::bind(&CanSocket::write, &can, _1));
			}
			while(true);
		});

		can2tcp.join();
		tcp2can.join();
	}
	else
	{
		// Server
		TcpServer tcp(7000);

		std::thread can2tcp([&]()
		{
			do
			{
				can.proxy(std::bind(&TcpServer::write, &tcp, _1));
			}
			while(true);
		});

		std::thread tcp2can([&]()
		{
			do
			{
				tcp.proxy(std::bind(&CanSocket::write, &can, _1));
			}
			while(true);
		});

		can2tcp.join();
		tcp2can.join();
	}

	TcpSocket tcp(0xc0a8130b, 7000);

	return EXIT_SUCCESS;
}
