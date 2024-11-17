#include "ConsoleOutput.h"
#include "ui_ConsoleOutput.h"

ConsoleOutput::ConsoleOutput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConsoleOutput)
{
    ui->setupUi(this);
}

ConsoleOutput::ConsoleOutput(const QString& standardOutput,
                             const QString& errOutput, QWidget *parent)
: QWidget(parent)
, ui(new Ui::ConsoleOutput)
{
    ui->setupUi(this);
    ui->basicOutput->setText(standardOutput);
    ui->errorOutput->setText(errOutput);
}

ConsoleOutput::ConsoleOutput(const QString& standardOutput,
                             const QString& errOutput,
                             const QString& programOutput, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConsoleOutput)
{
    ui->setupUi(this);
    ui->basicOutput->setText(standardOutput);
    ui->errorOutput->setText(errOutput);
    ui->programOutput->setText(programOutput);
}

ConsoleOutput::~ConsoleOutput()
{
    delete ui;
}
