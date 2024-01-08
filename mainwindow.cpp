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
    ui->stackedWidget->setCurrentIndex(0);
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
    QString LANG = cmd->getOut("grep ^LANG /etc/default/locale").section("=",1,1);
    ui->buttonLocale->setText(LANG);
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

