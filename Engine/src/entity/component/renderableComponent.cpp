#include "renderableComponent.h"

#include "../../managers/renderMgr.h"

namespace robolab {
	namespace entity {
		namespace component {

			RenderableComponent::RenderableComponent(const std::string& meshName) {
				auto glIDs = manager::RenderMgr::makeDrawable(meshName);
				bufferIDs = glIDs.first;
				shaderIDs = glIDs.second;
			}

			RenderableComponent::~RenderableComponent() {
			}

			void RenderableComponent::init() {
				index = manager::RenderMgr::submitGLIDs(owner);
				isVisible = true;
			}

			const std::shared_ptr<GLBufferIDs> RenderableComponent::getGLBufferIDs() {
				return bufferIDs;
			}
			const std::shared_ptr<GLShaderIDs> RenderableComponent::getGLShaderIDs() {
				return shaderIDs;
			}

		}
	}
}