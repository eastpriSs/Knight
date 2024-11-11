#include "SyntaxHighlighter.h"
#include "Token.h"

SyntaxHiglighter::SyntaxHiglighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    analyzer = new Analyzer();

    // Keyword
    keywordHighlightingRule.setFontWeight(QFont::ExtraBold);

    // Id
    idHighlightingRule.setFontItalic(true);
    idHighlightingRule.setFontWeight(QFont::Bold);
    idHighlightingRule.setForeground(Qt::darkBlue);

    // Number
    numHighlightingRule.setFontWordSpacing(10.0);
    // Macro
    macroHighlightingRule.setForeground(Qt::darkCyan);
    // String
    stringLiterHighlightingRule.setForeground(Qt::darkGreen);
}

void SyntaxHiglighter::switchAnalyzer(Analyzer* a)
{
    if (analyzer != nullptr)
        delete analyzer;
    analyzer = a;
}

void SyntaxHiglighter::highlightBlock(const QString& text)
{
    Token token;
    analyzer->setScanningBlock(text);
    while((token = analyzer->getAnalysedToken()), token.stype != ShortType::eof)
    {
        switch (token.stype)
        {
        case ShortType::id:
            setFormat(token.posStartOfWord, token.posEndOfWord, idHighlightingRule);
            break;
        case ShortType::num:
            setFormat(token.posStartOfWord, token.posEndOfWord, numHighlightingRule);
            break;
        case ShortType::keyword:
            setFormat(token.posStartOfWord, token.posEndOfWord, keywordHighlightingRule);
            break;
        case ShortType::macro:
            setFormat(token.posStartOfWord, token.posEndOfWord, macroHighlightingRule);
            break;
        case ShortType::stringLiter:
            setFormat(token.posStartOfWord, token.posEndOfWord, stringLiterHighlightingRule);
            break;
        case ShortType::unknown:
            setFormat(token.posStartOfWord, token.posEndOfWord, QTextCharFormat());
            break;

        default : break;
        }
    }
}
