#
#  Copyright (c) 2011 Andrea Cisternino
#
#  This file is part of QtFractal.
#
#  QtFractal is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published
#  by the Free Software Foundation, version 2.
#
#  QtFractal is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with QtFractal.  If not, see <http://www.gnu.org/licenses/>.

CONFIG += debug console

TARGET   = QtFractal
TEMPLATE = app

SOURCES += qtfractal.cpp \
           mainwindow.cpp \
           fractalwidget.cpp \
           renderthread.cpp

HEADERS += qtfractal.h \
           mainwindow.h \
           fractalwidget.h \
           renderthread.h

RESOURCES = qtfractal.qrc

FORMS = mainwindow.ui
