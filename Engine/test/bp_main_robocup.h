#ifndef BP_MAIN_ROBOCUP_H
#define BP_MAIN_ROBOCUP_H

#include "../src/engine.h"


class BP_Main_Robocup : public IBlueprint
{
public:
	Entity Grid;
	std::vector<Entity> robocupObjects;

private:
	void loadMeshes(tinyxml2::XMLElement* element, Poco::Path parentDirectory)
	{
		auto modelElement = element->FirstChildElement("model");
		while (modelElement)
		{
			std::string name = (modelElement->Attribute("name"));
			Poco::Path path(parentDirectory);
			path.append(modelElement->Attribute("path"));

			if (Poco::Path::find(path.parent().toString(), path.getFileName(), path))
				Resource::loadMesh(Resource::MeshUsageType::VISUALIZATION, path.parent().toString(), name, Vec3f(0.01f));

			modelElement = modelElement->NextSiblingElement("model");
		}
	}

	void loadObjects(tinyxml2::XMLElement* element) {
		auto objectElement = element->FirstChildElement();
		while (objectElement) {
			std::string name = objectElement->Attribute("name");
			std::string model = objectElement->Attribute("model");
			float x = 0.0f, y = 0.0f, z = 0.0f, roll = 0.0f, pitch = 0.0f, yaw = 0.0f;
			auto transformElem = objectElement->FirstChildElement("transform");
			if (transformElem) {
				transformElem->QueryFloatAttribute("x", &x);
				transformElem->QueryFloatAttribute("y", &y);
				transformElem->QueryFloatAttribute("z", &z);
				transformElem->QueryFloatAttribute("roll", &roll);
				transformElem->QueryFloatAttribute("pitch", &pitch);
				transformElem->QueryFloatAttribute("yaw", &yaw);
			}

			robocupObjects.push_back(Entity(name, makeMat4(Vec3f(x, y, z), makeQuat(EulerAngles(roll, pitch, yaw)))));
			robocupObjects.back().addComponent<RenderableComponent>(model);

			objectElement = objectElement->NextSiblingElement();
		}
	}


	void readWorldConfig(const Poco::Path& fileName) 
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(fileName.toString().c_str());

		if (!doc.Error())
		{
			auto rootElement = doc.RootElement(); 
			auto locationNode = rootElement->FirstChildElement();
			auto locationNodeChild = locationNode->FirstChildElement();

			while (locationNodeChild) {
				std::string elementName = std::string(locationNodeChild->Value());
				if (elementName == "models_List")
					loadMeshes(locationNodeChild, fileName.parent());

				if (elementName == "objects_list")
					loadObjects(locationNodeChild);

				locationNodeChild = locationNodeChild->NextSiblingElement();
			}
		}
		else
			Logging::console(system::LOG_ERROR, doc.GetErrorStr1());
	}

public:
	BP_Main_Robocup() {
	}

	~BP_Main_Robocup() {
	}

	void init() override 
	{
		Resource::loadMesh(Resource::MeshUsageType::VISUALIZATION, "../Resources/internal", "grid", Vec3f(1.0f));
		Grid.setName("Grid");
		Grid.addComponent<RenderableComponent>("grid");

		readWorldConfig(Poco::Path("../Resources/robocup_lab/robocup.conf"));
	}

	void update(float deltaTime) override
	{
		if (Input::KeyPressed(KEY_ESCAPE))
			Engine::shutdown();
	}

	void destroy() override {
	}

	
};

#endif // !SURFACE_POINT_VALIDITY_TEST_H


