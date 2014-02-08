
#include <cstdio>
#include <string>
#include <boost/shared_ptr.hpp>

#include "loader.h"
#include "parser_factory.h"     // ParserFactory
#include "fsm.h"                // Fsm

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

    boost::shared_ptr< fsm::ParserI >   parser( fsm::ParserFactory::create( FSM_VERSION_100, fsm ) );

    if( parser == 0L )
    {
        printf( "ERROR: cannot create parser\n" );

        return 0;
    }

    bool parse_res  = parser->parse( scr );

    if( parse_res == false )
    {
        printf( "ERROR: cannot parse file\n" );

        return 0;
    }

    printf( "parsed - OK\n" );

    return 0;
}
