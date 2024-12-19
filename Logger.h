#ifndef LOGGER_H
#define LOGGER_H
#include <QString>

class Logger
{
public:
    Logger();
    virtual void write(const QString&) = 0;
};

#endif // LOGGER_H
