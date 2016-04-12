#include "renderMgr.h"

#include "resourceMgr.h"
#include "../wrapper/openGLWrapper.h"
#include "../graphics/shader.h"
#include "../system/logging.h"
#include "../utils/timer.h"

namespace robolab {
	using namespace wrapper;

	namespace manager {
		bool RenderMgr::isInitialized = false;
		Vec2i RenderMgr::windowSize;
		gui::Window RenderMgr::window;
		std::shared_ptr<graphics::Camera> RenderMgr::camera = nullptr;

		bool RenderMgr::isMouseLeftPresed = false;
		bool RenderMgr::isMouseMiddlePressed = false;
		Vec2f RenderMgr::mousePreviousPos;
		Vec2f RenderMgr::mouseCurrentPos;
		Vec2i RenderMgr::mouseWheel;

		std::shared_ptr<GLShaderIDs> RenderMgr::defaultNormalShader = nullptr;
		std::shared_ptr<GLShaderIDs> RenderMgr::defaultInstanceShader = nullptr;

		std::vector <RenderMgr::RenderableData> RenderMgr::drawables;
		std::unordered_map<std::string, std::shared_ptr<GLBufferIDs>> RenderMgr::meshGLBufferIdList;
		std::vector<std::shared_ptr<GLShaderIDs>> RenderMgr::meshGLShaderIdList;
		Mat4 RenderMgr::prevProjection = Mat4(1.0f); 
		Mat4 RenderMgr::prevView = Mat4(1.0f);
		std::vector<RenderMgr::DrawableInstace> RenderMgr::instanceModelsTransform;

		//#######################################################################################

		bool RenderMgr::initialize(const std::string& windowTitle, const Vec2i& WindowSize, bool enableVSync) {
			windowSize = WindowSize;
			if (window.initialize(windowTitle, windowSize.x, windowSize.y))
				isInitialized = false;
			else
				isInitialized = true;

			window.setVsync(enableVSync);
			window.setBackgroundColor(0.6f, 0.6f, 0.6f, 1.0f);
			window.update();

			camera =  std::make_shared<graphics::Camera>(70.0F, 0.75f, 1.0f, 1000000.0f, CAMERA_PERSPECTIVE);
			camera->setAspectRatio(windowSize);
			camera->rotateAroundTarget(35.0f, 135.0f);


			meshGLBufferIdList["EMPTY_MESH"] = std::shared_ptr<GLBufferIDs>();
			if (defaultNormalShader == 0) {
				defaultNormalShader = createGLShader(Shader::vertexShaded, Shader::fragmentShaded,
					std::vector<std::string>({ "ProjectionTransform", "ViewTransform", "ModelTransform" }));
			}
			if (defaultInstanceShader == 0) {
				defaultInstanceShader = createGLShader(Shader::vertexShadedInstance, Shader::fragmentShadedInstance,
					std::vector<std::string>({ "ProjectionTransform", "ViewTransform" }));
			}
			return isInitialized;
		}

		std::pair<std::shared_ptr<GLBufferIDs>, std::shared_ptr<GLShaderIDs>> RenderMgr::makeDrawable(const std::string& meshName) {
			if (meshGLBufferIdList.find(meshName) == meshGLBufferIdList.end())
			{
				if (ResourceMgr::existRenderMesh(meshName)) {
					//std::shared_ptr<GLBufferIDs> bufferIDs = createGLBuffersID(bufferData);
					std::shared_ptr<GLBufferIDs> bufferIDs = createGLInstanceBuffersID(ResourceMgr::getRenderMesh(meshName));
					meshGLBufferIdList[meshName] = bufferIDs;
					return std::make_pair(bufferIDs, defaultInstanceShader);
				}
				else {
					system::Logging::console(system::LOG_ERROR, "No mesh exist with name \"" + meshName + "\"" +
						"\nMake sure the given mesh name is correct.", LOCATION);
					return std::make_pair(meshGLBufferIdList["EMPTY_MESH"], defaultNormalShader);
				}
			}
			else {
				return std::make_pair(meshGLBufferIdList[meshName], defaultInstanceShader);
			}
		}

