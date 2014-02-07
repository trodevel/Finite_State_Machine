// DC29

#include "parser100.h"

#include "../utils/number_format.h"     // is_number_int
#include "str_helper.h"                 // to_string

#define TOK_A           "a"
#define TOK_ACT         "act"
#define TOK_CONST       "const"
#define TOK_END         "end"
#define TOK_EXIT        "exit"
#define TOK_FINITESTATEMACHINE      "finitestatemachine"
#define TOK_NS          "ns"
#define TOK_NEXTSTATE   "nextstate"
#define TOK_S           "s"
#define TOK_SEND_SIGNAL "sendsignal"
#define TOK_SIGNAL      "signal"
#define TOK_STATE       "state"
#define TOK_X           "x"

#include <set>          // std::set
#include <iostream>     // std::cout
#include <stdexcept>    // std::runtime_error
#include <sstream>      // std::stringstream
#include <boost/lexical_cast.hpp>   // lexical_cast

NAMESPACE_FSM_START

/* ********************************************************************************************* */

Parser100::Parser100( Fsm & h ):  h_( h )
{
}

/* ********************************************************************************************* */

// implementation


bool Parser100::is_cmd_supported( const std::string & cmd )
{
    static std::set<std::string> s;
    if( s.empty() )
    {
        s.insert( TOK_A );
        s.insert( TOK_ACT );
        s.insert( TOK_CONST );
        s.insert( TOK_END );
        s.insert( TOK_EXIT );
        s.insert( TOK_FINITESTATEMACHINE );
        s.insert( TOK_NS );
        s.insert( TOK_NEXTSTATE );
        s.insert( TOK_S );
        s.insert( TOK_SEND_SIGNAL );
        s.insert( TOK_SIGNAL );
        s.insert( TOK_STATE );
        s.insert( TOK_X );
    }
    return ( s.count( cmd ) > 0 );
}

enum state_e
{
    UNDEF   = 0,
    SCRIPT,
    STATE,
    SIGNAL,
    END
};

bool Parser100::parse( const std::vector<InputLine> & v )
{
    state_e state = UNDEF;

    VectInputLine::const_iterator it_end = v.end();
    VectInputLine::const_iterator it = v.begin();

    for( ; it != it_end; ++it )
    {
        const InputLine & l = *it;

        const std::string & p0 = l.tokens[0];

        switch( state )
        {
        case UNDEF:
            if ( p0 == TOK_FINITESTATEMACHINE )
            {
                state = SCRIPT;
            }
            break;
        case SCRIPT:
            if( p0 == TOK_CONST )
            {
                handle_const( l );
            }
            else if( p0 == TOK_STATE )
            {
                handle_state( l );
                state = STATE;
            }
            else if ( p0 == TOK_END )
            {
                state = END;
            }
            else
            {
                throw_error( "error parsing line", l );
            }
            break;
        case STATE:
            if( p0 == TOK_SIGNAL )
            {
                handle_signal_handler( l );
                state   = SIGNAL;
            }
            else if( p0 == TOK_STATE )
            {
                complete_current_state();
                handle_state( l );
                state = STATE;
            }
            else if ( p0 == TOK_END )
            {
                state = END;
            }
            else
            {
                throw_error( "error parsing line", l );
            }
            break;
        case SIGNAL:
            if( p0 == TOK_A || p0 == TOK_ACT )
            {
                handle_action( l );
            }
            else if( p0 == TOK_NS || p0 == TOK_NEXTSTATE )
            {
                handle_nextstate( l );
            }
            else if( p0 == TOK_X || p0 == TOK_EXIT )
            {
                handle_exit( l );
            }
            else if( p0 == TOK_S || p0 == TOK_SEND_SIGNAL )
            {
                handle_sendsignal( l );
            }
            else if( p0 == TOK_STATE )
            {
                complete_current_signal_handler();
                complete_current_state();
                handle_state( l );
                state = STATE;
            }
            else if( p0 == TOK_SIGNAL )
            {
                complete_current_signal_handler();
                handle_signal_handler( l );
                state   = SIGNAL;
            }
            else if ( p0 == TOK_END )
            {
                state = END;
            }
            else
            {
                throw_error( "error parsing line", l );
            }
            break;
        case END:
            // ignore all commands
            break;
        default:
            {
                throw_error( "error parsing line", l );
            }
            break;
        }
    }

    return true;
}

/* ********************************************************************************************* */

void Parser100::handle_const( const InputLine & l )
{
    // format: const name value
    if( l.tokens.size() < 3 )
        throw_error( "expected 3 arguments", l );

    const std::string & name    = l.tokens[1];
    const std::string & val     = l.tokens[2];

    if( has_const( name ) )
        throw_error( "constant is already defined", l );

    if( is_number_int( val ) )
    {
        int32 val_i   = boost::lexical_cast<int32>( val );
        add_const( name, val_i );
    }
    else if( is_number_float( val ) )
    {
        double val_d   = boost::lexical_cast<double>( val );
        add_const( name, val_d );
    }
    else
    {
        add_const( name, val );
    }
}

