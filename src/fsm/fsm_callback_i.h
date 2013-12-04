// DC4
// callback interface

#include <string>
#include <vector>

#include "parameter.h"      // Param

#include "namespace_fsm.h"  // NAMESPACE_FSM_START

NAMESPACE_FSM_START

class FsmCallbackI
{
public:

    virtual ~FsmCallbackI() {};

    // operation
    virtual bool send_signal( const std::string & name, std::vector<Param> pars )   = 0;
    virtual bool call_action( const std::string & name, std::vector<Param> pars )   = 0;

};


NAMESPACE_FSM_END

