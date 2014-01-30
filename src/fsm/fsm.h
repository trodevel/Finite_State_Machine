// DC12

#include "fsm_i.h"    // FsmI

#include <map>          // std::map
#include "../utils/types.h" // int32

NAMESPACE_FSM_START

class Fsm: virtual public FsmI
{
public:
    typedef std::map< std::string, std::string >    MapStrToStr;
    typedef std::map< std::string, int32 >         MapStrToInt;
    typedef std::map< std::string, double >         MapStrToDouble;

    typedef std::map< std::string, State >          MapStrToState;

public:

    Fsm();
    ~Fsm();

    // administration
    bool load( const std::string & filename );
    bool load_from_str( const std::string & str );
    bool set_callback_if( FsmCallbackI * callback );

    // operation
    bool send_signal( const std::string & name, std::vector<Param> pars );
    bool start();

    bool clock();


    // loading helpers
    bool has_const( const std::string & s ) const;
    bool add_const( const std::string & s, const std::string & v );
    bool add_const( const std::string & s, int32 val );
    bool add_const( const std::string & s, double val );

    bool has_state( const std::string & name );
    bool add_state( const State & s );

private:
    MapStrToStr     const_str_;
    MapStrToInt     const_int_;
    MapStrToDouble  const_double_;

    MapStrToState   states_;


};


NAMESPACE_FSM_END

