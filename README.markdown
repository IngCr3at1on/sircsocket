Simple IRCSocket
=========
_Simple IRCSocket_ is a simple IRC Socket written for C++ . It is originally
taken from an IRCClient developed by Fredi Machado and therefore retains the
same license.

## Limitations ##
Only allows for connecting on a single IRC server at a time.
While this should support Windows I have only tested it in Linux myself.

## DOWNLOAD ##
You can this project in either
[zip](http://github.com/IngCr3ation/zipball/master "zip") or
[tar](http://github.com/IngCr3at1on/tarball/master "tar") formats.

You can also clone the project with [Git](http://git-scm.com "Git") by running:

	$ git clone git://github.com/IngCr3at1on/sircsocket

If developing in git consider adding as a
[Submodule](http://git-scm.com/docs/git-submodule "Submodule) by running:

	$ git submodule add git://github.com/IngCr3at1on/sircsocket

## USAGE ##

### Init ###
`bool Init()`	
Initiates IRC Socket before connecting, returns true on success.

### Connect ###
`bool Connect(char const* host, int port)`
Connects to a given host and port number, returns true on success.

### Connected ###
`bool Connected()`
Returns true if currently connected.

### Disconnect ###
`void Disconnect()`
Disconnect from the current IRC session.

### SendData ###
`bool SendData(char const* data)`
Send data to the current IRC server, returns true on success.

### ReceiveData ###
`std::string ReceiveData()`
Returns a string containing the buffered data from the current IRC session.
Receives data in raw bytes, if bytes are less than 0 this will force a disconnect.

## LICENSE ##
This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

See included COPYING file for complete license.
