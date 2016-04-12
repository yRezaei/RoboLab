#include "GeometricalState.h"


GeometricalState::GeometricalState()
{
	initConnectednessRelations();
}


GeometricalState::~GeometricalState()
{
}

Vec3f GeometricalState::generateLocationConnectedness(Bounds bbDistObj, Bounds bbManipObj, ConnectednessPredicates connect)
{
	// ptoject the distObj into plane
	// get plane limits of the distObj (for example for min and max for x and y)
	// get 1/2 of height, length and weidth of manObj
	// depending on connectedness find limits for two variables
	Vec3f test;

	return test;
}

void GeometricalState::initConnectednessRelations()
{
	//ConnectednessAspect aspect;
	ConnectednessRelations[ConnectednessPredicates::ABOVE] = this->setAspect(RCC8::DC, ProjectionPlane::XY, ComparisonSymbol::minMOMTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::ALONG] = this->setAspect(RCC8::DC, ProjectionPlane::XY, ComparisonSymbol::minMOEQmaxDO);
	ConnectednessRelations[ConnectednessPredicates::BELOW] = this->setAspect(RCC8::DC, ProjectionPlane::XY, ComparisonSymbol::maxMOLTminDO);
	ConnectednessRelations[ConnectednessPredicates::ABOVEEC] = this->setAspect(RCC8::EC, ProjectionPlane::XY, ComparisonSymbol::minMOMTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::ALONGEC] = this->setAspect(RCC8::EC, ProjectionPlane::XY, ComparisonSymbol::minMOEQmaxDO);
	ConnectednessRelations[ConnectednessPredicates::BELOWEC] = this->setAspect(RCC8::EC, ProjectionPlane::XY, ComparisonSymbol::maxMOLTminDO);
	ConnectednessRelations[ConnectednessPredicates::TANOVER] = this->setAspect(RCC8::TPP, ProjectionPlane::XY, ComparisonSymbol::minMOMTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::TANON] = this->setAspect(RCC8::TPP, ProjectionPlane::XY, ComparisonSymbol::minMOEQmaxDO);
	ConnectednessRelations[ConnectednessPredicates::TANUNDER] = this->setAspect(RCC8::TPP, ProjectionPlane::XY, ComparisonSymbol::maxMOLTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::OVER] = this->setAspect(RCC8::NTPP, ProjectionPlane::XY, ComparisonSymbol::minMOMTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::ON] = this->setAspect(RCC8::NTPP, ProjectionPlane::XY, ComparisonSymbol::minMOEQmaxDO);
	ConnectednessRelations[ConnectednessPredicates::UNDER] = this->setAspect(RCC8::NTPP, ProjectionPlane::XY, ComparisonSymbol::maxMOLTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::PARTIALLYOVER] = this->setAspect(RCC8::PO, ProjectionPlane::XY, ComparisonSymbol::minMOMTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::PARTIALLYON] = this->setAspect(RCC8::PO, ProjectionPlane::XY, ComparisonSymbol::minMOEQmaxDO);
	ConnectednessRelations[ConnectednessPredicates::PARTIALLYBELOW] = this->setAspect(RCC8::PO, ProjectionPlane::XY, ComparisonSymbol::maxMOLTminDO);
	ConnectednessRelations[ConnectednessPredicates::OVERCOVERED] = this->setAspect(RCC8::EQ, ProjectionPlane::XY, ComparisonSymbol::minMOMTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::ONCOVERED] = this->setAspect(RCC8::EQ, ProjectionPlane::XY, ComparisonSymbol::minMOEQmaxDO);
	ConnectednessRelations[ConnectednessPredicates::UNDERCOVERED] = this->setAspect(RCC8::EQ, ProjectionPlane::XY, ComparisonSymbol::maxMOLTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::TANCIRCUMOVER] = this->setAspect(RCC8::TPPi, ProjectionPlane::XY, ComparisonSymbol::minMOMTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::TANCIRCUMON] = this->setAspect(RCC8::TPPi, ProjectionPlane::XY, ComparisonSymbol::minMOEQmaxDO);
	ConnectednessRelations[ConnectednessPredicates::TANCIRCUMUNDER] = this->setAspect(RCC8::TPPi, ProjectionPlane::XY, ComparisonSymbol::maxMOLTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::CIRCUMOVER] = this->setAspect(RCC8::NTPPi, ProjectionPlane::XY, ComparisonSymbol::minMOMTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::CIRCUMON] = this->setAspect(RCC8::NTPPi, ProjectionPlane::XY, ComparisonSymbol::minMOEQmaxDO);
	ConnectednessRelations[ConnectednessPredicates::CIRCUMUNDER] = this->setAspect(RCC8::NTPPi, ProjectionPlane::XY, ComparisonSymbol::maxMOLTmaxDO);
	ConnectednessRelations[ConnectednessPredicates::CLOSE] = this->setAspect(RCC8::DC, ProjectionPlane::XY, ComparisonSymbol::minMOMTminDO);
}

