#ifndef ANALYZERAPRAAM_H
#define ANALYZERAPRAAM_H

#include "Analyzer.h"

class AnalyzerApraam final : public Analyzer
{
public:
    AnalyzerApraam();
    AnalyzerApraam(Logger*);
    Token getAnalysedToken() override;
    void setScanningBlock(const QString&) override;
    void holdCompleterModel(QAbstractItemModel*);
};

#endif // ANALYZERAPRAAM_H
