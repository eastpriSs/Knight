#include "ConsoleOutput.h"
#include "ui_consoleoutput.h"

ConsoleOutput::ConsoleOutput(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConsoleOutput)
{
    ui->setupUi(this);
}

ConsoleOutput::ConsoleOutput(QString basicOutput,
                             QString errOutput, QWidget *parent)
: QWidget(parent)
, ui(new Ui::ConsoleOutput)
{
    ui->setupUi(this);
    ui->basicOutput->setText(basicOutput);
    ui->errorOutput->setText(errOutput);
}

ConsoleOutput::~ConsoleOutput()
{
    delete ui;
}
