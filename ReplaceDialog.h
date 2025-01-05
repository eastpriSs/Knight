#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(const QString&, QWidget *parent = nullptr);
    ~ReplaceDialog();

    QString getGoal();
    QString getReplacement();

private:
    Ui::ReplaceDialog *ui;
};

#endif // REPLACEDIALOG_H
