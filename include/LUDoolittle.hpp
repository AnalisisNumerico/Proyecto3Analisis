/**
 * Copyright (C) 2018
 * Área Académica de Ingeniería en Computadoras, ITCR, Costa Rica
 *
 * This file is part of the numerical analysis lecture CE3102 at TEC
 *
 * @Author: 
 * @Date  : 03.03.2018
 */

#include <cmath>
#include <limits>
#include <functional>
#include <algorithm>

#include "Exception.hpp"
#include "Matrix.hpp"

#ifndef ANPI_LU_DOOLITTLE_HPP
#define ANPI_LU_DOOLITTLE_HPP

namespace anpi {

  /**
* Auxiliary method used to debug LU decomposition.
*
* It separates a packed LU matrix into the lower triangular matrix
* L and the upper triangular matrix U, such that the diagonal of L
* is composed by 1's.
*/
  template<typename T>
  void unpackDoolittle(const Matrix<T> &LU,
                       Matrix<T> &L,
                       Matrix<T> &U) {

    if (LU.cols() == LU.rows()) {

      int luCols = LU.cols();
      int luRows = LU.rows();

      U = Matrix<T>(luRows, luCols);

      for (int j = 0; j < luCols; j++) {
        for (int i = 0; i <= j; i++) {
          U[i][j] = LU[i][j];
        }
      }

      L = Matrix<T>(luRows, luCols);

      for (int i = 0; i < luRows; i++) { //diagonal
        L[i][i] = T(1);
      }

      for (int i = 1; i < luRows; i++) {
        for (int j = 0; j < i; j++) {
          L[i][j] = LU[i][j];
        }
      }

    } else {
      throw anpi::Exception("Unpack Doolittle: Invalid compressed matrix size");
    }

  }

  /**
   * Decompose the matrix A into a lower triangular matrix L and an
   * upper triangular matrix U.  The matrices L and U are packed into
   * a single matrix LU.
   *
   * The L matrix will have in the Doolittle's LU decomposition a
   * diagonal of 1's
   *
   * @param[in] A a square matrix
   * @param[out] LU matrix encoding the L and U matrices
   * @param[out] permut permutation vector, holding the indices of the
   *             original matrix falling into the corresponding element.
   *             For example if permut[5]==3 holds, then the fifth row
   *             of the LU decomposition in fact is dealing with the third
   *             row of the original matrix.
   *
   * @throws anpi::Exception if matrix cannot be decomposed, or input
   *         matrix is not square.
   */
  template<typename T>
  void luDoolittle(const Matrix<T> &A,
                   Matrix<T> &LU,
                   std::vector<size_t> &permut) {

    if (A.rows() == A.cols()) {

      LU = A;
      int n = A.rows();
      std::vector<size_t> index(A.rows());

      for (int i = 0; i < n; i++) { //relleno vector indice
        index[i] = i;
      }

      for (int j = 0; j < n - 1; j++) {

        int bigI = j;
        for (int i = j; i < n; i++) { //busco el mayor numero en la columna
          if (std::abs(LU[bigI][j]) < std::abs(LU[i][j])) { //cambio el indice de la fila
            bigI = i;
          }
        }
        if (bigI != j) { //si se encontro un pivote mayor se intercambian filas
          T matrixTmp;
          for (int k = 0; k < n; k++) { //intercambio fila en matriz LU <<<<<<<<<<<<<<<<<<<<<< posible error k = 0
            matrixTmp = LU[j][k];
            LU[j][k] = LU[bigI][k];
            LU[bigI][k] = matrixTmp;
          }
          size_t indexTmp;
          indexTmp = index[j];    //intercambio en vector indice
          index[j] = index[bigI];
          index[bigI] = indexTmp;
        }

        if (LU[0][0] == T(0)) {
          throw anpi::Exception("Doolittle: division by zero"); // Anadir povoteo horizontal
        }

        for (int i = j + 1; i < n; i++) {
          LU[i][j] /= LU[j][j]; // obtencion de l
          for (int k = j + 1; k < n; k++) {
            LU[i][k] = LU[i][k] - LU[i][j] * LU[j][k];
          }
        }

      }
      permut = index;
    } else {
      throw anpi::Exception("Doolittle: invalid decomposition matrix size");
    }
  }


}
  
#endif



