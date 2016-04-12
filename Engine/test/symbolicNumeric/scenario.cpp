#include "scenario.h"

namespace symbolicNumeric {

	Scenario::Scenario() {

	}

	Scenario::~Scenario() {

	}

	void Scenario::readPredicates(tinyxml2::XMLElement *predicatesNode, const std::string& state, std::vector<PredicateInfo>& predicates) {
		do
		{
			if (std::string(predicatesNode->Name()) == "predicate") {
				PredicateInfo predicate(predicatesNode->Attribute("type"), predicatesNode->Attribute("name"), predicatesNode->Attribute("validity"));
				tinyxml2::XMLElement *argChild = predicatesNode->FirstChildElement();
				if (argChild) {
					do
					{
						if (std::string(argChild->Name()) == "argument") {
							if (argChild->Attribute("axis"))
								predicate.arguments["axis"] = argChild->Attribute("axis");
							if (argChild->Attribute("plane"))
								predicate.arguments["plane"] = argChild->Attribute("plane");
						}

						if (std::string(argChild->Name()) == "active") {
							if (argChild->Attribute("object"))
								predicate.active.push_back(argChild->Attribute("object"));

							if (argChild->Attribute("multiple_object")) {
								std::string str(argChild->Attribute("multiple_object"));
								std::regex reg("[\\w]+");
								std::sregex_token_iterator iter(str.begin(), str.end(), reg);
								std::vector<std::string> objects(iter, std::sregex_token_iterator());
								for (auto obj : objects)
									predicate.active.push_back(obj);
							}

							if (argChild->Attribute("tag")) {
								for (auto obj : objectList[std::string(argChild->Attribute("tag"))])
									predicate.active.push_back(obj);
							}
						}

						if (std::string(argChild->Name()) == "passive") {
							if (argChild->Attribute("object"))
								predicate.passive.push_back(argChild->Attribute("object"));

							if (argChild->Attribute("multiple_object")) {
								std::string str(argChild->Attribute("multiple_object"));
								std::regex reg("[\\w]+");
								std::sregex_token_iterator iter(str.begin(), str.end(), reg);
								std::vector<std::string> objects(iter, std::sregex_token_iterator());
								for (auto obj : objects)
									predicate.passive.push_back(obj);
							}

							if (argChild->Attribute("tag")) {
								for (auto obj : objectList[std::string(argChild->Attribute("tag"))])
									predicate.passive.push_back(obj);
							}
						}
					} while (argChild = argChild->NextSiblingElement());
					predicates.push_back(predicate);
				}
			}
		} while (predicatesNode = predicatesNode->NextSiblingElement());
	}

	bool Scenario::loadDescriptionFile(const std::string& fileName) {
		tinyxml2::XMLDocument xmlDoc;
		xmlDoc.LoadFile(fileName.c_str());
		if (xmlDoc.Error())
			return false;

		tinyxml2::XMLElement *rootElement = xmlDoc.RootElement();

		if (std::string(rootElement->Name()) == "problem_description") {
			this->name = rootElement->Attribute("name");
			rootElement->QueryUnsignedAttribute("numberOfSamples", &this->nrOfSamples);
			tinyxml2::XMLElement *rootChild = rootElement->FirstChildElement();
			if (rootChild) {
				do
				{
					if (std::string(rootChild->Name()) == "objects_list") {
						tinyxml2::XMLElement *objectsChild = rootChild->FirstChildElement();
						if (objectsChild) {
							do
							{
								if (std::string(objectsChild->Name()) == "object")
									objectList[std::string(objectsChild->Attribute("tag"))].push_back(std::string(objectsChild->Attribute("name")));
							} while (objectsChild = objectsChild->NextSiblingElement());
						}
					}

					if (std::string(rootChild->Name()) == "action") {
						this->action = rootChild->Attribute("name");
						tinyxml2::XMLElement *actionChild = rootChild->FirstChildElement();
						if (actionChild) {
							do
							{
								if (std::string(actionChild->Name()) == "initial_state") {
									tinyxml2::XMLElement *pridicateChild = actionChild->FirstChildElement();
									if (pridicateChild) {
										readPredicates(pridicateChild, "initial_state", this->initilStatePredicates);
									}
								}

								if (std::string(actionChild->Name()) == "goal_state") {
									tinyxml2::XMLElement *pridicateChild = actionChild->FirstChildElement();
									if (pridicateChild) {
										readPredicates(pridicateChild, "goal_state", this->goalStatePredicates);
									}
								}
							} while (actionChild = actionChild->NextSiblingElement());
						}
					}
				} while (rootChild = rootChild->NextSiblingElement());
			}
		}
		else
			return false;
		return true;
	}
}