#include "transformComponent.h"
#include "../entity.h"
#include "../../managers/renderMgr.h"

namespace robolab {
	namespace entity {
		namespace component {

			TransformComponent::TransformComponent(const Mat4& mat4) {
				isChanged = true;
				transform = mat4;
			}

			TransformComponent::TransformComponent(const Vec3f& vec3) {
				isChanged = true;
				transform = makeMat4(vec3);
			}

			TransformComponent::TransformComponent(const Quat& quat) {
				isChanged = true;
				transform = makeMat4(quat);
			}

			TransformComponent::TransformComponent(const Vec3f& vec3, const Quat& quat) {
				isChanged = true;
				transform = makeMat4(vec3, quat);
			}

			TransformComponent::~TransformComponent() {

			}

			void TransformComponent::init() {
				isChanged = true;
			}

			void TransformComponent::setTransform(const float& mat4) {
				isChanged = true;
				transform = Mat4(mat4);
				updateOtherComponent();
			}

			void TransformComponent::setTransform(const Mat4& mat4) {
				isChanged = true;
				transform = mat4;
				updateOtherComponent();
			}

			void TransformComponent::setTransform(const Vec3f& vec3, const Quat& quat) {
				isChanged = true;
				transform = makeMat4(vec3, quat);
				updateOtherComponent();
			}

			void TransformComponent::setPosition(const Vec3f& vec3) {
				isChanged = true;
				transform[3] = Vec4f(vec3, 1.0f);
				updateOtherComponent();
			}

			void TransformComponent::setRotation(const Mat3& mat3) {
				isChanged = true;
				Vec4f position = transform[3];
				transform = glm::mat4(mat3);
				transform[3] = position;
				updateOtherComponent();
			}

			void TransformComponent::setRotation(const Quat& quat) {
				isChanged = true;
				transform = makeMat4(Vec3f(transform[3]), quat);
				updateOtherComponent();
			}

			Vec3f TransformComponent::getPosition() {
				return Vec3f(transform[3]);
			}

			Quat TransformComponent::getRotation() {
				return makeQuat(transform);
			}

			const Mat4& TransformComponent::getTransform() {
				return transform;
			}

			const float& TransformComponent::getPtr() {
				isChanged = false;
				return (transform[0][0]);
			}

			void TransformComponent::updateOtherComponent() {
				if (owner->hasComponent<PhysicComponent>()) {
					owner->getComponent<PhysicComponent>()->setGlobalTransform(transform);
				}
				if (owner->hasComponent<RenderableComponent>()) {
					std::size_t glID = owner->getComponent<RenderableComponent>()->getGLBufferIDs()->getID();
					int transformID = owner->getComponent<RenderableComponent>()->index;
					manager::RenderMgr::updateActorTransform(glID, transformID, transform);
				}
			}

		}
	}
}