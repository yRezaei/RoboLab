#include "Connectedness.h"


Connectedness::Connectedness()
{
}


Connectedness::~Connectedness()
{
}
ConnectednessPredicates Connectedness::getConnectednessFromAspect(ConnectednessAspect aspect)
{
	ConnectednessPredicates connectedness = ConnectednessPredicates::UNKNOWN;
	// Plane XY
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::ABOVE;
	}
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::ALONG;
	}
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::BELOW;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::ABOVEEC;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::ALONGEC;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::BELOWEC;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::TANOVER;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::TANON;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::maxMOLTmaxDO)
	{
		connectedness = ConnectednessPredicates::TANUNDER;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::OVER;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::ON;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::maxMOLTmaxDO)
	{
		connectedness = ConnectednessPredicates::UNDER;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYOVER;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYON;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::maxMOLTmaxDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYBELOW;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::OVERCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::ONCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::maxMOLTmaxDO)
	{
		connectedness = ConnectednessPredicates::UNDERCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::TPPi&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::TANCIRCUMOVER;
	}
	if (aspect.rcc8Relation == RCC8::TPPi&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::TANCIRCUMON;
	}
	if (aspect.rcc8Relation == RCC8::TPPi&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::maxMOLTmaxDO)
	{
		connectedness = ConnectednessPredicates::TANCIRCUMUNDER;
	}
	if (aspect.rcc8Relation == RCC8::NTPPi&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::CIRCUMOVER;
	}
	if (aspect.rcc8Relation == RCC8::NTPPi&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::CIRCUMON;
	}
	if (aspect.rcc8Relation == RCC8::NTPPi&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::maxMOLTmaxDO)
	{
		connectedness = ConnectednessPredicates::CIRCUMUNDER;
	}
	if ((aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOMTminDO)||
	   (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XY&&aspect.comparison == ComparisonSymbol::minMOLTmaxDO))
	{
		connectedness = ConnectednessPredicates::CLOSE;
	}
	// plane YZ
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::LEFTSIDE;//change name add the new one
	}
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::RIGHTSIDE;//change name add the new one
	}
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::LEFTSIDE;
	}
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::RIGHTSIDE;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::LEFTSIDETOUCH;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::RIGHTSIDETOUCH;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::LEFTSIDEEC;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::RIGHTSIDEEC;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::TANLEFTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::TANRIGHTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::TANLEFTOF;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::TANRIGHTOF;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::LEFTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::RIGHTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::LEFTOF;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::RIGHTOF;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYLEFTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYRIGHTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYLEFTOF;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYRIGHTOF;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::LEFTOFTOUCHCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::RIGHTOFTOUCHCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::LEFTOFCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::YZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::RIGHTOFCOVERED;
	}
	
	// XZ
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::BACKSIDE;//change name add the new one
	}
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::FRONTSIDE;//change name add the new one
	}
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::BACKSIDE;
	}
	if (aspect.rcc8Relation == RCC8::DC&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::FRONTSIDE;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::BACKSIDETOUCH;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::FRONTSIDETOUCH;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::BACKSIDEEC;
	}
	if (aspect.rcc8Relation == RCC8::EC&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::FRONTSIDEEC;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::TANBEHINDTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::TANINFRONTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::TANBEHIND;
	}
	if (aspect.rcc8Relation == RCC8::TPP&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::TANINFRONTOF;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::BEHINDTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::INFRONTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::BEHIND;
	}
	if (aspect.rcc8Relation == RCC8::NTPP&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::INFRONTOF;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYBEHINDTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYINFRONTOFTOUCH;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYBEHIND;
	}
	if (aspect.rcc8Relation == RCC8::PO&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::PARTIALLYINFRONTOF;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOEQminDO)
	{
		connectedness = ConnectednessPredicates::BEHINDTOUCHCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOEQmaxDO)
	{
		connectedness = ConnectednessPredicates::INFRONTOFTOUCHCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::maxMOLTminDO)
	{
		connectedness = ConnectednessPredicates::BEHINDCOVERED;
	}
	if (aspect.rcc8Relation == RCC8::EQ&&aspect.plane == ProjectionPlane::XZ&&aspect.comparison == ComparisonSymbol::minMOMTmaxDO)
	{
		connectedness = ConnectednessPredicates::INFRONTOFCOVERED;
	}

	return connectedness;
}

