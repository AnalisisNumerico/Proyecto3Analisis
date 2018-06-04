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
  void heat(T lambda,
            const std::vector<T>& topBorder,
            const std::vector<T>& leftBorder,
            const std::vector<T>& rightBorder,
            const std::vector<T>& bottomBorder,
            const bool isolatedTop,
            const bool isolatedLeft,
            const bool isolatedRight,
            const bool isolatedBottom,
            Matrix<T>& plate) {

    T sum = T(0);
    T numberOfElements = T(0);

    if (!isolatedTop) {
      for (int i = 0; i < topBorder.size(); i++) {
        sum += topBorder[i];
      }
        numberOfElements += topBorder.size();
    }

    if (!isolatedLeft) {
      for (int i = 0; i < leftBorder.size(); i++) {
        sum += leftBorder[i];
      }
      numberOfElements += leftBorder.size();
    }

    if (!isolatedRight) {
      for (int i = 0; i < rightBorder.size(); i++) {
        sum += rightBorder[i];
      }
      numberOfElements += rightBorder.size();
    }

    if (!isolatedBottom) {
      for (int i = 0; i < bottomBorder.size(); i++) {
        sum += bottomBorder[i];
      }
      numberOfElements += bottomBorder.size();
    }

    T mean = sum / numberOfElements;

    plate = Matrix<T>(leftBorder.size(), topBorder.size(), mean);//pasar por referencia

    //metodo de iteracion
    bool finish = false;

    T top;
    T left;
    T right;
    T bottom;

    while(!finish) {

      finish = true;

      for (int i = 0; i < plate.rows(); i++) {
        for (int j = 0; j < plate.cols(); j++) {

          if (i - 1 < 0) {
            if (isolatedTop) {
              top = T(0);
              bottom = 2 * plate[i + 1][j];
            }
            else {
              top = topBorder[j];
              bottom = plate[i + 1][j];
            }
          }
          else if (i + 1 >= plate.rows()) {
            if (isolatedBottom) {
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
            if (isolatedLeft) {
              left = T(0);
              right = 2 * plate[i][j + 1];
            }
            else {
              left = leftBorder[i];
              right = plate[i][j + 1];
            }
          }
          else if (j + 1 >= plate.cols()) {
            if(isolatedRight) {
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

          //verificacion de condicion de parada
          if(finish && std::abs(newT - oldT) > (std::numeric_limits<T>::epsilon() * 1000)) {
            finish = false;
          }
        }
      }
    }
///VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV   PRINT
    for(int i = 0; i < plate.rows(); i++) {
      for(int j = 0; j < plate.cols(); j++) {
        std::cout << plate[i][j] << " ";
      }
      std::cout << std::endl;
    }
///AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA   PRINT
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