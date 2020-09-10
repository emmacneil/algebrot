# Algebrot

**Algebrot**, a 3D fractal (rendered in 2D cross-sections).

As of September 2020, the Wikipedia page on the Mandelbrot set contains the following statement:

>There is no perfect extension of the Mandelbrot set into 3D. This is because there is no 3D analogue of the complex numbers for it to iterate on.

However, computer renderings of the Mandelbrot set don't really use the field of complex numbers. They use the field of Gaussian rational numbers, one of many degree-2 extensions of the rational numbers. A 3D analogue of these exists: take any degree-3 extension of the rationals.

Algebrot is an attempt to see what a 3D analogue of the Mandelbrot looks like. This code was quickly slapped together over the course of a few days in Fall 2019, using SDL. I am currently migrating the code to Qt/OpenGL.
