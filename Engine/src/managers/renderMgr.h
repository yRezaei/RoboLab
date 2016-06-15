#ifndef RENDER_MGR_H
#define RENDER_MGR_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include "../gui/window.h"
#include "../graphics/camera/camera.h"
#include "../entity/entity.h"
#include "../mathematic/math3D.h"
#include "../graphics/mesh3D.h"
#include "../graphics/mesh.h"

namespace robolab {
	using namespace math3D;
	using namespace graphics;

	namespace manager {

		enum VisibilityOption {
			VISIBILITY_TRUE,
			VISIBILITY_FALSE
		};

		class RenderMgr
		{
		private:
			struct RenderableData
			{
				entity::component::TransformComponent* transformComp;
				entity::component::RenderableComponent* rendererComp;

				RenderableData() {}
				RenderableData(entity::component::TransformComponent* trans, entity::component::RenderableComponent* render)
				: transformComp(trans), rendererComp(render) {}
			};

			struct DrawableInstace
			{
				bool isChanged;
				std::size_t ID;
				std::vector<Mat4> transforms;
				std::shared_ptr<GLShaderIDs> shaderIDs;
				std::shared_ptr<GLBufferIDs> bufferIds;
				DrawableInstace() { isChanged = true; }
				DrawableInstace(std::size_t id, std::vector<Mat4>& Transforms, std::shared_ptr<GLShaderIDs> ShaderIDs, std::shared_ptr<GLBufferIDs> BufferIds)
				: ID(id), transforms(Transforms), shaderIDs(ShaderIDs), bufferIds(BufferIds) {
					isChanged = true;
				}
			};

		private:
			static Vec2i windowSize;
			static bool isInitialized;
			static gui::Window window;
			static std::shared_ptr<graphics::Camera> camera;

			static bool isMouseLeftPresed;
			static bool isMouseMiddlePressed;
			static Vec2f mousePreviousPos;
			static Vec2f mouseCurrentPos;
			static Vec2i mouseWheel;
			static void updateCameraControl();

			static std::shared_ptr<GLShaderIDs> defaultNormalShader;
			static std::shared_ptr<GLShaderIDs> defaultInstanceShader;

			static std::vector < RenderableData > drawables;
			static std::unordered_map<std::string, std::shared_ptr<GLBufferIDs>> meshGLBufferIdList;
			static std::vector<std::shared_ptr<GLShaderIDs>> meshGLShaderIdList;
			static std::vector<DrawableInstace> instanceModelsTransform;
			static Mat4 prevProjection, prevView;
		private:
			static std::shared_ptr<GLBufferIDs> createGLBuffersID(const std::shared_ptr<Mesh> meshData);
			static std::shared_ptr<GLBufferIDs> createGLInstanceBuffersID(const std::shared_ptr<Mesh> meshData);
			static std::shared_ptr<GLShaderIDs> createGLShader(const std::string& vertexShader, const std::string& fragmentShader, std::vector<std::string> shaderLocationsName);
			static void checkGLError(const std::string& location);
			static void drawInstance();
			static void draw();
			static void checkWindowSize();
		public:
			static bool isOK();
		public:
			static bool initialize(const std::string& windowTitle, const Vec2i& windowSize, bool enableVSync);
			static std::pair<std::shared_ptr<GLBufferIDs>, std::shared_ptr<GLShaderIDs>> makeDrawable(const std::string& meshName);
			static int submitGLIDs(entity::Entity* owner);
			static void updateActorTransform(std::size_t glBufferUniqueID, int transformIndex, const Mat4& transform);
			static void update(bool enableDrawing);
			static void shutdown();

		};

	}
}

#endif