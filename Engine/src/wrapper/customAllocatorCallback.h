#ifndef CUSTOM_ALLOCATOR_CALLBACK_H
#define CUSTOM_ALLOCATOR_CALLBACK_H

#include <physx/PxPhysicsAPI.h>
#include <physx/PxPhysics.h>
#include <Poco/Platform.h>

namespace robolab {
	namespace wrapper {

		class CustomAllocatorCallback : public physx::PxAllocatorCallback
		{
		public:
			CustomAllocatorCallback();
			~CustomAllocatorCallback();
			void* allocate(size_t size, const char*, const char*, int) override;

			void  deallocate(void* ptr) override;

		}; // end of class AllocatorCallback

	}
}

#endif // !CUSTOM_ALLOCATOR_CALLBACK_H
