#include <fcntl.h>
#include <fstream>
#include <unistd.h>

int main() {
  int fd = open("file.txt", O_RDWR | O_CREAT, 0644); // low-level open
  write(fd, "hello", 5);                             // low-level write
  close(fd);

  std::fstream file("file.txt",
                    std::ios::in | std::ios::out); // high-level C++ stream
  std::string s;
  file >> s;
}
