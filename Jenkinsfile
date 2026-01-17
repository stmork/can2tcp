//
//  SPDX-License-Identifier: MIT
//  SPDX-FileCopyrightText: Copyright (C) 2024 - 2026  Steffen A. Mork
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
				sh 'cmake -B build -DCMAKE_BUILD_TYPE=Release'
			}
		}
		stage ('Build')
		{
			steps
			{
				sh 'cmake --build build --parallel'
			}
		}
		stage ('CppCheck')
		{
			steps
			{
				sh 'make -C build cppcheck'
				publishCppcheck pattern: 'cppcheck.xml'
			}
		}

		stage('Package')
		{
			steps
			{
				sh "cpack --config build/CPackConfig.cmake"
			}
		}
	}

	post
	{
		success
		{
			archiveArtifacts artifacts: '*.deb', followSymlinks: false
		}
		always
		{
			chuckNorris()
			step([$class: 'Mailer', recipients: 'linux-dev@morknet.de'])
		}
	}
}
