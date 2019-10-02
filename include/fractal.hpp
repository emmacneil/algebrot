// fractal.hpp

#ifndef __FRACTAL_HPP__
#define __FRACTAL_HPP__

/* The fractal2d class should contain information about a 2-dimensional slice of the
 * 3-dimensional fractal.
 *
 * It should know the number field over which the fractal is defined, as well as the
 * iterating function. E.g., the default number field is
 *
 *    Q[x]/p(x), where p(x) = x^3 + x^2 - 2x - 1
 *
 * and the default iterating function is the same as that used by the Mandelbrot set,
 *
 *    f(z, c) = z^2 + c
 * 
 * The 2d image is the result of fixing one of the three coordinates of the 3d image.
 * The fractal2d class must know which of the three coordinates we are fixing and at what value.
 * The fractal2d class will also contain information about the graphical image. This includes
 * the coordinates of the upper-left hand corner of the image and the width and height of the
 * image.
 *
 * There should be a constant to set an upper bound no the number of times we iterate,
 * and a color gradient to choose how to color pixels.
 */
class fractal2d
{
  public :
    fractal2d();
    ~fractal2d();

    void resize();
    void fill_data()
  private :
    // Number field
    // Iterating function
    // Coordinate to fix
    // Value at which to fix it.
    // Upper left corner (u, v)
    // Width/height in pixels
    // Pixel data.
};

#endif
