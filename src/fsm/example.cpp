#include "loader.h"
#include "parser_factory.h"     // ParserFactory

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

    const std::vector<fsm::InputLine> &scr   = l.get_script();

    printf( "done, %d lines read\n", scr.size() );

    fsm::Fsm        fsm;

    fsm::ParserI    * parser = fsm::ParserFactory::create( FSM_VERSION_100, fsm );

    if( parser == 0L )
    {
        printf( "ERROR: cannot create parser\n" );

        return 0;
    }

    return 0;
}
