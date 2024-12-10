#include "AnalyzerApraam.h"
#include "ApraamTranslatorLexer.h"
#include "ApraamTranslatorParser.h"

AnalyzerApraam::AnalyzerApraam()
    : Analyzer()
{
    lex = new ApraamTranslatorLexer();
    pars = new ApraamTranslatorParser(lex);
}


Token AnalyzerApraam::getAnalysedToken()
{
    return pars->parse();
}
