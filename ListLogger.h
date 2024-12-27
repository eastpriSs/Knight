#ifndef LISTLOGGER_H
#define LISTLOGGER_H

#include <QListWidget>
#include <QListWidgetItem>
#include "Logger.h"

class ListLogger : public Logger
{
    QListWidget list;
public:
    ListLogger(QWidget*);
    ListLogger(QWidget*, int,int,int,int);
    ListLogger() = default;
    void write(const QString&) override;
    inline void hide() { list.hide(); }
    inline void show() { list.show(); }
};

#endif // LISTLOGGER_H
