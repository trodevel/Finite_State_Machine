// DC4

#include <string>
#include <vector>

#include "namespace_fsm.h" // NAMESPACE_FSM_START

NAMESPACE_FSM_START

enum param_type_e
{
    PARTP_UNDEF = 0,
    PARTP_INT,
    PARTP_FLOAT,
    PARTP_STR
};

class Param
{
public:
    Param();
    Param( param_type_e type, const std::string & value );

public:
    param_type_e    type_;
    std::string     value_;
};

NAMESPACE_FSM_END

