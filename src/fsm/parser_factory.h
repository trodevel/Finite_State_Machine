// DC15

#ifndef ParserFactory_H
#define ParserFactory_H

#include "parser_i.h"               // ParserI

#include "namespace_fsm.h"  // NAMESPACE_FSM_START

NAMESPACE_FSM_START


#define FSM_VERSION_100  ( 100 )    // current version of fsm - 1.0

class ParserFactory
{
private:
    ParserFactory();

public:
    static bool is_version_supported( uint32 ver );

    static ParserI* create( uint32 ver, Fsm & h );
};

NAMESPACE_FSM_END

#endif  // ParserFactory_H
