#ifndef SCENARIO_H
#define SCENARIO_H

#include "../../src/engine.h"
#include <unordered_map>
#include <regex>
#include <string>

namespace symbolicNumeric {

	class Scenario {
	private:
		struct PredicateInfo
		{
			std::string type;
			std::string name;
			std::string validity;
			std::unordered_map<std::string, std::string> arguments;
			std::vector<std::string> active;
			std::vector<std::string> passive;
			PredicateInfo() {}
			PredicateInfo(const std::string& Type, const std::string& Name, const std::string& Validity)
				: type(Type), name(Name), validity(Validity) {}
		};
	public:
		std::unordered_map<std::string, std::vector<std::string>> objectList;
		std::string name;
		unsigned int nrOfSamples;
		std::string action;
		std::vector<PredicateInfo> initilStatePredicates;
		std::vector<PredicateInfo> goalStatePredicates;

	private:
		void readPredicates(tinyxml2::XMLElement *predicatesNode, const std::string& state, std::vector<PredicateInfo>& predicates);
	public:
		Scenario();
		~Scenario();
		bool loadDescriptionFile(const std::string& fileName);
	};
}


#endif // !SCENARIO_H

