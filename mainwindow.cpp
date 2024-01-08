/**********************************************************************
 *  mainwindow.cpp
 **********************************************************************
 * Copyright (C) 2019 MX Authors
 *
 * Authors: Dolphin Oracle
 *          MX Linux <http://mxlinux.org>
 *          using live-usb-maker by BitJam
 *          and mx-live-usb-maker gui by adrian
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


#include "about.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "version.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QTextStream>

#include <QDebug>
#include <unistd.h>
#include <cmd.h>
#include <choosedialog.h>

MainWindow::MainWindow()  :
    ui(new Ui::MainWindow)
{
    qDebug().noquote() << QCoreApplication::applicationName() << "version:" << VERSION;
    ui->setupUi(this);
    setWindowFlags(Qt::Window); // for the close, min and max buttons
    setup();
    this->adjustSize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// setup versious items first time program runs
void MainWindow::setup()
{
    cmd = new Cmd(this);
    cmdprog = new Cmd(this);
    connect(qApp, &QApplication::aboutToQuit, this, &MainWindow::cleanup);
    this->setWindowTitle("MX Locale");
    ui->tabWidget->setCurrentIndex(0);
    ui->buttonCancel->setEnabled(true);
    height = this->heightMM();
    getcurrentlang();
}

// cleanup environment when window is closed
void MainWindow::cleanup()
{
    QString log_name = "/tmp/mx-locale.log";
    system("[ -f " + log_name.toUtf8() + " ] && rm " + log_name.toUtf8());
}


// About button clicked
void MainWindow::on_buttonAbout_clicked()
{
    this->hide();
    displayAboutMsgBox(tr("About %1").arg(this->windowTitle()), "<p align=\"center\"><b><h2>" + this->windowTitle() +"</h2></b></p><p align=\"center\">" +
                       tr("Version: ") + VERSION + "</p><p align=\"center\"><h3>" +
                       tr("Program for formatting USB devices") +
                       "</h3></p><p align=\"center\"><a href=\"http://mxlinux.org\">http://mxlinux.org</a><br /></p><p align=\"center\">" +
                       tr("Copyright (c) MX Linux") + "<br /><br /></p>",
                       "/usr/share/doc/mx-locale/license.html", tr("%1 License").arg(this->windowTitle()), true);
    this->show();
}

// Help button clicked
void MainWindow::on_buttonHelp_clicked()
{
    QString url = "file:///usr/share/doc/mx-locale/help/mx-locale.html";
    displayDoc(url, tr("%1 Help").arg(this->windowTitle()), true);
}

//get current language
void MainWindow::getcurrentlang(){

    if (QFileInfo::exists(QStringLiteral("/etc/default/locale"))) {
        QSettings defaultlocale(QStringLiteral("/etc/default/locale"), QSettings::NativeFormat);
        QString lang = defaultlocale.value(QStringLiteral("LANG")).toString();
        if (lang.isEmpty()){
            lang = "C";
        }
        QString ctype = defaultlocale.value(QStringLiteral("LC_CTYPE")).toString();
        if (ctype.isEmpty()){
            ctype = lang;
        }
        QString numeric = defaultlocale.value(QStringLiteral("LC_NUMERIC")).toString();
        if (numeric.isEmpty()){
            numeric = lang;
        }
        QString time = defaultlocale.value(QStringLiteral("LC_TIME")).toString();
        if (time.isEmpty()){
            time = lang;
        }
        QString collate = defaultlocale.value(QStringLiteral("LC_COLLATE")).toString();
        if (collate.isEmpty()){
            collate = lang;
        }
        QString monetary = defaultlocale.value(QStringLiteral("LC_MONETARY")).toString();
        if (monetary.isEmpty()){
            monetary = lang;
        }
        QString messages = defaultlocale.value(QStringLiteral("LC_MESSAGES")).toString();
        if (messages.isEmpty()){
            messages = lang;
        }
        QString paper = defaultlocale.value(QStringLiteral("LC_PAPER")).toString();
        if (paper.isEmpty()){
            paper = lang;
        }
        QString name = defaultlocale.value(QStringLiteral("LC_NAME")).toString();
        if (name.isEmpty()){
            name = lang;
        }
        QString address = defaultlocale.value(QStringLiteral("LC_ADDRESS")).toString();
        if (address.isEmpty()){
            address = lang;
        }
        QString telephone = defaultlocale.value(QStringLiteral("LC_TELEPHONE")).toString();
        if (telephone.isEmpty()){
            telephone = lang;
        }
        QString measurement = defaultlocale.value(QStringLiteral("LC_MEASUREMENT")).toString();
        if (measurement.isEmpty()){
            measurement = lang;
        }
        QString identification = defaultlocale.value(QStringLiteral("LC_IDENTIFICATION")).toString();
        if (identification.isEmpty()){
            identification = lang;
        }

        ui->buttonLocale->setText(lang);
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

void MainWindow::on_buttonLocale_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->buttonLocale->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonCType_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonCType->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonNumeric_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonNumeric->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonTime_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonTime->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonCollate_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonCollate->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonMonetary_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonMonetary->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonMessages_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonMessages->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonPaper_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonPaper->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonName_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonName->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonAddress_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonAddress->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonTelephone_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonTelephone->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonMeasurement_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonMeasurement->setText(dialog.selection());

        }
}


void MainWindow::on_pushButtonIdentification_clicked()
{
    chooseDialog dialog;
    dialog.setModal(true);
    if(dialog.exec() == QDialog::Accepted)
        {
          ui->pushButtonIdentification->setText(dialog.selection());

        }
}

