#include "choosedialog.h"
#include "QFile"
#include "ui_choosedialog.h"
#include <QMessageBox>
#include <cmd.h>

chooseDialog::chooseDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::chooseDialog)
{
    ui->setupUi(this);
    setup();
}

chooseDialog::~chooseDialog()
{
    delete ui;
}

// Setup versious items first time program runs
void chooseDialog::setup()
{
    cmd = new Cmd(this);
    cmdprog = new Cmd(this);
    this->setWindowTitle("MX Locale");
    buildLocaleList();
}

void chooseDialog::buildLocaleList()
{
    QFile libFile("/usr/lib/mx-locale/locale.lib");
    QStringList libFileList;
    QString localelist;
    localelist = cmd->getOut("locale --all-locales");
    availablelocales = localelist.split(QRegExp("(\\r\\n)|(\\n\\r)|\\r|\\n"), Qt::SkipEmptyParts);

    if (!libFile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Error opening file", "Could not open locale.lib");
    } else {
        while (!libFile.atEnd()) {
            libFileList.append(libFile.readLine());
        }

        libFile.close();
    }
    libFileList.removeDuplicates();
    ui->listWidgetAvailableLocales->addItems(availablelocales);
}

QString chooseDialog::selection()
{
    return ui->listWidgetAvailableLocales->currentItem()->text();
}

void chooseDialog::on_textSearch_textChanged(const QString & /*arg1*/)
{
    ui->listWidgetAvailableLocales->clear();

    for (const QString &itemText : availablelocales) {
        if (itemText.contains(ui->textSearch->text(), Qt::CaseInsensitive)) {
            ui->listWidgetAvailableLocales->addItem(itemText);
        }
    }
}
