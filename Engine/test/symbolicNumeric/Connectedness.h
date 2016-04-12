#ifndef CONNECTEDNESS_H
#define CONNECTEDNESS_H

#include <vector>
using namespace std;
#include "math3d.h"

enum class RCC8 { DC = 1, EC = 2, TPP = 3, NTPP = 4, PO = 5, EQ = 6, TPPi = 7, NTPPi = 8 };
enum class ProjectionPlane { XY = 1, XZ = 2, YZ = 3 };
//enum class StyleAxis {X=1,Y=2,Z=3};
enum class ComparisonSymbol {
	EQ = 1, MT = 2, LT = 3, UNKNOWN = 4, maxMOEQminDO, maxMOEQmaxDO, minMOEQminDO, minMOEQmaxDO, maxMOMTmaxDO,
	minMOMTminDO, maxMOMTminDO, minMOMTmaxDO, maxMOLTmaxDO, minMOLTminDO, minMOLTmaxDO, maxMOLTminDO
};
enum class ConnectednessPredicates {
	NONE = 1, ABOVE, ALONG, BELOW, ABOVEEC, ALONGEC, BELOWEC, TANOVER, TANON, TANUNDER,
	OVER, ON, UNDER, PARTIALLYOVER, PARTIALLYON, PARTIALLYBELOW,
	OVERCOVERED, ONCOVERED, UNDERCOVERED, TANCIRCUMOVER, TANCIRCUMON, TANCIRCUMUNDER,
	CIRCUMOVER, CIRCUMON, CIRCUMUNDER, CLOSE,
	LEFTSIDE, RIGHTSIDE, LEFTSIDETOUCH, RIGHTSIDETOUCH, LEFTSIDEEC, RIGHTSIDEEC,
	TANLEFTOFTOUCH, TANRIGHTOFTOUCH, TANLEFTOF, TANRIGHTOF, LEFTOFTOUCH, RIGHTOFTOUCH, LEFTOF, RIGHTOF, PARTIALLYLEFTOF,
	PARTIALLYRIGHTOF, PARTIALLYLEFTOFTOUCH, PARTIALLYRIGHTOFTOUCH, LEFTOFTOUCHCOVERED, RIGHTOFTOUCHCOVERED,
	LEFTOFCOVERED, RIGHTOFCOVERED,
	BACKSIDE, FRONTSIDE, BACKSIDETOUCH, FRONTSIDETOUCH, BACKSIDEEC, FRONTSIDEEC, TANBEHINDTOUCH, TANINFRONTOFTOUCH,
	TANBEHIND, TANINFRONTOF, BEHINDTOUCH, INFRONTOFTOUCH, INFRONTOF, BEHIND, PARTIALLYBEHINDTOUCH,
	PARTIALLYINFRONTOFTOUCH, PARTIALLYBEHIND, PARTIALLYINFRONTOF, BEHINDTOUCHCOVERED, INFRONTOFTOUCHCOVERED,
	BEHINDCOVERED, INFRONTOFCOVERED, UNKNOWN

};


struct ConnectednessAspect
{
	RCC8 rcc8Relation;
	ProjectionPlane plane;
	//StyleAxis style;
	ComparisonSymbol comparison;

	ConnectednessAspect() { }

	ConnectednessAspect(RCC8 rcc8Relation, ProjectionPlane plane, ComparisonSymbol comparison)
	{
		this->rcc8Relation = rcc8Relation;
		this->plane = plane;
		//this->style = style;
		this->comparison = comparison;
	}
	void SetAspect(RCC8 rcc8Relation, ProjectionPlane plane, ComparisonSymbol comparison)
	{
		this->rcc8Relation = rcc8Relation;
		this->plane = plane;
		//this->style = style;
		this->comparison = comparison;
	}
};

struct BBox2D
{
	float top;
	float bottom;
	float left;
	float right;

	BBox2D() { };
	BBox2D(float t, float b, float l, float r)
		:top(t), bottom(b), left(l), right(r)
	{};
	void Init(float t, float b, float l, float r)
	{
		top = t;
		bottom = b;
		left = l;
		right = r;
	};
};
struct sortVectors
{
	std::vector<Vec2f> exteriorList;
	std::vector<Vec2f> boundaryList;
	std::vector<Vec2f> interiorList;
	//StyleAxis style;
	//ComparisonSymbol comparison;

	sortVectors() { }

};
class Connectedness
{
public:
	Connectedness();
	~Connectedness();
	ConnectednessPredicates getConnectednessFromAspect(ConnectednessAspect aspect);
	sortVectors sortFigObjVectors(BBox2D groundBB2D, BBox2D figureBB2D);
	std::vector<Vec2f> calculateFigureBoundaryPP(BBox2D figureBB2D);

	bool EvaluatePlanarDC(int exteriorNum, int boundaryNum, int interiorNum);
	bool EvaluatePlanarEC(int exteriorNum, int boundaryNum, int interiorNum);
	bool EvaluatePlanarTPP(int exteriorNum, int boundaryNum, int interiorNum);
	bool EvaluatePlanarNTPP(int exteriorNum, int boundaryNum, int interiorNum);
	bool EvaluatePlanarPO(int exteriorNum, int boundaryNum, int interiorNum);
	bool EvaluatePlanarEQ(int exteriorNum, int boundaryNum, int interiorNum);
	bool EvaluatePlanarNTPPi(int exteriorNum, int boundaryNum, int interiorNum);
	bool isPointOnBoundary(Vec2f P, BBox2D box);
	bool isPointInsideRactangle(Vec2f P, BBox2D box);
};



#endif // !CONNECTEDNESS_H