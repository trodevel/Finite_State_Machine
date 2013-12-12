// DC12

#include "fsm_i.h"    // FsmI

NAMESPACE_FSM_START

class Fsm: virtual public FsmI
{
public:

    Fsm();
    ~Fsm();

    // administration
    bool load( const std::string & filename );
    bool load_from_str( const std::string & str );
    bool set_callback_if( FsmCallbackI * callback );

    // operation
    bool send_signal( const std::string & name, std::vector<Param> pars );
    bool start();

    bool clock();

};


NAMESPACE_FSM_END

