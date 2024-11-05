#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Token.h"

class Parser
{
protected:
    Lexer *lex;
    Token currTkn = {};

public:
    Parser(Lexer*);
    virtual ~Parser() = default;
    virtual Token parse();
};

#endif // PARSER_H
