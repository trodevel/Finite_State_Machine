// DC26

#include "str_helper.h"             // self

#include <sstream>                  // std::ostringstream

#include "input_line.h"             // Direction

NAMESPACE_FSM_START


std::string to_string( const InputLine &d )
{
    std::ostringstream s;

    s << "{ " << d.filename << ":" << d.line_num << ": ";

    for( int i = 0; i < ( int )d.tokens.size(); ++i )
    {
        s << d.tokens[i] << " ";
    }

    s << "}";

    return s.str();
}

NAMESPACE_FSM_END

