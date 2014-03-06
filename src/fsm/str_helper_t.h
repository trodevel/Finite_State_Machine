// DC26

#include <sstream>                  // std::ostringstream
#include <vector>                   // std::vector
#include <map>                      // std::map

#include "namespace_fsm.h"      // NAMESPACE_FSM_START

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

NAMESPACE_FSM_END

