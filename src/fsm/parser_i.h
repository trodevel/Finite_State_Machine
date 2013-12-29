// dc15
// interface

#ifndef ParserI_H
#define ParserI_H

#include "../types.h"              // uint32
#include "input_line.h"             // InputLine

#include "namespace_fsm.h"  // NAMESPACE_FSM_START

NAMESPACE_FSM_START

class ParserI
{
public:
    virtual ~ParserI() {};

public:
    virtual bool parse( const std::vector<InputLine> & v ) = 0;
};

NAMESPACE_FSM_END

#endif  // ParserI_H
