#ifndef TOKEN_H
#define TOKEN_H


enum class ShortType
{
    unknown, keyword, num, id, opeartor, eof
};

class Token
{
public:
    Token() = default;
    Token(ShortType);
    ShortType stype = ShortType::eof;
    int posStartOfWord = 0;
    int posEndOfWord = 0;
    bool syntaxError = false;
};

#endif // TOKEN_H
