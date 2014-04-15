/*

printf for std::string.

http://stackoverflow.com/questions/69738/c-how-to-get-fprintf-results-as-a-stdstring-w-o-sprintf#69911

Copyright (C) 2014 Sergey Kolevatov

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

*/

// $Id: vformat.h 384 2014-04-15 16:21:07Z serge $

#ifndef VFORMAT_H
#define VFORMAT_H

#include <string>               // std::string
#include <stdarg.h>             // va_list stuff

std::string vformat( const char *fmt, va_list ap );
std::string vformat_2( const char* fmt, ... );

#endif // VFORMAT_H