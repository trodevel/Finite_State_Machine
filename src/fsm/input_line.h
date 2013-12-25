// DC17

#ifndef InputLine_H
#define InputLine_H

#include <string>               // std::string
#include <vector>
#include <iostream>             // std::ostream

#include "../utils/types.h"     // uint32

#include "namespace_fsm.h"  // NAMESPACE_FSM_START

NAMESPACE_FSM_START

typedef std::vector<std::string>   VectStr;


class InputLine
{
public:
    VectStr         tokens;
    std::string     filename;
    uint32          line_num;
};

typedef std::vector< InputLine >  VectInputLine;

NAMESPACE_FSM_END

#endif  // InputLine_H
