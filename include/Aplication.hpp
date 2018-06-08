#ifndef ANPI_APLICATION

#define ANPI_APLICATION

#include "Matrix.hpp"
#include "omp.h"
#include "PlotPyTNSHA.hpp"

#include "Spline.hpp"
#include "LinearIncrement.hpp"
#include <chrono>

#define CHUNKSIZE 10

namespace anpi {

  /**
   *         -------->
   *       | * * * * * |
   *       | * * * * * |
   *       | * * * * * |
   *       | * * * * * |
   *       v * * * * * v
   *         -------->
   *
   * @tparam T
   */
  template<typename T>
  void heat(const int               horizontal ,
            const int                 vertical ,
            T                           lambda ,
            const std::vector<T>&    topBorder ,
            const std::vector<T>&   leftBorder ,
            const std::vector<T>&  rightBorder ,
            const std::vector<T>& bottomBorder ,
            Matrix<T>&                   plate ) {

    if (int(topBorder.size())    <= 0 &&
        int(leftBorder.size())   <= 0 &&
        int(rightBorder.size())  <= 0 &&
        int(bottomBorder.size()) <= 0 ){
      plate = Matrix<T>(vertical, horizontal, T(-273));
    }

    else {

      T sum = T(0);
      T numberOfElements = T(0);

      if (topBorder.size() > 0) {
        for (int i = 0; i < horizontal; i++) {
          sum += topBorder[i];
        }
        numberOfElements += horizontal;
      }

      if (leftBorder.size() > 0) {
        for (int i = 0; i < vertical; i++) {
          sum += leftBorder[i];
        }
        numberOfElements += vertical;
      }

      if (rightBorder.size() > 0) {
        for (int i = 0; i < vertical; i++) {
          sum += rightBorder[i];
        }
        numberOfElements += vertical;
      }

      if (bottomBorder.size() > 0) {
        for (int i = 0; i < horizontal; i++) {
          sum += bottomBorder[i];
        }
        numberOfElements += horizontal;
      }

      T mean = sum / numberOfElements;

      plate = Matrix<T>(vertical, horizontal, mean);

      //metodo de iteracion
      bool finish = false;

      T top;
      T left;
      T right;
      T bottom;

      int chunk = CHUNKSIZE;

      int counter = 0;

      while (!finish) {

        finish = true;

        #pragma omp parallel for shared(topBorder, leftBorder, rightBorder, bottomBorder, plate, finish) private(top, left, right, bottom) schedule(monotonic:dynamic,chunk) //<<<<<<<<<<<<<<<<<<<<<<<<<<<<

        for (int i = 0; i < vertical; i++) {
          for (int j = 0; j < horizontal; j++) {

            if (i - 1 < 0) {
              if (topBorder.size() <= 0) {
                top = T(0);
                bottom = 2 * plate[i + 1][j];
              }
              else {
                top = topBorder[j];
                bottom = plate[i + 1][j];
              }
            }
            else if (i + 1 >= vertical) {
              if (bottomBorder.size() <= 0) {
                top = 2 * plate[i - 1][j];
                bottom = T(0);
              }
              else {
                top = plate[i - 1][j];
                bottom = bottomBorder[j];
              }
            }
            else  {
              top = plate[i - 1][j];
              bottom = plate[i + 1][j];
            }

            if (j - 1 < 0) {
              if (leftBorder.size() <= 0) {
                left = T(0);
                right = 2 * plate[i][j + 1];
              }
              else {
                left = leftBorder[i];
                right = plate[i][j + 1];
              }
            }
            else if (j + 1 >= horizontal) {
              if(rightBorder.size() <= 0) {
                left  = 2 * plate[i][j - 1];
                right = T(0);
              }
              else {
                left  = plate[i][j - 1];
                right = rightBorder[i];
              }
            }
            else {
              left  = plate[i][j - 1];
              right = plate[i][j + 1];
            }

            //aplicando sobrerelajacion
            T oldT = plate[i][j];
            T newT = lambda * ((top + left + right + bottom) / 4) + (1 - lambda) * oldT;

            plate[i][j] = newT;

            //verificacion de condicion de finalizacion
            if(finish && std::abs(newT - oldT) > (std::numeric_limits<T>::epsilon() * 1000)) {
              finish = false;
            }
          }
        }

        counter++;

        if(counter >= 1500) {
          lambda = ((lambda - 1) / 2) + 1;
          //std::cout << "new lambda: " << lambda << std::endl;
          counter = 0;
        }

      }

///VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV   PRINT
/*    for(int i = 0; i < int( plate.rows()); i++) {
      for(int j = 0; j < int(plate.cols()); j++) {
        std::cout << plate[i][j] << " ";
      }
      std::cout << std::endl;
    }*/
///AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA   PRINT

    }

  }

