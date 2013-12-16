// DC15

#ifndef Parser100_H
#define Parser100_H

#include "fsm.h"                // Fsm, Token
#include "parser_i.h"           // ParserI

#include "namespace_fsm.h"      // NAMESPACE_FSM_START

NAMESPACE_FSM_START

class Parser100: public virtual ParserI
{
public:
    Parser100( Fsm & h );

private:
    Parser100( Parser100 & h ); // no copy
    Parser100& operator=( const Parser100 & h ); // no copy

public:
    bool parse();

private:

private:
    Fsm   & h_;
};

NAMESPACE_FSM_END

#endif  // Parser100_H
