//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include "cansocket.h"

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <linux/can/raw.h>

#include <cstring>
#include <stdexcept>
#include <iomanip>

CanSocket::CanSocket(const char * device_name)
{
	struct sockaddr_can addr {};
	struct ifreq        ifr;

	socket_handle = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (socket_handle < 0)
	{
		throw std::runtime_error("CAN failed.");
	}

	strncpy(ifr.ifr_name, device_name, sizeof(ifr.ifr_name) - 1);
	if (ioctl(socket_handle, SIOCGIFINDEX, &ifr) != 0)
	{
		close(socket_handle);
		throw std::runtime_error("Socket failed.");
	}

	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(socket_handle, (struct sockaddr *)&addr, sizeof(addr)) != 0)
	{
		close(socket_handle);
		throw std::runtime_error("Bind failed.");
	}
}

CanSocket::~CanSocket()
{
	close(socket_handle);
}

bool CanSocket::read(can_frame & frame)
{
	return ::read(socket_handle, &frame, sizeof(can_frame)) == sizeof(can_frame);
}

size_t CanSocket::write(const can_frame & frame)
{
	return ::write(socket_handle, &frame, CAN_MTU);
}
