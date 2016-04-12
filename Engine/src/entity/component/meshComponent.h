#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "icomponent.h"
#include <memory>

namespace robolab {
	namespace entity {
		namespace component {

			class MeshComponent : public IComponent
			{
			public:
				MeshComponent(const std::string& meshName);
				~MeshComponent();
			public:
				void init() override;
			};
		}
	}
}

#endif // !MESH_COMPONENT_H

