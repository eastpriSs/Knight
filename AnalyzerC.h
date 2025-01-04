#ifndef ANALYZERC_H
#define ANALYZERC_H

#include "Analyzer.h"

class AnalyzerC final : public Analyzer
{
private:
    QStringListModel* completerModel;
public:
    AnalyzerC();
    Token getAnalysedToken() override;
    void holdCompleterModel(QAbstractItemModel*);
};

#endif // ANALYZERC_H
