// NOTE: idea here is to make c++ vector with ruby features
// eg negative indices, manipulating subarrays easily
// - could subclass my_vector
#include "my_vector.h"
#include <vector>

template <typename T> class rubyVector : public myVector<T> {
  using myVector<T>::myVector;

public:
  virtual T &operator[](size_t index) {

    if (index < 0) {
    }
  }
  virtual const T &operator[](size_t index) const {
    while (index < 0) {
      index += this->m_size;
    }

    return this->m_data[index];
  }
};
