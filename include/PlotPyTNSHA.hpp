//
// Created by ger534 on 27/04/18.
//

#ifndef PROYECTO2ANALISIS_PLOTPYTNSHA_HPP
#define PROYECTO2ANALISIS_PLOTPYTNSHA_HPP

#include <python2.7/Python.h>
#include <stdlib.h>
#include <string>
#include <vector>

namespace anpi {

  /**
   * Two-dimensional plots
   *
   * Given a set of x coordinates and a corresponding set of y values,
   * plot a line between each point (x,y).
   *
   * You give a pair of vectors with the x and y values with the
   * plot() method to plot a curve.  You may overlay as many curves as
   * you need simply by calling plot() as many times as you need to.
   *
   * Finally, you call show() to display the window with all plotted curves.
   */
  template<typename T>
  class  PlotTNSHA {
  private:
    //Titulo de la grafica.
    std::string _title;
    //Estiqueta del eje x
    std::string _xlabel;
    //Etiqueta del eje y
    std::string _ylabel;
    //Tamano de la cuadricula
    T _sizeGrid;

  public:
    /// Constructors
    //@{
    PlotTNSHA();
    //@}

    /**
     * Initialize a plot window.
     *
     * Each id is associated with a different plot window.
     */
    void initialize();

    /**
     * Plot a curve by drawing line segments from
     * the sequence of points (datax[i],datay[i]).  The
     * curve will have the given legend
     */
    void plot(std::vector<T>& dataPathx,std::vector<T>& dataPathy,std::vector<T>& datax,std::vector<T>& datay,std::vector<T>& datau,std::vector<T>& datav,std::vector<T>& datap,std::vector<T>& dataq);

    /**
     * Show all curves plotted so far.
     */
    void show();


  }; //class Plot2d

} // namespace anpi

#include "PlotPyTNSHA.tpp"

#endif //PROYECTO2ANALISIS_PLOTPYTNSHA_HPP