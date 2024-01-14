#include <color_macros.h>
#include <queue>

using namespace std;
int main(int argc, char *argv[]) {
  queue<int> buf;
  buf.push(1);
  buf.push(2);
  buf.push(3);
  // front() accesses first element
  // back() accesses first element
  // pop() removes first element
  // push() adds element to end
  cout << buf.front() << endl;
  cout << buf.back() << endl;

  cout << "queue size: " << buf.size() << endl;
  int a;
  while (!buf.empty()) {
    cout << buf.front() << endl;
    buf.pop();
  }
  // queue is empty - buf.front()returns 0, not error
  cout << buf.front() << endl;
  cout << buf.front() << endl;

  // queue is empty - pop() doesnt error either
  buf.pop();

  return 0;
}
