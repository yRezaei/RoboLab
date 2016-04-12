#ifndef SPATIAL_RELATIONS_H
#define SPATIAL_RELATIONS_H

#include <bitset>
#include <utility>
#include <map>
#include <vector>

namespace symbolicNumeric {

	enum SpatialPropositions {
		PROPOSITION_FRONT,
		PROPOSITION_BACK,
		PROPOSITION_LEFT,
		PROPOSITION_RIGHT,
		PROPOSITION_ABOVE,
		PROPOSITION_BELLOW,
		PROPOSITION_UNDER,
		PROPOSITION_INSIDE,
		PROPOSITION_IN_BETWEEN
	};

	enum SpatialTopologies {
		TOPOLOGY_DC, //disconnected
		TOPOLOGY_EC, //externally connected
		TOPOLOGY_EQ, //equal
		TOPOLOGY_PO, //partially overlapping
		TOPOLOGY_TTP, //tangential proper part
		TOPOLOGY_TPPI, //tangential proper part inverse
		TOPOLOGY_NTPP, //non-tangential proper part
		TOPOLOGY_NTPPI //non-tangential proper part inverse
	};

	enum SpatialDistance {
		DISTANCE_IN_TOUCH,
		DISTANCE_VERY_CLOSE,
		DISTANCE_NEAR,
		DISTANCE_FAR,
		DISTANCE_VERY_FAR
	};

	
	enum SpatialOrientation {
		ORIENTATION_ARBITRARY,
		ORIENTATION_STAND_UP,
		ORIENTATION_LIE_on_side,
		ORIENTATION_UPSIDE_DOWN
	};
	

	/*enum SpatialOrientation {
		ORIENTATION_ARBITRARY,
		ORIENTATION_PARALLEL_XY,
		ORIENTATION_PARALLEL_YZ,
		ORIENTATION_PARALLEL_XZ,
		ORIENTATION_STRAIGHT_ALONG_X,
		ORIENTATION_STRAIGHT_ALONG_Y,
		ORIENTATION_STRAIGHT_ALONG_Z,
		ORIENTATION_INVERTED_ALONG_X,
		ORIENTATION_INVERTED_ALONG_Y,
		ORIENTATION_INVERTED_ALONG_Z
	};*/

	struct SpatialRelations
	{
		std::vector<std::pair<SpatialPropositions, SpatialTopologies>> position;
		SpatialOrientation orientation;

		SpatialRelations() {
			position.push_back(std::make_pair(PROPOSITION_ABOVE, TOPOLOGY_NTPP));
			orientation = ORIENTATION_ARBITRARY;
		}

		SpatialRelations(std::vector<std::pair<SpatialPropositions, SpatialTopologies>> Position, SpatialOrientation Orientation) {
			position = Position;
			orientation = Orientation;
		}

		~SpatialRelations() {}

		bool isValid() {
			/*std::vector<SpatialTopologies> topologyList;
			switch (proposition)
			{
			case symbolicNumeric::PROPOSITION_FRONT:
				break;
			case symbolicNumeric::PROPOSITION_BACK:
				break;
			case symbolicNumeric::PROPOSITION_LEFT:
				break;
			case symbolicNumeric::PROPOSITION_RIGHT:
				break;
			case symbolicNumeric::PROPOSITION_ABOVE:
				topologyList = std::vector<SpatialTopologies>({ TOPOLOGY_DC });
				break;
			case symbolicNumeric::PROPOSITION_BELLOW:
				topologyList = std::vector<SpatialTopologies>({ TOPOLOGY_DC });
				break;
			}
			
			for (auto item : topologyList) {
				if (topology == item)
					return false;
			}*/
			return true;
		}
	};
}



#endif // !SPATIAL_RELATIONSHIP_H

