// $Id: dummy_logger.cpp 282 2013-11-18 22:38:28Z serge $

/*

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

#include "dummy_logger.h"       // self
#include "sprintf.h"            // spf_2
#include <iostream>             // cout

void dummy_log( const int level, const char *module_name, const char *fmt, ... )
{
    std::string res;
    va_list ap;
    va_start( ap, fmt );

    spf_2( res, fmt, ap );
    va_end( ap );

    std::cout << module_name << ": " << res << std::endl;
}

