#ifndef ANPI_LINEARINCREMENT

#define ANPI_LINEARINCREMENT

namespace anpi {

  template<typename T>
  void linearIncrement(T initial, T final, int size, std::vector<T>& values) {

    T step = (final - initial)/(size - 1);

    T value = initial;
    values.clear();

    while(values.size() < size) {
      values.push_back(value);
      value += step;
    }

    for(int i = 0; i < size; i++) {
      std::cout << values[i] << " ";
    }

  }

}

#endif