		int RenderMgr::submitGLIDs(entity::Entity* owner) {
			int index = -1;
			drawables.push_back(RenderableData(owner->getComponent<entity::component::TransformComponent>(), owner->getComponent<entity::component::RenderableComponent>()));
			auto glId = owner->getComponent<entity::component::RenderableComponent>()->getGLBufferIDs();
			bool drawableGroupExist = false;
			for (auto& drawable : instanceModelsTransform)
			{
				if (drawable.bufferIds == glId) {
					drawable.transforms.push_back(owner->getComponent<entity::component::TransformComponent>()->getTransform());
					drawableGroupExist = true;
					index = (int)drawable.transforms.size() - 1;
					break;
				}
			}
			if (!drawableGroupExist) {
				instanceModelsTransform.push_back(
					DrawableInstace(glId->getID(), std::vector<Mat4>({ owner->getComponent<entity::component::TransformComponent>()->getTransform() }),
						owner->getComponent<entity::component::RenderableComponent>()->getGLShaderIDs(),
						owner->getComponent<entity::component::RenderableComponent>()->getGLBufferIDs()));
				index = 0;
			}
			return index;
		}

		void RenderMgr::updateActorTransform(std::size_t glBufferUniqueID, int transformIndex, const Mat4& transform) {
			if (transformIndex != -1) {
				for (auto& drawable : instanceModelsTransform)
				{
					if (drawable.bufferIds->getID() == glBufferUniqueID) {
						drawable.transforms[transformIndex] = transform;
						break;
					}
				}
			}
		}


