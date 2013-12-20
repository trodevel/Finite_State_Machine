// DC18

#include <string>

#include "../utils/trim.h"      // trim
/**
 * @descr remove comments starting with '#'
 */
std::string remove_comments( const std::string & str, const std::string::value_type c = '#' )
{
    std::string::size_type hash_pos = str.find( c );

    if( std::string::npos == hash_pos )
        return str;

    std::string res = str.substr( 0, hash_pos );

    return trim( res );
}