#ifndef SPATIAL_PROPOSITION_H
#define SPATIAL_PROPOSITION_H

#include <unordered_map>
#include "iPredicate.h"
#include "../../src/engine.h"

namespace symbolicNumeric {

	enum PropositionType {
		PROPOSITION_FRONT,
		PROPOSITION_BACK,
		PROPOSITION_LEFT,
		PROPOSITION_RIGHT,
		PROPOSITION_ABOVE,
		PROPOSITION_BELOW,
		PROPOSITION_INSIDE,
		PROPOSITION_IN_BETWEEN
	};

	std::unordered_map<std::string, PropositionType> stringToProposition;
	std::unordered_map<PropositionType, std::string> propositionToString;

	struct PropositionFront : public IPredicate 
	{
		std::shared_ptr<RigidObject> activeObject;
		std::shared_ptr<RigidObject> passiveObject;

		PropositionFront(std::shared_ptr<RigidObject> ActiveObject, std::shared_ptr<RigidObject> PassiveObject, bool Validity) {
			type = "proposition";
			name = "front";
			validity = Validity;
			activeObject = ActiveObject;
			passiveObject = PassiveObject;
		}

		~PropositionFront() {
		}

		void init() override {

		}

		bool isValid() override {

			return false;
		}
	};
}


#endif // !SPATIAL_PROPOSITION_H