		std::shared_ptr<GLBufferIDs> RenderMgr::createGLBuffersID(const std::shared_ptr<MeshDataBuffers> meshData) {
			auto VAO = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_VERTEX_ARRAY);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_VERTEX_ARRAY, VAO);
			checkGLError(LOCATION);
			std::unordered_map<std::string, unsigned int> attributsIDs;
			attributsIDs["vertices"] = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_ATTRIBUTE);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, attributsIDs["vertices"]);
			wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_ATTRIBUTE, meshData->vertices.data(), meshData->vertices.size() * sizeof(meshData->vertices[0]));
			wrapper::opengl::setAttributeShaderLocation(0, 3);
			checkGLError(LOCATION);
			attributsIDs["normals"] = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_ATTRIBUTE);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, attributsIDs["normals"]);
			wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_ATTRIBUTE, meshData->normals.data(), meshData->normals.size() * sizeof(meshData->normals[0]));
			wrapper::opengl::setAttributeShaderLocation(1, 3);
			checkGLError(LOCATION);
			attributsIDs["colors"] = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_ATTRIBUTE);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, attributsIDs["colors"]);
			wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_ATTRIBUTE, meshData->colors.data(), meshData->colors.size() * sizeof(meshData->colors[0]));
			wrapper::opengl::setAttributeShaderLocation(2, 3);
			checkGLError(LOCATION);
			auto indexID = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_INDEX);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_INDEX, indexID);
			wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_INDEX, meshData->indices.data(), meshData->indices.size() * sizeof(meshData->indices[0]));
			auto indexSize = meshData->indices.size();
			checkGLError(LOCATION);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_VERTEX_ARRAY, 0);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, 0);

			return std::make_shared<GLBufferIDs>(internal::getUniqueRenderableGroupID(), meshData->getName(), VAO, indexID, indexSize, attributsIDs);
		}

		std::shared_ptr<GLBufferIDs> RenderMgr::createGLInstanceBuffersID(const std::shared_ptr<MeshDataBuffers> meshData) {
				
			auto VAO = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_VERTEX_ARRAY);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_VERTEX_ARRAY, VAO);
			checkGLError(LOCATION);
			std::unordered_map<std::string, unsigned int> attributsIDs;
			attributsIDs["vertices"] = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_ATTRIBUTE);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, attributsIDs["vertices"]);
			wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_ATTRIBUTE, meshData->vertices.data(), meshData->vertices.size() * sizeof(meshData->vertices[0]));
			wrapper::opengl::setAttributeShaderLocation(0, 3);
			checkGLError(LOCATION);
			attributsIDs["normals"] = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_ATTRIBUTE);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, attributsIDs["normals"]);
			wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_ATTRIBUTE, meshData->normals.data(), meshData->normals.size() * sizeof(meshData->normals[0]));
			wrapper::opengl::setAttributeShaderLocation(1, 3);
			checkGLError(LOCATION);
			attributsIDs["colors"] = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_ATTRIBUTE);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, attributsIDs["colors"]);
			wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_ATTRIBUTE, meshData->colors.data(), meshData->colors.size() * sizeof(meshData->colors[0]));
			wrapper::opengl::setAttributeShaderLocation(2, 3);
			checkGLError(LOCATION);
			auto indexID = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_INDEX);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_INDEX, indexID);
			wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_INDEX, meshData->indices.data(), meshData->indices.size() * sizeof(meshData->indices[0]));
			auto indexSize = meshData->indices.size();
			checkGLError(LOCATION);
			attributsIDs["modelInstanceTransform"] = wrapper::opengl::genBufferID(wrapper::opengl::BUFFER_ATTRIBUTE);
			checkGLError(LOCATION);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, attributsIDs["modelInstanceTransform"]);
			checkGLError(LOCATION);
			for (unsigned int i = 0; i < 4; i++) {
				wrapper::opengl::setInstaceAttributeShaderLocation(3 + i, 4, sizeof(Mat4), (const void*)(sizeof(Vec4f) * i));
			}
			checkGLError(LOCATION);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_VERTEX_ARRAY, 0);
			wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, 0);

			return std::make_shared<GLBufferIDs>(internal::getUniqueRenderableGroupID(), meshData->getName(), VAO, indexID, indexSize, attributsIDs);
		}


		std::shared_ptr<GLShaderIDs> RenderMgr::createGLShader(const std::string& vertexShader, const std::string& fragmentShader, std::vector<std::string> shaderLocationsName) {
			std::unordered_map<std::string, unsigned int> locationIDs;
			auto shaderID = wrapper::opengl::createShader(vertexShader, fragmentShader);
			for (auto location : shaderLocationsName) {
				locationIDs[location] = wrapper::opengl::getUniformLocation(shaderID, location);
				checkGLError(LOCATION);
			}
			return std::make_shared<GLShaderIDs>(shaderID, locationIDs);
		}

		static bool isInstanceChanged = true;

		void RenderMgr::drawInstance() {
			if (instanceModelsTransform.size() > 0 && instanceModelsTransform[0].shaderIDs->shaderID != 0) 
			{
				opengl::setShader(instanceModelsTransform[0].shaderIDs->shaderID);
				opengl::setUniformMat4(instanceModelsTransform[0].shaderIDs->locationIDs["ProjectionTransform"], &camera->getProjectionMat()[0][0]);
				opengl::setUniformMat4(instanceModelsTransform[0].shaderIDs->locationIDs["ViewTransform"], &camera->getViewMat()[0][0]);
					
				for (auto drawable : instanceModelsTransform)
				{
					if(drawable.isChanged) {
						wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, drawable.bufferIds->attributesID["modelInstanceTransform"]);
						wrapper::opengl::addDataToBuffer(wrapper::opengl::BUFFER_ATTRIBUTE, drawable.transforms.data(), drawable.transforms.size() * sizeof(drawable.transforms[0]));
						wrapper::opengl::setActive(wrapper::opengl::BUFFER_ATTRIBUTE, 0);
						//drawable.isChanged = false;
					}
						if (drawable.bufferIds->VAO != 0) {
							opengl::setPolygonMode(opengl::POLYGON_PRIMITIVE_FILL, 0.0f, 0.0f);
							opengl::setActive(opengl::BUFFER_VERTEX_ARRAY, drawable.bufferIds->VAO);
							glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)drawable.bufferIds->indexSize, GL_UNSIGNED_INT, 0, (GLsizei)drawable.transforms.size());
							//glDrawArraysInstanced(GL_TRIANGLES, 0, (GLsizei)drawable.bufferIds->indexSize, (GLsizei)drawable.transforms.size());
						}
						else
							system::Logging::console(system::LOG_WARNING, "The given vertex array ID is zero."
								" Make sure the vertex array is initialized correctly", __func__);
					//checkGLError(LOCATION);
				}
			}
			else
				system::Logging::console(system::LOG_WARNING, "The given shader ID is zero. Make sure the shader is initialized correctly", __func__);
			opengl::setActive(opengl::BUFFER_VERTEX_ARRAY, 0);
			opengl::setShader(0);
		}

		void RenderMgr::draw() {
			std::shared_ptr<GLBufferIDs> bufferIDs;
			std::shared_ptr<GLShaderIDs> shaderIDs;
			bool updateProjection = true, updateView = true;
			if (prevProjection == camera->getProjectionMat())
				updateProjection = false;
			else
				prevProjection = camera->getProjectionMat();

			if (prevView == camera->getViewMat())
				updateView = false;
			else
				prevView = camera->getViewMat();


			for (auto model : drawables) 
			{
				if (model.rendererComp->isVisible) 
				{
					bufferIDs = model.rendererComp->getGLBufferIDs();
					shaderIDs = model.rendererComp->getGLShaderIDs();
					if (shaderIDs->shaderID != 0) {
						opengl::setShader(shaderIDs->shaderID);
						//, "ViewTransform", "ModelTransform"
						if(updateProjection)
							opengl::setUniformMat4(shaderIDs->locationIDs["ProjectionTransform"], &prevProjection[0][0]);
						if(updateView)
							opengl::setUniformMat4(shaderIDs->locationIDs["ViewTransform"], &prevView[0][0]);
						//if (model.transformComp->isChanged)
							opengl::setUniformMat4(shaderIDs->locationIDs["ModelTransform"], &model.transformComp->getPtr());
							if (bufferIDs->VAO != 0) {
								opengl::setPolygonMode(opengl::POLYGON_PRIMITIVE_FILL, 0.0f, 0.0f);
								opengl::setActive(opengl::BUFFER_VERTEX_ARRAY, bufferIDs->VAO);
								opengl::drawPrimitive(opengl::DRAW_PRIMITIVE_TRIANGLE, bufferIDs->indexSize);
							}
							else
								system::Logging::console(system::LOG_WARNING, "The given vertex array ID is zero."
									" Make sure the vertex array is initialized correctly", __func__);
					}
					else
						system::Logging::console(system::LOG_WARNING, "The given shader ID is zero."
							" Make sure the shader is initialized correctly", __func__);
					checkGLError(LOCATION);
					opengl::setActive(opengl::BUFFER_VERTEX_ARRAY, 0);
					opengl::setShader(0);
				}
			}
		}

		bool RenderMgr::isOK() {
			return window.isOK();
		}

		void RenderMgr::update(bool enableDrawing) {
			wrapper::opengl::clearScreen();
			if( enableDrawing)
				drawInstance();
			window.update();

			checkWindowSize();
			updateCameraControl();

			window.setTitle(window.getTitle()
				+ " - FPS: " + std::to_string(utils::Timer::getFPS()) + "(f/s)"
				+ " - Delta time: " + std::to_string(utils::Timer::getDeltaTime()) + "(s)");
		}

		void RenderMgr::shutdown() {
			for (auto glIDs : meshGLBufferIdList) {
				if (glIDs.first != "EMPTY_MESH") {
					if (glIDs.second->VAO != 0)
						wrapper::opengl::freeBuffer(glIDs.second->VAO);
					if (glIDs.second->indexID != 0)
						wrapper::opengl::freeBuffer(glIDs.second->indexID);
					for (auto attrib : glIDs.second->attributesID) {
						if (attrib.second != 0)
							wrapper::opengl::freeBuffer(attrib.second);
					}
				}
			}
			for (auto shader : meshGLShaderIdList) {
				if(shader != 0)
					wrapper::opengl::freeProgram(shader->shaderID);
			}
			wrapper::opengl::freeProgram(defaultNormalShader->shaderID);
		}

		void RenderMgr::updateCameraControl() {
			mouseCurrentPos = system::Input::MousePos();
			mouseWheel = system::Input::MouseWheel();
			if (system::Input::MousePressed(system::MOUSE_BUTTON_LEFT)) {
				isMouseLeftPresed = true;
				mousePreviousPos = mouseCurrentPos;
			}
			if (system::Input::MousePressed(system::MOUSE_BUTTON_MIDDLE)) {
				isMouseMiddlePressed = true;
				mousePreviousPos = mouseCurrentPos;
			}
			if (system::Input::MouseReleased(system::MOUSE_BUTTON_LEFT)) {
				isMouseLeftPresed = false;
			}
			if (system::Input::MouseReleased(system::MOUSE_BUTTON_MIDDLE)) {
				isMouseMiddlePressed = false;
			}

			if (isMouseLeftPresed && system::Input::IsMouseMoving()) {
				camera->rotateAroundTarget((mouseCurrentPos.y - mousePreviousPos.y) * 0.5f, -(mouseCurrentPos.x - mousePreviousPos.x) * 0.5f);
				mousePreviousPos = mouseCurrentPos;
			}

			if (isMouseMiddlePressed && system::Input::IsMouseMoving()) {
				camera->translate((mouseCurrentPos.x - mousePreviousPos.x)* 0.03f, (mouseCurrentPos.y - mousePreviousPos.y)* 0.03f);
				mousePreviousPos = mouseCurrentPos;
			}

			if (system::Input::IsMouseWheelRotating()) {
				if (mouseWheel.y != 0) {
					if (mouseWheel.y < 0)
						camera->zoom(1.1f);
					else
						camera->zoom(0.9f);
				}
			}

			
		}


		void RenderMgr::checkGLError(const std::string& location) {
			auto error = wrapper::opengl::checkError();
			if(error != GL_NO_ERROR) {
				system::Logging::console(system::LOG_ERROR, wrapper::opengl::getOpenGlError(error), location);
			}
		}


		void RenderMgr::checkWindowSize() {
			if (windowSize != window.getSize()) {
				windowSize = window.getSize();
				camera->setAspectRatio(windowSize);
				wrapper::opengl::setDrawableArea(0,0, windowSize.x, windowSize.y);
			}
		}

	} // end of namespace manager
}// end of namespace robolab