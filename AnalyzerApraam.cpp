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

void AnalyzerApraam::holdCompleterModel(QAbstractItemModel* m)
{
    completerModel = dynamic_cast<QStringListModel*>(m);
    lex->fillCompleterModel(completerModel);
}

Token AnalyzerApraam::getAnalysedToken()
{
    return pars->parse();
}

void AnalyzerApraam::setScanningBlock(const QString &  block)
{
    lex->setScanningBlock(block);
    pars->prepare();
}
