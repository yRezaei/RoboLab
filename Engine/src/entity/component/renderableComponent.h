#ifndef RENDERABLE_COMPONENT_H
#define RENDERABLE_COMPONENT_H

#include <memory>
#include "icomponent.h"
#include "../../graphics/mesh3D.h"
#include "../../mathematic/math3D.h"

namespace robolab {
	using namespace graphics;

	namespace entity {
		namespace component {

			class RenderableComponent : public IComponent
			{
			private:
				std::shared_ptr<GLBufferIDs> bufferIDs;
				std::shared_ptr<GLShaderIDs> shaderIDs;
				//std::shared_ptr<RenderableObject> renderableData;
			public:
				int index;
				bool isVisible;
			public:
				RenderableComponent(const std::string& meshName);
				~RenderableComponent();
			public:
				void init() override;
				const std::shared_ptr<GLBufferIDs> getGLBufferIDs();
				const std::shared_ptr<GLShaderIDs> getGLShaderIDs();
			};
		}
	}
}

#endif // !RENDERABLE_COMPONENT_H



