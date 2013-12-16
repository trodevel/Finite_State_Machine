// dc15
// interface

#ifndef ParserI_H
#define ParserI_H

#include "../types.h"              // uint32

class ParserI
{
public:
    virtual ~ParserI() {};

public:
    virtual bool parse() = 0;
};

#endif  // ParserI_H
