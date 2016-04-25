#include "utility.h"

namespace robolab {
	namespace utils {

		bool isValidPath(const std::string& path) {
			return Poco::File(path).exists();
		}

		std::vector<Path> getListOfFiles(const Path& directory, const std::string& nameFilter, const std::string& extFilter)
		{
			std::vector<Path> filesList;
			std::vector<Poco::File> files;
			Poco::File(directory).list(files);
			files.erase(std::remove_if(files.begin(), files.end(), [nameFilter, extFilter](Poco::File item)
			{
				if (item.isDirectory())
					return true;
				else {
					if (item.isFile()) {
						if (nameFilter == "any" && extFilter == "any") {
							return false;
						}
						else {
							if (nameFilter == "any" && extFilter != "any") {
								if (Path(item.path()).getExtension() == extFilter)
									return false;
								else
									return true;
							}
							else
							{
								if (nameFilter != "any" && extFilter == "any") {
									if (Path(item.path()).getBaseName().find(nameFilter) != std::string::npos)
										return false;
									else
										return true;
								}
								else
								{
									if (Path(item.path()).getBaseName().find(nameFilter) != std::string::npos &&
										Path(item.path()).getExtension() == extFilter)
										return false;
									else
										return true;
								}
							}
						}
					}
					else
						return true;
				}

			}), files.end());
			for (auto item : files) {
				filesList.push_back(Path(item.path()));
			}
			return filesList;
		}
	}
}