void Parser100::handle_state( const InputLine & l )
{
    // format: state <state_name>
    if( l.tokens.size() < 2 )
        throw_error( "expected 2 arguments", l );

    temp_state_     = State();  // clear the temp state

    const std::string & name    = l.tokens[1];

    temp_state_.name_   = name;

}
void Parser100::handle_signal_handler( const InputLine & l )
{
    // format: signal <signal_name>
    if( l.tokens.size() < 2 )
        throw_error( "expected 2 arguments", l );

    temp_signal_handler_     = SignalHandler();  // clear the temp signal

    const std::string & name    = l.tokens[1];

    temp_signal_handler_.name_       = name;

}

void Parser100::handle_action( const InputLine & l )
{
    // format: (a|act) action_name [arg1 [arg2]]
    if( l.tokens.size() < 2 )
        throw_error( "expected 2 or more arguments", l );

    Action a;

    a.type_ = ACT_CALL;
    a.name_ = l.tokens[1];

    for( int i = 2; i < l.tokens.size(); ++i )
    {
        Param p = str_to_param( l.tokens[i] );
        a.pars_.push_back( p );
    }

    temp_signal_handler_.actions_.push_back( a );
}

void Parser100::handle_sendsignal( const InputLine & l )
{
    // format: (s|sendsignal) signal_name [arg1 [arg2]]
    if( l.tokens.size() < 2 )
        throw_error( "expected 2 or more arguments", l );

    Action a;

    a.type_ = ACT_SIGNAL;
    a.name_ = l.tokens[1];

    for( int i = 2; i < l.tokens.size(); ++i )
    {
        Param p = str_to_param( l.tokens[i] );
        a.pars_.push_back( p );
    }

    temp_signal_handler_.actions_.push_back( a );
}

void Parser100::handle_nextstate( const InputLine & l )
{
    // format: (ns|nextstate) state_name
    if( l.tokens.size() != 2 )
        throw_error( "expected 2 arguments", l );

    Action a;

    a.type_ = ACT_NEXT_STATE;
    a.name_ = l.tokens[1];

    temp_signal_handler_.actions_.push_back( a );
}

void Parser100::handle_exit( const InputLine & l )
{
    // format: (x|exit)
    if( l.tokens.size() != 1 )
        throw_error( "expected 1 argument", l );

    Action a;

    a.type_ = ACT_EXIT;

    temp_signal_handler_.actions_.push_back( a );
}

void Parser100::complete_current_signal_handler()
{
    temp_state_.map_.insert( State::MapSignalToHandler::value_type( temp_signal_handler_.name_, temp_signal_handler_ ));

    temp_signal_handler_ = SignalHandler();   // clear
}
void Parser100::complete_current_state()
{
    h_.add_state( temp_state_ );

    temp_state_ = State();      // clear
}

/* ********************************************************************************************* */

void Parser100::throw_error( const std::string & msg, const InputLine & l )
{
    throw_error( msg.c_str(), l );
}

void Parser100::throw_error( const char* msg, const InputLine & l )
{
    std::stringstream out;

    out << msg << ", " << to_string( l );

    printf( "ERROR: %s\n", out.str().c_str() );

    throw std::runtime_error( out.str().c_str() );
}

/* ********************************************************************************************* */


/**
 * @return true if given constant already exist
 */
bool Parser100::has_const( const std::string & s ) const
{
    if( const_str_.count( s ) )
        return true;
    if( const_int_.count( s ) )
        return true;
    if( const_double_.count( s ) )
        return true;

    return false;
}

bool Parser100::add_const( const std::string & s, const std::string & v )
{
    const_str_[ s ] = v;
    return true;
}
bool Parser100::add_const( const std::string & s, int32 val )
{
    const_int_[ s ] = val;
    return true;
}
bool Parser100::add_const( const std::string & s, double val )
{
    const_double_[ s ] = val;
    return true;
}


/* ********************************************************************************************* */


Param Parser100::str_to_param( const std::string & s ) const
{
    if( is_number_int( s ) )
    {
        Param res( PARTP_INT, s );

        return res;
    }
    else if( is_number_float( s ) )
    {
        Param res( PARTP_FLOAT, s );

        return res;
    }
    else if( has_const( s ) )
    {
        Param res   = const_to_param( s );

        return res;
    }

    Param res( PARTP_STR, s );

    return res;
}

Param Parser100::const_to_param( const std::string &s ) const
{
    Param res;

    if( const_str_.count( s ) )
        return Param( PARTP_STR, const_str_.find( s )->second );

    if( const_int_.count( s ) )
        return Param( PARTP_INT, const_int_.find( s )->second );

    if( const_double_.count( s ) )
        return Param( PARTP_FLOAT, const_double_.find( s )->second );

    return res;
}

NAMESPACE_FSM_END

/* ********************************************************************************************* */
