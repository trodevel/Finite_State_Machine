// DC15

#include "parser_factory.h"         // self

#include "fsm.h"                    // fsm


#include "parser100.h"              // Parser100

NAMESPACE_FSM_START

bool ParserFactory::is_version_supported( uint32 ver )
{
    switch( ver )
    {
    case FSM_VERSION_100:
        return true;

    default:
        break;
    }

    return false;
}

ParserI* ParserFactory::create( uint32 ver, Fsm & h )
{
    switch( ver )
    {
    case FSM_VERSION_100:
        return new Parser100( h );

    default:
        break;
    }

    return 0L;
}

NAMESPACE_FSM_END
