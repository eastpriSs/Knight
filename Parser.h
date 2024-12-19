#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include "Token.h"
#include "Logger.h"

class Parser
{
protected:
    Lexer *lex;
    Logger *logger;
    Token currTkn = {};

public:
    Parser(Lexer*);
    Parser(Lexer*, Logger*);
    virtual ~Parser() = default;
    virtual Token parse();
};

#endif // PARSER_H
