#include "FileIO.h"

using Poco::StringTokenizer;
using Poco::NumberParser;


namespace robolab {
	namespace utils {

		namespace fileIO
		{
			namespace scf // Scenario Configuration File
			{
				/*void load(const std::string& fileName, ScenearioInfo& scenarioInfo)
				{
					XML::XMLDocument xmlDoc;
					xmlDoc.LoadFile(fileName.c_str());

					if (!xmlDoc.Error())
					{
						XML::XMLElement *rootElement = xmlDoc.RootElement();
						XML::XMLElement *childElem;
						if (std::string(rootElement->Name()) == "ScenarioDescription") {
							scenarioInfo.scenarioName = rootElement->Attribute("senario");
							rootElement->QueryUnsignedAttribute("parallel_scene", &scenarioInfo.paralelScene);
							childElem = rootElement->FirstChildElement();
							XML::XMLElement* elem;
							do {
								if (std::string(childElem->Name()) == "listOfMeshe") {
									for (elem = childElem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
									{
										if (std::string(elem->Name()) == "mesh") {
											scenarioInfo.meshFilesList.push_back(std::string(elem->GetText()));
										}
									}
									continue;
								}

								if (std::string(childElem->Name()) == "listOfActor") {
									for (elem = childElem->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
									{
										if (std::string(elem->Name()) == "actor")
										{
											scenarioInfo.actorInfoList.push_back(ActorInfo());
											scenarioInfo.actorInfoList.back().name = elem->Attribute("name");
											scenarioInfo.actorInfoList.back().tag = elem->Attribute("tag");
											scenarioInfo.actorInfoList.back().meshName = elem->Attribute("mesh");
											elem->FirstChildElement("position")->QueryFloatAttribute("x", &scenarioInfo.actorInfoList.back().position.x);
											elem->FirstChildElement("position")->QueryFloatAttribute("y", &scenarioInfo.actorInfoList.back().position.y);
											elem->FirstChildElement("position")->QueryFloatAttribute("z", &scenarioInfo.actorInfoList.back().position.z);
											elem->FirstChildElement("eulerAngles")->QueryFloatAttribute("roll", &scenarioInfo.actorInfoList.back().rotation.x);
											elem->FirstChildElement("eulerAngles")->QueryFloatAttribute("pitch", &scenarioInfo.actorInfoList.back().rotation.y);
											elem->FirstChildElement("eulerAngles")->QueryFloatAttribute("yaw", &scenarioInfo.actorInfoList.back().rotation.z);
											elem->FirstChildElement("scale")->QueryFloatAttribute("x", &scenarioInfo.actorInfoList.back().scale.x);
											elem->FirstChildElement("scale")->QueryFloatAttribute("y", &scenarioInfo.actorInfoList.back().scale.y);
											elem->FirstChildElement("scale")->QueryFloatAttribute("z", &scenarioInfo.actorInfoList.back().scale.z);
											elem->FirstChildElement("physic")->QueryFloatAttribute("mass", &scenarioInfo.actorInfoList.back().mass);
											elem->FirstChildElement("physic")->QueryBoolAttribute("isDynamic", &scenarioInfo.actorInfoList.back().isDynamic);
										}
									}
									continue;
								}

								break;
							} while (childElem = childElem->NextSiblingElement());

						}
					}

				}*/
			}
		}
	}
}