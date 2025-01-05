#include "ReplaceDialog.h"
#include "ui_ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(const QString& title, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    setWindowTitle(title);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

QString ReplaceDialog::getGoal()
{
    return ui->goal->text();
}

QString ReplaceDialog::getReplacement()
{
    return ui->replacement->text();
}
