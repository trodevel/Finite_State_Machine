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

bool Fsm::has_state( const std::string & name )
{
    return states_.count( name ) == 0;
}
bool Fsm::add_state( const State & s )
{
    states_[ s.name_ ]  = s;
    return true;
}



NAMESPACE_FSM_END

