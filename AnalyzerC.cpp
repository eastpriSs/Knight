#include "AnalyzerC.h"
#include "LexerC.h"

AnalyzerC::AnalyzerC()
    : Analyzer()
{
    lex = new LexerC();
}


Token AnalyzerC::getAnalysedToken()
{
    return lex->scan();
}
