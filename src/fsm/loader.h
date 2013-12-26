// DC17

#ifndef Loader_H
#define Loader_H

#include "input_line.h"     // InputLine

#include <vector>

#include "namespace_fsm.h"  // NAMESPACE_FSM_START

NAMESPACE_FSM_START

/* ********************************************************************************************* */
typedef std::vector<std::string>   VectStr;
/* ********************************************************************************************* */


class Loader
{
public:
    Loader();

private:
    Loader( Loader & h ); // no copy
    Loader& operator=( const Loader & h ); // no copy

public:
    bool load_file( const std::string & filename );

    const std::vector<InputLine> & get_script() const;

private:

    void handle_version( const InputLine & l );

    bool add_to_script( const InputLine & l );

    InputLine create_input_line( const std::string & str, const std::string & filename, uint32 line_number );

    bool include_file( const std::string & filename, const InputLine & l );
    void read_file( const std::string & filename, const InputLine & l, VectStr & lines );
    bool process_lines( const VectStr & lines, const std::string & filename );

    void throw_error( const std::string & msg, const InputLine & l );
    void throw_error( const char* msg, const InputLine & l );

private:
    bool                        is_version_defined_;

    uint32                      ver_;

    std::vector< InputLine >    script_;
};

NAMESPACE_FSM_END

#endif  // Loader_H
