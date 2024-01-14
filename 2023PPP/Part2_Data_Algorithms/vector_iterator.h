// TODO make this work with concepts
// make this work with sort (currently it gives error missing operator- function
// i think this is where difference_type and functions become relevant
template <typename T, typename A = allocator<T>> class my::vector;

/* template <typename T, typename A = allocator<T>> class my::vector<T, A>::iter
 * {
 */
template <typename T, typename A = allocator<T>> class my::vector<T, A>::iter {
private:
  T *curr;

public:
  iter(T *t) : curr{t} {}

  iter &operator++() {
    curr += 1;
    return *this;
  }
  iter &operator--() {
    curr -= 1;
    return *this;
  }
  iter &next() { return ++curr; }
  iter &prev() { return --curr; }

  bool operator==(iter i) { return (i.curr == curr); }
  bool operator!=(iter i) { return (i.curr != curr); }
  T &operator*() { return *curr; }
};
