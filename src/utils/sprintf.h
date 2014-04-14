// $Id: sprintf.h 282 2013-11-18 22:38:28Z serge $
// @url http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf

#ifndef SPRINTF_H
#define SPRINTF_H

#include <string>               // std::string
#include <stdarg.h>             // va_list stuff

void spf( std::string &s, const char *fmt, ... );
void spf_2( std::string &s, const char *fmt, va_list ap );

#endif // SPRINTF_H
