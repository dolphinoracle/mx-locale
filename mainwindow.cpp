/**********************************************************************
 *  mainwindow.cpp
 **********************************************************************
 * Copyright (C) 2024 MX Authors
 *
 * Authors: Dolphin Oracle
 *          MX Linux <http://mxlinux.org>
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this package. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

#include "mainwindow.h"
#include "about.h"
#include "ui_mainwindow.h"
#include "version.h"

#include <QDebug>
#include <QFileDialog>
#include <QScrollBar>
#include <QTextStream>

#include "choosedialog.h"
#include "cmd.h"
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::MainWindow)
{
    qDebug().noquote() << QCoreApplication::applicationName() << "version:" << VERSION;
    ui->setupUi(this);
    setWindowFlags(Qt::Window); // For the close, min and max buttons
    setup();
    this->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Setup versious items first time program runs
void MainWindow::setup()
{
    cmd = new Cmd(this);
    cmdprog = new Cmd(this);
    connect(qApp, &QApplication::aboutToQuit, this, &MainWindow::cleanup);
    this->setWindowTitle("MX Locale");
    ui->tabWidget->setCurrentIndex(0);
    ui->buttonCancel->setEnabled(true);
    height = this->heightMM();
    getCurrentLang();
    setSubvariables();
    setButtons();
}

// Cleanup environment when window is closed
void MainWindow::cleanup()
{
    QString log_name = "/tmp/mx-locale.log";
    system("[ -f " + log_name.toUtf8() + " ] && rm " + log_name.toUtf8());
}

void MainWindow::onGroupButton(int button_id)
{
    qDebug() << "clicked " << button_id;
    chooseDialog dialog;
    dialog.setModal(true);
    if (dialog.exec() == QDialog::Accepted) {
        buttonGroup->button(button_id)->setText(dialog.selection().section('\t', 0, 0).trimmed());
    }
}

void MainWindow::on_buttonAbout_clicked()
{
    this->hide();
    displayAboutMsgBox(tr("About %1").arg(this->windowTitle()),
                       "<p align=\"center\"><b><h2>" + this->windowTitle() + "</h2></b></p><p align=\"center\">"
                           + tr("Version: ") + VERSION + "</p><p align=\"center\"><h3>"
                           + tr("Program for formatting USB devices")
                           + "</h3></p><p align=\"center\"><a href=\"http://mxlinux.org\">http://mxlinux.org</a><br "
                             "/></p><p align=\"center\">"
                           + tr("Copyright (c) MX Linux") + "<br /><br /></p>",
                       "/usr/share/doc/mx-locale/license.html", tr("%1 License").arg(this->windowTitle()), true);
    this->show();
}

void MainWindow::on_buttonHelp_clicked()
{
    QString url = "file:///usr/share/doc/mx-locale/help/mx-locale.html";
    displayDoc(url, tr("%1 Help").arg(this->windowTitle()), true);
}

// Get current language
void MainWindow::getCurrentLang()
{

    if (QFileInfo::exists("/etc/default/locale")) {
        QSettings defaultlocale("/etc/default/locale", QSettings::NativeFormat);
        QString lang = defaultlocale.value("LANG", "C").toString();
        ui->buttonLocale->setText(lang);
    }
}

void MainWindow::setSubvariables()
{

    if (QFileInfo::exists("/etc/default/locale")) {
        QSettings defaultlocale("/etc/default/locale", QSettings::NativeFormat);

        QString lang = ui->buttonLocale->text();

        QString ctype = defaultlocale.value("LC_CTYPE").toString();
        if (ctype.isEmpty()) {
            ctype = lang;
        }
        QString numeric = defaultlocale.value("LC_NUMERIC").toString();
        if (numeric.isEmpty()) {
            numeric = lang;
        }
        QString time = defaultlocale.value("LC_TIME").toString();
        if (time.isEmpty()) {
            time = lang;
        }
        QString collate = defaultlocale.value("LC_COLLATE").toString();
        if (collate.isEmpty()) {
            collate = lang;
        }
        QString monetary = defaultlocale.value("LC_MONETARY").toString();
        if (monetary.isEmpty()) {
            monetary = lang;
        }
        QString messages = defaultlocale.value("LC_MESSAGES").toString();
        if (messages.isEmpty()) {
            messages = lang;
        }
        QString paper = defaultlocale.value("LC_PAPER").toString();
        if (paper.isEmpty()) {
            paper = lang;
        }
        QString name = defaultlocale.value("LC_NAME").toString();
        if (name.isEmpty()) {
            name = lang;
        }
        QString address = defaultlocale.value("LC_ADDRESS").toString();
        if (address.isEmpty()) {
            address = lang;
        }
        QString telephone = defaultlocale.value("LC_TELEPHONE").toString();
        if (telephone.isEmpty()) {
            telephone = lang;
        }
        QString measurement = defaultlocale.value("LC_MEASUREMENT").toString();
        if (measurement.isEmpty()) {
            measurement = lang;
        }
        QString identification = defaultlocale.value("LC_IDENTIFICATION").toString();
        if (identification.isEmpty()) {
            identification = lang;
        }

        ui->pushButtonCType->setText(ctype);
        ui->pushButtonNumeric->setText(numeric);
        ui->pushButtonTime->setText(time);
        ui->pushButtonCollate->setText(collate);
        ui->pushButtonMonetary->setText(monetary);
        ui->pushButtonMessages->setText(messages);
        ui->pushButtonPaper->setText(paper);
        ui->pushButtonName->setText(name);
        ui->pushButtonAddress->setText(address);
        ui->pushButtonTelephone->setText(telephone);
        ui->pushButtonMeasurement->setText(measurement);
        ui->pushButtonIdentification->setText(identification);
    }
}

void MainWindow::setButtons()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->pushButtonAddress, 1);
    buttonGroup->addButton(ui->pushButtonCollate, 2);
    buttonGroup->addButton(ui->pushButtonCType, 3);
    buttonGroup->addButton(ui->pushButtonIdentification, 4);
    buttonGroup->addButton(ui->pushButtonMeasurement, 5);
    buttonGroup->addButton(ui->pushButtonMessages, 6);
    buttonGroup->addButton(ui->pushButtonMonetary, 7);
    buttonGroup->addButton(ui->pushButtonName, 8);
    buttonGroup->addButton(ui->pushButtonNumeric, 9);
    buttonGroup->addButton(ui->pushButtonPaper, 10);
    buttonGroup->addButton(ui->pushButtonTelephone, 11);
    buttonGroup->addButton(ui->pushButtonTime, 12);
    buttonGroup->addButton(ui->buttonLocale, 13);
    connect(buttonGroup, &QButtonGroup::idClicked, this, &MainWindow::onGroupButton);
}
