/*
 * entity.h
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
#ifndef ENTITY_H
#define ENTITY_H

#include <functional>
#include <array>
#include <string>
#include "../mathematic/math3D.h"
#include "component/components.h"


namespace robolab {
	namespace wrapper {
		class CustomEventCallback;
	}
}

namespace robolab {
	namespace entity {
		using namespace std::placeholders;
		using namespace math3D;
		using namespace component;

		//#####################################################
		struct Hit
		{
			bool isTrue;
			Entity* otherActor;

			Hit() : isTrue(false), otherActor(NULL) {}
			Hit(bool isCollided, Entity* actor) : isTrue(isCollided), otherActor(actor) {}
		};
		
		class Entity
		{
			friend wrapper::CustomEventCallback;
		private:
			std::size_t id;
			std::string name;
			ComponentArray componentList;
			ComponentBitset componentBitset;
		public:
			Entity();
			Entity(const std::string& Name, const Mat4& transform);
			virtual ~Entity();		
			
		public:
			Hit hit;
		public:
			void setName(const std::string& Name);
			const std::string& getName();
			const std::size_t& getID();
			void setPosition(const Vec3f& position);
			void setRotation(const Quat& rotation);
			void setTransform(const Mat4& transform);
			Vec3f getPosition();
			Quat getRotation();
			const Mat4& getTransform();
		public:
			template <typename T> bool hasComponent() const {
				return componentBitset[getComponentTypeID<T>()];
			}

			template <typename T, typename... TArgs> T* addComponent(TArgs&&... mArgs) {
				assert(!hasComponent<T>());
				IComponent* newComponent = new T(std::forward<TArgs>(mArgs)...);
				newComponent->owner = this;
				componentList[getComponentTypeID<T>()] = newComponent;
				componentBitset[getComponentTypeID<T>()] = true;
				newComponent->init();
				return static_cast<T*>(newComponent);
			}

			template <typename T> T* getComponent() {
				assert(hasComponent<T>());
				auto compPtr(componentList[getComponentTypeID<T>()]);
				return static_cast<T*>(compPtr);
			}
		};

	}
}
#endif // !ENTITY_H

