#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "icomponent.h"
#include <memory>
#include "../../graphics/mesh.h"

namespace robolab {
	namespace entity {
		namespace component {
			using VisualizationMesh = std::shared_ptr<graphics::Mesh>;
			using PhysicMesh = std::shared_ptr<std::vector<std::shared_ptr<graphics::Mesh>>>;

			class MeshComponent : public IComponent
			{
			private:
				VisualizationMesh visualMesh;
				PhysicMesh physicMesh;
			public:
				MeshComponent(VisualizationMesh VisualizationMesh, PhysicMesh PhysicMesh);
				~MeshComponent();
				const VisualizationMesh getVisualizationMesh();
				const PhysicMesh getPhysicMesh();
			};
		}
	}
}

#endif

