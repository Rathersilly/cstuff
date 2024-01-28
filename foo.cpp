#include <iostream>
#include <string>
#include <typeinfo> // for typeid(foo).name()
#include <vector>

using namespace std;
class Point2D {
private:
  int m_x;
  int m_y;

public:
  // A default constructor
  Point2D() : m_x{0}, m_y{0} {}

  // A specific constructor
  Point2D(int x, int y) : m_x{x}, m_y{y} {}

  // An overloaded output operator
  friend std::ostream &operator<<(std::ostream &out, const Point2D &point) {
    out << '(' << point.m_x << ", " << point.m_y << ')';
    return out;
  }

  // Access functions
  void setPoint(int x, int y) {
    m_x = x;
    m_y = y;
  }
};
class Creature {
private:
public:
  std::string m_name;
  Point2D m_location;
  Creature(std::string_view name, const Point2D &location)
      : m_name{name}, m_location{location} {}

  friend std::ostream &operator<<(std::ostream &out, const Creature &creature) {
    out << creature.m_name << " is at " << creature.m_location;
    return out;
  }

  void moveTo(int x, int y) { m_location.setPoint(x, y); }
};

int main() {
  Creature bob{"bob", Point2D(2, 3)};
  Creature foo = bob;
  cout << foo.m_name;

  return 0;
}
