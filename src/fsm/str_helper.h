// DC26

#include <string>
#include <vector>

#include "data_types_enums.h"   // action_type_e

#include "namespace_fsm.h"      // NAMESPACE_FSM_START

NAMESPACE_FSM_START

class InputLine;
class Fsm;
class State;
class SignalHandler;
class Action;
class Param;

std::string to_string( const InputLine & l );
std::string to_string( const Fsm & l );
std::string to_string( const State & l );
std::string to_string( const SignalHandler & l );
std::string to_string( const Action & l );
std::string to_string( const Param & l );
std::string to_string( const action_type_e l );


NAMESPACE_FSM_END

