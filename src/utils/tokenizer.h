// DC18

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

#include <boost/tokenizer.hpp>      // tokenizer

inline void tokenize_to_vector( std::vector<std::string> & res, const std::string & str, const char * delimeter )
{
    typedef boost::tokenizer<boost::char_separator<std::string::value_type> > tokenizer;
    boost::char_separator<std::string::value_type> sep( delimeter, "", boost::keep_empty_tokens );
    tokenizer tokens( str, sep );
    for( tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter )
        res.push_back( *tok_iter );
}


#endif // TOKENIZER_H
