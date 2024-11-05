#ifndef ANALYZER_H
#define ANALYZER_H

#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

class Analyzer
{
protected:
    Lexer *lex;
    Parser *pars;

public:
    Analyzer();
    virtual Token getAnalysedToken();
};

#endif // ANALYZER_H
