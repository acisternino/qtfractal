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
 *  \file fractalwidget.h
 *  \brief Header file defining the FractalWidget class
 *  \author Andrea Cisternino
 */

#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPixmap>

#include "renderthread.h"       // class RenderThread

// ---- FractalWidget -----------------------------------------------------

/*!
 *  \brief Main widget responsible for displaying the fractals in a window.
 */
class FractalWidget : public QWidget
{
    Q_OBJECT

    QPixmap pixmap;         //!< This QPixmap is used by the Painter to display the image
    RenderThread thread;    //!< Thread used to render the fractal asynchronously

public:

    // ---- Lifecycle -----------------------------------------------------

    /*!
     *  \brief Creates a FractalWidget instance.
     */
    FractalWidget(QWidget *parent = 0);

    // ---- Slots ---------------------------------------------------------

private slots:

    /*!
     *  \brief Invoked by the rendering thread when an image is ready.
     *
     *  The connection between the thread's signal and this slot is a queued
     *  connection, i.e. asynchronous.
     *
     *  \param[in] image the image containing the rendered fractal.
     */
    void updatePixmap(const QImage &image);

protected:

    // ---- Event listeners -----------------------------------------------

    /*!
     *  This is used to trap the ESC key and exit.
     */
    void keyReleaseEvent(QKeyEvent *event);

    /*!
     *  \brief Received when the system thinks that the widget needs to be repainted.
     *
     *  This is the only place where the use of a QPainter is allowed and in
     *  fact this is where we get the rendered fractal image and copy it
     *  to the widget.
     */
    void paintEvent(QPaintEvent *event);

    /*!
     *  \brief Receive notifications of window resizes.
     *
     *  When we get this event the widget already has the proper size.
     *  This event is used to trigger the regeneration of the image.
     */
    void resizeEvent(QResizeEvent *event);

};

#endif  // FRACTALWIDGET_H
