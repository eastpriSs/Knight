#ifndef ANALYZER_H
#define ANALYZER_H

#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Logger.h"
#include <QStringListModel>

class Analyzer
{
protected:
    Lexer *lex;
    Parser *pars;
    Logger *logger;
    QStringListModel* completerModel;

public:
    Analyzer();
    Analyzer(Logger*);
    void setScanningBlock(const QString&);
    virtual Token getAnalysedToken();
    virtual ~Analyzer() = default;
};

#endif // ANALYZER_H
