#include "SymbolState.h"


SymbolState::SymbolState()
{
	declareConnectednessMap();
	declareConnectednessMapInv();
	declareOrientationMap();
	declareOrientationMapInv();
	declareRCC8MapInv();
}


SymbolState::~SymbolState()
{
}

void SymbolState::setOrientation(string orient, ExecutionState state)
{
	if (state == ExecutionState::INIT)//INIT STATE
	{
		if (orientationMap.count(orient) == 0) { 
 			orientInit = OrientationPredicates::ABITRARYORIENTATION; 
		}
		else { 
			orientInit = orientationMap[orient]; 
		}
	}
	else if (state == ExecutionState::GOAL)
	{
		if (orientationMap.count(orient) == 0) { orientGoal = OrientationPredicates::ABITRARYORIENTATION; }
		else { orientGoal = orientationMap[orient]; }
	}

}

void SymbolState::setConnectedness(string connect, ExecutionState state)
{
	if (state == ExecutionState::INIT)//INIT STATE
	{
		if (connectednessMap.count(connect) == 0) { connectInit = ConnectednessPredicates::NONE; }
		else { connectInit = connectednessMap[connect]; }
	}
	else if (state == ExecutionState::GOAL)
	{
		if (connectednessMap.count(connect) == 0) { connectGoal = ConnectednessPredicates::NONE; }
		else { connectGoal = connectednessMap[connect]; }
	}
}

void SymbolState::setRelativeDist(float dist[2], ExecutionState state)
{
	if (state == ExecutionState::GOAL){ return; } // GOAL state does not have Relative distance aspect
	distInit[0] = dist[0];
}

void SymbolState::setRelativeDist(string dist, ExecutionState state)
{
	if (state == ExecutionState::GOAL){	return;	} // GOAL state does not have Relative distance aspect
	//std::vector<std::string> limits;
	std::string::size_type sz;     // alias of size_t
	//float test[2];
	distInit[0] = std::stof(dist, &sz);
	distInit[1] = std::stof(dist.substr(sz));
}

OrientationPredicates SymbolState::getOrientation(ExecutionState state)
{
	if (state == ExecutionState::INIT)//INIT STATE
	{
		return orientInit;
	}
	else // (state == ExecutionState::GOAL)
	{
		return orientGoal;
	}

}

ConnectednessPredicates SymbolState::getConnectedness(ExecutionState state)
{
	if (state == ExecutionState::INIT)//INIT STATE
	{
		return connectInit;
	}
	else // (state == ExecutionState::GOAL)
	{
		return connectGoal;
	}
}

