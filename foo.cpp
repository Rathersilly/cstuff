#include <iostream>
#include <string>
using namespace std;

// Prototype interface
class Shape {
public:
  virtual Shape *clone() = 0; // Make a copy of itself
  virtual void draw() = 0;    // Draw the shape
};

// Concrete prototype
class Circle : public Shape {
private:
  string color;

public:
  Circle(string color) : color(color) {}

  // This creates a copy of the circle.
  Shape *clone() override { return new Circle(this->color); }

  // This is how a circle draws itself.
  void draw() override { cout << "Drawing a " << color << " circle." << endl; }
};

// Client code
class ShapeClient {
private:
  Shape *shapePrototype;

public:
  ShapeClient(Shape *shapePrototype) : shapePrototype(shapePrototype) {}

  // This method creates a new shape using the prototype.
  Shape *createShape() { return shapePrototype->clone(); }
};

// Main class
int main() {
  // Create a concrete prototype (a red circle).
  Shape *circlePrototype = new Circle("red");

  // Create a client and give it the prototype.
  ShapeClient client(circlePrototype);

  // Use the prototype to create a new shape (a red circle).
  Shape *redCircle = client.createShape();

  // Draw the newly created red circle.
  redCircle->draw();

  Shape *other = circlePrototype->clone();

  other->draw();

  delete circlePrototype;
  delete redCircle;
  return 0;
}
