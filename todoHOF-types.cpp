// TODO casts - bring in examples from other HOFs like templates imo

int main(int argc, char *argv[]) {

  int a = 3, b = 4;
  decltype(a) c = a;
  decltype(a = b) d = a;
  // static cast
  // reinterpret cast (use at your own risk)

  return 0;
}
