#ifndef UTILITY_H
#define UTILITY_H

#include "../commen/dataTypes.h"

namespace robolab {
	namespace utils {

		bool isValidPath(const std::string& path);
		std::vector<Path> getListOfFiles(const Path& directory, const std::string& nameFilter = "any", const std::string& extFilter = "any");
	}
}
#endif // !UTILITY_H
