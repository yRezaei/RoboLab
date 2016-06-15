/*
* customErrorCallback.h
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
