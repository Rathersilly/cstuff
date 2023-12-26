#include <iostream>
#include <string>
#include <string_view>

class Monster {
public:
  enum Type {
    dragon,
    goblin,
    ogre,
    orc,
    skeleton,
    troll,
    vampire,
    zombie,
    max_monster_types
  };

private:
  Type m_type{};
  std::string m_name{"???"};
  std::string m_roar{"???"};
  int m_hitPoints{};

public:
  Monster(Type type, std::string_view name, std::string_view roar,
          int hitPoints)
      : m_type{type}, m_name{name}, m_roar{roar}, m_hitPoints{hitPoints} {}

  // We're returning strings that are known at compile-time. Returning
  // std::string could add a considerable run-time cost.
  std::string_view getTypeString() const {
    switch (m_type) {
    case dragon:
      return "dragon";
    case goblin:
      return "goblin";
    case ogre:
      return "ogre";
    case orc:
      return "orc";
    case skeleton:
      return "skeleton";
    case troll:
      return "troll";
    case vampire:
      return "vampire";
    case zombie:
      return "zombie";
    default:
      return "???";
    }
  }

  void print() const {
    std::cout << m_name << " the " << getTypeString() << " has " << m_hitPoints
              << " hit points and says " << m_roar << '\n';
  }
};

namespace MonsterGenerator {
std::string_view getName(int n) {
  switch (n) {
  case 0:
    return "Blarg";
  case 1:
    return "Moog";
  case 2:
    return "Pksh";
  case 3:
    return "Tyrn";
  case 4:
    return "Mort";
  case 5:
    return "Hans";
  default:
    return "???";
  }
}

std::string_view getRoar(int n) {
  switch (n) {
  case 0:
    return "*ROAR*";
  case 1:
    return "*peep*";
  case 2:
    return "*squeal*";
  case 3:
    return "*whine*";
  case 4:
    return "*growl*";
  case 5:
    return "*burp*";
  default:
    return "???";
  }
}

Monster generate() {
  return Monster{Monster::skeleton, getName(0), getRoar(0), 4};
}

}; // namespace MonsterGenerator

int main() {
  Monster m{MonsterGenerator::generate()};
  m.print();

  return 0;
}
