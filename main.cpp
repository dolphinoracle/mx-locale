/**********************************************************************
 *  main.cpp
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

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QIcon>
#include <QLocale>
#include <QTranslator>

#include "mainwindow.h"
#include <unistd.h>
#include <version.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (a.arguments().contains("--version") || a.arguments().contains("-v")) {
        qDebug() << "Version:" << VERSION;
        return EXIT_SUCCESS;
    }

    a.setWindowIcon(QIcon::fromTheme("mx-locale"));

    QTranslator qtTran;
    qtTran.load(QString("qt_") + QLocale::system().name());
    a.installTranslator(&qtTran);

    QTranslator appTran;
    appTran.load(QString("mx-locale_") + QLocale::system().name(), "/usr/share/mx-locale/locale");
    a.installTranslator(&appTran);

    qDebug() << "Program Version:" << VERSION;

    MainWindow w;
    w.show();
    return a.exec();
}
