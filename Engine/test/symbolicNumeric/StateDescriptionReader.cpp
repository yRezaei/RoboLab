#include "StateDescriptionReader.h"



#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return false; }
#endif


StateDescriptionReader::StateDescriptionReader()
{
}


StateDescriptionReader::~StateDescriptionReader()
{
}

bool StateDescriptionReader::LoadDescriptionXML(string XMLFile)
{
	XMLError eResult = xmlDoc.LoadFile(XMLFile.c_str());
	XMLCheckResult(eResult);
	XMLNode* pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) {
		printf("XML Error: File read error\n"); return false;
	}
	pInitStateElement = pRoot->FirstChildElement("InitState");
	if (pInitStateElement == nullptr) {
		printf("XML Error: Parsing InitState element\n"); return false;
	}
	pGoalStateElement = pRoot->FirstChildElement("GoalState");
	if (pGoalStateElement == nullptr) {
		printf("XML Error: Parsing GoalState element\n"); return false;
	}
	return true;
}

bool StateDescriptionReader::readConnectedness(string& connectedness, ExecutionState state)
{
	//string strConnect;
	if (state == ExecutionState::INIT) //INIT
	{
		XMLElement *pConnectednessElement = pInitStateElement->FirstChildElement("Connectedness");
		if (pConnectednessElement == nullptr) {
			printf("XML Error: Parsing InitState/Connectedness element\n"); return false;
		}
		//return pConnectednessElement->GetText();
		connectedness = pConnectednessElement->GetText();
	}
	else //if (state == 1) //GOAL
	{
		XMLElement *pConnectednessElement = pGoalStateElement->FirstChildElement("Connectedness");
		if (pConnectednessElement == nullptr) {
			printf("XML Error: Parsing GoalState/Connectedness element\n"); return false;
		}
		connectedness = pConnectednessElement->GetText();
	}
	//connectedness = strConnect;
	return true;
}

bool StateDescriptionReader::readOrientation(string& orientation, ExecutionState state)
{
	XMLElement *pOrientationElement;
	if (state == ExecutionState::INIT) //INIT
	{
		pOrientationElement = pInitStateElement->FirstChildElement("Orientation");
		if (pOrientationElement == nullptr) {
			printf("XML Error: Parsing InitState/Orientation element\n"); return false;
		}		
	}
	else //if (state == ExecutionState::GOAL) //GOAL
	{
		pOrientationElement = pGoalStateElement->FirstChildElement("Orientation");
		if (pOrientationElement == nullptr) {
			printf("XML Error: Parsing GoalState/Orientation element\n"); return false;
		}
		//orientation = pOrientationElement->GetText();
	}
	orientation = pOrientationElement->GetText();//orientation = strOrient;
	return true;
 }

bool StateDescriptionReader::readRelativeDistance(string& relativeDist, ExecutionState state)
{
	if (state == ExecutionState::INIT) //INIT
	{
		XMLElement *pDistElement = pInitStateElement->FirstChildElement("RelativeDistance");
		if (pDistElement == nullptr) {
			printf("XML Error: Parsing InitState/Relative Distance element\n"); return false;
		}
		XMLNode* textNode = pDistElement->FirstChild();
		if (textNode == nullptr) {
			relativeDist = ""; // if the RelativeDistance tag does not contain any text then return emptz string
		}
		else {
			relativeDist = textNode->ToText()->Value();
		}		
	}
	else //if (state == 1) //GOAL
	{
		/*XMLElement *pDistElement = pGoalStateElement->FirstChildElement("RelativeDistance");
		if (pDistElement == nullptr) {
			printf("XML Error: Parsing GoalState/Orientation element\n"); return false;
		}
		XMLError eResult = pDistElement->QueryFloatText(&fRelevantDist);
		XMLCheckResult(eResult);*/
		return false;
	}
	
	return true;
}
//bool StateDescriptionReader::isInitStateDefined()
/*void StateDescriptionReader::loadXML2xmlDoc(string XMLFile)
{
	XMLDocument xmlDoc1;
	XMLError eResult = xmlDoc.LoadFile(XMLFile.c_str());
	//XMLCheckResult(eResult);
	return;
}*/