  template<typename T>
  void flow( const int               horizontal ,
             const int                 vertical ,
             const std::vector<T>&    topBorder ,
             const std::vector<T>&   leftBorder ,
             const std::vector<T>&  rightBorder ,
             const std::vector<T>& bottomBorder ,
             const      Matrix<T>&        plate ) {

    std::vector<T> xPositionVector;
    std::vector<T> yPositionVector;
    std::vector<T> xTempVector;
    std::vector<T> yTempVector;
    std::vector<T> xFlowVector;
    std::vector<T> yFlowVector;

    T k = 2.37; //conductividad termica del aluminio

    for(int i = 0; i < vertical; i++) {
      for(int j = 0; j < horizontal; j++) {

        T top;

        if (i - 1 < 0) {
          top = topBorder[j];
        } else {
          top = plate[i - 1][j];
        }

        T left;

        if (j - 1 < 0) {
          left = leftBorder[i];
        } else {
          left = plate[i][j - 1];
        }

        T right;

        if (j + 1 >= int(plate.cols())) {
          right = rightBorder[i];
        } else {
          right = plate[i][j + 1];
        }

        T bottom;

        if (i + 1 >= int(plate.rows())) {
          bottom = bottomBorder[j];
        } else {
          bottom = plate[i + 1][j];
        }

        xPositionVector.push_back(j);
        yPositionVector.push_back(i);
        xTempVector.push_back(plate[i][j]);
        yTempVector.push_back(plate[i][j]);
        xFlowVector.push_back(-k * ((right - left) / 2));
        yFlowVector.push_back(-k * ((bottom - top) / 2));

      }
    }

    anpi::PlotTNSHA<T> plotter;
    plotter.initialize();
    plotter.quiver(xPositionVector, yPositionVector, xTempVector, yTempVector, xFlowVector, yFlowVector);
    plotter.show();

  }

  template<typename T>
  void obtainBorderValues(const int plateBorderSize              ,
                          const std::vector<T>& borderTemperature,
                          std::vector<T>&            borderValues) {

    if (borderTemperature.size() >= 3) {
      spline<T>(plateBorderSize, borderTemperature, borderValues);
      std::cout << "using splines \n";
    }

    else if (borderTemperature.size() == 2) {
      linearIncrement<T>(plateBorderSize, borderTemperature, borderValues);
      std::cout << "lineal increment \n";
    }

    else if (borderTemperature.size() == 1) {
      for (int i = 0; i < plateBorderSize; i++) {
        borderValues.push_back(borderTemperature[0]);
      }
      std::cout << "constant values \n";
    }

    else {
      std::cout << "border isolated \n";
    }

  }

  /** metodo utilizado para interpretar todos los valores parseados desde consola
   *
   * @tparam T
   * @param horizontal
   * @param vertical
   * @param topBorderTemperature
   * @param leftBorderTemperature
   * @param rightBorderTemperature
   * @param bottomBorderTemperature
   * @param graphicate
   */
  template<typename T>
  void aplication(const            int               horizontal ,
                  const            int                 vertical ,
                  const std::vector<T>&    topBorderTemperature ,
                  const std::vector<T>&   leftBorderTemperature ,
                  const std::vector<T>&  rightBorderTemperature ,
                  const std::vector<T>& bottomBorderTemperature ,
                  const           bool               graphicate ) {

    std::vector<T>    topBorderValues;
    std::vector<T> bottomBorderValues;
    std::vector<T>   leftBorderValues;
    std::vector<T>  rightBorderValues;

    std::cout << "\n";
    std::cout << "obtaining plate top border temperature values, ";
    obtainBorderValues( horizontal,    topBorderTemperature,    topBorderValues);
    std::cout << "obtaining plate bottom border temperature values, ";
    obtainBorderValues( horizontal, bottomBorderTemperature, bottomBorderValues);
    std::cout << "obtaining plate left border temperature values, ";
    obtainBorderValues(   vertical,   leftBorderTemperature,   leftBorderValues);
    std::cout << "obtaining plate right border temperature values, ";
    obtainBorderValues(   vertical,  rightBorderTemperature,  rightBorderValues);

    Matrix<T> plate;
    double lambda = double(2);

    std::cout << "\nobtaining plate temperatures... \n";
    const auto _start = std::chrono::high_resolution_clock::now();
    anpi::heat<T>(horizontal, vertical, lambda, topBorderValues, leftBorderValues, rightBorderValues, bottomBorderValues, plate);
    std::chrono::duration<T> durat = std::chrono::high_resolution_clock::now()-_start;
    std::cout << "plate temperatures calculated in: "<< durat.count() << " seconds \n";

    if(graphicate) {
      anpi::PlotTNSHA<T> plotter;
      plotter.initialize();
      plotter.imgshow(plate);
      plotter.show();
    }
  }

}

#endif