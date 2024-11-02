#ifndef SETTINGMENUSENDACTION_H
#define SETTINGMENUSENDACTION_H

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QDebug>

namespace Ui {
class SettingMenuSendAction;
}

class SettingMenuSendAction : public QDialog
{
    Q_OBJECT

public:
    explicit SettingMenuSendAction(QWidget *parent = nullptr);
    ~SettingMenuSendAction();

private slots:
    void on_confirm_clicked();

private:
    Ui::SettingMenuSendAction *ui;
};

#endif // SETTINGMENUSENDACTION_H
