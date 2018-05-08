/**
 * Copyright (C) 2017
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 *
 * @Author: JP
 * @Date  : 27.03.2018
 */

#include <boost/test/unit_test.hpp>

#include <iostream>
#include <exception>
#include <cstdlib>
#include <functional>
#include <cmath>

#include "Solver.hpp"

namespace anpi {
  namespace test {

    template<typename T>
    void forwardSubstitutionTest() {

      anpi::Matrix<T> L = { {  1,   0,  0, 0 },
                            { -1,   1,  0, 0 },
                            {  0, 0.5,  1, 0 },
                            {  6,   1, 14, 1 } };

      std::vector<T> b = {1,-1,2,1};
      std::vector<T> y;

      anpi::forwardSubstitution<T>(L,b,y);

      std::vector<T> Y = {1,0,2,-33};

      BOOST_CHECK(Y==y);

    }

    template<typename T>
    void backwardSubstitutionTest() {

      ///permutation matrix test
      {
        std::vector<size_t> p = {2,0,1};
        anpi::Matrix<T> P = { {0,0,1},
                              {1,0,0},
                              {0,1,0}};
        anpi::Matrix<T> pMatrix;
        anpi::permutationMatrix(p,pMatrix);
        BOOST_CHECK(pMatrix == P);
      }

      anpi::Matrix<T> U = { { -4,  -2,     1 },
                            {  0, 3.5, -1.75 },
                            {  0,   0,   3.5 } };

      std::vector<T> y = {-5,1.75,10.5};
      std::vector<T> x;

      anpi::backwardSubstitution<T>(U,y,x);

      std::vector<T> X = {1,2,3};

      BOOST_CHECK(x==X);

    }

    /// Test the given closed root finder
    template<typename T>
    void solveLUTest(const std::function<void(const Matrix<T>&,
                                              std::vector<T>&,
                                              std::vector<T>&)>& qr) {
      // Test solveQR
      {

        anpi::Matrix<T> A = { {1,2,-3},
                              {-3,4,5},
                              {7,1,2} };
        std::vector<T> b = {1,5,6};
        std::vector<T> x;

        anpi::solveLU(A,x,b);

        const T eps = 1e-5;

        //const T eps = std::numeric_limits<T>::epsilon();


        std::vector<T> verdaderoX = {0.561798, 1.01124, 0.52809};

        for (size_t i=0;i<verdaderoX.size();++i) {

          BOOST_CHECK(std::abs(verdaderoX[i] - x[i]) < eps*100);
        }

      }
    }

  } // test
}  // anpi

BOOST_AUTO_TEST_SUITE( Solver )

  BOOST_AUTO_TEST_CASE(forwardSubstitution) {
    anpi::test::forwardSubstitutionTest<float>();
    anpi::test::forwardSubstitutionTest<double>();
  }

  BOOST_AUTO_TEST_CASE(backwardSubstitution) {
    anpi::test::backwardSubstitutionTest<float>();
    anpi::test::backwardSubstitutionTest<double>();
  }

  BOOST_AUTO_TEST_CASE( LU ) {
    anpi::test::solveLUTest<float>(anpi::solveLU<float>);
  }

BOOST_AUTO_TEST_SUITE_END()