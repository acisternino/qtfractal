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
 *  \file renderthread.h
 *  \brief Header file defining the RenderThread class
 *  \author Andrea Cisternino
 */
#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>

class QImage;

// ---- RenderThread ------------------------------------------------------

/*!
 *  \brief Class responsible for rendering fractals in the background.
 */
class RenderThread : public QThread
{
    Q_OBJECT

    QMutex mutex;               //!< Used to protect all shared data members from concurrent access
    QWaitCondition condition;   //!< Condition variable used to synchronize thread execution
    QSize imageSize;            //!< The size of the image to create

    // shared variables
    bool restart;       //!< Set when the main thread needs to restart the rendering thread
    bool abort;         //!< Set when the main thread needs to stop the rendering thread

public:

    // ---- Lifecycle -----------------------------------------------------

    /*!
     *  \brief Constructs a new RenderThread. The thread does not begin executing
     *         until start() is called.
     */
    RenderThread(QObject *parent = 0);

    /*!
     *  \brief Terminates all running instances of RenderThread.
     *
     *  Remember, this is executed by the controlling thread (the GUI thread.)
     *  Its responsibility is that of terminating the child threads by using the
     *  shared variables.
     */
    ~RenderThread();

    // ---- Public API ----------------------------------------------------

    /*!
     *  \brief Main entry point for the rendering action.
     *
     *  Communicates with the continuosly running thread (the run() function)
     *  using shared variables.
     *
     *  \param[in] size the size of the image to render.
     */
    void render(QSize size);

    // ---- Signals -------------------------------------------------------

signals:

    /*!
     *  \brief Signal emitted when the image is ready.
     *  \param[in] image the rendered image
     */
    void renderedImage(const QImage &image);

    // ---- Thread code --------------------------------------------------

protected:

    /*!
     *  \brief Main thread code; overridden from QThread.
     *
     *  This is the only code that is actually run in his own thread and
     *  is started by the invocation of the start() method.
     */
    void run();

private:

    // ---- Render fractal -----------------------------------------------

    /*!
     *  \brief Renders the image of a complete Mandelbrot set in the given image.
     *  \param image the QImage to render the image to.
     *  \return the number of milliseconds used to generate the image.
     */
    qint64 mandelbrot(const QImage &image);

};

#endif  // RENDERTHREAD_H
