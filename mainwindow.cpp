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
 *  \file mainwindow.cpp
 *  \brief Application window implementation
 *  \author Andrea Cisternino
 */

#include <QtGui>
#include <QtDebug>

#include "mainwindow.h"

//--- Lifecycle ----------------------------------------------------------
//

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    setupUi(this);

    // the FractalWidget responsible for fractals rendering
    fw.setParent(this);
    setCentralWidget(&fw);
}

//--- SLOTS --------------------------------------------------------------
//

void
MainWindow::on_actionQuit_triggered(bool /* checked */)
{
    qDebug() << "MainWindow::on_actionQuit_triggered(): quitting application...";
    qApp->quit();
}
