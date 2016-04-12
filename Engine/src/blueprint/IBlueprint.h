#ifndef I_BLUEPRINT_H
#define I_BLUEPRINT_H

namespace robolab {
	namespace blueprint {

		class IBlueprint
		{
		public:
			virtual ~IBlueprint() {}
			virtual void init() {}
			virtual void update(float deltaTime) {}
			virtual void destroy() {}
		};
	}
}

#endif // !I_BLUEPRINT_H

