#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>

class SyntaxHiglighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHiglighter(QTextDocument *parent = 0);
private:
    QStringList keywords;
};

#endif // SYNTAXHIGHLIGHTER_H
