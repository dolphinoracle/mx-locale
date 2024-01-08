#ifndef CHOOSEDIALOG_H
#define CHOOSEDIALOG_H

#include <QDialog>
#include <cmd.h>

namespace Ui {
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


private:
    Ui::chooseDialog *ui;
    Cmd *cmd;
    Cmd *cmdprog;
    QString value;
};

#endif // CHOOSEDIALOG_H
