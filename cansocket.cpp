//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <cstring>
#include <iomanip>
#include <iostream>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <poll.h>

#include "cansocket.h"
#include "exception.h"

CanSocket::CanSocket(const char * device_name)
{
	struct sockaddr_can addr {};
	struct ifreq        ifr;

	socket_handle = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (socket_handle < 0)
	{
		throw Exception("CAN failed", errno);
	}

	strncpy(ifr.ifr_name, device_name, sizeof(ifr.ifr_name) - 1);
	if (ioctl(socket_handle, SIOCGIFINDEX, &ifr) != 0)
	{
		close(socket_handle);
		throw Exception("CAN socket failed", errno);
	}

	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(socket_handle, (struct sockaddr *)&addr, sizeof(addr)) != 0)
	{
		close(socket_handle);
		throw Exception("CAN bind failed", errno);
	}
}

CanSocket::~CanSocket()
{
	close(socket_handle);
}

int CanSocket::poll(const std::chrono::milliseconds timeout)
{
	struct pollfd descriptor {};

	descriptor.events  = POLLIN;
	descriptor.revents = 0;
	descriptor.fd      = socket_handle;

	return ::poll(&descriptor, 1, timeout.count());
}

bool CanSocket::read(can_frame & frame)
{
	const bool success = ::read(socket_handle, &frame, sizeof(can_frame)) == sizeof(can_frame);

	std::cout << "< " << frame << std::endl;
	return success;
}

size_t CanSocket::write(const can_frame & frame)
{
	const size_t written = ::write(socket_handle, &frame, CAN_MTU);

	std::cout << "> " << frame << std::endl;
	return written;
}

std::ostream & operator<<(std::ostream & os, const can_frame & frame)
{
	os << std::setfill('0') << std::setw(3) << std::hex << frame.can_id;
	os << " #";
	for (int i = 0; i < frame.can_dlc; ++i)
	{
		os << " " << std::setw(2) << unsigned(frame.data[i]);
	}
	return os;
}
