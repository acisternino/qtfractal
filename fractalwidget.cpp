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
 *  \file fractalwidget.cpp
 *  \brief Implementation of the FractalWidget class
 *  \author Andrea Cisternino
 */

#include <QtGui>
#include <QtDebug>

#include "fractalwidget.h"

//--- Lifecycle ----------------------------------------------------------
//

FractalWidget::FractalWidget(QWidget *parent)
    : QWidget(parent)
    , scalePixmap(false)
{
    setAttribute(Qt::WA_OpaquePaintEvent);

    // QImage cannot be used by queued signals without being registered first
    qRegisterMetaType<QImage>("QImage");

    // inter-thread signal-slot connection: queued
    connect(&thread, SIGNAL(renderedImage(QImage)), this, SLOT(updatePixmap(QImage)));
}

//--- SLOTS --------------------------------------------------------------
//

void
FractalWidget::updatePixmap(const QImage &image)
{
    qDebug() << "FractalWidget::updatePixmap()";

    pixmap = QPixmap::fromImage(image);

    update();           // triggers a paintEvent()
}

//--- EVENTS -------------------------------------------------------------
//
//  void paintEvent(QPaintEvent *event)
//
//  After resizing the window this method is invoked twice instead than once.
//  The first time immediately after the resize event (that also triggers
//  a fractal redraw by the separate thread) and the second time when the
//  updatePixmap() slot is invoked upon termination of the rendering thread.
//  The idea is that the first time the soon to be obsolete image is scaled
//  to fill the newly resized window.

void
FractalWidget::paintEvent(QPaintEvent * /* event */)
{
    qDebug() << "FractalWidget::paintEvent()";

    // we paint directly on this widget surface
    // here the painter has the same coordinate system of the resized widget
    QPainter p(this);
    p.fillRect(rect(), Qt::black);

    if (pixmap.isNull()) {
        // first invocation
        p.setPen(Qt::white);
        p.drawText(rect(), Qt::AlignCenter, tr("Rendering initial image, please wait..."));
        scalePixmap = false;
        return;
    }

    p.save();
    if (scalePixmap) {
        // we don't scale the pixmap, we scale the painter
        qreal scaleX = ((double) size().width()) / pixmap.size().width();
        qreal scaleY = ((double) size().height()) / pixmap.size().height();
        p.scale(scaleX, scaleY);
    }
    p.drawPixmap(0, 0, pixmap);
    p.restore();

    scalePixmap = false;        // next paint blits the new image
}

void
FractalWidget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "FractalWidget::resizeEvent():" << event->size();

    thread.render(event->size());   // start rendering thread and return immediately

    scalePixmap = true;             // next paint scales image
}
