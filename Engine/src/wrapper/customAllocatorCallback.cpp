#include "customAllocatorCallback.h"


namespace robolab {
	namespace wrapper {

		CustomAllocatorCallback::CustomAllocatorCallback() {}
		CustomAllocatorCallback::~CustomAllocatorCallback() {}
		void* CustomAllocatorCallback::allocate(size_t size, const char*, const char*, int) {
			if (POCO_OS == POCO_OS_WINDOWS_NT)
				return _aligned_malloc(size, 16);
			else
				return malloc(size);
		}

		void  CustomAllocatorCallback::deallocate(void* ptr) {
			if (POCO_OS == POCO_OS_WINDOWS_NT)
				_aligned_free(ptr);
			else
				delete ptr;
		}
	}
}