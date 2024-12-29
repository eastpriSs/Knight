#include "AnalyzerC.h"
#include "LexerC.h"

AnalyzerC::AnalyzerC()
    : Analyzer()
{
    lex = new LexerC();
}

void AnalyzerC::holdCompleterModel(QAbstractItemModel* m)
{
    completerModel = dynamic_cast<QStringListModel*>(m);
    lex->holdCompleterModel(completerModel);
    lex->fillCompleterModel(completerModel);
}

Token AnalyzerC::getAnalysedToken()
{
    return lex->scan();
}
