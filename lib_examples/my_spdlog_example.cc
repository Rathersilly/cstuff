#define SPDLOG_COMPILED_LIB
#include "spdlog/sinks/basic_file_sink.h"    // For basic file logging
#include "spdlog/sinks/stdout_color_sinks.h" // For colored console output
#include "spdlog/spdlog.h"

int main() {
  // This line will output to the default logger (default sink is stdout)
  spdlog::info("This is sent to default logger (stdout)");

  // SOP is to use shared_ptr to logger.
  // basic_logger_mt() is factory: it creates and registers a shared_ptr<logger>
  // - basic_logger_mt = multi threaded (uses mutex)
  // - basic_logger_st = single threaded (uses null mutex)

  auto my_logger =
      spdlog::basic_logger_mt("my_file_logger", "logs/my_log.txt", true);

  my_logger->set_level(spdlog::level::warn);
  my_logger->warn("heyyyy");

  fmt::print("default logger is: {}\n", spdlog::default_logger()->name());
  spdlog::set_default_logger(my_logger); // will register logger if needed
  spdlog::set_default_logger(spdlog::get("my_file_logger")); // same as above
  fmt::print("default logger is: {}\n", spdlog::default_logger()->name());

  spdlog::info("This is sent to my_logger (logs/my_log.txt)");
  my_logger->info("ditto");

  // NOTE: Example creating a logger with multiple sinks (console and file)
  // - logger class has a std::vector<sink_ptr> sinks_;
  // - it is accessible with my_logger->sinks();

  // Create a console sink (with colors)
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::info); // Set minimum level for console

  // Create a basic file sink
  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      "mylog.log", true);                     // "true" for appending
  file_sink->set_level(spdlog::level::trace); // Set minimum level for file

  // Create a vector of sinks
  std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

  // Create a logger with multiple sinks
  auto logger = std::make_shared<spdlog::logger>("multi_sink_logger",
                                                 sinks.begin(), sinks.end());

  spdlog::register_logger(logger); // Register the logger (optional)

  // you can avoid a shared_ptr, but its not best practice
  // spdlog::logger this_logger{"this_logger", file_sink};

  // NOTE: Registering logger makes it accessible anywhere:
  //
  // class SomeFarawayRandomClass {
  //    m_logger = spdlog::get("some_logger");

  // Log messages
  logger->trace("This is a trace message.");
  logger->debug("This is a debug message.");
  logger->info("This is an info message.");
  logger->warn("This is a warning message.");
  logger->error("This is an error message.");
  logger->critical("This is a critical message.");

  // Flush the logger (optional, ensures all messages are written)
  logger->flush();

  return 0;
}
