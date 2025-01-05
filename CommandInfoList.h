#ifndef COMMANDINFOLIST_H
#define COMMANDINFOLIST_H

#include <QListWidget>

class CommandInfoList : public QListWidget
{
private:
    const static QStringList infoLabels;
public:
    CommandInfoList(QWidget* parent = nullptr);
};

#endif // COMMANDINFOLIST_H
