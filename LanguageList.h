#ifndef LANGUAGELIST_H
#define LANGUAGELIST_H

#include <QListWidget>

class LanguageList final : public QListWidget
{
private:
    const QList<QString>& languages;

private slots:
    void keyPressEvent(QKeyEvent*) override;

public:
    LanguageList(const QList<QString>&);
};

#endif // LANGUAGELIST_H
