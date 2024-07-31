//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 Steffen A. Mork
//

pipeline
{
	agent any

	stages
	{
		stage ('Clean')
		{
			steps
			{
				sh 'rm -rf build'
			}
		}
		stage ('CMake')
		{
			steps
			{
				sh 'cmake -B build'
			}
		}
		stage ('Build')
		{
			steps
			{
				sh 'make -C build -j `nproc`'
			}
		}
	}

	post
	{
		always
		{
			chuckNorris()
			step([$class: 'Mailer', recipients: 'linux-dev@morknet.de'])
		}
	}
}
