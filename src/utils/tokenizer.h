// DC18

// inspired by stackoverflow:
// http://stackoverflow.com/questions/18675364/c-tokenize-a-string-with-spaces-and-quotes

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include <boost/tokenizer.hpp>      // tokenizer

inline void tokenize_to_vector( std::vector<std::string> & res, const std::string & str, const char * delimeter )
{
    std::string temp;

    const char quote = '"';

    for( size_t i = 0; i < str.length(); i++ )
    {
        char c = str[i];
        if( c == delimeter[0] )
        {
            if( !temp.empty() )
            {
                res.push_back( temp );
                temp.clear();
            }
        }
        else if( c == quote )
        {
            i++;
            while( str[i] != quote )
            {
                temp.append( 1, str[i] );
                i++;
            }
        }
        else
        {
            temp.append( 1, c );
        }
    }

    if( !temp.empty() )
    {
        res.push_back( temp );
    }
}


#endif // TOKENIZER_H
