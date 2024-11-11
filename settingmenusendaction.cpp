#include "settingmenusendaction.h"
#include "ui_settingmenusendaction.h"

SettingMenuSendAction::SettingMenuSendAction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingMenuSendAction)
{
    ui->setupUi(this);
}

SettingMenuSendAction::~SettingMenuSendAction()
{
    delete ui;
}

void SettingMenuSendAction::on_confirm_clicked()
{
    QFile compilerSettingFile("compiler.cfg");
    compilerSettingFile.open(QIODevice::WriteOnly);
    qDebug() << "Creating Setting file :" << compilerSettingFile.fileName();

    QTextStream out(&compilerSettingFile);
    QString outputCommand = ui->compilerName->text() + ' '
                            + ui->flags->text()      + ' '
                            + ui->outputExe->text();
    out << outputCommand << Qt::endl;
    compilerSettingFile.close();
}


void SettingMenuSendAction::on_cancel_clicked()
{
    this->close();
}


void SettingMenuSendAction::on_compilerName_editingFinished()
{

}


void SettingMenuSendAction::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    ui->compilerName->setText(item->text(column));
}

