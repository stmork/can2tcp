//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include "io.h"

bool ProxyIo::proxy(ProxyIo & writer)
{
	const int count = poll();

	if (count > 0)
	{
		can_frame  frame{};

		if (read(frame))
		{
			return writer.write(frame) > 0;
		}
	}
	else if (count == 0)
	{
		// Timeout. Everything looks fine.
		return true;
	}
	return false;
}
