#ifndef IPREDICATE_H
#define IPREDICATE_H

#include <string>
#include "../../src/engine.h"

namespace symbolicNumeric {

	struct IPredicate {
		std::string name;
		std::string type;
		bool validity;
		virtual ~IPredicate() {}
		virtual void init() {}
		virtual bool isValid() {}
	};
}

#endif // !IPredicate_H

