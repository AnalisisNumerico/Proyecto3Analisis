#ifndef ANPI_SPLINE_HPP
#define ANPI_SPLINE_HPP

namespace anpi {

    /** funcion utilizada para generar Ax = b si los<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<Asegurarse que sea mayor o igual a 3
     * valores es pecificados en frontera son 3 o mas
     *
     * @tparam T
     * @param size
     * @param temperatures
     */
    template<typename T>
    void interpolate(int xSize, std::vector<T>& yVector) {

      ///fill x vector
      T spacing = T(xSize) / T(yVector.size() - 1);///VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV Si hay error verificar aca

      T xValue = T(0);
      std::vector<T> xVector;

      while(xVector.size() < yVector.size()) {

        xVector.push_back(xValue);
        if(xValue + spacing >= xSize) {
          xValue = xSize - 1;
        }
        else {
          xValue += spacing;
        }

      }///AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

      int solutionSize = yVector.size() - 2;

      Matrix<T> A = Matrix<T>(solutionSize, solutionSize);

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

      std::vector<T> x (solutionSize,T(1));

      std::vector<T> b;

      for(int i = 0 ; i < solutionSize; i++) {
        b.push_back(6 * ((yVector[i + 2] - yVector[i + 1])/(xVector[i + 2] - xVector[i + 1])) -
              6 * ((yVector[i + 1] - yVector[i])/(xVector[i + 1] - xVector[i]))
        );
      }

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

    }

}//anpi

#endif