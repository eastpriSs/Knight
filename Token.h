#ifndef TOKEN_H
#define TOKEN_H
#include <variant>

enum class ShortTokType
{
    unknown, keyword, num, id, _operator, macro, stringLiter, eof
};

enum class ApraamTokType {
    PUSH,POP,SWAP,IN,OUT,IF,
    numberLiteral,id,unknown,assgm,
    to,from,plus,mul,sub,div,VAR,shift,operand,
    label,operLess,operBigger,operEqLess,operEqBig,operEq,
    operNotEqual,stop,jmpConstruction,call,ret,then,startSymbol,
    additiveOperator, logicOperator, multiplicativeOperator,
    assigmentOperator, regA, regB, blockSymbol,
    eof
};

enum class ClanTokType{ INT, FLOAT, DOUBLE, AUTO, CHAR, SHORT, VOID};

class Token
{
public:
    using TokenType = std::variant<ApraamTokType, ClanTokType, std::monostate>;

    Token() = default;
    Token(ShortTokType);
    Token(ApraamTokType, ShortTokType);
    Token(ClanTokType, ShortTokType);

    ShortTokType stype = ShortTokType::eof;
    TokenType ttype = std::monostate{};
    int posStartOfWord = 0;
    int posEndOfWord = 0;
    int linePosition = 0;
    bool syntaxError = false;
};

#endif // TOKEN_H
