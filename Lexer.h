#ifndef LEXER_H
#define LEXER_H

#include <QStringList>
#include "Token.h"

class Lexer
{
protected:
    QStringList keywords;
    QString::ConstIterator begin;
    QString::ConstIterator it;
    QString::ConstIterator forward;

public:
    Lexer() = delete;
    Lexer(const QString&);
    void setScanningBlock(const QString&);
    virtual void addKeyword(QString&&);
    virtual Token scan();
    virtual ~Lexer() = default;
};

#endif // LEXER_H
