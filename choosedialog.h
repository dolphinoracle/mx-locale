#pragma once

#include <QDialog>
#include <cmd.h>

namespace Ui
{
class chooseDialog;
}

class chooseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit chooseDialog(QWidget *parent = nullptr);
    ~chooseDialog();
    void setup();
    void buildLocaleList();
    QString selection();

private slots:

    void on_textSearch_textChanged(const QString &arg1);

private:
    Ui::chooseDialog *ui;
    Cmd *cmd;
    Cmd *cmdprog;
    QString value;
    QStringList availablelocales;
};
