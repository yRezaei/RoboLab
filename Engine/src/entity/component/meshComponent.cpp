#include "meshComponent.h"


namespace robolab {
	namespace entity {
		namespace component {
			MeshComponent::MeshComponent(VisualizationMesh visualizationMesh, PhysicMesh physicMesh)
			{
				this->visualMesh = visualizationMesh;
				this->physicMesh = physicMesh;
			}


			MeshComponent::~MeshComponent()
			{
			}

			const VisualizationMesh MeshComponent::getVisualizationMesh() {
				return visualMesh;
			}

			const PhysicMesh MeshComponent::getPhysicMesh() {
				return physicMesh;
			}

		}
	}
}