void SymbolState::declareConnectednessMap()
{
	//CHANGE
	connectednessMap["Above"] = ConnectednessPredicates::ABOVE;
	connectednessMap["Along"] = ConnectednessPredicates::ALONG;
	connectednessMap["Below"] = ConnectednessPredicates::BELOW;
	connectednessMap["Above-EC"] = ConnectednessPredicates::ABOVEEC;
	connectednessMap["Along-EC"] = ConnectednessPredicates::ALONGEC;
	connectednessMap["Below-EC"] = ConnectednessPredicates::BELOWEC;
	connectednessMap["Tan-over"] = ConnectednessPredicates::TANOVER;
	connectednessMap["Tan-on"] = ConnectednessPredicates::TANON;
	connectednessMap["Tan-under"] = ConnectednessPredicates::TANUNDER;
	connectednessMap["Over"] = ConnectednessPredicates::OVER;
	connectednessMap["On"] = ConnectednessPredicates::ON;
	connectednessMap["Under"] = ConnectednessPredicates::UNDER;
	connectednessMap["Partially-over"] = ConnectednessPredicates::PARTIALLYOVER;
	connectednessMap["Partially-on"] = ConnectednessPredicates::PARTIALLYON;
	connectednessMap["Partially-below"] = ConnectednessPredicates::PARTIALLYBELOW;
	connectednessMap["Over-covered"] = ConnectednessPredicates::OVERCOVERED;
	connectednessMap["On-covered"] = ConnectednessPredicates::ONCOVERED;
	connectednessMap["Under-covered"] = ConnectednessPredicates::UNDERCOVERED;
	connectednessMap["Tan-circum-over"] = ConnectednessPredicates::TANCIRCUMOVER;
	connectednessMap["Tan-circum-on"] = ConnectednessPredicates::TANCIRCUMON;
	connectednessMap["Tan-circum-under"] = ConnectednessPredicates::TANCIRCUMUNDER;
	connectednessMap["Circum-over"] = ConnectednessPredicates::CIRCUMOVER;
	connectednessMap["Circum-on"] = ConnectednessPredicates::CIRCUMON;
	connectednessMap["Close"] = ConnectednessPredicates::CLOSE;
	connectednessMap["Left-side"] = ConnectednessPredicates::LEFTSIDE;
	connectednessMap["Right-side"] = ConnectednessPredicates::RIGHTSIDE;
	connectednessMap["Left-side-touch"] = ConnectednessPredicates::LEFTSIDETOUCH;
	connectednessMap["Right-side-touch"] = ConnectednessPredicates::RIGHTSIDETOUCH;
	connectednessMap["Left-side-EC"] = ConnectednessPredicates::LEFTSIDEEC;
	connectednessMap["Right-side-EC"] = ConnectednessPredicates::RIGHTSIDEEC;
	connectednessMap["Tan-leftof-touch"] = ConnectednessPredicates::TANLEFTOFTOUCH;
	connectednessMap["Tan-rightof-touch"] = ConnectednessPredicates::TANRIGHTOFTOUCH;
	connectednessMap["Tan-leftof"] = ConnectednessPredicates::TANLEFTOF;
	connectednessMap["Tan-rightof"] = ConnectednessPredicates::TANRIGHTOF;
	connectednessMap["Leftof-touch"] = ConnectednessPredicates::LEFTOFTOUCH;
	connectednessMap["Rightof-touch"] = ConnectednessPredicates::RIGHTOFTOUCH;
	connectednessMap["Left-of"] = ConnectednessPredicates::LEFTOF;
	connectednessMap["Right-of"] = ConnectednessPredicates::RIGHTOF;
	connectednessMap["Partially-leftof-touch"] = ConnectednessPredicates::PARTIALLYLEFTOFTOUCH;
	connectednessMap["Partially-rightof-touch"] = ConnectednessPredicates::PARTIALLYRIGHTOFTOUCH;
	connectednessMap["Partially-leftof"] = ConnectednessPredicates::PARTIALLYLEFTOF;
	connectednessMap["Partially-rightof"] = ConnectednessPredicates::PARTIALLYRIGHTOF;
	connectednessMap["Leftof-touch-covered"] = ConnectednessPredicates::LEFTOFTOUCHCOVERED;
	connectednessMap["Rightof-touch-covered"] = ConnectednessPredicates::RIGHTOFTOUCHCOVERED;
	connectednessMap["Leftof-covered"] = ConnectednessPredicates::LEFTOFCOVERED;
	connectednessMap["Rightof-covered"] = ConnectednessPredicates::RIGHTOFCOVERED;
	connectednessMap["Back-side"] = ConnectednessPredicates::BACKSIDE;
	connectednessMap["Front-side"] = ConnectednessPredicates::FRONTSIDE;
	connectednessMap["Back-side-touch"] = ConnectednessPredicates::BACKSIDETOUCH;
	connectednessMap["Front-side-touch"] = ConnectednessPredicates::FRONTSIDETOUCH;
	connectednessMap["Back-side-EC"] = ConnectednessPredicates::BACKSIDEEC;
	connectednessMap["Front-side-EC"] = ConnectednessPredicates::FRONTSIDEEC;
	connectednessMap["Tan-behind-touch"] = ConnectednessPredicates::TANBEHINDTOUCH;
	connectednessMap["Tan-infrontof-touch"] = ConnectednessPredicates::TANINFRONTOFTOUCH;
	connectednessMap["Tan-behind"] = ConnectednessPredicates::TANBEHIND;
	connectednessMap["Tan-infrontof"] = ConnectednessPredicates::TANINFRONTOF;
	connectednessMap["Behind-touch"] = ConnectednessPredicates::BEHINDTOUCH;
	connectednessMap["Infrontof-touch"] = ConnectednessPredicates::INFRONTOFTOUCH;
	connectednessMap["Behind"] = ConnectednessPredicates::BEHIND;
	connectednessMap["In-front-of"] = ConnectednessPredicates::INFRONTOF;
	connectednessMap["Partially-behind-touch"] = ConnectednessPredicates::PARTIALLYBEHINDTOUCH;
	connectednessMap["Partially-infrontof-touch"] = ConnectednessPredicates::PARTIALLYINFRONTOFTOUCH;
	connectednessMap["Partially-behind"] = ConnectednessPredicates::PARTIALLYBEHIND;
	connectednessMap["Partially-infrontof"] = ConnectednessPredicates::PARTIALLYINFRONTOF;
	connectednessMap["Behind-touch-covered"] = ConnectednessPredicates::BEHINDTOUCHCOVERED;
	connectednessMap["Infrontof-touch-covered"] = ConnectednessPredicates::INFRONTOFTOUCHCOVERED;
	connectednessMap["Behind-covered"] = ConnectednessPredicates::BEHINDCOVERED;
	connectednessMap["Infrontof-covered"] = ConnectednessPredicates::INFRONTOFCOVERED;

}
void SymbolState::declareConnectednessMapInv()
{
	//CHANGE
	connectednessMapInv[ConnectednessPredicates::ABOVE] = "Above";
	connectednessMapInv[ConnectednessPredicates::ALONG] = "Along";
	connectednessMapInv[ConnectednessPredicates::BELOW] = "Below";
	connectednessMapInv[ConnectednessPredicates::ABOVEEC] = "Above-EC";
	connectednessMapInv[ConnectednessPredicates::ALONGEC] = "Along-EC";
	connectednessMapInv[ConnectednessPredicates::BELOWEC] = "Below-EC";
	connectednessMapInv[ConnectednessPredicates::TANOVER] = "Tan-over";
	connectednessMapInv[ConnectednessPredicates::TANON] = "Tan-on";
	connectednessMapInv[ConnectednessPredicates::TANUNDER] = "Tan-under";
	connectednessMapInv[ConnectednessPredicates::OVER] = "Over";
	connectednessMapInv[ConnectednessPredicates::ON] = "On";
	connectednessMapInv[ConnectednessPredicates::UNDER] = "Under";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYOVER] = "Partially-over";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYON] = "Partially-on";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYBELOW] = "Partially-below";
	connectednessMapInv[ConnectednessPredicates::OVERCOVERED] = "Over-covered";
	connectednessMapInv[ConnectednessPredicates::ONCOVERED] = "On-covered";
	connectednessMapInv[ConnectednessPredicates::UNDERCOVERED] = "Under-covered";
	connectednessMapInv[ConnectednessPredicates::TANCIRCUMOVER] = "Tan-circum-over";
	connectednessMapInv[ConnectednessPredicates::TANCIRCUMON] = "Tan-circum-on";
	connectednessMapInv[ConnectednessPredicates::TANCIRCUMUNDER] = "Tan-circum-under";
	connectednessMapInv[ConnectednessPredicates::CIRCUMOVER] = "Circum-over";
	connectednessMapInv[ConnectednessPredicates::CIRCUMON] = "Circum-on";
	connectednessMapInv[ConnectednessPredicates::CIRCUMUNDER] = "Circum-under";
	connectednessMapInv[ConnectednessPredicates::CLOSE] = "Close";
	connectednessMapInv[ConnectednessPredicates::UNKNOWN] = "Unknown";
	connectednessMapInv[ConnectednessPredicates::LEFTSIDE] = "Left-side";
	connectednessMapInv[ConnectednessPredicates::RIGHTSIDE] = "Right-side";
	connectednessMapInv[ConnectednessPredicates::LEFTSIDETOUCH] = "Left-side-touch";
	connectednessMapInv[ConnectednessPredicates::RIGHTSIDETOUCH] = "Right-side-touch";
	connectednessMapInv[ConnectednessPredicates::LEFTSIDEEC] = "Left-side-EC";
	connectednessMapInv[ConnectednessPredicates::RIGHTSIDEEC] = "Right-side-EC";
	connectednessMapInv[ConnectednessPredicates::TANLEFTOFTOUCH] = "Tan-leftof-touch";
	connectednessMapInv[ConnectednessPredicates::TANRIGHTOFTOUCH] = "Tan-rightof-touch";
	connectednessMapInv[ConnectednessPredicates::TANLEFTOF] ="Tan-leftof";
	connectednessMapInv[ConnectednessPredicates::TANRIGHTOF] = "Tan-rightof";
	connectednessMapInv[ConnectednessPredicates::LEFTOFTOUCH] = "Leftof-touch";
	connectednessMapInv[ConnectednessPredicates::RIGHTOFTOUCH] = "Rightof-touch";
	connectednessMapInv[ConnectednessPredicates::LEFTOF] = "Left-of";
	connectednessMapInv[ConnectednessPredicates::RIGHTOF] = "Right-of";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYLEFTOFTOUCH] = "Partially-leftof-touch";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYRIGHTOFTOUCH] = "Partially-rightof-touch";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYLEFTOF] = "Partially-leftof";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYRIGHTOF] = "Partially-rightof";
	connectednessMapInv[ConnectednessPredicates::LEFTOFTOUCHCOVERED] = "Leftof-touch-covered";
	connectednessMapInv[ConnectednessPredicates::RIGHTOFTOUCHCOVERED] = "Rightof-touch-covered";
	connectednessMapInv[ConnectednessPredicates::LEFTOFCOVERED] = "Leftof-covered";
	connectednessMapInv[ConnectednessPredicates::RIGHTOFCOVERED] = "Rightof-covered";
	connectednessMapInv[ConnectednessPredicates::BACKSIDE] = "Back-side";
	connectednessMapInv[ConnectednessPredicates::FRONTSIDE] = "Front-side";
	connectednessMapInv[ConnectednessPredicates::BACKSIDETOUCH] = "Back-side-touch";
	connectednessMapInv[ConnectednessPredicates::FRONTSIDETOUCH] = "Front-side-touch";
	connectednessMapInv[ConnectednessPredicates::BACKSIDEEC] = "Back-side-EC";
	connectednessMapInv[ConnectednessPredicates::FRONTSIDEEC] = "Front-side-EC";
	connectednessMapInv[ConnectednessPredicates::TANBEHINDTOUCH] = "Tan-behind-touch";
	connectednessMapInv[ConnectednessPredicates::TANINFRONTOFTOUCH] = "Tan-infrontof-touch";
	connectednessMapInv[ConnectednessPredicates::TANBEHIND] = "Tan-behind";
	connectednessMapInv[ConnectednessPredicates::TANINFRONTOF] = "Tan-infrontof";
	connectednessMapInv[ConnectednessPredicates::BEHINDTOUCH] = "Behind-touch";
	connectednessMapInv[ConnectednessPredicates::INFRONTOFTOUCH] = "Infrontof-touch";
	connectednessMapInv[ConnectednessPredicates::BEHIND] = "Behind";
	connectednessMapInv[ConnectednessPredicates::INFRONTOF] = "In-front-of";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYBEHINDTOUCH] = "Partially-behind-touch";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYINFRONTOFTOUCH] = "Partially-infrontof-touch";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYBEHIND] = "Partially-behind";
	connectednessMapInv[ConnectednessPredicates::PARTIALLYINFRONTOF] = "Partially-infrontof";
	connectednessMapInv[ConnectednessPredicates::BEHINDTOUCHCOVERED] = "Behind-touch-covered";
	connectednessMapInv[ConnectednessPredicates::INFRONTOFTOUCHCOVERED] = "Infrontof-touch-covered";
	connectednessMapInv[ConnectednessPredicates::BEHINDCOVERED] = "Behind-covered";
	connectednessMapInv[ConnectednessPredicates::INFRONTOFCOVERED] = "Infrontof-covered";

}

