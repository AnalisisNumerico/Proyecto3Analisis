/**
 * Copyright (C) 2017
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * @author: Gabriel
 * @date:   27.04.2017
 */

namespace anpi {

  template <typename T>
  PlotTNSHA<T>::PlotTNSHA(){}

  template <typename T>
  void PlotTNSHA<T>::initialize(){
    Py_Initialize();
    PyRun_SimpleString("import matplotlib.pyplot as plt");
    PyRun_SimpleString("import numpy as np");
    PyRun_SimpleString("from mpl_toolkits.axes_grid1 import make_axes_locatable");
  }

  template <typename T>
  void  PlotTNSHA<T>::quiver(std::vector<T>& datax,std::vector<T>& datay,std::vector<T>& datau,std::vector<T>& datav) {

    // Convert the vectors of data into Python strings
    std::string xstr  = "X = [";
    std::string ystr  = "Y = [";
    std::string ustr  = "U = [";
    std::string vstr  = "V = [";

    char c=',';
    for(size_t i = 0; i < datax.size(); i++) {
          if (i == datax.size()-1) {
            c=']';
          }
    xstr.append(std::to_string(datax[i])   + c);
    ystr.append(std::to_string(datay[i])   + c);

  }
   c=',';
   for(size_t i = 0; i < datav.size(); i++) {
            if (i == datav.size()-1) {
              c=']';
            }
      ustr.append(std::to_string(datau[i])   + c);
      vstr.append(std::to_string(datav[i])   + c);

   }
   c=',';

    PyRun_SimpleString(xstr.c_str());
    PyRun_SimpleString(ystr.c_str());
    PyRun_SimpleString(ustr.c_str());
    PyRun_SimpleString(vstr.c_str());
    PyRun_SimpleString("ax.quiver(X, Y, U, V)");
}
  template <typename T>
  void PlotTNSHA<T>::imgshow(anpi::Matrix<T>& image){
        std::string xstr  = "x = [[";
        std::string c=",";
        for(size_t i = 0; i < image.rows(); i++) {
            for(size_t j = 0; j < image.cols(); j++) {
                if (j == image.cols()-1 &&  i != image.rows()-1){
                  c="],[";
                }
                if (j == image.cols()-1 && i == image.rows()-1){
                                  c="]]";
                }
               xstr.append(std::to_string(image[i][j]) + c);
               c=",";
            }
        }
        PyRun_SimpleString(xstr.c_str());
        PyRun_SimpleString("fig, ax = plt.subplots(nrows=1, sharex=True, figsize=(10, 10))");
        PyRun_SimpleString("ax.set_title('placa')");
        PyRun_SimpleString("im = ax.imshow(x, origin='upper', interpolation='bilinear',cmap='plasma')");

        PyRun_SimpleString("divider = make_axes_locatable(ax)");
        PyRun_SimpleString("cax = divider.append_axes('right', size='5%', pad=0.05)");
        PyRun_SimpleString("plt.colorbar(im, cax=cax)");


  }

  template <typename T>
  void PlotTNSHA<T>::show(){
    PyRun_SimpleString("plt.show()");
  }

} // namespace anpi