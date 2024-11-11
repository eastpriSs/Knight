#include "LanguageList.h"
#include <QKeyEvent>

LanguageList::LanguageList()
{
}

void LanguageList::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return)
        this->close();
    QListWidget::keyPressEvent(event);
}
