/*
* transformComponent.h
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
#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "icomponent.h"
#include "../../mathematic/math3D.h"

namespace robolab {
	using namespace math3D;

	namespace entity {
		namespace component {

			class PhysicComponent;
			class TransformComponent : public IComponent
			{
				friend class PhysicComponent;
			private:
				Mat4 transform;
			public:
				bool isChanged;
			public:
				TransformComponent(const Mat4& mat4 = Mat4(1.0f));
				TransformComponent(const Vec3f& vec3);
				TransformComponent(const Vec3f& vec3, const Quat& quat);
				TransformComponent(const Quat& quat);
				~TransformComponent();
			public:
				void init() override;
				void setTransform(const float& mat4);
				void setTransform(const Mat4& mat4);
				void setTransform(const Vec3f& vec3, const Quat& quat);
				void setPosition(const Vec3f& vec3);
				void setRotation(const Mat3& mat3);
				Vec3f getPosition();
				Quat getRotation();
				void setRotation(const Quat& quat);
				const Mat4& getTransform();
				const float& getPtr();
			private:
				void updateOtherComponent();
			};
		}
	}
}


#endif // !TRANSFORM_COMPONENT_H
