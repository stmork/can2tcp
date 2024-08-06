//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <thread>

#include "tcpconnection.h"

Connection::Connection(ProxyIo & left, ProxyIo & right) :
	first(left), second(right)
{
}

void Connection::loop()
{
	l2r_loop = true;
	r2l_loop = true;

	std::thread l2r_thread([&]()
	{
		do
		{
			l2r_loop = first.proxy(second);
		}
		while (l2r_loop && r2l_loop);
	});

	std::thread r2l_thread([&]()
	{
		do
		{
			r2l_loop = second.proxy(first);
		}
		while (l2r_loop && r2l_loop);
	});

	l2r_thread.join();
	r2l_thread.join();
}

void Connection::stop()
{
	l2r_loop = false;
	r2l_loop = false;
}
