/*
* icomponent.h
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
#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <bitset>
#include <array>

namespace robolab {
	namespace entity {
		class Entity;

		namespace component {
			
			class IComponent
			{
				friend class Entity;
			public:
				Entity* owner;
				IComponent() {}
				virtual ~IComponent() {}
				virtual void init() {}
				virtual void update() {}
				virtual void destroy() {}
			};

			//#####################################################
			constexpr std::size_t maxComponentCount{ 5 };
			using ComponentTypeID = std::size_t;

			using uint = unsigned int;

			using ComponentBitset = std::bitset<maxComponentCount>;
			using ComponentArray = std::array<IComponent*, maxComponentCount>;

			//#####################################################

			namespace internalUse
			{
				inline ComponentTypeID getUniqueComponentID() noexcept
				{
					static ComponentTypeID lastComponentID{ 0u };
					return lastComponentID++;
				}
			}

			//#####################################################

			template <typename T>
			inline ComponentTypeID getComponentTypeID() noexcept
			{
				static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");
				static ComponentTypeID UniqueComponentID{ internalUse::getUniqueComponentID() };
				return UniqueComponentID;
			}

		}
	}
}

#endif // !ICOMPONENT