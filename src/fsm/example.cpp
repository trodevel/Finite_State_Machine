
#include <cstdio>
#include <string>
#include <boost/shared_ptr.hpp>

#include <iostream>             // cout

#include "loader.h"
#include "parser_factory.h"     // ParserFactory
#include "fsm.h"                // Fsm
#include "str_helper.h"         // StrHelper

#include "str_helper_t.h"       // to_string2
#include "fsm_callback_i.h"     // FsmCallbackI
class Callback: public fsm::FsmCallbackI
{
public:
    bool send_signal( const std::string & name, std::vector<fsm::Param> pars );
    bool call_action( const std::string & name, std::vector<fsm::Param> pars );

};

bool Callback::send_signal( const std::string & name, std::vector<fsm::Param> pars )
{
    std::cout << "recv signal '" << name << "' { " << fsm::to_string2( pars ) << "}" << std::endl;
    return true;
}
bool Callback::call_action( const std::string & name, std::vector<fsm::Param> pars )
{
    std::cout << "call '" << name << "' ( " << fsm::to_string2( pars ) << ")" << std::endl;
    return true;
}

void control( fsm::Fsm & fsm )
{
    std::cout << "type exit for exit, s - send signal\n";
    while( true )
    {
        std::string inp;

        std::cout << "$ ";
        std::cin >> inp;

        if( inp == "exit" || inp == "quit" )
            break;
    }

    std::cout << "exiting" << std::endl;
}

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

    std::cout << "DEBUG:\n" << fsm::StrHelper::to_string( fsm ) << "\n";
    //printf( "DEBUG:\n%s\n", fsm::StrHelper::to_string( fsm ).c_str() );

    Callback cb;

    fsm.set_callback_if( & cb );

    return 0;
}
