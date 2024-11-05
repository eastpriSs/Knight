#ifndef LEXER_H
#define LEXER_H

#include <QStringList>
#include "Token.h"

class Lexer
{
private:
    QStringList keywords;
    QString::ConstIterator begin;
    QString::ConstIterator it;
    QString::ConstIterator forward;

    void skipWhiteSpaces();
    [[nodiscard]]
    Token scanNumber();
    [[nodiscard]]
    Token scanIdOrKeyword();

public:
    Lexer() = delete;
    Lexer(const QString&);
    inline void setScanningBlock(const QString&);
    virtual void addKeyword(QString&&);
    virtual Token scan();
    virtual ~Lexer() = default;
};

#endif // LEXER_H
