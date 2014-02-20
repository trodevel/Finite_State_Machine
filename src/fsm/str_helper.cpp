// DC26

#include "str_helper.h"             // self

#include <sstream>                  // std::ostringstream

#include "input_line.h"             // Direction
#include "parameter.h"              // Param
#include "data_types.h"             // Action, SignalHandler, State
#include "fsm.h"                    // Fsm

NAMESPACE_FSM_START

template <class T>
std::string to_string2( const std::vector<T> & l )
{
    std::ostringstream s;

    typename std::vector<T>::const_iterator it = l.begin();
    typename std::vector<T>::const_iterator it_end = l.end();

    for( ; it != it_end; ++it )
    {
        s << StrHelper::to_string( *it ) << " ";
    }

    return s.str();
}

template <class T, class V>
std::string to_string2( const std::map<T,V> & l )
{
    std::ostringstream s;

    typename std::map<T,V>::const_iterator it = l.begin();
    typename std::map<T,V>::const_iterator it_end = l.end();

    for( ; it != it_end; ++it )
    {
        s << StrHelper::to_string( (*it).second ) << " ";
    }

    return s.str();
}


std::string StrHelper::to_string( const InputLine &d )
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

std::string StrHelper::to_string( const Fsm & l )
{
    std::ostringstream s;

    s << "fsm\n"
            << "states = " << l.states_.size() << "\n"
            << to_string2( l.states_ )
            << "\n";

    return s.str();
}
std::string StrHelper::to_string( const State & l )
{
    std::ostringstream s;

    s << "state '" << l.name_ << "', signals = " << l.map_.size() << "\n"
            << to_string2( l.map_ )
            << "\n";

    return s.str();
}
std::string StrHelper::to_string( const SignalHandler & l )
{
    std::ostringstream s;

    s << "on signal '" << l.name_ << "', actions = " << l.actions_.size() << "\n"
            << to_string2( l.actions_ )
            << "\n";

    return s.str();
}

std::string StrHelper::to_string( const Action & l )
{
    std::ostringstream s;

    std::string act = to_string( l.type_ );

    switch( l.type_ )
    {
    case ACT_CALL:
        s << act << " " << l.name_ << " " << to_string2( l.pars_ );
        break;
    case ACT_SIGNAL:
        s << act << " " << l.name_;
        break;
    case ACT_NEXT_STATE:
        s << act << " " << l.name_;
        break;
    case ACT_EXIT:
        s << act;
        break;
    default:
        break;
    }

    return s.str();
}


std::string StrHelper::to_string( const Param & l )
{
    std::ostringstream s;

    switch( l.type_ )
    {
    case PARTP_INT:
        s << l.val_int_;
        break;
    case PARTP_FLOAT:
        s << l.val_float_;
        break;
    case PARTP_STR:
        s << "'" << l.value_ << "'";
        break;
    default:
        break;
    }

    return s.str();
}

std::string StrHelper::to_string( const action_type_e l )
{
    switch( l )
    {
    case ACT_UNDEF:
        return "UNDEF";
    case ACT_CALL:
        return "CALL";
    case ACT_SIGNAL:
        return "SIGNAL";
    case ACT_NEXT_STATE:
        return "NEXT_STATE";
    case ACT_EXIT:
        return "EXIT";
    default:
        break;
    };

    return "";
}

NAMESPACE_FSM_END

