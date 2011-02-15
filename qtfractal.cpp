/*
**  Copyright (c) 2011 Andrea Cisternino
**
**  This file is part of QtFractal.
**
**  QtFractal is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published
**  by the Free Software Foundation, version 2.
**
**  QtFractal is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with QtFractal.  If not, see <http://www.gnu.org/licenses/>.
*/
/*!
 *  \file qtfractal.cpp
 *  \brief Main source file for the QtFractal application
 *  \author Andrea Cisternino
 */

#include <QApplication>
#include <QIcon>
#include <QDebug>

#ifdef Q_OS_WIN32
#  define WIN32_LEAN_AND_MEAN       1
#  include <windows.h>
#endif

#include "fractalwidget.h"
#include "mainwindow.h"

// ---- Global variables --------------------------------------------------

int cpuNum = 1;         // number of cpus in the system

// ---- Support methods ---------------------------------------------------

int
detectCpuNumber()
{
    int np = 1;

#ifdef Q_OS_LINUX
    np = sysconf(_SC_NPROCESSORS_ONLN);
    if (np == -1) {
        exit(EXIT_FAILURE);         // value unavailable, scary!
    } else if (np == 0) {
        np = 1;
    }
#elif defined Q_OS_WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    np = sysinfo.dwNumberOfProcessors;
#endif

    return np;
}

// ---- Main --------------------------------------------------------------

int
main(int argc, char *argv[])
{
    // find number of CPU's in the system
    cpuNum = detectCpuNumber();
    qDebug() << "CPU's detected:" << cpuNum;

    // prepare the Application object and load resources
    QApplication app(argc, argv);
    app.setApplicationName("QtFractal");
    app.setOrganizationName("Craftware");
    app.setQuitOnLastWindowClosed(true);
    Q_INIT_RESOURCE(qtfractal);

    // fire up GUI
    MainWindow mw;
    mw.setWindowIcon(QIcon(":/images/winicon.png"));
    mw.show();

    return app.exec();
}
