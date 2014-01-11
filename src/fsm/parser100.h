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
    bool parse( const std::vector<InputLine> & v );

private:
    bool is_cmd_supported( const std::string & cmd );

    void handle_action( const InputLine & l );
    void handle_const( const InputLine & l );
    void handle_finitestatemachine( const InputLine & l );
    void handle_state( const InputLine & l );
    void handle_signal( const InputLine & l );
    void handle_nextstate( const InputLine & l );
    void handle_sendsignal( const InputLine & l );
    void handle_exit( const InputLine & l );
    void handle_end( const InputLine & l );

    void complete_current_state();
    void complete_current_signal();


    void throw_error( const std::string & msg, const InputLine & l );
    void throw_error( const char* msg, const InputLine & l );


private:
    Fsm   & h_;
};

NAMESPACE_FSM_END

#endif  // Parser100_H
