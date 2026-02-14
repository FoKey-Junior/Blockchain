#ifndef BLOCKCHAIN_CORE_LOG_H
#define BLOCKCHAIN_CORE_LOG_H

#include <string>

namespace core::log {

enum class Level { Debug, Info, Warn, Error };

void write(Level level, const std::string& message);

} // namespace core::log

#endif
