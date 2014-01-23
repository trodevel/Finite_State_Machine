// DC12

#include "fsm.h"        // self

NAMESPACE_FSM_START

Fsm::Fsm()
{

}
Fsm::~Fsm()
{

}

// administration
bool Fsm::load( const std::string & filename )
{
    return false;
}
bool Fsm::load_from_str( const std::string & str )
{
    return false;
}
bool Fsm::set_callback_if( FsmCallbackI * callback )
{
    return false;
}

// operation
bool Fsm::send_signal( const std::string & name, std::vector<Param> pars )
{
    return false;
}
bool Fsm::start()
{
    return false;
}

bool Fsm::clock()
{
    return false;
}


/**
 * @return true if given constant already exist
 */
bool Fsm::has_const( const std::string & s ) const
{
    if( const_str_.count( s ) )
        return true;
    if( const_int_.count( s ) )
        return true;
    if( const_double_.count( s ) )
        return true;

    return false;
}

bool Fsm::add_const( const std::string & s, const std::string & v )
{
    const_str_[ s ] = v;
    return true;
}
bool Fsm::add_const( const std::string & s, int32 val )
{
    const_int_[ s ] = val;
    return true;
}
bool Fsm::add_const( const std::string & s, double val )
{
    const_double_[ s ] = val;
    return true;
}


NAMESPACE_FSM_END

