#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
#include "Analyzer.h"

class SyntaxHiglighter final : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHiglighter(QTextDocument *parent = 0);
    void switchAnalyzer(Analyzer*);

private:
    void highlightBlock(const QString&) override;

private:
    QTextCharFormat keywordHighlightingRule;
    QTextCharFormat idHighlightingRule;
    QTextCharFormat numHighlightingRule;
    QTextCharFormat macroHighlightingRule;
    QTextCharFormat stringLiterHighlightingRule;
    Analyzer *analyzer;
};

#endif // SYNTAXHIGHLIGHTER_H
