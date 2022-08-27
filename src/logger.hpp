#pragma once

// HACK: where the hell is isnan being defined as _isnan?? is math.h being included somewhere??
#undef isnan
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace gd_att_history {
  inline std::shared_ptr<spdlog::logger> logger;

  static int init_logger() {
  try {
    logger = spdlog::basic_logger_st("GDAH", "logs/gd-attempt-history.txt");
    logger->set_pattern("%^[%T] %n: %v%$");
    logger->set_level(spdlog::level::trace);
    logger->trace("Initialized logger");
  }
  catch (const spdlog::spdlog_ex&) {
    return 1;
  }
  
  return 0;
  }
}
