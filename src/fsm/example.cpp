#include "loader.h"

#include <cstdio>
#include <string>

int main( int argc, const char** argv )
{
    printf( "Hello, world!\n" );

    if( argc <= 1 )
    {
        printf( "USAGE: example <name.fsm>\n" );

        return 0;
    }

    std::string filename( argv[1] );

    fsm::Loader l;

    printf( "reading %s ...\n", filename.c_str() );

    bool b = l.load_file( filename );

    if( !b )
    {
        printf( "ERROR: error loading file\n" );

        return 0;
    }

    if( !l.is_script_read() )
    {
        printf( "ERROR: script is incomplete\n" );

        return 0;
    }

    const std::vector<fsm::InputLine> &scr   = l.get_script();

    printf( "done, %d lines read\n", scr.size() );

    return 0;
}
