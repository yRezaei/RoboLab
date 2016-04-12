#include "meshComponent.h"
#include "../entity.h"
#include "../../managers/resourceMgr.h"

namespace robolab {
	namespace entity {
		namespace component {

			MeshComponent::MeshComponent(const std::string& meshName) {
				if (manager::ResourceMgr::isMeshLoaded(meshName))
				{

				}
			}

			MeshComponent::~MeshComponent() {

			}

			void MeshComponent::init() {

			}

		}
	}
}