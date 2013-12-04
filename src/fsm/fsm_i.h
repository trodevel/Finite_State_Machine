// DC4

#include <string>
#include <vector>

#include "parameter.h"      // Param

#include "namespace_fsm.h"  // NAMESPACE_FSM_START

NAMESPACE_FSM_START

class FsmCallbackI; // call back interface

class FsmI
{
public:

    virtual ~FsmI() {};

    // administration
    virtual bool load( const std::string & filename )       = 0;    // load FSM from file
    virtual bool load_from_str( const std::string & str )   = 0;    // load FSM from string
    virtual bool set_callback_if( FsmCallbackI * callback ) = 0;    // set callback interface

    // operation
    virtual bool send_signal( const std::string & name, std::vector<Param> pars )   = 0;
    virtual bool start()                                    = 0;    // start transition

    virtual bool clock()                                    = 0;    // clock

};


NAMESPACE_FSM_END

