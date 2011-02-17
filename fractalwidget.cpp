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

void
FractalWidget::paintEvent(QPaintEvent * /* event */)
{
    qDebug() << "FractalWidget::paintEvent()";

    QPainter p(this);       // we paint directly on this widget surface
    p.fillRect(rect(), Qt::black);

    if (pixmap.isNull()) {
        p.setPen(Qt::white);
        p.drawText(rect(), Qt::AlignCenter, tr("Rendering initial image, please wait..."));
        return;
    }

    p.drawPixmap(0, 0, pixmap);
}

void
FractalWidget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "FractalWidget::resizeEvent():" << event->size();

    thread.render(event->size());
}
