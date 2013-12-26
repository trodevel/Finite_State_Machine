// DC17

#include "loader.h"

#define TOK_ENDSCRIPT   "endscript"
#define TOK_INCLUDE     "$include"
#define TOK_VER         "$ver"

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <stdexcept>    // std::runtime_error
#include <sstream>      // std::stringstream

#include <sstream>                  // std::ostringstream

#include <boost/lexical_cast.hpp>       // lexical_cast
#include "../utils/string_utils.h"      // remove_comments, remove_quotes
#include "../utils/tokenizer.h"         // tokenize_to_vector
#include "str_helper.h"                 // to_string

NAMESPACE_FSM_START

/* ********************************************************************************************* */

Loader::Loader():
    is_version_defined_( false ),
    is_script_read_( false ),
    ver_( 0 )
{
}

/* ********************************************************************************************* */

// implementation

InputLine Loader::create_input_line( const std::string & str, const std::string & filename, uint32 line_number )
{
    InputLine l;

    tokenize_to_vector( l.tokens, str, " " );

    l.line_num  = line_number;
    l.filename  = filename;

    std::cout << to_string( l ) << std::endl;

    return l;
}

bool Loader::add_to_script( const InputLine & l )
{
    // format: endscript
    if( l.tokens.size() < 1 )
    {
        throw_error( "expected 1 argument", l );
        return false;
    }

    const std::string & cmd = l.tokens[0];

    if( cmd == TOK_VER )
    {
        handle_version( l );
        return true;
    }

    if( cmd == TOK_ENDSCRIPT )
    {
        script_.push_back( l );
        is_script_read_ = true;
        return true;
    }

    if( cmd == TOK_INCLUDE )
    {
        if( l.tokens.size() < 2 )
            throw_error( "expected 2 arguments", l );

        return include_file( remove_quotes( l.tokens[1] ), l );
    }

    script_.push_back( l );

    return true;
}

bool Loader::is_script_read() const
{
    return is_script_read_;
}

const std::vector<InputLine> & Loader::get_script() const
{
    return script_;
}

void Loader::handle_version( const InputLine & l )
{
    // format: $ver version
    if( l.tokens.size() < 2 )
        throw_error( "expected 2 arguments", l );

    ver_    = boost::lexical_cast<uint32>( l.tokens[1] );

    if( is_version_defined_ )
        throw_error( "version is already defined", l );

    is_version_defined_    = true;
}

void Loader::read_file( const std::string & filename, const InputLine & l, VectStr & lines )
{
    std::ifstream in_file( filename.c_str() );
    std::string line;

    if( in_file.is_open() )
    {
        while( in_file.good() )
        {
            getline( in_file, line );

            lines.push_back( line.c_str() );
        }
        in_file.close();
    }
    else
    {
        throw_error( "Unable to open file", l );
    }

}

bool Loader::process_lines( const VectStr & lines, const std::string & filename )
{
    VectStr::const_iterator it_end = lines.end();
    VectStr::const_iterator it = lines.begin();

    for( int i = 1; it != it_end; ++it, ++i )
    {
        const std::string & line = *it;

        if( line.empty() )
            continue;

        std::string line2 = remove_comments( line );

        line2 = trim( line2 );

        if( line2.empty() )
            continue;

        InputLine l = create_input_line( line2, filename, i );

        add_to_script( l );

        bool should_stop = is_script_read();

        if( should_stop )
            return true;
    }

    return false;
}

bool Loader::load_file( const std::string & filename )
{
    InputLine dummy;

    dummy.filename  = filename;
    dummy.line_num  = 1;

    return include_file( filename, dummy );
}

bool Loader::include_file( const std::string & filename, const InputLine & l )
{
    VectStr lines;

    printf( "filename %s\n", filename.c_str() );

    read_file( filename, l, lines );

    return process_lines( lines, filename );
}

/* ********************************************************************************************* */

void Loader::throw_error( const std::string & msg, const InputLine & l )
{
    throw_error( msg.c_str(), l );
}

void Loader::throw_error( const char* msg, const InputLine & l )
{
    std::stringstream out;

    out << msg << ", " << to_string( l );

    printf( "ERROR: %s\n", out.str().c_str() );

    throw std::runtime_error( out.str().c_str() );
}

NAMESPACE_FSM_END
