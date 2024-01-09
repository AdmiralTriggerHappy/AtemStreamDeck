
#include <StreamDeckSDK/ESDMain.h>

#include "AtemStreamDeckPlugin.h"

int main(int argc, const char** argv) {
  auto plugin = std::make_unique<AtemStreamDeckPlugin>();
  return esd_main(argc, argv, plugin.get());
}
