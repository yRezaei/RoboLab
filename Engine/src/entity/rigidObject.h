/*
 * rigidObject.h
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
#ifndef RIGID_OBJECT_H
#define RIGID_OBJECT_H

#include "entity.h"

namespace robolab {
	namespace entity {
		struct CollisionInfo
		{
			Entity* otherObject;
		};

		class RigidObject : public Entity
		{
		public:
			RigidObject(const std::string& Name, const Mat4& transform, const std::string& meshName, bool isDynamic);
			~RigidObject();

			bool onCollision(CollisionInfo& collisionInfo);

		};
	}
}

#endif //!RIGID_OBJECT_H
