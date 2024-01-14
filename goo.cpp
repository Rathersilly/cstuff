// https://exercism.org/tracks/cpp/exercises/robot-simulator
#include <color_macros.h>

#include <queue>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
/* using std::string; */
/* using std::stringstream; */
using namespace std;

enum Dir { n = 1, e = 2, s = 3, w = 4 };

class Robot {
private:
  // position stdpair
  int x_;
  int y_;
  int dir_; // NESW
  /* stringstream cmdbuf_; */
  // would use queue, but must copy queue to print it
  vector<char> cmdbuf_;

  void turn_left() {
    dir_ -= 1;
    if (dir_ == 0)
      dir_ = 4;
  }
  void turn_right() {
    dir_ += 1;
    if (dir_ == 5)
      dir_ = 1;
  }
  void advance() {
    switch (dir_) {
    case 'n':
      y_ += 1;
      break;
    case 'e':
      x_ += 1;
      break;
    case 's':
      y_ += 1;
      break;
    case 'w':
      x_ += 1;
      break;
    }
  }

public:
  void act() {
    // take a char from cmdbuf and take appropriate action
    char cmd;
    cmd = cmdbuf_.front();
    /* char cmd = cmdbuf_.pop(); */
    switch (cmd) {
    case 'R':
      turn_right();
      break;
    case 'L':
      turn_left();
      break;
    case 'A':
      advance();
      break;
    }
  }
  void act_all() {}

  Robot(int x, int y, Dir d) : x_{x}, y_{y} { dir_ = d; }

  void command(string cmd) {
    PFUN;
    for (char c : cmd) {
      cmdbuf_.push(c);
    }
  }
  void status() {
    cout << "Position: " << x_ << "," << y_ << endl;
    cout << "Direction: " << dir_ << endl;
    stringstream ss(cmdbuf_.str());
    cout << "Command buffer: " << cmdbuf_.str() << endl;
    cout << "Command buffer: " << ss.str() << endl;
  }
};

int main(int argc, char *argv[]) {
  string command_string = "RAALAL";
  Robot bob(7, 3, Dir::n);
  bob.command(command_string);
  cout << "---" << endl;
  bob.status();
  cout << "---" << endl;
  bob.status();
  /* bob.status(); */
  /* bob.act(); */
  /* bob.status(); */
  /* bob.act(); */
  /* bob.status(); */
  /* bob.act(); */
  /* bob.status(); */
  return 0;
}
