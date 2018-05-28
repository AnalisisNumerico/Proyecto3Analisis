/**
 * Copyright (C) 2017
 * Área Académica de Ingeniería en Computadoras, TEC, Costa Rica
 *
 * This file is part of the CE3102 Numerical Analysis lecture at TEC
 */

#include <boost/test/unit_test.hpp>

#include <Matrix.hpp>
#include "Thomas.hpp"

namespace anpi {
  namespace test {

    template<typename T>
    void thomasTest(const std::function<void(Matrix<T>&, std::vector<T>&, std::vector<T>&)>& tomas) {

      Matrix<T> A = { {2.04,  -1 ,   0,     0} ,
                      {  -1, 2.04,  -1,     0} ,
                      {   0,   -1, 2.04,   -1} ,
                      {   0,    0,   -1, 2.04} };

      std::vector<T> x(4,1);

      std::vector<T> b = {40.08, 0.8, 0.8, 200.8};

      tomas(A,x,b);

      std::vector<T> X = {65.4256, 93.3883, 124.286, 159.356};

      const T eps = 1;

      for (int i = 0 ; i < x.size(); i++) {
        std::cout << x[i] << " ";
        BOOST_CHECK(std::abs(x[i] - X[i]) <= eps);
      }

      A = { {1, 2, 3, 4} };

      try {
        tomas(A,x,b);
        BOOST_CHECK_MESSAGE(false,"Invalid argumets size not properly catched");
      }

      catch(anpi::Exception& exc) {
        BOOST_CHECK_MESSAGE(true,"Invalid argumets size properly detected");
      }

    }

  } // test
}  // anpi

BOOST_AUTO_TEST_SUITE( Solver )

  BOOST_AUTO_TEST_CASE(Thomas) {
    anpi::test::thomasTest<float>(anpi::thomas<float>);
    anpi::test::thomasTest<double>(anpi::thomas<double>);
  }

BOOST_AUTO_TEST_SUITE_END()
