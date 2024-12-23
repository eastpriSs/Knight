#include "ListLogger.h"
#include <QToolTip>

ListLogger::ListLogger(QWidget* parent)
{
    list.setParent(parent);
    list.setGeometry(500, 300, 400, 200);
    list.hide();
}

void ListLogger::write(const QString& m)
{
    list.clear();
    list.addItem(m);
}
