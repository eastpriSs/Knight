#ifndef LANGUAGELIST_H
#define LANGUAGELIST_H

#include <QListWidget>
#include <QObject>
#include <QWidget>

class LanguageList final : public QListWidget
{

private slots:
    void keyPressEvent(QKeyEvent*) override;

public:
    LanguageList();
};

#endif // LANGUAGELIST_H
