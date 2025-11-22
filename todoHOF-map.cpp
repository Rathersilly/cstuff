// std::map
// value_type is std::pair
//
// duplicate keys are INVALID; duplicate values are VALID
// keys are stored in order - in red black tree
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int main(int argc, char *argv[]) {
  map<int, string> students;
  students[1] = "petunia"; // [] will insert if key is not present
  students[1] = "alice";   // [] updates
  students[2] = "daisy";
  students.insert(pair(2, "bob"));     // insert pair or iterator range
                                       // won't overwrite existing pair
  students.insert_or_assign(2, "bob"); // insert/assign key/value pair
  /* gquiz1.insert(pair<int, int>(2, 30)); */
  print_map(students);

  if (students.contains(2)) { // contains checks for key
    cout << "contains 2" << endl;
  }

  std::map<int, string>::iterator iter = students.find(2);
  cout << iter->second << endl;

  students.erase(1);
  students.erase(1);
  students[3] = "charlie";
  students[1] = "alice";

  for (auto a = students.begin(); a != students.end(); ++a) {
    std::cout << a->first << "\t\t" << a->second << std::endl;
  }
  for (const auto &[key, value] : students) {
    std::cout << key << ": " << value << std::endl;
  }
  return 0;
}
