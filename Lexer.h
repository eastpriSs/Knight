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
    QStringListModel* completerModel;

public:
    Lexer() = default;
    Lexer(const QString&);
    void setScanningBlock(const QString&);
    void fillCompleterModel(QStringListModel*);
    void holdCompleterModel(QStringListModel*);
    virtual void addKeyword(QString&&);
    virtual Token scan();
    virtual ~Lexer() = default;
    virtual QString getLastLexem() const;
};

#endif // LEXER_H
