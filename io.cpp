//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include "io.h"

bool ProxyIo::proxy(ProxyIo & writer)
{
	can_frame  frame{};
	const bool received = read(frame);

	if (received)
	{
		writer.write(frame);
	}
	return received;
}
