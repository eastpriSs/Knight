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

    // Number
    numHighlightingRule.setFontWordSpacing(10.0);

    //Error
    errorHighlightingRule.setFontUnderline(true);
    errorHighlightingRule.setUnderlineStyle(QTextCharFormat::WaveUnderline);

    // Colors
    turnOnLightTheme();
}

void SyntaxHiglighter::turnOnDarkTheme()
{
    keywordHighlightingRule.setForeground(QColor::fromRgb(210,67,115));
    idHighlightingRule.setForeground(QColor::fromRgb(166,117,234));
    macroHighlightingRule.setForeground(Qt::lightGray);
    operatorHighlightingRule.setForeground(Qt::yellow);
    errorHighlightingRule.setUnderlineColor(Qt::red);
}

void SyntaxHiglighter::turnOnLightTheme()
{
    keywordHighlightingRule.setForeground(Qt::black);
    idHighlightingRule.setForeground(Qt::darkBlue);
    macroHighlightingRule.setForeground(Qt::darkCyan);
    operatorHighlightingRule.setForeground(Qt::black);
    errorHighlightingRule.setUnderlineColor(Qt::red);
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
    while((token = analyzer->getAnalysedToken()), token.stype != ShortTokType::eof)
    {
        qDebug() << 1;
        switch (token.stype)
        {
        case ShortTokType::id:
            setFormat(token.posStartOfWord, token.posEndOfWord, idHighlightingRule);
            break;
        case ShortTokType::num:
            setFormat(token.posStartOfWord, token.posEndOfWord, numHighlightingRule);
            break;
        case ShortTokType::keyword:
            setFormat(token.posStartOfWord, token.posEndOfWord, keywordHighlightingRule);
            break;
        case ShortTokType::macro:
            setFormat(token.posStartOfWord, token.posEndOfWord, macroHighlightingRule);
            break;
        case ShortTokType::stringLiter:
            setFormat(token.posStartOfWord, token.posEndOfWord, stringLiterHighlightingRule);
            break;
        case ShortTokType::_operator:
            setFormat(token.posStartOfWord, token.posEndOfWord, operatorHighlightingRule);
            break;
        case ShortTokType::unknown:
            setFormat(token.posStartOfWord, token.posEndOfWord, QTextCharFormat());
            break;

        default : break;
        }
        if (token.syntaxError)
            setFormat(token.posStartOfWord, token.posEndOfWord, errorHighlightingRule);
    }
}
