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

bool Fsm::check()
{
    if( start_state_.empty() )
    {
        set_err_message( "start_state is empty" );
        return false;
    }

    // check whether state exists
    if( !has_state( start_state_ ) )
    {
        set_err_message( std::string( "start_state doesn't exist - " ) + start_state_ );
        return false;
    }

    return true;
}

const std::string & Fsm::get_error_message() const
{
    return err_message_;
}


// operation
bool Fsm::send_signal( const std::string & name, std::vector<Param> pars )
{
    return false;
}
bool Fsm::start()
{
    curr_state_ = states_.find( start_state_ );

    if( curr_state_ == states_.end() )
    {
        set_err_message( "start: cannot find start state" );
        return false;
    }

    return true;
}

bool Fsm::clock()
{
    return false;
}

bool Fsm::has_state( const std::string & name )
{
    return states_.count( name ) > 0;
}
bool Fsm::add_state( const State & s )
{
    states_[ s.name_ ]  = s;
    return true;
}

bool Fsm::set_start_state( const std::string & s )
{
    // check if state is already defined
    if( !start_state_.empty() )
        return false;

    if( s.empty() )
        return false;

    // check whether state exists
    if( !has_state( s ) )
        return false;

    start_state_    = s;

    return true;
}

void Fsm::set_err_message( const std::string & s )
{
    err_message_    = s;
}

NAMESPACE_FSM_END