void SymbolState::declareOrientationMap()
{
	orientationMap["ArbitraryOrientation"] = OrientationPredicates::ABITRARYORIENTATION;
	orientationMap["Parallel-xy"] = OrientationPredicates::PARALLELXY;
	orientationMap["Parallel-xz"] = OrientationPredicates::PARALLELXZ;
	orientationMap["Parallel-yz"] = OrientationPredicates::PARALLELYZ;
	orientationMap["StraightAlong-x"] = OrientationPredicates::STRAIGHTALONGX;
	orientationMap["StraightAlong-y"] = OrientationPredicates::STRAIGHTALONGY;
	orientationMap["StraightAlong-z"] = OrientationPredicates::STRAIGHTALONGZ;
	orientationMap["InvertedAlong-x"] = OrientationPredicates::INVERTEDALONGX;
	orientationMap["InvertedAlong-y"] = OrientationPredicates::INVERTEDALONGY;
	orientationMap["InvertedAlong-z"] = OrientationPredicates::INVERTEDALONGZ;
}
void SymbolState::declareOrientationMapInv()
{
	//std::vector<std::pair<float, float>> limX;
	orientationMapInv[OrientationPredicates::ABITRARYORIENTATION] = "ArbitraryOrientation";
	orientationMapInv[OrientationPredicates::PARALLELXY] = "Parallel-xy";
	orientationMapInv[OrientationPredicates::PARALLELXZ] = "Parallel-xz";
	orientationMapInv[OrientationPredicates::PARALLELYZ] = "Parallel-yz";
	orientationMapInv[OrientationPredicates::STRAIGHTALONGX] = "StraightAlong-x";
	orientationMapInv[OrientationPredicates::STRAIGHTALONGY] = "StraightAlong-y";
	orientationMapInv[OrientationPredicates::STRAIGHTALONGZ] = "StraightAlong-z";
	orientationMapInv[OrientationPredicates::INVERTEDALONGX] = "InvertedAlong-x";
	orientationMapInv[OrientationPredicates::INVERTEDALONGY] = "InvertedAlong-y";
	orientationMapInv[OrientationPredicates::INVERTEDALONGZ] = "InvertedAlong-z";
}
void SymbolState::declareRCC8MapInv()
{
	RCC8MapInv[RCC8::DC] = "DC";
	RCC8MapInv[RCC8::EC] = "EC";
	RCC8MapInv[RCC8::EQ] = "EQ";
	RCC8MapInv[RCC8::NTPP] = "NTPP";
	RCC8MapInv[RCC8::NTPPi] = "NTPPi";
	RCC8MapInv[RCC8::PO] = "PO";
	RCC8MapInv[RCC8::TPP] = "TPP";
	RCC8MapInv[RCC8::TPPi] = "TPPi";
}
OrientationPredicates SymbolState::convertRotation2Symb(EulerAngles orientation)
{
	OrientationPredicates sympolFormula;
	float sa = SMALLEST_ANGLE*MPI / 180;
	const double halfC = 180 / MPI; // parameter to convert degree to radian

	//if ((orientation.pitch<((3 * MPI / 4) + sa)*halfC && orientation.pitch>((MPI / 4) - sa)*halfC) && // Pitch close to Zero 
	//	(orientation.yaw<((MPI / 16) + sa)*halfC && orientation.yaw > ((-MPI / 16) - sa)*halfC))
	if ( (orientation.pitch < ((17 * MPI / 16) + sa)*halfC && orientation.pitch > ((15*MPI / 16) - sa)*halfC) && // Pitch close to Zero 
		(orientation.yaw < ((MPI / 16) + sa)*halfC && orientation.yaw > ((-MPI / 16) - sa)*halfC) )
	{
		sympolFormula = OrientationPredicates::STRAIGHTALONGX;
	}
	else if ((orientation.roll < ((-MPI / 4) + sa)*halfC && orientation.roll > ((-3 * MPI / 4) - sa)*halfC) && // Pitch close to Zero 
		(orientation.yaw < ((MPI / 16) + sa)*halfC && orientation.yaw > ((-MPI / 16) - sa)*halfC))
	{
		sympolFormula = OrientationPredicates::STRAIGHTALONGY;
	}
	//else if ((orientation.roll<(MPI / 25)*halfC && orientation.roll>(-MPI / 25)*halfC) && // Pitch close to Zero 
	//	(orientation.pitch<(MPI / 25)*halfC && orientation.pitch >(-MPI / 25)*halfC))
	else if ((orientation.roll < ((MPI / 16) + sa)*halfC && orientation.roll > (-(MPI / 16) - sa)*halfC) && // Pitch close to Zero 
		(orientation.pitch < ((MPI / 16)+sa)*halfC && orientation.pitch > ((-MPI / 16)-sa)*halfC))
	{
		sympolFormula = OrientationPredicates::STRAIGHTALONGZ;
	}
	else if ((orientation.pitch < ((7 * MPI / 4) + sa)*halfC && orientation.pitch > ((5 * MPI / 4) - sa)*halfC) && // Pitch close to Zero 
		(orientation.yaw < ((MPI / 16) + sa)*halfC && orientation.yaw > ((-MPI / 16) - sa)*halfC))
	{
		sympolFormula = OrientationPredicates::INVERTEDALONGX;
	}
	else if ((orientation.roll < (3 * MPI / 4 + sa)*halfC && orientation.roll > (MPI / 4 - sa)*halfC) && // Pitch close to Zero 
		(orientation.yaw < ((MPI / 16) + sa)*halfC && orientation.yaw > ((-MPI / 16) - sa)*halfC))
	{
		sympolFormula = OrientationPredicates::INVERTEDALONGY;
	}
	else if ((orientation.roll < ((17 * MPI / 16) +sa)*halfC && orientation.roll > ((15 * MPI / 16)-sa)*halfC) // ||
		//(orientation.roll>((17 * MPI / 16)-sa)*halfC && orientation.roll<((15 * MPI / 16)+sa)*halfC)) // Pitch close to Zero 
		&& (orientation.pitch < ((MPI / 16)+sa)*halfC && orientation.pitch > (-(MPI / 16)-sa)*halfC))
	{
		//orientLimits[0] = FRotator((-MPI / 16)*halfC, -MPI*halfC, (15 * MPI / 16)*halfC);
		//orientLimits[1] = FRotator((MPI / 16)*halfC, MPI*halfC, (17 * MPI / 16)*halfC);

		sympolFormula = OrientationPredicates::INVERTEDALONGZ;
	}
	else if ((orientation.roll < (MPI / 4 + sa)*halfC && orientation.roll  >(-MPI / 4 - sa)*halfC) && // Pitch close to Zero 
		(orientation.pitch < (MPI / 4 + sa)*halfC && orientation.pitch > (-MPI / 4 - sa)*halfC))
	{
		sympolFormula = OrientationPredicates::PARALLELXY;
	}
	else if ((orientation.pitch < (MPI / 4 + sa)*halfC && orientation.pitch > (-MPI / 4 - sa)*halfC) && // Pitch close to Zero 
		(orientation.yaw < (MPI / 4 + sa)*halfC && orientation.yaw > (-MPI / 4 - sa)*halfC))
	{
		sympolFormula = OrientationPredicates::PARALLELYZ;
	}
	else if ((orientation.roll < (MPI / 4 + sa)*halfC && orientation.roll > (-MPI / 4 - sa)*halfC) && // Pitch close to Zero 
		(orientation.yaw < (MPI / 4 + sa)*halfC && orientation.yaw > (-MPI / 4 - sa)*halfC))
	{
		sympolFormula = OrientationPredicates::PARALLELXZ;
	}
	else
	{
		sympolFormula = OrientationPredicates::ABITRARYORIENTATION;
	}

	return sympolFormula;
}
OrientationPredicates SymbolState::convertQuat2Symb(Quat quaternion)
{
	OrientationPredicates sympolFormula = OrientationPredicates::ABITRARYORIENTATION;
	// introduce unit vectors
	Vec3f zV(0, 0, 1), xV(1, 0, 0), yV(0, 1, 0);
	// rotating unit vectors with quatanion of the object
	Vec3f zR;
	zR = Vec3f((makeMat4(quaternion) * makeMat4(Vec3f(zV)))[3]);//.RotateVector(zV);
	float zRxV, zRyV, zRzV;

	zRxV = glm::dot(zR, xV);
	zRyV = glm::dot(zR, yV);
	zRzV = glm::dot(zR, zV);
	bool zRparallelX = ApproxEqual(zRxV, 1.0); // zR parallel to X
	bool zRantiparallelX = ApproxEqual(zRxV, -1.0);
	if (zRparallelX) // zR parallel to X
	{
		sympolFormula = OrientationPredicates::STRAIGHTALONGX;
		return sympolFormula;
	}
	if (zRantiparallelX) // zR antiparallel to X
	{
		sympolFormula = OrientationPredicates::INVERTEDALONGX;
		return sympolFormula;
	}
	bool zRparallelY = ApproxEqual(zRyV, 1.0); // zR parallel to Y
	bool zRantiparallelY = ApproxEqual(zRyV, -1.0);

	if (zRparallelY) // zR parallel to Y
	{
		sympolFormula = OrientationPredicates::STRAIGHTALONGY;
		return sympolFormula;
	}
	if (zRantiparallelY) // zR antiparallel to Y
	{
		sympolFormula = OrientationPredicates::INVERTEDALONGY;
		return sympolFormula;
	}
	bool zRparallelZ = ApproxEqual(zRzV, 1.0); // zR parallel to Z
	bool zRantiparallelZ = ApproxEqual(zRzV, -1.0);

	if (zRparallelZ) // zR parallel to Z
	{
		sympolFormula = OrientationPredicates::STRAIGHTALONGZ;
		return sympolFormula;
	}
	if (zRantiparallelZ) // zR antiparallel to Z
	{
		sympolFormula = OrientationPredicates::INVERTEDALONGZ;
		return sympolFormula;
	}
	bool zRorthZ = ApproxEqual(zRzV, 0);
	if (zRorthZ && !zRparallelX&&!zRparallelY&&!zRantiparallelX&&!zRantiparallelY) // zR orthogonal Z
	{
		sympolFormula = OrientationPredicates::PARALLELXY;
		return sympolFormula;
	}
	bool zRorthX = ApproxEqual(zRxV, 0);
	if (zRorthX && !zRparallelY&&!zRparallelZ&&!zRantiparallelZ&&!zRantiparallelY) // zR orthogonal X
	{
		sympolFormula = OrientationPredicates::PARALLELYZ;
		return sympolFormula;
	}
	bool zRorthY = ApproxEqual(zRyV, 0);
	if (zRorthY && !zRparallelX&&!zRparallelZ&&!zRantiparallelZ&&!zRantiparallelX) // zR orthogonal Y
	{
		sympolFormula = OrientationPredicates::PARALLELXZ;
		return sympolFormula;
	}
	return sympolFormula;
}
std::vector<ConnectednessPredicates> SymbolState::convertPosition2Symb(Bounds bbFigure, Bounds bbObj)
{
	std::vector<ConnectednessPredicates> returnPredicates(3);
	ConnectednessAspect forXYplane;
	ConnectednessAspect forYZplane;
	ConnectednessAspect forXZplane;
	forXYplane.plane = ProjectionPlane::XY;
	forYZplane.plane = ProjectionPlane::YZ;
	forXZplane.plane = ProjectionPlane::XZ;
	// get RCC8 description
	//BBox2D groundBB2D, figureBB2D;
	Vec3f figCenter = bbFigure.center();


	BBox2D groundXYBB2D(bbObj.getMin().y, bbObj.getMin().y, bbObj.getMin().x, bbObj.getMax().x);
	BBox2D figureXYBB2D(bbFigure.getMax().y, bbFigure.getMin().y, bbFigure.getMin().x, bbFigure.getMax().x);
	BBox2D groundXZBB2D(bbObj.getMax().z, bbObj.getMin().z, bbObj.getMin().x, bbObj.getMax().x);
	BBox2D figureXZBB2D(bbFigure.getMax().z, bbFigure.getMin().z, bbFigure.getMin().x, bbFigure.getMax().x);
	BBox2D groundYZBB2D(bbObj.getMax().z, bbObj.getMin().z, bbObj.getMin().y, bbObj.getMax().y);
	BBox2D figureYZBB2D(bbFigure.getMax().z, bbFigure.getMin().z, bbFigure.getMin().y, bbFigure.getMax().y);
	float groundZ[] = { bbObj.getMin().z, bbObj.getMax().z };
	float groundY[] = { bbObj.getMin().y, bbObj.getMax().y };
	float groundX[] = { bbObj.getMin().x, bbObj.getMax().x };
	float figZ[] = { bbFigure.getMin().z, bbFigure.getMax().z };
	float figY[] = { bbFigure.getMin().y, bbFigure.getMax().y };
	float figX[] = { bbFigure.getMin().x, bbFigure.getMax().x };
	forXYplane.rcc8Relation = convertGeom2RCC8(groundXYBB2D, figureXYBB2D);
	forXZplane.rcc8Relation = convertGeom2RCC8(groundXZBB2D, figureXZBB2D);
	forYZplane.rcc8Relation = convertGeom2RCC8(groundYZBB2D, figureYZBB2D);
	forXYplane.comparison = convertGeom2Comparison(groundZ, figZ);
	forXZplane.comparison = convertGeom2Comparison(groundY, figY);
	forYZplane.comparison = convertGeom2Comparison(groundX, figX);
	ConnectednessPredicates predicate4XY = connectedness.getConnectednessFromAspect(forXYplane);
	ConnectednessPredicates predicate4XZ = connectedness.getConnectednessFromAspect(forXZplane);
	ConnectednessPredicates predicate4YZ = connectedness.getConnectednessFromAspect(forYZplane);
	// return array of predicates
	//returnPredicates.push_back(predicate4XY, predicate4XZ, predicate4YZ);
	//

	return { predicate4XY, predicate4XZ, predicate4YZ };
}
ConnectednessPredicates SymbolState::convertLocation2Symb(Bounds bbFigure, Bounds bbGround, Vec3f location)
{
	//ConnectednessPredicates outputPredicate = ConnectednessPredicates::ABOVE;
	ConnectednessAspect forXYplane;
	ConnectednessAspect forYZplane;
	ConnectednessAspect forXZplane;
	forXYplane.plane = ProjectionPlane::XY;
	forYZplane.plane = ProjectionPlane::YZ;
	forXZplane.plane = ProjectionPlane::XZ;
	// get RCC8 description
	//BBox2D groundBB2D, figureBB2D;
	Vec3f figCenter = bbFigure.center();

	
	BBox2D groundXYBB2D(bbGround.getMax().y, bbGround.getMin().y, bbGround.getMin().x, bbGround.getMax().x);
	BBox2D figureXYBB2D(bbFigure.getMax().y, bbFigure.getMin().y, bbFigure.getMin().x, bbFigure.getMax().x);
	BBox2D groundXZBB2D(bbGround.getMax().z, bbGround.getMin().z, bbGround.getMin().x, bbGround.getMax().x);
	BBox2D figureXZBB2D(bbFigure.getMax().z, bbFigure.getMin().z, bbFigure.getMin().x, bbFigure.getMax().x);
	BBox2D groundYZBB2D(bbGround.getMax().z, bbGround.getMin().z, bbGround.getMin().y, bbGround.getMax().y);
	BBox2D figureYZBB2D(bbFigure.getMax().z, bbFigure.getMin().z, bbFigure.getMin().y, bbFigure.getMax().y);
	float groundZ[] = { bbGround.getMin().z, bbGround.getMax().z };
	float groundY[] = { bbGround.getMin().y, bbGround.getMax().y };
	float groundX[] = { bbGround.getMin().x, bbGround.getMax().x };
	float figZ[] = { bbFigure.getMin().z, bbFigure.getMax().z };
	float figY[] = { bbFigure.getMin().y, bbFigure.getMax().y };
	float figX[] = { bbFigure.getMin().x, bbFigure.getMax().x };
	forXYplane.rcc8Relation = convertGeom2RCC8(groundXYBB2D, figureXYBB2D);
	forXZplane.rcc8Relation = convertGeom2RCC8(groundXZBB2D, figureXZBB2D);
	forYZplane.rcc8Relation = convertGeom2RCC8(groundYZBB2D, figureYZBB2D);
	forXYplane.comparison = convertGeom2Comparison(groundZ, figZ);
	forXZplane.comparison = convertGeom2Comparison(groundY, figY);
	forYZplane.comparison = convertGeom2Comparison(groundX, figX);
	ConnectednessPredicates predicate4XY = connectedness.getConnectednessFromAspect(forXYplane);
	ConnectednessPredicates predicate4XZ = connectedness.getConnectednessFromAspect(forXZplane);
	ConnectednessPredicates predicate4YZ = connectedness.getConnectednessFromAspect(forYZplane);
	// return array of predicates

	//
	return predicate4XY;
}
ConnectednessPredicates SymbolState::getConnectednessFromRCC8Comparison(RCC8 rcc8, ComparisonSymbol comparison, ProjectionPlane plane)
{
	ConnectednessAspect aspect;
	aspect.rcc8Relation = rcc8;
	aspect.comparison = comparison;
	aspect.plane = plane;
	return connectedness.getConnectednessFromAspect(aspect);
}

