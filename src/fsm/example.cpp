
#include <cstdio>
#include <string>
#include <boost/shared_ptr.hpp>

#include <iostream>             // cout

#include "loader.h"
#include "parser_factory.h"     // ParserFactory
#include "fsm.h"                // Fsm
#include "str_helper.h"         // StrHelper

#include "../utils/tokenizer.h" // tokenize_to_vector

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

#include "../utils/number_format.h"  // is_number_int

fsm::Param str_to_param( const std::string & s )
{
    if( is_number_int( s ) )
    {
        fsm::Param res( fsm::PARTP_INT, s );

        return res;
    }
    else if( is_number_float( s ) )
    {
        fsm::Param res( fsm::PARTP_FLOAT, s );

        return res;
    }

    fsm::Param res( fsm::PARTP_STR, s );

    return res;
}

void control( fsm::Fsm & fsm )
{
    std::cout << "type exit or quit to quit: " << std::endl;
    std::cout << "supported commands:\n"
            << "c    - send clock impulse\n"
            << "test - send test signal\n"
            << "s <name> [<par>]- send signal 'name'\n"
            << std::endl;

    std::string input;

    while( true )
    {
        //std::cout << "your command: " << std::endl;

        std::getline( std::cin, input );
        std::cout << "command: " << input << std::endl;

        std::vector< std::string > pars;

        tokenize_to_vector( pars, input, " " );

        if( pars.empty() )
            continue;

        const std::string & p0 = pars[0];

        if( p0 == "exit" || p0 == "quit" )
            break;
        else if( p0 == "test" )
        {
        }
        else if( p0 == "c" )
        {
            fsm.clock();
        }
        else if( p0 == "s" )
        {
            if( pars.size() < 2 )
            {

                std::cout << "ERROR: need signal name" << std::endl;
                continue;
            }

            const std::string name = pars[1];

            //const std::string p1 = pars[1];

            std::vector<fsm::Param> pars2;

            for( int i = 2; i < (int)pars.size(); ++i )
            {
                fsm::Param p = str_to_param( pars[i] );
                pars2.push_back( p );
            }

            fsm.send_signal( name, pars2 );
        }
    };

    std::cout << "exiting ..." << std::endl;
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

    bool check = fsm.check();

    if( check == false )
    {
        std::cout << "ERROR: check failed - '" + fsm.get_error_message() + "'\n";

        return 0;
    }

    control( fsm );

    return 0;
}
