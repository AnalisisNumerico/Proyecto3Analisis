#ifndef ANPI_APLICATION

#define ANPI_APLICATION

#include "Matrix.hpp"

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
  void heat() {
    Matrix <T> plate = Matrix<T>(10, 10);//pasar por referencia
    std::vector <T>    topBorder(10, 0);//pasar por referencia
    std::vector <T>   leftBorder(10, -10);//pasar por referencia
    std::vector <T>  rightBorder(10, 200);//pasar por referencia
    std::vector <T> bottomBorder(10, 100);//pasar por referencia

    T lambda = T(1.9);

    //metodo de iteracion
    bool finish = false;

    while(!finish) {

      finish = true;

      for (int i = 0; i < plate.rows(); i++) {
        for (int j = 0; j < plate.cols(); j++) {

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

          if (j + 1 >= plate.cols()) {
            right = rightBorder[i];
          } else {
            right = plate[i][j + 1];
          }

          T bottom;

          if (i + 1 >= plate.rows()) {
            bottom = bottomBorder[j];
          } else {
            bottom = plate[i + 1][j];
          }

          //aplicando sobrerelajacion
          T oldT = plate[i][j];
          T newT = lambda * ((top + left + right + bottom) / 4) + (1 - lambda) * oldT;

          plate[i][j] = newT;

          //verificacion de condicion de parada
          if(finish && std::abs(newT - oldT) > (std::numeric_limits<T>::epsilon() * 1000)) {
            finish = false;
          }
        }
      }
    }

    for(int i = 0; i < plate.rows(); i++) {
      for(int j = 0; j < plate.cols(); j++) {
        std::cout << plate[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

  template<typename T>
  void flow(Matrix<T>& plate) {

    std::vector <T>    topBorder(5, 0);//pasar por referencia
    std::vector <T>   leftBorder(5, 0);//pasar por referencia
    std::vector <T>  rightBorder(5, 0);//pasar por referencia
    std::vector <T> bottomBorder(5, 0);//pasar por referencia

    Matrix <T> xFlowMatrix = Matrix<T>(5, 5);//pasar por referencia
    Matrix <T> yFlowMatrix = Matrix<T>(5, 5);//pasar por referencia

    T k = 2.37; //conductividad termica del aluminio

    for(int i = 0; i < plate.rows(); i++) {
      for(int j = 0; j < plate.cols(); j++) {

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

        if (j + 1 >= plate.cols()) {
          right = rightBorder[i];
        } else {
          right = plate[i][j + 1];
        }

        T bottom;

        if (i + 1 >= plate.rows()) {
          bottom = bottomBorder[j];
        } else {
          bottom = plate[i + 1][j];
        }

        xFlowMatrix[i][j] = -k * ((right - left) / 2);
        yFlowMatrix[i][j] = -k * ((bottom - top) / 2);

      }
    }

  }

}

#endif