ConnectednessAspect GeometricalState::setAspect(RCC8 rcc8Relation, ProjectionPlane plane, ComparisonSymbol comparison)
{
	ConnectednessAspect aspect(rcc8Relation, plane, comparison);
	return aspect;
}
std::array<EulerAngles, 2> GeometricalState::extractOrientationLimits(OrientationPredicates orient)
{
	std::array<EulerAngles, 2> orientLimits;
	float sa = SMALLEST_ANGLE*MPI / 180;
	const float halfC = 180/MPI; // parameter to convert degree to radian
	const float devideVal = 25;
	switch (orient)
	//   pitch,  yaw, roll
	{
	case OrientationPredicates::STRAIGHTALONGX:
		//orientLimits[0] = Vec3f((MPI / 4)*halfC, (-MPI / 16)*halfC, (-MPI)*halfC);
		//orientLimits[1] = Vec3f((3 * MPI / 4)*halfC, (MPI / 16)*halfC, MPI*halfC);
		
		//orientLimits[0] = Vec3f((15*MPI / 16)*halfC, (-MPI / 16)*halfC, (-MPI)*halfC);
		//orientLimits[1] = Vec3f((17 * MPI / 16)*halfC, (MPI / 16)*halfC, MPI*halfC);
		
		// desired position!
		//orientLimits[0] = Vec3f((-MPI)*halfC, ((MPI / 2))*halfC, (MPI / 2 - (MPI / 25))*halfC);
		//orientLimits[1] = Vec3f((MPI)*halfC, ((MPI / 2))*halfC, (MPI / 2 + (MPI / 25))*halfC);
		//!!!
		orientLimits[0] = EulerAngles((-MPI / 2 + (MPI / devideVal))*halfC, -(MPI / devideVal)*halfC, -MPI*halfC);
		orientLimits[1] = EulerAngles((-MPI / 2 - (MPI / devideVal))*halfC, (MPI / devideVal)*halfC, MPI*halfC);
		break;
	case OrientationPredicates::STRAIGHTALONGY:
		//orientLimits[0] = Vec3f(-(MPI / 25)*halfC, (-MPI / 25)*halfC, (-MPI)*halfC);
		//orientLimits[1] = Vec3f((MPI / 25) * halfC, (MPI / 25)*halfC, (MPI)*halfC);

		orientLimits[0] = EulerAngles((-MPI)*halfC, (-MPI / devideVal)*halfC, (MPI / 2 - (MPI / devideVal))*halfC);
		orientLimits[1] = EulerAngles(MPI*halfC, (MPI / devideVal)*halfC, (MPI / 2 + (MPI / devideVal))*halfC);

		
		//orientLimits[0] = Vec3f((-MPI)*halfC, (-MPI / 16)*halfC,  ((-3 * MPI / 4) - sa)*halfC);
		//orientLimits[1] = Vec3f(MPI*halfC, (MPI / 16)*halfC,((-MPI / 4) - sa)*halfC);

		//orientLimits[0] = Vec3f(((-3 * MPI / 4) - sa)*halfC, (-MPI)*halfC, (-MPI / 16)*halfC);
		//orientLimits[1] = Vec3f(((-MPI / 4) - sa)*halfC, MPI*halfC, (MPI / 16)*halfC);
		break;
	case OrientationPredicates::STRAIGHTALONGZ:
		//orientLimits[0] = Vec3f((-MPI / 25)*halfC, (-MPI)*halfC, (-MPI / 25)*halfC );
		//orientLimits[1] = Vec3f((MPI / 25)*halfC, MPI*halfC, (MPI / 25)*halfC );

		orientLimits[0] = EulerAngles((-MPI / devideVal)*halfC, (-MPI)*halfC, (-MPI / devideVal)*halfC);
		orientLimits[1] = EulerAngles((MPI / devideVal)*halfC, MPI*halfC, (MPI / devideVal)*halfC);
		break;//CHANGED!
	case OrientationPredicates::INVERTEDALONGX:
		orientLimits[0] = EulerAngles((MPI / 2 - (MPI / devideVal))*halfC, -(MPI / devideVal)*halfC, -MPI*halfC);
		orientLimits[1] = EulerAngles((MPI / 2 + (MPI / devideVal))*halfC, (MPI / devideVal)*halfC, MPI*halfC);

		//orientLimits[0] = Vec3f((5 * MPI / 4) *halfC, (-MPI / 16)*halfC,(-MPI)*halfC);
		//orientLimits[1] = Vec3f((7 * MPI / 4) *halfC, (MPI / 16)*halfC, MPI*halfC );

		
		//orientLimits[0] = Vec3f((-MPI)*halfC, ((5 * MPI / 4) + sa)*halfC, (-MPI / 16)*halfC);
		//orientLimits[1] = Vec3f(MPI*halfC, ((7 * MPI / 4) - sa)*halfC, (MPI / 16)*halfC);
		break;
	case OrientationPredicates::INVERTEDALONGY:
		orientLimits[0] = EulerAngles((-MPI)*halfC, (-MPI / devideVal)*halfC, (-MPI / 2 + (MPI / devideVal))*halfC);
		orientLimits[1] = EulerAngles(MPI*halfC, (MPI / devideVal)*halfC, (-MPI / 2 - (MPI / devideVal))*halfC);


		
		//orientLimits[0] = Vec3f((-MPI / 4 + sa)*halfC, (-MPI)*halfC, (-MPI / 16)*halfC);
		//orientLimits[1] = Vec3f((3 * MPI / 4 - sa)*halfC, MPI*halfC, (MPI / 16)*halfC);
		break;
	case OrientationPredicates::INVERTEDALONGZ:
		orientLimits[0] = EulerAngles((-MPI / devideVal)*halfC, -MPI*halfC, ((devideVal - 1) * MPI / devideVal)*halfC);
		orientLimits[1] = EulerAngles((MPI / devideVal)*halfC, MPI*halfC, ((devideVal + 1)* MPI / devideVal)*halfC);
		
		//orientLimits[0] = Vec3f((15 * MPI / 16)*halfC, (-MPI / 16)*halfC, -MPI*halfC);
		//orientLimits[1] = Vec3f((17 * MPI / 16)*halfC, (MPI / 16)*halfC, MPI*halfC);
		break;
	case OrientationPredicates::PARALLELXY:
		orientLimits[0] = EulerAngles((MPI / 2 - (MPI / devideVal))*halfC, -(MPI)*halfC, -MPI*halfC);
		orientLimits[1] = EulerAngles((MPI / 2 + (MPI / devideVal))*halfC, (MPI)*halfC, MPI*halfC);

		//orientLimits[0] = Vec3f((-MPI / 4 )*halfC, -MPI*halfC, (-MPI / 4 )*halfC);
		//orientLimits[1] = Vec3f( (MPI / 4 )*halfC, MPI*halfC, (MPI / 4 )*halfC);


		//orientLimits[0] = Vec3f((-MPI / 4 + sa)*halfC, (-MPI / 4 + sa)*halfC, -MPI*halfC);
		//orientLimits[1] = Vec3f((MPI / 4 - sa)*halfC, (MPI / 4 - sa)*halfC, MPI*halfC);
		break;
	case OrientationPredicates::PARALLELYZ:
		orientLimits[0] = EulerAngles((-MPI / 4 )*halfC, (-MPI / 4 )*halfC, -MPI*halfC);
		orientLimits[1] = EulerAngles((MPI / 4 )*halfC, (MPI / 4 )*halfC, MPI*halfC);


		//orientLimits[0] = Vec3f(-MPI*halfC, (-MPI / 4 + sa)*halfC, (-MPI / 4 + sa)*halfC);
		//orientLimits[1] = Vec3f(MPI*halfC, (MPI / 4 - sa)*halfC, (MPI / 4 - sa)*halfC);
		break;
	case OrientationPredicates::PARALLELXZ:
		orientLimits[0] = EulerAngles(-MPI*halfC, (-MPI)*halfC, (-MPI / devideVal)*halfC);
		orientLimits[1] = EulerAngles(MPI*halfC, (MPI)*halfC, (MPI / devideVal)*halfC);


		//orientLimits[0] = Vec3f((-MPI / 4 + sa)*halfC, -MPI*halfC, (-MPI / 4 + sa)*halfC);
		//orientLimits[1] = Vec3f((MPI / 4 - sa)*halfC, MPI*halfC, (MPI / 4 - sa)*halfC);
		break;
	case OrientationPredicates::ABITRARYORIENTATION:
		orientLimits[0] = EulerAngles(-MPI*halfC, -MPI*halfC, -MPI*halfC);
		orientLimits[1] = EulerAngles(MPI*halfC, MPI*halfC, MPI*halfC);
	}
	return orientLimits;
}
//std::array<FVector, 2> GeometricalState::extractPositionLimits(Bounds bbGround, Bounds bbFigure, ConnectednessPredicates connect)
GeomLimits GeometricalState::extractPositionLimits(Bounds bbGround, Bounds bbFigure, ConnectednessPredicates connect)
{
	//std::array<FVector, 2> positionLimits;
	ConnectednessAspect relation = ConnectednessRelations[connect];
	float dimFigure[] = { abs(bbFigure.getMax().x - bbFigure.getMin().x), 
						  abs(bbFigure.getMax().y - bbFigure.getMin().y),
						  abs(bbFigure.getMax().z - bbFigure.getMin().z) };
	float figureMinMax[2];
	figureMinMax[0] = min(min(dimFigure[0], dimFigure[1]), dimFigure[2]);
	figureMinMax[1] = sqrt(dimFigure[0] * dimFigure[0] +
						   dimFigure[1] * dimFigure[1] + 
						   dimFigure[2] * dimFigure[2]);
	std::pair<float, float> styleLimits; // change to std::vector<std::pair<float, float>>
	std::array<std::vector<pair<float, float>>, 2> planeRanges;


	// get RCC8 description
	if (relation.plane == ProjectionPlane::XY)
	{
		float countourGround[] = { bbGround.getMin().x, bbGround.getMax().x, bbGround.getMin().y, bbGround.getMax().y };
		float planeZ[2] = { bbGround.getMin().z, bbGround.getMax().z };
		if (relation.comparison != ComparisonSymbol::EQ)
		{
			float zMinMax[] = { -1 * STABLE_UC_Z_MAX, STABLE_UC_Z_MAX };
			styleLimits = calculateStyleLimits(zMinMax, planeZ, figureMinMax[0], relation.comparison);
			geometricalLim.limZ.clear();
			geometricalLim.limZ.push_back(styleLimits);
			planeRanges = calculatePlaneLimits(planeZ, countourGround, figureMinMax, relation.rcc8Relation);
			geometricalLim.limX = planeRanges[0];// .push_back(planeRanges[0]);
			geometricalLim.limY = planeRanges[1];
		}		
	}
	else if (relation.plane == ProjectionPlane::XZ)
	{
		float countourGround[] = { bbGround.getMin().x, bbGround.getMax().x, bbGround.getMin().z, bbGround.getMax().z };
		float planeY[2] = { bbGround.getMin().y, bbGround.getMax().y };
		if (relation.comparison != ComparisonSymbol::EQ)
		{
			float yMinMax[] = { -1 * STABLE_UC_Y_MAX, STABLE_UC_Y_MAX };
			styleLimits = calculateStyleLimits(yMinMax, planeY, figureMinMax[0], relation.comparison);
			geometricalLim.limY.clear();
			geometricalLim.limY.push_back(styleLimits);
			planeRanges = calculatePlaneLimits(planeY, countourGround, figureMinMax, relation.rcc8Relation);
			geometricalLim.limX = planeRanges[0];// .push_back(planeRanges[0]);
			geometricalLim.limZ = planeRanges[1];
		}
	}
	else if (relation.plane == ProjectionPlane::YZ)
	{
		float countourGround[] = { bbGround.getMin().y, bbGround.getMax().y, bbGround.getMin().z, bbGround.getMax().z };
		float planeX[2] = { bbGround.getMin().x, bbGround.getMax().x };
		if (relation.comparison != ComparisonSymbol::EQ)
		{
			float xMinMax[] = { -1 * STABLE_UC_Y_MAX, STABLE_UC_Y_MAX };
			styleLimits = calculateStyleLimits(xMinMax, planeX, figureMinMax[0], relation.comparison);
			geometricalLim.limX.clear();
			geometricalLim.limX.push_back(styleLimits);
			planeRanges = calculatePlaneLimits(planeX, countourGround, figureMinMax, relation.rcc8Relation);
			geometricalLim.limY = planeRanges[0];// .push_back(planeRanges[0]);
			geometricalLim.limZ = planeRanges[1];
		}
	}
	// get 2D-projection on plane
	// get style limits
	return geometricalLim;
}
std::pair<float, float> GeometricalState::calculateStyleLimits(const float *styleMinMax, 
															const float *ground, 
															float minFigure, 
															ComparisonSymbol comparison)
{
	std::pair<float, float> limits;// = { 0, 0 };
	if (comparison == ComparisonSymbol::MT)
	{
		limits = std::make_pair(ground[1] + 2*minFigure, STABLE_UC_Z_MAX);
	}
	else if (comparison == ComparisonSymbol::LT)
	{
		limits = std::make_pair(-1 * STABLE_UC_Z_MAX, ground[0] - minFigure);
	}

	return limits;
}

