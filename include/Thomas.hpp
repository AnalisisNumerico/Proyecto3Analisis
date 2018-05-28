#ifndef ANPI_THOMAS_HPP
#define ANPI_THOMAS_HPP

namespace anpi {

  /**Metodo utilizado para obtener la descomposicion inisitu de la matriz A
   *
   * @tparam T
   * @param A
   */
  template<typename T>
  void decomposition(Matrix<T>& A) {

    for (int i = 1; i < int(A.rows()); i++) {
      A[i][i - 1] /= A[i - 1][i - 1];
      A[i][i] -= A[i][i - 1] * A[i - 1][i];
    }

  }

  /** Metodo utilizado para realizar la sustitucion hacia adelante en la ecuacion
   *  Ax = b
   *
   * @tparam T
   * @param A
   * @param b
   */
  template<typename T>
  void forwardSubstitution(Matrix<T>& A, std::vector<T>& b) {

    for (int i = 1; i < int(A.rows()); i++) {
      b[i] -= A[i][i - 1] * b[i - 1];
    }

  }

  /** Metodo utilizado para obtener las substitucion hacia atras en la ecuacion
   *  A x = b que obtiene la solucion
   *
   * @tparam T
   * @param A
   * @param x
   * @param b
   */
  template<typename T>
  void backwardSubstitution(Matrix<T>& A, std::vector<T>& x, std::vector<T>& b) {

    x[x.size() - 1] = b[b.size() - 1]/A[A.rows() - 1][A.cols() - 1];

    for(int i = A.rows() - 2; i >= 0; i--) {
      x[i] = (b[i] - A[i][i + 1] * x[i + 1]) / A[i][i];
    }

  }

  /** Algoritmo utilizado para la solucion de la ecuacion Ax = b en una matriz tridiagonal
   *
   * @tparam T
   * @param A
   * @param x
   * @param b
   */
  template<typename T>
  void thomas(Matrix<T>& A, std::vector<T>& x, std::vector<T>& b) {

    if(A.cols() == A.rows() && A.rows() == x.size() && x.size() == b.size()) {
      decomposition<T>(A);
      forwardSubstitution<T>(A, b);
      backwardSubstitution<T>(A, x, b);
    }

    else {
      throw anpi::Exception("Error at thomas: invalid argument array(s) size");
    }

  }

}//anpi

#endif