//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#include <cstring>

#include "exception.h"

Exception::Exception(const char * reason, const int error) : std::runtime_error(error_text)
{
	error_text.assign(reason);

	const char * text = strerror(error);

	if ((text != nullptr) && (error != 0))
	{
		error_text += ": ";
		error_text += std::string(text);
	}
	else
	{
		error_text += "!";
	}
}

const char * Exception::what() const noexcept
{
	return error_text.c_str();
}