std::array<std::vector<pair<float, float>>, 2> GeometricalState::calculatePlaneLimits(const float *planeMinMax, // groundZ (if plane lies in xy-plane)
	const float *countourGround, // [Xmin, Xmax, Ymin, Ymax]
	const float *figureMinMax, // min and max (diagonal) size of the figure
	RCC8 rcc8)
// return value of type std::array<std::vector<pair<float, float>>, 2> is an 2d array of multiple pairs, where each dimension of an array
// is an axis and iach pair is a min, max range.
{
	// UPDATE
	//std::array<std::vector<MinMaxRange>, 2> setsOfRanges;
	std::array<std::vector<pair<float, float>>, 2> setsOfRanges;
	if (rcc8 == RCC8::NTPP)
	{
		setsOfRanges[0].push_back(std::make_pair(countourGround[0] + figureMinMax[0], countourGround[1] - figureMinMax[0]));
		setsOfRanges[1].push_back(std::make_pair(countourGround[2] + figureMinMax[0], countourGround[3] - figureMinMax[0]));
		setsOfRanges[1] = { std::make_pair(countourGround[2] + figureMinMax[0], countourGround[3] - figureMinMax[0]) };
	}
	else if (rcc8 == RCC8::DC)
	{
    	// ranges for axis1
		setsOfRanges[0] = { std::make_pair(countourGround[0] - abs(2 * countourGround[0]), countourGround[0] - figureMinMax[0]),
			std::make_pair(countourGround[1] + figureMinMax[0], countourGround[1] + abs(2 * countourGround[1])) };
		// ranges for axis2
		setsOfRanges[1] = { std::make_pair(countourGround[2] - abs(2 * countourGround[2]), countourGround[2] - figureMinMax[0]),
			std::make_pair(countourGround[3] + figureMinMax[0], countourGround[3] + abs(2 * countourGround[3])) };
	}
	else if (rcc8 == RCC8::PO)
	{
		// ranges for axis1
		setsOfRanges[0] = { std::make_pair(countourGround[0] - abs(2 * countourGround[0]), countourGround[0] - figureMinMax[0]),
			std::make_pair(countourGround[1] - figureMinMax[1], countourGround[1] + figureMinMax[1]) };
		// ranges for axis2
		setsOfRanges[1] = { std::make_pair(countourGround[2] - figureMinMax[1], countourGround[2] + figureMinMax[1]),
			std::make_pair(countourGround[3] - figureMinMax[1], countourGround[3] + figureMinMax[1]) };
	}
	else if (rcc8 == RCC8::EQ)
	{
		// here we return only one point center of countourGround
		// ranges for axis1
		setsOfRanges[0] = { std::make_pair((countourGround[0] + countourGround[1]) / 2, (countourGround[0] + countourGround[1]) / 2)};
		// ranges for axis2
		setsOfRanges[1] = { std::make_pair((countourGround[2] + countourGround[3]) / 2, (countourGround[2] + countourGround[3]) / 2) };
	}
	return setsOfRanges;
}
bool GeometricalState::checkConnectedness(Bounds bbGroundObj, Bounds bbFigureObj, ConnectednessPredicates connect)
{
	ConnectednessAspect relation = ConnectednessRelations[connect];
	bool returnFlag = false;
	if (relation.plane == ProjectionPlane::XY)
	{
		float groundZ[2] = {bbGroundObj.getMin().z, bbGroundObj.getMax().z};
		float figureZ[2] = {bbFigureObj.getMin().z, bbFigureObj.getMax().z};
		BBox2D groundXYBB2D(bbGroundObj.getMax().y, bbGroundObj.getMin().y, bbGroundObj.getMin().x, bbGroundObj.getMax().x);
		BBox2D figureXYBB2D(bbFigureObj.getMax().y, bbFigureObj.getMin().y, bbFigureObj.getMin().x, bbFigureObj.getMax().x);

		if (checkStyleConditions(relation.comparison, groundZ, figureZ))
		{
			returnFlag = checkPlaneConditions(relation.rcc8Relation, groundXYBB2D, figureXYBB2D);
		}
	}
	else if (relation.plane == ProjectionPlane::XZ)
	{
		float groundY[2] = { bbGroundObj.getMin().y, bbGroundObj.getMax().y };
		float figureY[2] = { bbFigureObj.getMin().y, bbFigureObj.getMax().y };
		BBox2D groundXZBB2D(bbGroundObj.getMax().z, bbGroundObj.getMin().z, bbGroundObj.getMin().x, bbGroundObj.getMax().x);
		BBox2D figureXZBB2D(bbFigureObj.getMax().z, bbFigureObj.getMin().z, bbFigureObj.getMin().x, bbFigureObj.getMax().x);

		if (checkStyleConditions(relation.comparison, groundY, figureY))
		{
			returnFlag = checkPlaneConditions(relation.rcc8Relation, groundXZBB2D, figureXZBB2D);
		}
	}
	else if (relation.plane == ProjectionPlane::YZ)
	{
		float groundX[2] = { bbGroundObj.getMin().x, bbGroundObj.getMax().x };
		float figureX[2] = { bbFigureObj.getMin().x, bbFigureObj.getMax().x };
		BBox2D groundYZBB2D(bbGroundObj.getMax().z, bbGroundObj.getMin().z, bbGroundObj.getMin().y, bbGroundObj.getMax().y);
		BBox2D figureYZBB2D(bbFigureObj.getMax().z, bbFigureObj.getMin().z, bbFigureObj.getMin().y, bbFigureObj.getMax().y);

		if (checkStyleConditions(relation.comparison, groundX, figureX))
		{
			returnFlag = checkPlaneConditions(relation.rcc8Relation, groundYZBB2D, figureYZBB2D);
		}
	}
	return returnFlag;
}
bool GeometricalState::checkInitConditions(Bounds bbGroundObj, Bounds bbFigureObj, ConnectednessPredicates connect)
{
	bool returnFlag = false;
	returnFlag = checkConnectedness(bbGroundObj, bbFigureObj, connect);
	return returnFlag;
}