RCC8 SymbolState::getRCC8(Bounds bbFigure, Bounds bbGround, ProjectionPlane plane)
{
	BBox2D groundBB2D;
	BBox2D figureBB2D;
	if (plane == ProjectionPlane::XY)
	{
		groundBB2D.Init(bbGround.getMax().y, bbGround.getMin().y, bbGround.getMin().x, bbGround.getMax().x);
		figureBB2D.Init(bbFigure.getMax().y, bbFigure.getMin().y, bbFigure.getMin().x, bbFigure.getMax().x);
	}
	else if (plane == ProjectionPlane::XZ)
	{
		groundBB2D.Init(bbGround.getMax().z, bbGround.getMin().z, bbGround.getMin().x, bbGround.getMax().x);
		figureBB2D.Init(bbFigure.getMax().z, bbFigure.getMin().z, bbFigure.getMin().x, bbFigure.getMax().x);
	}
	else if (plane == ProjectionPlane::YZ)
	{
		groundBB2D.Init(bbGround.getMax().z, bbGround.getMin().z, bbGround.getMin().y, bbGround.getMax().y);
		figureBB2D.Init(bbFigure.getMax().z, bbFigure.getMin().z, bbFigure.getMin().y, bbFigure.getMax().y);
	}
	return convertGeom2RCC8(groundBB2D, figureBB2D);
}
ComparisonSymbol SymbolState::getComparison(Bounds bbFigure, Bounds bbGround, ProjectionPlane plane)
{
	float groundStyle[2];
	float figureStyle[2];
	if (plane == ProjectionPlane::XY)
	{
		groundStyle[0] = bbGround.getMin().z;
		groundStyle[1] = bbGround.getMax().z;
		figureStyle[0] = bbFigure.getMin().z;
		figureStyle[1] = bbFigure.getMax().z;
	}
	else if (plane == ProjectionPlane::XZ)
	{
		groundStyle[0] = bbGround.getMin().y;
		groundStyle[1] = bbGround.getMax().y;
		figureStyle[0] = bbFigure.getMin().y;
		figureStyle[1] = bbFigure.getMax().y;
	}
	else if (plane == ProjectionPlane::YZ)
	{
		groundStyle[0] = bbGround.getMin().x;
		groundStyle[1] = bbGround.getMax().x;
		figureStyle[0] = bbFigure.getMin().x;
		figureStyle[1] = bbFigure.getMax().x;
	}
	return convertGeom2Comparison(groundStyle, figureStyle);
}
RCC8 SymbolState::convertGeom2RCC8(BBox2D groundBB2D, BBox2D figureBB2D)
{
	RCC8 rcc8 = RCC8::DC;
	sortVectors vectorList = connectedness.sortFigObjVectors(groundBB2D, figureBB2D);
	if (connectedness.EvaluatePlanarDC((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size()))
	{
		rcc8 = RCC8::DC;
	}
	else if (connectedness.EvaluatePlanarEC((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size()))
	{
		rcc8 = RCC8::EC;
	}
	else if (connectedness.EvaluatePlanarTPP((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size()))
	{
		rcc8 = RCC8::TPP;
	}
	else if (connectedness.EvaluatePlanarNTPP((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size()))
	{
		rcc8 = RCC8::NTPP;
	}
	else if (connectedness.EvaluatePlanarPO((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size()))
	{
		rcc8 = RCC8::PO;

	}
	else if (connectedness.EvaluatePlanarEQ((int)vectorList.exteriorList.size(), (int)vectorList.boundaryList.size(), (int)vectorList.interiorList.size()))
	{
		rcc8 = RCC8::EQ;
	}
	return rcc8;
}

ComparisonSymbol SymbolState::convertGeom2Comparison(const float *groundStyle, const float *figureStyle)
{
	ComparisonSymbol comparison = ComparisonSymbol::UNKNOWN;
	/*if (groundStyle[1] < figureStyle[0])
	{
		comparison = ComparisonSymbol::MT; 
	}
	else if (groundStyle[0] >= figureStyle[1])
	{
		comparison = ComparisonSymbol::LT;
	}
	else if (MTmath.ApproxEqual(groundStyle[1], figureStyle[0]))
	{
		comparison = ComparisonSymbol::EQ; 
	}*/
	
	if ((!ApproxEqual(groundStyle[0], figureStyle[0])) && 
		(figureStyle[0] < groundStyle[0]) && (figureStyle[1] > groundStyle[0]))
	{
		comparison = ComparisonSymbol::minMOLTminDO;
	}
	else if ((!ApproxEqual(groundStyle[1], figureStyle[0])) && // maxMO != minDO
		     (figureStyle[0] < groundStyle[1]) && //minMO < maxDO
			 (figureStyle[1] > groundStyle[0]))
	{
		comparison = ComparisonSymbol::minMOLTmaxDO;
	}
	else if ((!ApproxEqual(groundStyle[0], figureStyle[1])) && (figureStyle[1] < groundStyle[0]))
	{
		comparison = ComparisonSymbol::maxMOLTminDO;
	}
	else if ((!ApproxEqual(groundStyle[1], figureStyle[1])) && 
		(figureStyle[1] < groundStyle[1]) && (figureStyle[1] > groundStyle[0]))
	{
		comparison = ComparisonSymbol::maxMOLTmaxDO;
	}
	else if (ApproxEqual(groundStyle[0], figureStyle[0]))
	{
		comparison = ComparisonSymbol::minMOEQminDO;
	}
	else if (ApproxEqual(groundStyle[0], figureStyle[1]))
	{
		comparison = ComparisonSymbol::maxMOEQminDO;
	}
	else if (ApproxEqual(groundStyle[1], figureStyle[1]))
	{
		comparison = ComparisonSymbol::maxMOEQmaxDO;
	}
	else if (ApproxEqual(groundStyle[1], figureStyle[0]))
	{
		comparison = ComparisonSymbol::minMOEQmaxDO;
	}
	else if ((!ApproxEqual(groundStyle[0], figureStyle[0])) && (figureStyle[0] > groundStyle[0]) && (figureStyle[0] < groundStyle[1]))
	{
		comparison = ComparisonSymbol::minMOMTminDO;
	}
	else if ((!ApproxEqual(groundStyle[1], figureStyle[0])) && (figureStyle[0] > groundStyle[1]))
	{
		comparison = ComparisonSymbol::minMOMTmaxDO;
	}
	else if ((!ApproxEqual(groundStyle[0], figureStyle[1])) && (figureStyle[1] > groundStyle[0]) && (figureStyle[1]<groundStyle[1]))
	{
		comparison = ComparisonSymbol::maxMOMTminDO;
	}
	else if ((!ApproxEqual(groundStyle[1], figureStyle[1])) && (figureStyle[1] > groundStyle[1]) && (figureStyle[0]<groundStyle[1]))
	{
		comparison = ComparisonSymbol::maxMOMTmaxDO;
	}
	//else 
	//{
	//	comparison = ComparisonSymbol::UNKNOWN;
	//}
	return comparison;
}
// get SymbolicFromGeom()
// get Rotation symbolic
// get location symbolic
 
