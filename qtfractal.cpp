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

#include "fractalwidget.h"

// ---- Global variables --------------------------------------------------

// ---- Main --------------------------------------------------------------

int
main(int argc, char *argv[])
{
    // prepare the application object and load resources
    QApplication app(argc, argv);
    app.setApplicationName("QtFractal");
    app.setOrganizationName("Craftware");
    app.setQuitOnLastWindowClosed(true);
    // Q_INIT_RESOURCE(qtfractal);

    // a QWidget without parent becomes a Window
    FractalWidget fw;
    fw.resize(300, 300);
    
    // this sends an initial resize and repaint events to the FractalWidget instance
    fw.show();

    return app.exec();
}

