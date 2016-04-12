#ifndef STATE_DESCRIPTION_READER_H
#define STATE_DESCRIPTION_READER_H

#include "tinyxml2.h"
#include "SymbolState.h"
#include "Utils.h"
#include <string>
#include <sstream>

using namespace tinyxml2;

class ScenarioDescription
{
private:
	bool validity;
private:
	void readInitialState();
	void readGoalState();
public:
	ScenarioDescription(const std::string& filepath);
	~ScenarioDescription();
	bool isValid();
};

class StateDescriptionReader
{
public:
	StateDescriptionReader();
	~StateDescriptionReader();
	bool LoadDescriptionXML(string XMLFile);
	bool readConnectedness(string& connectedness, ExecutionState state);
	//string readConnectedness(ExecutionState state);
	bool readOrientation(string& orientation, ExecutionState state);
	bool readRelativeDistance(string& relativeDist, ExecutionState state);
	//XMLDocument getxmlDoc();
	//bool getInitState();


private:
	XMLDocument xmlDoc;
	SymbolState* currState;
	XMLElement* pInitStateElement;
	XMLElement* pGoalStateElement;
};


#endif

