#ifndef ANPI_SPLINE_HPP

#define ANPI_SPLINE_HPP

#include "Thomas.hpp"

namespace anpi {

  template<typename T>
  void xVectorFiller(const int xSize,const std::vector<T>& yVector, std::vector<T>& xVector) {

    T spacing = T(xSize) / T(yVector.size() - 1);///VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV Si hay error verificar aca

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

  template<typename T>
  void matrixFiller(const std::vector<T>& xVector,
                    const std::vector<T>& yVector,
                    Matrix<T>& A,
                    std::vector<T>& x,
                    std::vector<T>& b) {

    int solutionSize = yVector.size() - 2;

    A = Matrix<T>(solutionSize, solutionSize);

    if(solutionSize == 3) {
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

  template<typename T>
  void interpolate(const            int               xSize,
                   const std::vector<T>&              xVect,
                   const std::vector<T>&              yVect,
                   const std::vector<T>&                  x,
                         std::vector<T>& interpolatedValues) {

    int index = 1;

    for(int i = 1; i <= xSize; i++) {

      if(i > xVect[index] && (index + 1) < xVect.size()) {
        index++;
      }

      interpolatedValues.push_back( x[index - 1] * (((i - 1) - xVect[index]) * ((i - 1) - xVect[index]) * ((i - 1) - xVect[index])) / (6 *(xVect[index - 1] - xVect[index])) +
                                    x[index] * (((i - 1) - xVect[index - 1]) * ((i - 1) - xVect[index - 1]) * ((i - 1) - xVect[index - 1])) / (6 *(xVect[index] - xVect[index - 1])) +
                                    (((yVect[index - 1])/(xVect[index - 1] - xVect[index])) - ((x[index - 1] * (xVect[index - 1] - xVect[index])) / 6)) * (i - 1 - xVect[index]) +
                                    (((yVect[index])/(xVect[index] - xVect[index - 1])) - ((x[index] * (xVect[index] - xVect[index - 1])) / 6)) * (i - 1 - xVect[index - 1])
      );

    }


  }

    /** funcion utilizada para generar Ax = b si los   <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Asegurarse que sea mayor o igual a 3
     * valores especificados en frontera son 3 o mas
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

      matrixFiller(xVector, yVector, A , x , b);

      thomas(A,x,b);

      interpolate(xSize, xVector, yVector, x, interpolatedValues);




/*
 *       U = Matrix<T>(luRows,luCols);
 *
 *     //resistVector.resize(2 * map.rows() * map.cols() - (map.rows() + map.cols()),T(1));
 *
 *
      std::cout << std::endl<< std::endl;

      std::cout << "x: " << std::endl;
      for(int i = 0; i < xVector.size(); i++) {
        std::cout << xVector[i] << " ";
      }

      std::cout << std::endl<< std::endl;

      std::cout << "y: " << std::endl;
      for(int i = 0; i < yVector.size(); i++) {
        std::cout << yVector[i] << " ";
      }

      std::cout << std::endl << std::endl;

      std::cout << "A: " << std::endl;
      for(int i = 0; i < solutionSize; i++) {
        for(int j = 0; j < solutionSize; j++) {
          std::cout << A[i][j] << " ";
        }
        std::cout << std::endl ;
      }

      std::cout << std::endl;

      std::cout << "b: " << std::endl;
      for(int i = 0; i < solutionSize; i++) {
          std::cout << b[i] << std::endl;
      }
*/
    }

}//anpi

#endif