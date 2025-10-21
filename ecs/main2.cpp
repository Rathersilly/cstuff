#include "my_vector/my_vector.h"
#include <fmt/color.h>
#include <fmt/format.h>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <vector>
std::mt19937 mt{std::random_device{}()};
std::uniform_int_distribution<> die2{0, 1};

class System {
public:
  virtual ~System() = default;
};
class Core;

class UpdateSystem : public System {
public:
private:
};

struct Transform {
  int id;
  int x;
  int y;
};
struct Message {
  int id;
  string message = "hello";
};
struct TextStyle {
  int id;
  fmt::color color;
  fmt::emphasis emphasis;
};

struct GameState {

  int max_id = 6;
  vector<Transform> transforms;
  vector<Message> messages;
  std::string msg;
  void initialize() {
    for (int i = 0; i < max_id; ++i) {
      transforms.emplace_back(i, i, i);
      if (i % 2) {
        // msg = fmt::format("Hello I'm Entity {}", i);
        msg = fmt::format("{}", i);
        messages.emplace_back(i, msg);
      }
    }
  }
};

struct NaivePrintSystem {
  void update(GameState *state) {
    for (int i = 0; i < state->max_id; ++i) {
      for (auto &msg : state->messages) {
        // fmt::print("{}", msg);
        if (msg.id == i)
          std::cout << msg.message;
      }
    }
    std::cout << std::endl;
  }
};
struct PrintSystem {
  // requires<Message>;
  // optional<Color>;
  // mutates<Nothing>;
  // vector<ComponentTuple> items;

  void update() {
    // update iterates through vector of tuples
    // tuples of the components needed by system
    // dont need to know the id?
    for (auto &x : items)
      auto [msg, style] = x;

    fmt::print(fg(style.color) | style.emphasis, "{}", msg.message);
  }
};

int main(int argc, char *argv[]) {
  GameState state;
  state.initialize();
  NaivePrintSystem sys;

  while (true) {

    sys.update(&state);

    std::this_thread::sleep_for(0.5s);
  }

  all_systems.register_system<UpdateSystem>();
}
