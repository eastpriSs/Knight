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
    out << ui->compilerName->text() << Qt::endl;
    compilerSettingFile.close();
}

