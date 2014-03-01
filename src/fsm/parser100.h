// DC15

#ifndef Parser100_H
#define Parser100_H

#include "fsm.h"                // Fsm, Token
#include "parser_i.h"           // ParserI
#include "data_types.h"         // Action, SignalHandler

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
    void handle_startstate( const InputLine & l );
    void handle_state( const InputLine & l );
    void handle_signal_handler( const InputLine & l );
    void handle_nextstate( const InputLine & l );
    void handle_sendsignal( const InputLine & l );
    void handle_exit( const InputLine & l );
    void handle_end( const InputLine & l );

    void complete_current_state();
    void complete_current_signal_handler();
    void complete_fsm( const InputLine & l );


    void throw_error( const std::string & msg, const InputLine & l );
    void throw_error( const char* msg, const InputLine & l );

    Param str_to_param( const std::string & s ) const;

    bool has_const( const std::string & s ) const;
    bool add_const( const std::string & s, const std::string & v );
    bool add_const( const std::string & s, int32 val );
    bool add_const( const std::string & s, double val );

    Param const_to_param( const std::string &s ) const;

private:
    typedef std::map< std::string, std::string >    MapStrToStr;
    typedef std::map< std::string, int32 >          MapStrToInt;
    typedef std::map< std::string, double >         MapStrToDouble;


private:
    Fsm             & h_;

    SignalHandler        temp_signal_handler_;
    State           temp_state_;

    MapStrToStr     const_str_;
    MapStrToInt     const_int_;
    MapStrToDouble  const_double_;

    std::string     start_state_;
};

NAMESPACE_FSM_END

#endif  // Parser100_H
