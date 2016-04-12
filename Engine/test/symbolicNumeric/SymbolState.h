#ifndef SYMBOL_STATE_H
#define SYMBOL_STATE_H

#include "../../src/engine.h"

#include <math.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <map>
#include "Utils.h"
#include "Global.h"
#include "GeometricalState.h"
#include "Connectedness.h"


class SymbolState
{
public:
	SymbolState();
	~SymbolState();
	void setOrientation(string orient, ExecutionState state);
	void setConnectedness(string connect, ExecutionState state);
	void setRelativeDist(float dist[2], ExecutionState state);
	void setRelativeDist(string dist, ExecutionState state);
	OrientationPredicates getOrientation(ExecutionState state);
	ConnectednessPredicates getConnectedness(ExecutionState state);
	float getRelativeDist(int state);
	void setExecRule(string rule);
	void setOrientationFromGeom(Vec3f rotation, ExecutionState state);
	OrientationPredicates convertRotation2Symb(EulerAngles orientation);
	OrientationPredicates convertQuat2Symb(Quat quaternion);
	map<string, ConnectednessPredicates> connectednessMap;
	map<string, OrientationPredicates> orientationMap;
	map<ConnectednessPredicates, string> connectednessMapInv;
	std::map<OrientationPredicates, string> orientationMapInv;
	map<RCC8, string> RCC8MapInv;
	ConnectednessPredicates convertLocation2Symb(Bounds bBoxObj, Bounds bBoxTable, Vec3f location);
	GeometricalState geomState;
	Connectedness connectedness;

	RCC8 getRCC8(Bounds bbFigure, Bounds bbGround, ProjectionPlane plane);
	ComparisonSymbol getComparison(Bounds bbFigure, Bounds bbGround, ProjectionPlane plane);
	ConnectednessPredicates getConnectednessFromRCC8Comparison(RCC8 rcc8, ComparisonSymbol comparison, ProjectionPlane plane);
	std::vector<ConnectednessPredicates> convertPosition2Symb(Bounds bbFigure, Bounds bbObj);

	//vector<string> split(string str, char delimiter);

private:
	OrientationPredicates orientInit;
	ConnectednessPredicates connectInit;
	float distInit[2];
	OrientationPredicates orientGoal;
	ConnectednessPredicates connectGoal;
	void declareConnectednessMap();
	void declareConnectednessMapInv();
	void declareOrientationMap();
	void declareOrientationMapInv();
	void declareRCC8MapInv();
	RCC8 convertGeom2RCC8(BBox2D groundBB2D, BBox2D figureBB2D);
	ComparisonSymbol convertGeom2Comparison(const float *groundStyle, const float *figureStyle);
	//float distGoal;

};



#endif // !SYMBOL_STATE_H

