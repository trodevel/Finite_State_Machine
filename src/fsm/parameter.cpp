// DC4

#include "parameter.h"  // self

NAMESPACE_FSM_START

Param::Param():
    type_( PARTP_UNDEF )
{
}

Param::Param( param_type_e type, const std::string & value ):
        type_( type ), value_( value )
{
}
