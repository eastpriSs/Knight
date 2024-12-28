#include "SettingMenuSendAction.h"
#include "ui_SettingMenuSendAction.h"

SettingMenuSendAction::SettingMenuSendAction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingMenuSendAction)
{
    ui->setupUi(this);
}


SettingMenuSendAction::SettingMenuSendAction(const QString& cfg, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingMenuSendAction)
{
    ui->setupUi(this);
    QStringList tmp = cfg.split(' ');
    QString complrPath;
    QString flags;

    complrPath.reserve(10);
    flags.reserve(100);

    QStringList::ConstIterator i = tmp.constBegin();
    complrPath = *(i++);
    for (; i != tmp.constEnd(); ++i) {
        flags += *i;
        flags += ' ';
    }
    ui->compilerName->setText(complrPath);
    ui->flags->setText(flags);
}

SettingMenuSendAction::~SettingMenuSendAction()
{
    delete ui;
}

void SettingMenuSendAction::on_confirm_clicked()
{
    QFile compilerSettingFile("compiler.cfg");
    compilerSettingFile.open(QIODevice::WriteOnly);

    QTextStream out(&compilerSettingFile);
    QString outputCommand = ui->compilerName->text() + ' '
                            + ui->flags->text();
    out << outputCommand << Qt::endl;
    compilerSettingFile.close();
}


void SettingMenuSendAction::on_cancel_clicked()
{
    this->close();
}
