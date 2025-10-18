// #include "spdlog/spdlog.h"
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
  spdlog::info("Welcome to spdlog version {}.{}.{}  !", SPDLOG_VER_MAJOR,
               SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
  return 0;
}
