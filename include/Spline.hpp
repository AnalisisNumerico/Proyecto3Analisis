#ifndef ANPI_SPLINE_HPP

#define ANPI_SPLINE_HPP

#include "Thomas.hpp"

namespace anpi {

  /** encuentra los valores de x correspondientes a los valores de y dados,
   *  dado un tamaño maximo de x
   *
   * @tparam T
   * @param xSize
   * @param yVector
   * @param xVector
   */
  template<typename T>
  void xVectorFiller(const int xSize,const std::vector<T>& yVector, std::vector<T>& xVector) {

    T spacing = T(xSize) / T(yVector.size() - 1);

    T xValue = T(0);

    xVector.clear();

    while(xVector.size() < yVector.size()) {

      xVector.push_back(xValue);
      if(xValue + spacing >= xSize) {
        xValue = xSize - 1;
      }
      else {
        xValue += spacing;
      }

    }
  }

  /** Funcion utiliza para rellenar los operandos de la ecuacion Ax = b dados los valores
   *  de un una funcion en x y y.
   *
   * @tparam T
   * @param xVector
   * @param yVector
   * @param A
   * @param x
   * @param b
   */
  template<typename T>
  void operandFiller(const std::vector<T>& xVector,
                     const std::vector<T>& yVector,
                                Matrix<T>&       A,
                           std::vector<T>&       x,
                           std::vector<T>&       b) {

    int solutionSize = yVector.size() - 2;

    A = Matrix<T>(solutionSize, solutionSize);

    if(solutionSize == 1) {
      A[0][0] = 2 * (xVector[2] - xVector[0]);
    }

    else {

      A[0][0] = 2 * (xVector[2] - xVector[0]);
      A[0][1] = xVector[2] - xVector[1];

      for (int i = 1; i < (solutionSize - 1); i++) {
        A[i][i - 1] = xVector[i + 1] - xVector[i];
        A[i][i] = 2 * (xVector[i + 2] - xVector[i]);
        A[i][i + 1] = xVector[i + 2] - xVector[i + 1];
      }

      A[solutionSize - 1][solutionSize - 2] = xVector[solutionSize + 1] - xVector[solutionSize];
      A[solutionSize - 1][solutionSize - 1] = 2 * (xVector[solutionSize + 2] - xVector[solutionSize]);

    }

    x.resize(solutionSize,T(1));

    b.clear();

    for(int i = 0 ; i < solutionSize; i++) {
      b.push_back(6 * ((yVector[i + 2] - yVector[i + 1])/(xVector[i + 2] - xVector[i + 1])) -
                  6 * ((yVector[i + 1] - yVector[i])/(xVector[i + 1] - xVector[i]))
      );
    }

  }

  /** metodod utilizado para rellenar un vector con los valores interpolados,
   * dados un vector con las x, otro con f(x) y otro con f''(x)
   *
   * @tparam T
   * @param xSize size of iterpolatedValues vector
   * @param xVect vector of x
   * @param yVect vector of f(x)
   * @param x     vector of f''(x)
   * @param interpolatedValues
   */
  template<typename T>
  void interpolate(const int                          xSize,
                   const std::vector<T>&              xVect,
                   const std::vector<T>&              yVect,
                   const std::vector<T>&                  x,
                         std::vector<T>& interpolatedValues) {

    int index = 1;

    for(int i = 1; i <= xSize; i++) {

      if(i > xVect[index] && (index + 1) < int(xVect.size())) {
        index++;
      }

      interpolatedValues.push_back( x[index - 1] * (((i - 1) - xVect[index]) * ((i - 1) - xVect[index]) * ((i - 1) - xVect[index])) / (6 *(xVect[index - 1] - xVect[index])) +
                                    x[index] * (((i - 1) - xVect[index - 1]) * ((i - 1) - xVect[index - 1]) * ((i - 1) - xVect[index - 1])) / (6 *(xVect[index] - xVect[index - 1])) +
                                    (((yVect[index - 1])/(xVect[index - 1] - xVect[index])) - ((x[index - 1] * (xVect[index - 1] - xVect[index])) / 6)) * (i - 1 - xVect[index]) +
                                    (((yVect[index])/(xVect[index] - xVect[index - 1])) - ((x[index] * (xVect[index] - xVect[index - 1])) / 6)) * (i - 1 - xVect[index - 1])
      );

    }


  }

    /** funcion utilizada para generar Ax = b si los
     *  valores especificados en frontera son 3 o mas
     *
     * @tparam T
     * @param size
     * @param temperatures
     */
    template<typename T>
    void spline(const int xSize,const std::vector<T>& yVector, std::vector<T>& interpolatedValues) {

      std::vector<T> xVector;

      xVectorFiller(xSize, yVector, xVector);

      Matrix<T> A;
      std::vector<T> x;
      std::vector<T> b;

      operandFiller(xVector, yVector, A , x , b);

      thomas(A,x,b);

      interpolate(xSize, xVector, yVector, x, interpolatedValues);

    }

}//anpi

#endif