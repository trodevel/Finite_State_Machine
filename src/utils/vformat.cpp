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

// $Id: vformat.cpp 384 2014-04-15 16:21:07Z serge $

#include "vformat.h"    // self

#include <vector>

std::string vformat( const char *fmt, va_list ap )
{
    // Allocate a buffer on the stack that's big enough for us almost
    // all the time.  Be prepared to allocate dynamically if it doesn't fit.
    size_t size = 1024;
    char stackbuf[1024];
    std::vector<char> dynamicbuf;
    char *buf = &stackbuf[0];

    while( true )
    {
        // Try to vsnprintf into our buffer.
        int needed = vsnprintf( buf, size, fmt, ap );
        // NB. C99 (which modern Linux and OS X follow) says vsnprintf
        // failure returns the length it would have needed.  But older
        // glibc and current Windows return -1 for failure, i.e., not
        // telling us how much was needed.

        if( needed <= (int)size && needed >= 0 )
        {
            // It fit fine so we're done.
            return std::string( buf, (size_t)needed );
        }

        // vsnprintf reported that it wanted to write more characters
        // than we allotted.  So try again using a dynamic buffer.  This
        // doesn't happen very often if we chose our initial size well.
        size = ( needed > 0 ) ? ( needed + 1 ) : ( size * 2 );
        dynamicbuf.resize( size );
        buf = &dynamicbuf[0];
    }

    return std::string();   // never reached, only to avoid warning
}


std::string vformat_2( const char* fmt, ... )
{
    std::string m;

    if( fmt != 0 )
    {
        va_list ap;

        va_start( ap, fmt );

        m   = vformat( fmt, ap );

        va_end( ap );
    }

    return m;
}
