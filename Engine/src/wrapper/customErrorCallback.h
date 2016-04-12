#ifndef CUSTOM_ERROR_CALLBACK_H
#define CUSTOM_ERROR_CALLBACK_H

#include <physx/PxPhysicsAPI.h>
#include <physx/PxPhysics.h>

namespace robolab {
	namespace wrapper {

		class CustomErrorCallback : public physx::PxErrorCallback
		{
		public:
			CustomErrorCallback();
			~CustomErrorCallback();
			void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override;
		};

	}
}

#endif // !CUSTOM_ALLOCATOR_CALLBACK_H
