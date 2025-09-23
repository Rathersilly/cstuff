#include <fcntl.h>
#include <fstream>
#include <unistd.h>

int main() {
  // O_RDWR is a posix flag
  int fd = open("file.txt", O_RDWR | O_CREAT, 0644); // low-level open
  write(fd, "hello", 5);                             // low-level write
  close(fd);

  std::fstream file("file.txt",
                    std::ios::in | std::ios::out); // high-level C++ stream
  std::string s;
  file >> s;
}
// C/posix way to open a file
// allows lower level flags like
#include <fcntl.h>
int fd = open("file.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
// C/Posix lets you manipulate things like locks
// #include <sys/file.h>
// int fd = open("file.txt", O_RDWR);
// flock(fd, LOCK_EX); // exclusive lock
// // do work
// flock(fd, LOCK_UN); // unlock

// C++ wraps posix flags with things like std::ios::in
#include <fstream>
std::fstream file("file.txt", std::ios::in | std::ios::out);

:e foo
