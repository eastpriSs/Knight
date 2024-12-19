#include "AnalyzerApraam.h"
#include "ApraamTranslatorLexer.h"
#include "ApraamTranslatorParser.h"

AnalyzerApraam::AnalyzerApraam()
    : Analyzer()
{
    lex = new ApraamTranslatorLexer();
    pars = new ApraamTranslatorParser(lex);
}

AnalyzerApraam::AnalyzerApraam(Logger* l)
    : Analyzer(l)
{
    lex = new ApraamTranslatorLexer();
    pars = new ApraamTranslatorParser(lex, l);
}

Token AnalyzerApraam::getAnalysedToken()
{
    return pars->parse();
}
