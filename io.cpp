//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include "io.h"

void ProxyIo::proxy(IoWriter writer)
{
	can_frame frame{};

	if (read(frame))
	{
		writer(frame);
	}
}
