#include "SyntaxHighlighter.h"

SyntaxHiglighter::SyntaxHiglighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    keywords.append("int");
}


QString makeString(const QString::const_iterator& b,
                   const QString::const_iterator& e)
{
    QString res;
    for(auto i = b; i != e; ++i)
        res.append(*i);
    return res;
}

void SyntaxHiglighter::highlightBlock(const QString& text)
{
    /*

        Пробная версия. Нужно добавить класс Анализатор.
    */
    auto first = text.begin();
    auto forward = first + 1;
    if (first->isLetter())
    {
        while(forward->isLetter() || forward->isDigit())
            ++forward;

        qDebug() << makeString(first, forward);
        if (keywords.contains(makeString(first, forward)))
            setFormat(first - text.begin(), forward - text.begin(), QFont("Arial", 20));
        else
            setFormat(first - text.begin(), forward - text.begin(), QFont("Arial", 30));
    }
}