sortVectors Connectedness::sortFigObjVectors(BBox2D groundBB2D, BBox2D figureBB2D)
{
	std::vector<Vec2f> figureBoundaryPP = calculateFigureBoundaryPP(figureBB2D);
	sortVectors returnValue;
	Vec2f A(groundBB2D.left, groundBB2D.bottom);
	Vec2f B(groundBB2D.left, groundBB2D.top);
	Vec2f C(groundBB2D.right, groundBB2D.top);
	Vec2f D(groundBB2D.right, groundBB2D.bottom);
	//float areaABCD = geometry.AreaRectangle(A, B, C, D);
	for (int i = 0; i < figureBoundaryPP.size(); i++)
	{
		Vec2f P = figureBoundaryPP[i];
		if (isPointOnBoundary(P, groundBB2D))
		{ 
			returnValue.boundaryList.push_back(P);
		}
		else {
		    // method using triangles
			/*float ABP = geometry.AreaTriangle(P, A, B);
			float BCP = geometry.AreaTriangle(P, B, C);
			float CDP = geometry.AreaTriangle(P, C, D);
			float DAP = geometry.AreaTriangle(P, D, A);
			*/
			std::vector<double> AP{ A.x - P.x, A.y - P.y };
			std::vector<double> AB{ A.x - B.x, A.y - B.y };
			std::vector<double> AD{ A.x - D.x, A.y - D.y };
			if ((0 < ScalarProduct(AP, AB) && 
				ScalarProduct(AP, AB)< ScalarProduct(AB, AB)) &&
				((0 < ScalarProduct(AP, AD)) && 
				(ScalarProduct(AP, AD) < ScalarProduct(AD, AD))))		
			/*
			if (geometry.ApproxEqual(areaABCD, (ABP + BCP + CDP + DAP)))*/
			{
				returnValue.interiorList.push_back(P);
			}
			else
			{
				returnValue.exteriorList.push_back(P);
			}
		}
	}
	return returnValue;

}
std::vector<Vec2f> Connectedness::calculateFigureBoundaryPP(BBox2D figureBB2D)
{
	float halfDistAx1 = Distance2D(figureBB2D.left, figureBB2D.right, figureBB2D.bottom, figureBB2D.bottom) / 2;
	float halfDistAx2 = Distance2D(figureBB2D.left, figureBB2D.left, figureBB2D.bottom, figureBB2D.top) / 2;
	return{ Vec2f(figureBB2D.left, figureBB2D.bottom), Vec2f(figureBB2D.right, figureBB2D.bottom),
		Vec2f(figureBB2D.left, figureBB2D.top), Vec2f(figureBB2D.right, figureBB2D.top),
		Vec2f(figureBB2D.left + halfDistAx1, figureBB2D.bottom), Vec2f(figureBB2D.left + halfDistAx1, figureBB2D.top),
		Vec2f(figureBB2D.left, figureBB2D.bottom + halfDistAx2), Vec2f(figureBB2D.right, figureBB2D.bottom + halfDistAx2)
	};
}

bool Connectedness::isPointOnBoundary(Vec2f P, BBox2D box)
{
	bool returnVal = (ApproxEqual(P.x, box.left) || ApproxEqual(P.x, box.right) ||
		ApproxEqual(P.y, box.top) || ApproxEqual(P.y, box.bottom));
	return returnVal;
}
bool Connectedness::isPointInsideRactangle(Vec2f P, BBox2D box)
{
	//bool returnVal = (geometry.ApproxEqual(P.axis1, box.left) || geometry.ApproxEqual(P.axis1, box.right) ||
	//	geometry.ApproxEqual(P.axis2, box.top) || geometry.ApproxEqual(P.axis2, box.bottom));
	Vec2f A(box.left, box.bottom);
	Vec2f B(box.left, box.top);
	//point2D C(groundBB2D.right, groundBB2D.top);
	Vec2f D(box.right, box.bottom);
	//Sbool returnVal = (0<geometry.ScalarProduct(A)
	//ScalarProduct
	return true;
}
bool Connectedness::EvaluatePlanarDC(int exteriorNum, int boundaryNum, int interiorNum)
{
	int total = exteriorNum + boundaryNum + interiorNum;
	if (exteriorNum == total) { return true; }
	else { return false; }
}
bool Connectedness::EvaluatePlanarEC(int exteriorNum, int boundaryNum, int interiorNum)
{
	//int total = exteriorNum + boundaryNum + interiorNum;
	if ((interiorNum == 0) && (exteriorNum > 0) && (boundaryNum > 0)){ return true; }
	else { return false; }
}
bool Connectedness::EvaluatePlanarTPP(int exteriorNum, int boundaryNum, int interiorNum)
{
	//int total = exteriorNum + boundaryNum + interiorNum;
	if ((interiorNum > 0) && (exteriorNum == 0) && (boundaryNum > 0)){ return true; }
	else { return false; }
}
bool Connectedness::EvaluatePlanarNTPP(int exteriorNum, int boundaryNum, int interiorNum)
{
	int total = exteriorNum + boundaryNum + interiorNum;
	if ((interiorNum == total) && (exteriorNum == 0) && (boundaryNum == 0)){ return true; }
	else { return false; }
}
bool Connectedness::EvaluatePlanarPO(int exteriorNum, int boundaryNum, int interiorNum)
{
	//int total = exteriorNum + boundaryNum + interiorNum;
	if ((interiorNum > 0) && (exteriorNum > 0) && (boundaryNum > 0)){ return true; }
	if ((interiorNum > 0) && (exteriorNum > 0) && (boundaryNum == 0)){ return true; }
	else { return false; }
}
bool Connectedness::EvaluatePlanarEQ(int exteriorNum, int boundaryNum, int interiorNum)
{
	//int total = exteriorNum + boundaryNum + interiorNum;
	if ((interiorNum > 0) && (exteriorNum == 0) && (boundaryNum > 0)){ return true; }
	else { return false; }
}


