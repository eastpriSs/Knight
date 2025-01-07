#include "ListLogger.h"

ListLogger::ListLogger(QWidget* parent)
{
    list.setParent(parent);
    list.setGeometry(500, 300, 400, 200);
    list.hide();
}
ListLogger::ListLogger(QWidget* parent, int ax,int ay,int x,int y)
{
    list.setParent(parent);
    list.setGeometry(ax, ay, x, y);
    list.hide();
}

void ListLogger::write(const QString& m)
{
    list.addItem(m);
}

bool ListLogger::isShowingMessage()
{
    return list.count() == 0;
}

void ListLogger::clear()
{
    list.clear();
}
