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

#include <QtGui>
#include <QtDebug>

#include "fractalwidget.h"

//-------------------------------------------------------------------------
//
//  Constructors
//

FractalWidget::FractalWidget(QWidget *parent)
    : QWidget(parent)
    , buffer(0)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
}

//-------------------------------------------------------------------------
//
//  void FractalWidget::renderMandelbrot()
//

// TODO move to specialized renderer class
void
FractalWidget::renderMandelbrot()
{
    buffer->fill(0);     // fill with black

    const double xstart = -2.2;
    const double xend   =  0.8;
    const double ystart = -1.2;
    const double yend   =  1.2;
    const int iter = 1000;

    int width = buffer->width();
    int height = buffer->height();

    // intervals corresponding to one screen pixel increment
    double xstep = (xend - xstart) / width;
    double ystep = (yend - ystart) / height;

    // current position in imaginary plane
    float x = xstart;
    float y = ystart;

    // foreach line
    for (int l = 0; l < height; l++) {

        QRgb *pixel = (QRgb *) buffer->scanLine(l);

        // foreach pixel in line
        for (int c = 0; c < width; c++) {

            double z = 0;
            double zi = 0;
            bool inset = true;

            double colour;

            // main loop for evaluating the point
            for (int k = 0; k < iter; k++) {

                /* z^2 = (a + bi)(a + bi) = a^2 + 2abi - b^2 */
                double newz = (z * z) - (zi * zi) + x;
                double newzi = 2 * z * zi + y;

                z = newz;
                zi = newzi;

                if (((z * z) + (zi * zi)) > 4) {
                    inset = false;
                    colour = k;
                    break;
                }
            }

            if (!inset) {
                // paint pixel with simple grayscale palette
                double y = colour / iter * 5000;
                int chanVal = (y > 255) ? 254 : (int) y;    // clip value
                pixel[c] = qRgb(chanVal, chanVal, chanVal);
            }

            x += xstep;
        }

        y += ystep;
        x = xstart;
    }

    qDebug() << "Mandelbrot set generated";
}

//-------------------------------------------------------------------------
//
//  void FractalWidget::keyReleaseEvent(QKeyEvent *event)
//

void
FractalWidget::keyReleaseEvent(QKeyEvent *event)
{
    qDebug() << "FractalWidget::keyReleaseEvent()";

    if (event->key() == Qt::Key_Escape) {
        qDebug() << "FractalWidget::keyReleaseEvent(): ESC pressed";
        event->accept();
        qApp->quit();
   }
   event->ignore();
}

//-------------------------------------------------------------------------
//
//  void FractalWidget::paintEvent(QPaintEvent *event)
//

void
FractalWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "FractalWidget::paintEvent()";

    // TODO use threads
    renderMandelbrot();

    QPainter p;

    // we paint on this widget surface
    p.begin(this);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawImage(QPoint(0, 0), *buffer);
    p.end();
}

//-------------------------------------------------------------------------
//
//  void FractalWidget::resizeEvent(QResizeEvent *event)
//

void
FractalWidget::resizeEvent(QResizeEvent *event)
{
    qDebug() << "FractalWidget::resizeEvent():" << event->size();

    if (buffer != 0) {
        delete buffer;
    }
    buffer = new QImage(event->size(), QImage::Format_ARGB32);
}
