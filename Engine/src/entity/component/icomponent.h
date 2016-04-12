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