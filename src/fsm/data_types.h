// DC4

#include <string>
#include <vector>

#include "parameter.h"      // Param

#include "namespace_fsm.h"  // NAMESPACE_FSM_START

NAMESPACE_FSM_START

enum action_type_e
{
    ACT_UNDEF   = 0,
    ACT_CALL,
    ACT_SIGNAL,
    ACT_NEXT_STATE,
    ACT_EXIT
};

class Action
{
public:


public:
    action_type_e       type_;  // action type
    std::string         name_;  // optional name
    std::vector<Param>  pars_;  // optional parameters
};

class OnSignal
{
public:

public:
    std::string         name_;      // name of the trigger signal
    std::vector<Action> actions_;   // optional actions to perform
};



NAMESPACE_FSM_END

