// fractal2d.hpp

#ifndef __FRACTAL2D_HPP__
#define __FRACTAL2D_HPP__

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
 *
 * This class stores, at each pixel in the image, the number of iterations it took for the
 * corresponding point to escape the sphere of radius 2.
 */
class fractal2d
{
  public :
    fractal2d();
    ~fractal2d();

    void fill_data();
    void move();
    void reset();
    void resize();
  private :
    // Number field
    number_field K;
    // Iterating function
    number f(number z, number c);
    // Coordinate to fix
    enum fixed_coord;
    // Value at which to fix it.
    double w;
    // Upper left corner (u, v)
    number u, v;
    // Distance between each pixle
    double step;
    // Width/height in pixels
    int width, height;
    // Pixel data.
    unsigned short * data;
    // Gradient data
    unsigned char * gradient;
};

#endif
