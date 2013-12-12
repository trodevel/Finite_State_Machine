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

NAMESPACE_FSM_END

