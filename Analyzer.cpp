#include "Analyzer.h"

Analyzer::Analyzer()
{
    lex = new Lexer();
    pars = new Parser(lex);
}

Analyzer::Analyzer(Logger* l)
{
    lex = new Lexer();
    pars = new Parser(lex);
    logger = l;
}


Token Analyzer::getAnalysedToken()
{
    return pars->parse();
}

void Analyzer::setScanningBlock(const QString& text)
{
    lex->setScanningBlock(text);
}
