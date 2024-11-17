#ifndef SETTINGMENUSENDACTION_H
#define SETTINGMENUSENDACTION_H

#include <QDialog>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTreeWidgetItem>

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

    void on_cancel_clicked();

    void on_compilerName_editingFinished();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::SettingMenuSendAction *ui;
};

#endif // SETTINGMENUSENDACTION_H
