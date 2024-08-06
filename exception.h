//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

class Exception : public std::runtime_error
{
	std::string error_text;

	Exception() = default;

public:
	Exception(const char * text, const int error);

	virtual const char * what() const noexcept override;
};

#endif // EXCEPTION_H
