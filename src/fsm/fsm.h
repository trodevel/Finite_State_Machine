// DC12

#ifndef FSM_H
#define FSM_H

#include "fsm_i.h"    // FsmI

#include <map>          // std::map
#include "../utils/types.h" // int32
#include "data_types.h"     // State

NAMESPACE_FSM_START

class Fsm: virtual public FsmI
{
    friend class StrHelper;

public:
    typedef std::map< std::string, State >          MapStrToState;

public:

    Fsm();
    ~Fsm();

    // administration
    bool load( const std::string & filename );
    bool load_from_str( const std::string & str );
    bool set_callback_if( FsmCallbackI * callback );
    bool check();
    const std::string & get_error_message() const;

    // operation
    bool send_signal( const std::string & name, std::vector<Param> pars );
    bool start();

    bool clock();


    // loading helpers
    bool has_state( const std::string & name );
    bool add_state( const State & s );
    bool set_start_state( const std::string & s );

private:
    void set_err_message( const std::string & s );

    bool execute_action( const Action & a );

private:

    MapStrToState   states_;

    std::string     start_state_;

    MapStrToState::const_iterator   curr_state_;

    std::string     err_message_;
};


NAMESPACE_FSM_END

#endif // FSM_H
