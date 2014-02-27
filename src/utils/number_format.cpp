// E110

#include "number_format.h"  // self

bool is_number_int( const std::string & arg )
{
    int sign_corr = 0;

    // check if sign is present
    if( arg.compare( 0, 1, "-" ) == 0 )
    {
        sign_corr = 1;
    }

    // check if hex number
    if( arg.compare( 0 + sign_corr, 2, "0x" ) == 0 )
    {
        for( int i = 2 + sign_corr; i < ( int )arg.length(); ++i )
            {
                int c = arg.at( i );
                if( ( c < '0' || c > '9' ) && ( c < 'a' || c > 'f' ) )
                    return false;
            }
    }
    else
    {
        // check if a decimal number
        for( int i = 0 + sign_corr; i < ( int )arg.length(); ++i )
        {
            int c = arg.at( i );
            if( c < '0' || c > '9')
                return false;
        }
    }
    return true;
}

bool is_number_float( const std::string & arg )
{
    // check if a floating point number
    for( int i = 0; i < ( int )arg.length(); ++i )
    {
        int c = arg.at( i );
        if( c != '-' && c != '.' && ( c < '0' || c > '9' ) )
            return false;
    }

    return true;
}
