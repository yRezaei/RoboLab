/*
* customAllocatorCallback.h
*
* Copyright 2016 Yashar Abbasalizadeh Rezaei <yashar.a.rezaei@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*
*/
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
