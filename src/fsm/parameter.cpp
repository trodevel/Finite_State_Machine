// DC4

#include "parameter.h"  // self

NAMESPACE_FSM_START

Param::Param():
    type_( PARTP_UNDEF ), val_int_( 0 ), val_float_( 0 )
{
}

Param::Param( param_type_e type, const std::string & value ):
        type_( type ), value_( value ), val_int_( 0 ), val_float_( 0 )
{
}

Param::Param( param_type_e type, const int32 value ):
        type_( type ), val_int_( value ), val_float_( 0 )
{
}

Param::Param( param_type_e type, const double value ):
        type_( type ), val_int_( 0 ), val_float_( value )
{
}

NAMESPACE_FSM_END
