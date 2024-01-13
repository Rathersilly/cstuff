#ifndef HUMAN_H
#define HUMAN_H

#include <string>
using std::string;
class Human {

private:
  string name_ = "alice";
  string dna_ = "";

public:
  Human(){};
  Human(string name, string dna = "gattaca") : name_{name}, dna_{dna} {}
  Human(Human &&h) : name_{h.name_}, dna_{h.dna_} {};
  string name() const { return name_; }
  void change_name(const string name) { name_ = name; }
};

#endif