bool GeometricalState::checkOrientation(Bounds bbGroundObj, Bounds bbFigureObj, OrientationPredicates orient)
{
	bool returnFlag = false;
	return returnFlag;
}
bool GeometricalState::checkStyleConditions(ComparisonSymbol comparison, const float *groundMinMax, const float *figureMinMax)
{
	bool returnFlag = false;
	if ((comparison == ComparisonSymbol::MT) && (groundMinMax[1] < figureMinMax[0])) { returnFlag = true; }
	else if ((comparison == ComparisonSymbol::LT) && (groundMinMax[0] >= figureMinMax[1])) { returnFlag = true; }
	//else if ((comparison == ComparisonSymbol::EQ) && (MTmath.ApproxEqual(groundMinMax[1], figureMinMax[0])))
	else if ((comparison == ComparisonSymbol::minMOLTminDO) && 
		(!ApproxEqual(groundMinMax[0], figureMinMax[0]))&&(figureMinMax[0] < groundMinMax[0]) && (figureMinMax[1] > groundMinMax[0]))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::minMOLTmaxDO) &&
		(!ApproxEqual(groundMinMax[1], figureMinMax[0])) && // maxMO != minDO
		(figureMinMax[0] < groundMinMax[1]) && //minMO < maxDO
		(figureMinMax[1] > groundMinMax[0]))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::maxMOLTminDO) &&
		(!ApproxEqual(groundMinMax[0], figureMinMax[1])) && (figureMinMax[1] < groundMinMax[0]))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::maxMOLTmaxDO) &&
		(!ApproxEqual(groundMinMax[1], figureMinMax[1])) &&
		(figureMinMax[1] < groundMinMax[1]) && (figureMinMax[1] > groundMinMax[0]))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::minMOEQminDO) &&
		(ApproxEqual(groundMinMax[0], figureMinMax[0])))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::maxMOEQminDO) &&
		(ApproxEqual(groundMinMax[0], figureMinMax[1])))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::minMOEQmaxDO) &&
		(ApproxEqual(groundMinMax[1], figureMinMax[0])))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::maxMOEQmaxDO) &&
		(ApproxEqual(groundMinMax[1], figureMinMax[1])))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::minMOMTminDO) &&
		(!ApproxEqual(groundMinMax[0], figureMinMax[0])) &&
		(figureMinMax[0] > groundMinMax[0]) && (figureMinMax[0] < groundMinMax[1]))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::minMOMTmaxDO) &&
		(!ApproxEqual(groundMinMax[1], figureMinMax[0])) &&
		(figureMinMax[0] > groundMinMax[1]))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::maxMOMTminDO) &&
		(!ApproxEqual(groundMinMax[0], figureMinMax[1])) &&
		(figureMinMax[1] > groundMinMax[0]) && (figureMinMax[1]<groundMinMax[1]))
	{
		returnFlag = true;
	}
	else if ((comparison == ComparisonSymbol::maxMOMTmaxDO) &&
		(!ApproxEqual(groundMinMax[1], figureMinMax[1])) &&
		(figureMinMax[1] > groundMinMax[1]) && (figureMinMax[0]<groundMinMax[1]))
	{
		returnFlag = true;
	}

	else if ((comparison == ComparisonSymbol::UNKNOWN)) { returnFlag = true; }
	return returnFlag;
}
bool GeometricalState::checkPlaneConditions(RCC8 rcc8, BBox2D groundBB2D, BBox2D figureBB2D)
{
	bool returnFlag = false;
	sortVectors vectorList = connectedness.sortFigObjVectors(groundBB2D, figureBB2D);
	if (rcc8 == RCC8::DC)
	{
		returnFlag = connectedness.EvaluatePlanarDC((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size());
	}
	else if (rcc8 == RCC8::EC)
	{
		returnFlag = connectedness.EvaluatePlanarEC((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size());
	}
	else if (rcc8 == RCC8::TPP)
	{
		returnFlag = connectedness.EvaluatePlanarTPP((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size());
	}
	else if (rcc8 == RCC8::NTPP)
	{
		returnFlag = connectedness.EvaluatePlanarNTPP((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size());
	}
	else if (rcc8 == RCC8::PO)
	{
		returnFlag = connectedness.EvaluatePlanarPO((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size());
	}
	else if (rcc8 == RCC8::EQ)
	{
		returnFlag = connectedness.EvaluatePlanarEQ((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size());
	}
	//else if (rcc8 == RCC8::NTPPi)
	//{
	//	returnFlag = EvaluatePlanarNTPPi(sizeof(vectorList.exteriorList), sizeof(vectorList.boundaryList), sizeof(vectorList.interiorList));
	//}
	return returnFlag;
}

GeomLimits GeometricalState::resetPositionLimits(Bounds bbGround, Bounds bbFigure, ConnectednessPredicates connect)
{
	ConnectednessAspect relation = ConnectednessRelations[connect];
	std::pair<float, float> styleLimits; // change to std::vector<std::pair<float, float>>
	std::array<std::vector<pair<float, float>>, 2> planeRanges;
	Vec3f figExtent = bbFigure.extents();
	Vec3f groundExtent = bbGround.extents();

	// get RCC8 description
	if (relation.plane == ProjectionPlane::XY)
	{
		float countourGround[] = { bbGround.getMin().x, bbGround.getMax().x, bbGround.getMin().y, bbGround.getMax().y, groundExtent.x, groundExtent.y };
		float planeZ[2] = { bbGround.getMin().z, bbGround.getMax().z };
		float figureGround[] = { figExtent[0], figExtent[1] };
		//float figureZ[2] = { bbFigure.getMin().z, bbFigure.getMax().z };
		float figureZ = figExtent[2];
		float zMinMax[] = { STABLE_UC_Z_MIN, STABLE_UC_Z_MAX };
		//styleLimits = resetStyleLimits(zMinMax, planeZ, figureZ, relation.comparison);
		styleLimits = resetStyleLimits(zMinMax, planeZ, figExtent[2], relation.comparison);
		geometricalLim.limZ.clear();
		geometricalLim.limZ.push_back(styleLimits);
		planeRanges = resetPlaneLimits(countourGround, figureGround, relation.rcc8Relation);
		geometricalLim.limX = planeRanges[0];// .push_back(planeRanges[0]);
		geometricalLim.limY = planeRanges[1];

	}
	else if (relation.plane == ProjectionPlane::XZ)
	{
		float countourGround[] = { bbGround.getMin().x, bbGround.getMax().x, bbGround.getMin().z, bbGround.getMax().z };
		float planeY[2] = { bbGround.getMin().y, bbGround.getMax().y };
		//float figureGround[] = { bbFigure.getMin().x, bbFigure.getMax().x, bbFigure.getMin().z, bbFigure.getMax().z };
		float figureGround[] = { figExtent[0], figExtent[2] };
		float figureY[2] = { bbFigure.getMin().y, bbFigure.getMax().y };
		//float figureZ = figExtent[2];
		float yMinMax[] = { -1 * STABLE_UC_Y_MAX, STABLE_UC_Y_MAX };
		styleLimits = resetStyleLimits(yMinMax, planeY, figExtent[1], relation.comparison);
		geometricalLim.limY.clear();
		geometricalLim.limY.push_back(styleLimits);
		planeRanges = resetPlaneLimits(countourGround, figureGround, relation.rcc8Relation);
		geometricalLim.limX = planeRanges[0];// .push_back(planeRanges[0]);
		geometricalLim.limZ = planeRanges[1];
	}
	else if (relation.plane == ProjectionPlane::YZ)
	{
		float countourGround[] = { bbGround.getMin().y, bbGround.getMax().y, bbGround.getMin().z, bbGround.getMax().z };
		float planeX[2] = { bbGround.getMin().x, bbGround.getMax().x };
		//float figureGround[] = { bbFigure.getMin().y, bbFigure.getMax().y, bbFigure.getMin().z, bbFigure.getMax().z };
		float figureGround[] = { figExtent[1], figExtent[2] };
		float figureX[2] = { bbFigure.getMin().x, bbFigure.getMax().x };
		float xMinMax[] = { -1 * STABLE_UC_Y_MAX, STABLE_UC_Y_MAX };
		styleLimits = resetStyleLimits(xMinMax, planeX, figExtent[0], relation.comparison);
		geometricalLim.limX.clear();
		geometricalLim.limX.push_back(styleLimits);
		planeRanges = resetPlaneLimits(countourGround, figureGround, relation.rcc8Relation);
		geometricalLim.limY = planeRanges[0];// .push_back(planeRanges[0]);
		geometricalLim.limZ = planeRanges[1];
	}
	// get 2D-projection on plane
	// get style limits
	return geometricalLim;
}

std::pair<float, float> GeometricalState::resetStyleLimits(const float *styleMinMax,
	const float *ground, //ground = {minVal, maxVal}
	float figure,//extent
	ComparisonSymbol comparison)
{
	std::pair<float, float> limits;// = { 0, 0 };
	float sv = 0.01f;
	if (comparison == ComparisonSymbol::MT)
	{
		limits = std::make_pair(ground[1] + figure+ sv, styleMinMax[1]);
	}
	else if (comparison == ComparisonSymbol::LT)
	{
		limits = std::make_pair(styleMinMax[0], ground[1] - figure - sv);
	}
	else if (comparison == ComparisonSymbol::EQ)
	{
		limits = std::make_pair(ground[1] + figure, ground[1] + figure);
	}
	else if (comparison == ComparisonSymbol::maxMOEQmaxDO)
	{
		limits = std::make_pair(ground[1] - figure, ground[1] - figure);
	}
	else if (comparison == ComparisonSymbol::maxMOEQminDO)
	{
		limits = std::make_pair(ground[0] - figure, ground[0] - figure);
	}
	else if (comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		limits = std::make_pair(ground[1] + figure, ground[1] + figure);
	}
	else if (comparison == ComparisonSymbol::minMOEQminDO)
	{
		limits = std::make_pair(ground[0] + figure, ground[0] + figure);
	}
	else if (comparison == ComparisonSymbol::minMOMTminDO)
	{
		limits = std::make_pair(ground[0] + figure + sv, styleMinMax[1]);
	}
	else if (comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		limits = std::make_pair(ground[1] + figure + sv, styleMinMax[1]);
	}
	else if (comparison == ComparisonSymbol::maxMOMTminDO)
	{
		limits = std::make_pair(ground[0] - figure + sv, styleMinMax[1]);
	}
	else if (comparison == ComparisonSymbol::maxMOMTmaxDO)
	{
		limits = std::make_pair(ground[1] - figure + sv, styleMinMax[1]);
	}
	else if (comparison == ComparisonSymbol::minMOLTminDO)
	{
		limits = std::make_pair(styleMinMax[0], ground[0] + figure + sv);
	}
	else if (comparison == ComparisonSymbol::minMOLTmaxDO)
	{
		limits = std::make_pair(styleMinMax[0], ground[1] + figure + sv);
	}
	else if (comparison == ComparisonSymbol::maxMOLTminDO)
	{
		limits = std::make_pair(styleMinMax[0], ground[0] - figure + sv);
	}
	else if (comparison == ComparisonSymbol::maxMOLTmaxDO)
	{
		limits = std::make_pair(styleMinMax[0], ground[1] - figure + sv);
	}

	return limits;
}


std::array<std::vector<pair<float, float>>, 2> GeometricalState::resetPlaneLimits(
	const float *countourGround, // [Xmin, Xmax, Ymin, Ymax, Xext, Yext]
	const float *countourFigure, // [Xextent, Yextent]
	RCC8 rcc8)
	// return value of type std::array<std::vector<pair<float, float>>, 2> is an 2d array of multiple pairs, where each dimension of an array
	// is an axis and iach pair is a min, max range.
{
	std::array<std::vector<pair<float, float>>, 2> setsOfRanges;
	float sv = 0.01f;
	if (rcc8 == RCC8::NTPP)
	{
		if ((countourGround[0] + countourFigure[0] + sv < countourGround[1] - countourFigure[0] - sv) &&
			(countourGround[2] + countourFigure[1] + sv < countourGround[3] - countourFigure[1] - sv))
		{
			setsOfRanges[0] = { std::make_pair(countourGround[0] + countourFigure[0] + sv, countourGround[1] - countourFigure[0] - sv) };
			setsOfRanges[1] = { std::make_pair(countourGround[2] + countourFigure[1] + sv, countourGround[3] - countourFigure[1] - sv) };
		}
		else
		{
			int i = 0;
		}
	}
	else if (rcc8 == RCC8::TPP)
	{
		setsOfRanges[0] = { std::make_pair(countourGround[0] + countourFigure[0] + sv, countourGround[0] + countourFigure[0] + sv),
			std::make_pair(countourGround[1] - countourFigure[0] - sv, countourGround[1] - countourFigure[0] - sv),
			std::make_pair(countourGround[0] + countourFigure[0] + sv, countourGround[1] - countourFigure[0] - sv)
		};
		setsOfRanges[1] = { std::make_pair(countourGround[2] + countourFigure[1], countourGround[2] + countourFigure[1]),
			std::make_pair(countourGround[3] - countourFigure[1], countourGround[3] - countourFigure[1]),
			std::make_pair(countourGround[2] + countourFigure[1], countourGround[3] - countourFigure[1])
		};
	}

	else if (rcc8 == RCC8::DC)
	{
		// ranges for axis1
		setsOfRanges[0] = { std::make_pair(countourGround[0] - /*inf*/3 * countourFigure[0], countourGround[0] - countourFigure[0]),
			std::make_pair(countourGround[1] + countourFigure[0], /*inf*/countourGround[1] + abs(2 * countourGround[1])) };
		// ranges for axis2
		setsOfRanges[1] = { std::make_pair(countourGround[2] - /*inf*/abs(3 * countourFigure[1]), countourGround[2] -countourFigure[1]),
			std::make_pair(countourGround[3] + countourFigure[1], countourGround[3] + /*inf*/abs(2 * countourGround[3])) };
	}

	else if (rcc8 == RCC8::EC)
	{
		setsOfRanges[0] = { std::make_pair(countourGround[0] - abs(countourFigure[0]), countourGround[0] - abs(countourFigure[0])),
			std::make_pair(countourGround[1] + abs(countourFigure[0]), countourGround[1] + abs(countourFigure[0])),
			std::make_pair(countourGround[0] + abs(countourFigure[0]), countourGround[1] - abs(countourFigure[0])) };
		setsOfRanges[1] = { std::make_pair(countourGround[2] - abs(countourFigure[1]), countourGround[2] - abs(countourFigure[1])),
			std::make_pair(countourGround[3] + abs(countourFigure[1]), countourGround[3] + abs(countourFigure[1])),
			std::make_pair(countourGround[2] + abs(countourFigure[1]), countourGround[3] - abs(countourFigure[1])) };
	}

	else if (rcc8 == RCC8::PO)
	{
		// ranges for axis1
		setsOfRanges[0] = { std::make_pair(countourGround[0], countourGround[0]),
			std::make_pair(countourGround[1], countourGround[1]),
			std::make_pair(countourGround[0], countourGround[1]) };
		// ranges for axis2
		setsOfRanges[1] = { std::make_pair(countourGround[2], countourGround[2]),
			std::make_pair(countourGround[3], countourGround[3]),
			std::make_pair(countourGround[2], countourGround[3]) };
	}
	else if (rcc8 == RCC8::EQ)
	{
		// here we return only one point center of countourGround
		//get center of a plane box
		// ranges for axis1
		setsOfRanges[0] = { std::make_pair((countourGround[0] + countourGround[1]) / 2, (countourGround[0] + countourGround[1]) / 2) };
		// ranges for axis2

		setsOfRanges[1] = { std::make_pair((countourGround[2] + countourGround[3]) / 2, (countourGround[2] + countourGround[3]) / 2) };
	}

	return setsOfRanges;

}

Quat GeometricalState::CalculateQuat(EulerAngles& rotation, OrientationPredicates orientSymb)
{
	Quat quaternion;
	// for StraightAlongX and StraightAlongY create quarternion
	//1)first set pitch = -90 and yaw = 0 and then we can rotate aroung X axes -180<roll<180 => straight along X
	//Vec3f t(0, 0, 130);<=roll
	//Vec3f t1(90, 0, 0);<=pitch, yaw=0

	//2)first set roll = 90 and yaw = 0 and then we can rotate aroung Y axes -180<pitch<180 => straight along Y
	//Vec3f t(0,0,90);
	//Vec3f t1(0, 90, 0);

	//3)first set roll = 0 and pitch = 0 and then we can rotate aroung Z axes -180<yaw<180 => straight along Z
	//Vec3f t(0,90,0);
	//Vec3f t1(0, 0, 0);

	if ((orientSymb == OrientationPredicates::STRAIGHTALONGX)||(orientSymb == OrientationPredicates::INVERTEDALONGX))
	{
		//quaternion = Quat(0.f, 0.f, rotation.x, 1.f) * Quat(rotation.z, rotation.y, 0.f, 1.f);// (tmpPose.rotation.Pitch, tmpPose.rotation.Yaw, 0);
		quaternion = makeQuat(EulerAngles(rotation.roll, 0.f, 0.f)) * makeQuat(EulerAngles(0.f, rotation.pitch, rotation.yaw));
	}
	else if (orientSymb == OrientationPredicates::PARALLELXY)
	{
		quaternion = makeQuat(EulerAngles(rotation.roll, 0.f, 0.f)) * makeQuat(EulerAngles( 0.f, rotation.pitch, 0.f)) * Quat(90.f, 0.f, 0.f, 1.f);// (tmpPose.rotation.Pitch, tmpPose.rotation.Yaw, 0);
	}
	else if ((orientSymb == OrientationPredicates::STRAIGHTALONGY) || (orientSymb == OrientationPredicates::INVERTEDALONGY))
	{
		quaternion = makeQuat(EulerAngles(0.f, 0.f, rotation.yaw)) * makeQuat(EulerAngles(rotation.roll, rotation.pitch, 0.0f));// (tmpPose.rotation.Pitch, tmpPose.rotation.Yaw, 0);
	}
	else if	(orientSymb == OrientationPredicates::PARALLELYZ)
	{
		quaternion = makeQuat(EulerAngles(rotation.roll, 0.f, 0.f)) *  makeQuat(EulerAngles(0.f, rotation.pitch, 0.f));
	}
	else if ((orientSymb == OrientationPredicates::STRAIGHTALONGZ) || (orientSymb == OrientationPredicates::INVERTEDALONGZ))
	{
		quaternion = makeQuat(EulerAngles(0.f, rotation.pitch, 0.f)) *  makeQuat(EulerAngles(rotation.roll, 0.f, rotation.yaw));// (tmpPose.rotation.Pitch, tmpPose.rotation.Yaw, 0);
	}
	else if (orientSymb == OrientationPredicates::PARALLELXZ)
	{
		quaternion = makeQuat(EulerAngles(0.f, rotation.pitch, 0.f)) *  makeQuat(EulerAngles(0.f, 0.f, rotation.yaw));// (tmpPose.rotation.Pitch, tmpPose.rotation.Yaw, 0);
	}

	else
	{
		quaternion = makeQuat(rotation);
	}
	return quaternion;
}




