/*
 * Copyright (C) 2014 Nathan Bass <https://github.com/IngCr3at1on>
 * Copyright (C) 2011 Fredi Machado <https://github.com/Fredi>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/*******************************************************************************
Simple IRC Socket Handling:

	This has been pulled from https://github.com/Fredi/IRCClient for use in
	other IRC applications.

	For a full IRC Client or simple bot please see the above repo.

	All comments were added by me (Nathan) when updating for use as a library.

Changes from original:
	Added namespace.
	Converted to header only library.
	Changed cout usage to cerr.
	Removed class in lieu of namespacing.

TODO:
	Test Windows functionality.
	Allow for connecting to multiple servers and multiple channels.
	Possibly rewrite to support C and C++.
*******************************************************************************/

#ifndef _IRCSOCKET_H_
#define _IRCSOCKET_H_

#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
	#include <winsock2.h>
#else
	#include <netinet/in.h>
	#include <netdb.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <unistd.h> // Added to accomodate missing close declaration.
#endif

#define closesocket(s) close(s)
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define MAXDATASIZE 4096

namespace sircsocket {
	int _socket;
	bool _connected;

	bool Init() {
		if((_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
			std::cerr << "Socket error." << std::endl;
			return false;
		}

		int on = 1;
		if(setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (char const*)&on, sizeof(on)) == -1) {
			std::cerr << "Invalid socket." << std::endl;
			return false;
		}

		fcntl(_socket, F_SETFL, O_NONBLOCK);
		fcntl(_socket, F_SETFL, O_ASYNC);

		return true;
	}

	bool Connect(char const* host, int port) {
		hostent* he;

		if(!(he = gethostbyname(host))) {
			std::cerr << "Could not resolve host: " << host << std::endl;
			return false;
		}

		sockaddr_in addr;

		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr = *((const in_addr*)he->h_addr);
		memset(&(addr.sin_zero), '\0', 8);

		if(connect(_socket, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
			std::cerr << "Could not connect to: " << host << std::endl;
			closesocket(_socket);
			return false;
		}

		_connected = true;
		return true;
	}

	void Disconnect() {
		if(_connected) {
			closesocket(_socket);
			_connected = false;
		}
	}

	bool Connected() { return _connected; }

	bool SendData(char const* data) {
		if(_connected) {
			if(send(_socket, data, strlen(data), 0) == -1) {
				return false;
			}
			return true;
		}
	}

	std::string ReceiveData() {
		char buffer[MAXDATASIZE];

		memset(buffer, 0, MAXDATASIZE);

		int bytes = recv(_socket, buffer, MAXDATASIZE - 1, 0);

		if(bytes > 0) {
			return std::string(buffer);
		} else {
			Disconnect();
		}

		return "";
	}
} // namespace sircsocket

#endif // _IRCSOCKET_H_
