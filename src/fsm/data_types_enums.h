// E28

#ifndef DATA_TYPES_ENUMS_H
#define DATA_TYPES_ENUMS_H


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


NAMESPACE_FSM_END

#endif  // DATA_TYPES_ENUMS_H
