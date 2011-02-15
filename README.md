QtFractal
=========

A Qt4 based simple Fractal generator developed as a learning tool
-----------------------------------------------------------------

QtFractal is a very simple fractal generator developed as an exercise
to learn Qt4 and refresh my C++. It is not and will probably never be a
full-fledged fractal rendering application like Gnofract 4D, Fractint
and others.

Heavily influenced by the great [mandelbrot](http://doc.qt.nokia.com/latest/threads-mandelbrot.html)
tutorial at Nokia.


Building
--------

To build QtFractal you need to have a recent Qt4 development environment.

### Linux

All modern Linux distributions, KDE or Gnome based, provide the correct
packages. Once the Qt development packages are installed a simple

    $ qmake
    $ make

will build the project.

### Windows

To develop on Windows you have to download the Qt Windows SDK that comes
equipped with the mingw32 free compiler. Please refer to the
[Qt Nokia site](http://qt.nokia.com/downloads) for more information.

Further Reading
---------------

_Qt Quarterly_: [Another Look at Events](http://doc.qt.nokia.com/qq/qq11-events.html)
Qt documentation: [The Event System](http://doc.qt.nokia.com/latest/eventsandfilters.html)
