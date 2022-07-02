#include <console_bridge/console.h>

int main() {
  // will print anything equal or above DEBUG level
  console_bridge::setLogLevel(console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_DEBUG);
  CONSOLE_BRIDGE_logDebug("Testing Log (Debug)");
  CONSOLE_BRIDGE_logInform("Testing Log (Inform)");
  CONSOLE_BRIDGE_logWarn("Testing Log (Warn)");
  CONSOLE_BRIDGE_logError("Testing Log (Error)");

  // will print anything equal or above NONE level, i.e. print suppressed
  console_bridge::setLogLevel(console_bridge::LogLevel::CONSOLE_BRIDGE_LOG_NONE);
  CONSOLE_BRIDGE_logDebug("Testing Log (Debug)");
  CONSOLE_BRIDGE_logInform("Testing Log (Inform)");
  CONSOLE_BRIDGE_logWarn("Testing Log (Warn)");
  CONSOLE_BRIDGE_logError("Testing Log (Error)");
  return 0;
}