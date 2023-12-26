// reading and writing to a file in binary / char modes
// made while reading PP ch 11
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T> char *as_bytes(T &i) {
  void *addr = &i;
  return static_cast<char *>(addr);
}

int main(int argc, char *argv[]) {
  int v[10];
  for (int i = 0; i < 10; ++i) {
    v[i] = i;
  }
  ofstream ofsbin("binary", ios_base::binary);
  ofsbin.seekp(0);
  ofsbin.write(as_bytes(v), sizeof(int) * 10);

  ofstream ofs("chars");
  for (int i = 0; i < 10; ++i) {
    ofs << v[i];
  }
  ofsbin.close();
  ofs.close();

  ifstream ifsbin("binary", ios_base::binary);
  ifstream ifs("chars");
  int binread[10];
  int charread[10];
  /* ifsbin.seekg(2); */
  ifsbin.read(as_bytes(binread), sizeof(int) * 10);
  for (int i = 0; i < 10; ++i) {
    cout << binread[i] << " ";
  }

  cout << endl;

  for (int i = 0; i < 10; ++i) {
    charread[i] = int(ifs.get()) - 48;
  }
  for (int i = 0; i < 10; ++i) {
    cout << charread[i] << " ";
  }
  cout << endl;

  return 0;
}
