#include "Analyzer.h"

Analyzer::Analyzer()
{
    lex = new Lexer("");
    pars = new Parser(lex);
}

Token Analyzer::getAnalysedToken()
{
    return pars->parse();
}

void Analyzer::setScanningBlock(const QString& text)
{
    lex->setScanningBlock(text);
}
