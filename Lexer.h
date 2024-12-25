#ifndef LEXER_H
#define LEXER_H

#include <QStringList>
#include <QStringListModel>
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
    void setCompleterModel(QStringListModel*);
    virtual void addKeyword(QString&&);
    virtual Token scan();
    virtual ~Lexer() = default;
};

#endif // LEXER_H
