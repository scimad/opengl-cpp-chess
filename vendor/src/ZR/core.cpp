#include <ZR/core.hpp>

namespace zr{
	VERBOSITY_LEVEL log_level = VERBOSITY_LEVEL::ERROR;
	std::string level_name[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	// , "INFO", "WARNING", "ERROR"};

	void log(std::string message, VERBOSITY_LEVEL level){
		/* TODO:
			* implement color for different verbosity level.
		*/
		if (level >= log_level)
			std::cout << "\033[0;35m" << "[ZR] " "\033[1;32m" << zr::level_name[level] <<": " << message << "\033[0m" << std::endl;
	}
}
