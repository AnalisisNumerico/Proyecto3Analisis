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
  }

  template <typename T>
  void  PlotTNSHA<T>::quiver(std::vector<T>& datax,std::vector<T>& datay,std::vector<T>& datau,std::vector<T>& datav,std::vector<T>& datap,std::vector<T>& dataq) {


    // Convert the vectors of data into Python strings
    std::string xstr  = "X = [";
    std::string ystr  = "Y = [";
    std::string ustr  = "U = [";
    std::string vstr  = "V = [";
    std::string pstr  = "P = [";
    std::string qstr  = "Q = [";

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
      for(size_t i = 0; i < datap.size(); i++) {
               if (i == datap.size()-1) {
                 c=']';
               }
         pstr.append(std::to_string(datap[i])   + c);
         qstr.append(std::to_string(dataq[i])   + c);

      }
    c=',';

    PyRun_SimpleString(xstr.c_str());
    PyRun_SimpleString(ystr.c_str());
    PyRun_SimpleString(ustr.c_str());
    PyRun_SimpleString(vstr.c_str());
    PyRun_SimpleString(pstr.c_str());
    PyRun_SimpleString(qstr.c_str());
    PyRun_SimpleString("M = np.hypot(U, V)");
    PyRun_SimpleString("ax.quiver(X, Y, U, V,M)");
    PyRun_SimpleString("plt.plot(P,Q,'ro')");
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
        std::cout << xstr << std::endl;
        PyRun_SimpleString(xstr.c_str());
        PyRun_SimpleString("fig, ax = plt.subplots(nrows=1, sharex=True, figsize=(10, 10))");
        PyRun_SimpleString("ax.set_title('placa')");
        ///TODO origin can be important, see it with JP
        PyRun_SimpleString("ax.imshow(x, origin='upper', interpolation='bilinear')");
        //PyRun_SimpleString("plt.plot(P,Q,'ro')");

  }

  template <typename T>
  void PlotTNSHA<T>::show(){
    PyRun_SimpleString("plt.show()");
  }

} // namespace anpi