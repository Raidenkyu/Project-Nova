#include <seasocks/Logger.h>

class ServerLogger : public seasocks::Logger {
	void log(Level level, const char* message) override;
};
