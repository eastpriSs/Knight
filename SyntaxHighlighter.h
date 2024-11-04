#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>

class SyntaxHiglighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHiglighter(QTextDocument *parent = 0);
protected:
    void highlightBlock(const QString&) override;
private:
    QStringList keywords;
};

#endif // SYNTAXHIGHLIGHTER_H
