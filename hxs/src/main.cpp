/*
* LXS
* Copyright (C) 2010 nex
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include <iostream>
#include <cstdlib>
#include <cstring>
#include <hxs.h>

#include <csignal>

SymClass test;

void
now_dump(  )
{
	std::cout << "\n====== END EXECUTING ======\n";

	test.dump();

	exit( 1 );
}

int
main(int argc,char *argv[])
{
	int err = 0;

	signal( SIGINT, (__sighandler_t)now_dump );

	if(!argv[1])
	{
		test.stdin_read();
		
		std::cout << "\n";

	} else if (!strcmp(argv[1],"-s") || !strcmp(argv[1],"--source")) {
		if (!argv[2])
		{
			std::cout << "Error bad usage, type -h for help." << std::endl;

			return 1;
		}

		err = test.readfile(argv[2]);

		if( err )
		{
			std::cout << "Error reading file." << std::endl;

			return 1;
		}

	} else if (!strcmp(argv[1],"-x") || !strcmp(argv[1],"--binary")) {
		if (!argv[2])
		{
			std::cout << "Error bad usage, type -h for help." << std::endl;

			return 1;
		}

		err = test.read_bin(argv[2]);

		if ( err == 1 )
		{
			std::cout << "Error reading file." << std::endl;

			return 1;
		} else if ( err == 2 ) {
			std::cout << "Not a valid HXS file." << std::endl;

			return 1;
		}

	} else if (!strcmp(argv[1],"-c") || !strcmp(argv[1],"--compile")) {
		if (!argv[2] || !argv[3]) 
		{
			std::cout << "Error bad usage, type -h for help." << std::endl;

			return 1;
		}

		if(!test.pseudo_compile(argv[2],argv[3]))
		{
			std::cout << "Compilation complete!" << std::endl;
		} else {
			std::cout << "Error reading file." << std::endl;

			return 1;
		}

		return 0;
	} else if (!strcmp(argv[1],"-v") || !strcmp(argv[1],"--version")) {
		std::cout << VTEXT << std::endl;

		return 0;
	} else if (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")) {
		std::cout << "Usage: " << argv[0] << " [-s <file>] [-x <file>] [-c <file> <compiled>]\n"
				   "\t-s|--source\tSelect the source file.\n"
				   "\t-x|--binary\tSelect the binary source file.\n"
				   "\t-c|--compile\tCompile from plain text source to binary source file.\n"
				   "\t-v|--version\tShow version.\n"
				   "\t-h|--help\tShow this help.\n";
		
		return 0;
	} else {
		std::cout << "Error bad usage, type -h for help." << std::endl;

		return 1;
	}

	std::cout << "====== EXECUTING CODE ======\n\n";

	test.execute();

	std::cout << "\n====== END EXECUTING ======\n";
	
	test.dump();

	return 0;
}
