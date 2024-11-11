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
    void setScanningBlock(const QString&);
    virtual Token getAnalysedToken();
    virtual ~Analyzer() = default;
};

#endif // ANALYZER_H
