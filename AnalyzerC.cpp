#include "AnalyzerC.h"
#include "LexerC.h"

AnalyzerC::AnalyzerC(QStringListModel* cmodel)
    : Analyzer()
{
    lex = new LexerC();
    lex->fillCompleterModel(cmodel);
}


Token AnalyzerC::getAnalysedToken()
{
    return lex->scan();
}
