/*
**  Copyright (c) 2011 Andrea Cisternino
**
**  This file is part of QtFractal.
**
**  QtFractal is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published
**  by he Free Software Foundation, version 2.
**
**  QtFractal is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with QtFractal.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QtGui>

// ---- FractalWidget -----------------------------------------------------

/*!
 *  FractalWidget
 */
class FractalWidget : public QWidget
{
    Q_OBJECT

    QImage *buffer;     //!< The QImage we use to draw the fractal image

public:

    FractalWidget(QWidget *parent = 0);

public slots:

    /*!
     *  Very simple and unoptimized version of a Mandelbrot set generator
     */
    void renderMandelbrot();

protected:

    /*! this is used to trap the ESC key and exit */
    void keyReleaseEvent(QKeyEvent *event);

    /*!
     *  Received when the system thinks that the widget needs to be repainted.
     *  This is the only place where the use of a QPainter is allowed and in
     *  fact this is where we trigger fractal image generation.
     */
    void paintEvent(QPaintEvent *event);

    /*!
     *  When we get this event the widget already has the proper size.
     *  I use this event to delete the existing QImage and allocate a new one.
     */
    void resizeEvent(QResizeEvent *event);
};

#endif  // FRACTALWIDGET_H
