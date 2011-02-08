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
 *  \file renderthread.cpp
 *  \brief Implementation of the RenderThread class
 *  \author Andrea Cisternino
 */

#include <QImage>
#include <QElapsedTimer>
#include <QtDebug>

#include "renderthread.h"       // class RenderThread

// ---- Global constants -------------------------------------------------

const double xstart = -2.2;
const double xend   =  0.8;
const double ystart = -1.2;
const double yend   =  1.2;
const int iter = 1000;

//-------------------------------------------------------------------------
//
//  Lifecycle
//

RenderThread::RenderThread(QObject *parent)
    : QThread(parent)
    , restart(false)
    , abort(false)
{
}

RenderThread::~RenderThread()
{
    mutex.lock();
    abort = true;           // notify threads that we are done
    condition.wakeAll();    // wake up threads if sleeping
    mutex.unlock();

    wait();                 // wait for threads to process abort command and terminate
}

//-------------------------------------------------------------------------
//
//  void render(QSize resultSize)
//

void
RenderThread::render(QSize size)
{
    qDebug() << "RenderThread::render(): size:" << size;

    QMutexLocker locker(&mutex);        // automatically locks the mutex

    imageSize = size;                   // copy new image size to shared variable

    if (!isRunning()) {
        start(LowPriority);
    } else {
        // thread is already running and mutex is locked
        // change shared variable and wake all threads waiting on condition
        restart = true;
        condition.wakeAll();
    }

    // locker goes out of scope and automatically releases the mutex
}

//-------------------------------------------------------------------------
//
//  void run()
//

void
RenderThread::run()
{
    forever {

        // get size of image set by the resizeEvent in the GUI thread
        mutex.lock();
        QSize size = imageSize;
        mutex.unlock();

        qDebug() << "RenderThread::run(): size:" << size;

        QImage image(size, QImage::Format_ARGB32);
        image.fill(Qt::gray);      // fill with black

        // check global variables used to communicate with main thread
        if (restart) {
            break;          // no need to go on, restart loop
        }
        if (abort) {
            return;         // exit method (i.e. terminate thread)
        }

        // finally render mandlebrot set
        quint64 elapsed = mandelbrot(image);
        qDebug() << "RenderThread::run(): elapsed ms:" << elapsed;

        emit renderedImage(image);

        // the image is on screen now, wait for next render or restart
        // immediately if ordered to do so
        mutex.lock();
        if (!restart) {
            condition.wait(&mutex);
        }
        restart = false;
        mutex.unlock();
    }
}

//-------------------------------------------------------------------------
//
//  void mandelbrot(const QImage &image)
//
//  This is a very naive implementation using a simple grayscale palette

qint64
RenderThread::mandelbrot(const QImage &image)
{
    int width = image.width();
    int height = image.height();

    QElapsedTimer timer;
    timer.start();

    // intervals corresponding to one screen pixel increment
    double xstep = (xend - xstart) / width;
    double ystep = (yend - ystart) / height;

    // current position in imaginary plane
    float x = xstart;
    float y = ystart;

    // foreach line
    for (int l = 0; l < height; l++) {

        QRgb *pixel = (QRgb *) image.scanLine(l);

        // foreach pixel in line
        for (int c = 0; c < width; c++) {

            double z = 0;
            double zi = 0;
            bool inset = true;

            double colour;

            // main loop for evaluating the point
            for (int k = 0; k < iter; k++) {

                // z^2 = (a + bi)(a + bi) = a^2 + 2abi - b^2
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

    return timer.elapsed();
}
