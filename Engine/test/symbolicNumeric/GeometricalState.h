#ifndef GEOMETRIC_STATE_H
#define GEOMETRIC_STATE_H

#include "../../src/engine.h"

#include <string>
#include <map>
#include <vector>
#include <array>
#include <stdlib.h>
using namespace std;
#include "Utils.h"
#include "Global.h"
#include "Connectedness.h"


struct GeomLimits
{
	std::vector<std::pair<float, float>> limX;
	std::vector<std::pair<float, float>> limY;
	std::vector<std::pair<float, float>> limZ;
	//StyleAxis style;
	//ComparisonSymbol comparison;

	GeomLimits() { }

};

class GeometricalState
{
public:
	GeometricalState();
	~GeometricalState();
	Vec3f generateLocationConnectedness(Bounds bbDistObj, Bounds bbManipObj, ConnectednessPredicates connect);
	std::array<EulerAngles, 2> extractOrientationLimits(OrientationPredicates orient);
	GeomLimits extractPositionLimits(Bounds bbDistObj, Bounds bbManipObj, ConnectednessPredicates connect);
	void initConnectednessRelations();
	bool checkInitConditions(Bounds bbGroundObj, Bounds bbFigureObj, ConnectednessPredicates connect);
	bool checkConnectedness(Bounds bbGroundObj, Bounds bbFigureObj, ConnectednessPredicates connect);
	bool checkOrientation(Bounds bbGroundObj, Bounds bbFigureObj, OrientationPredicates orient);

	//checkFinalConditions
	GeomLimits resetPositionLimits(Bounds bbGround, Bounds bbFigure, ConnectednessPredicates connect);
	/*GeomLimits updatePositionLimits(FBox bbGround, FV activeObjExtent,
	this->stateDescription.getConnectedness(ExecutionState::INIT));*/
	map <ConnectednessAspect, ConnectednessPredicates> ConnectednessRelationsInv;
	Connectedness connectedness;

	Quat CalculateQuat(EulerAngles& rotation, OrientationPredicates orientSymb);

private:
	map <ConnectednessPredicates, ConnectednessAspect> ConnectednessRelations;
	ConnectednessAspect setAspect(RCC8 rcc8Relation, ProjectionPlane plane, ComparisonSymbol comparison);
	std::pair<float, float> calculateStyleLimits(const float *styleMinMax, const float *ground, float minFigure, ComparisonSymbol comparison);
	std::array<std::vector<pair<float, float>>, 2> calculatePlaneLimits(const float *planeMinMax, const float *ground, const float *figureMinMax, RCC8 rcc8);
	//std::pair<float, float> resetStyleLimits(const float *styleMinMax, const float *ground, const float *figure, ComparisonSymbol comparison);
	std::pair<float, float> resetStyleLimits(const float *styleMinMax, const float *ground, float figure, ComparisonSymbol comparison);


	//std::array<std::vector<pair<float, float>>, 2> resetPlaneLimits(const float *ground, const float *figureMinMax, RCC8 rcc8);
	std::array<std::vector<pair<float, float>>, 2> resetPlaneLimits(const float *ground, const float *figureMinMax, RCC8 rcc8);

	GeomLimits geometricalLim;

	bool checkStyleConditions(ComparisonSymbol comparison, const float *groundMinMax, const float *figureMinMax);
	bool checkPlaneConditions(RCC8 rcc8, BBox2D groundBB2D, BBox2D figureBB2D);
};

#endif // !GEOMETRIC_STATE_H




