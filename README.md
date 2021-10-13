# Algebrot

**Algebrot**, a 3D fractal (rendered in 2D cross-sections).

Algebrot requires Qt 5 and OpenGL.
These can be installed on Ubuntu 20.04 using `sudo apt install mesa-common-dev qt5-default`.
To compile, it should be enough to run
```
$ qmake
$ make
```
and run with `./algebrot`.

This project sprang from a desire to know what a 3D analogue of the Mandelbrot set would look like. Wikipedia says (Sept. 2020)

>There is no perfect extension of the Mandelbrot set into 3D. This is because there is no 3D analogue of the complex numbers for it to iterate on.

However, computer renderings of the Mandelbrot set don't really use the field of complex numbers.
Rather, they use the field of Gaussian rational numbers, a degree-2 algebraic extension of the rational numbers.
(The completeness of the complex numbers is irrelevant to fractal renders.)
To make a 3D Mandelbrot, we can do the same thing over a degree-3 algebraic extension, and there are infinitely many of these!

For the layperson who doesn't know what any of this means, feel free to run the program anyway.
Changing the values of A, B, and C in the fractal explorer window yields different analogues of the complex numbers.
Left- and right-clicking the image will zoom in and out on the selected (X, Y)-coordinate.
Since I have no strategy for actually making a 3D image, the explorer shows 2D cross-sections instead.
Changing the value of Z yields different cross-sections of the fractal.

The resulting image is both surprising and anti-climactic!
