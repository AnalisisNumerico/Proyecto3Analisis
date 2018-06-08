#ifndef ANPI_LINEARINCREMENT

#define ANPI_LINEARINCREMENT

namespace anpi {

  /** funcion utilizada para rellenar un vector con valores que incrementan
   *  linealmente entre los limites especificados
   *
   * @tparam T
   * @param size tamaño del vector values
   * @param limitValues vector de tamaño 2, que contiene los valores limites
   * @param values vector que contiene todos los valores
   */
  template<typename T>
  void linearIncrement(const int size, const std::vector<T>& limitValues, std::vector<T>& values) {

    T step = (limitValues[1] - limitValues[0])/(size - 1);

    T value = limitValues[0];
    values.clear();

    while(int(values.size()) < size) {
      values.push_back(value);
      value += step;
    }

  }

}

#endif