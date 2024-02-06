  // copy assignment
  array operator=(const array arg) {
    size_ = arg.size();
    std::copy(arg.begin(), arg.end(), elem);
  }
  // move assignment
  array &operator=(array &&other) {
    delete[] elem;
    size_ = other.size_;
    elem = other.elem;
    other.elem = nullptr;
    other.size_ = 0;
    return *this;
  }
  
  hoo = std::move(foo);

  template <typename T>
bool assert_equal(T a, T b, string msg = "",
                  string caller = __builtin_FUNCTION()) {

  stringstream local_msg;
  if (a != b)
    local_msg << "Expected " << a << " = " << b << "\n";
  return assert(a == b, local_msg.str() + msg, caller);
}

  assert_equal(foo.data(), nullptr);
