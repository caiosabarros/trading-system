#include "logging.h"

int main() {

	using namespace Common;

	Logger logger("random_file.log");

	logger.log("Hello World - 6:29 PM - 11/18/2026");

	return 0;
}
