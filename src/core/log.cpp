#include "core/log.h"

#include <iostream>
#include <mutex>
#include <chrono>

namespace core::log {

namespace {
std::mutex log_mutex;

const char* level_to_string(Level level) {
    switch (level) {
        case Level::Debug: return "DEBUG";
        case Level::Info: return "INFO";
        case Level::Warn: return "WARN";
        case Level::Error: return "ERROR";
        default: return "INFO";
    }
}
} // namespace

void write(Level level, const std::string& message) {
    std::scoped_lock lock(log_mutex);
    const auto now = std::chrono::system_clock::now().time_since_epoch();
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
    std::cerr << "[" << ms << "][" << level_to_string(level) << "] " << message << "\n";
}

} // namespace core::log
