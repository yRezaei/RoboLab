#include "entity.h"

namespace robolab {
	namespace entity {

		Entity::Entity() {
			id = getUniqueEntityID();
			name = "object_" + std::to_string(id);
			this->addComponent<TransformComponent>(Mat4(1.0f));
		}

		Entity::Entity(const std::string& Name, const Mat4& transform ) {
			id = getUniqueEntityID();
			name = Name;
			this->addComponent<TransformComponent>(transform);
		}

		Entity::~Entity() {

		}

		void Entity::setName(const std::string& Name) {
			name = Name;
		}

		const std::string& Entity::getName() {
			return name;
		}

		const std::size_t& Entity::getID() {
			return id;
		}

		void Entity::setPosition(const Vec3f& position) {
			this->getComponent<TransformComponent>()->setPosition(position);
		}

		void Entity::setRotation(const Quat& rotation) {
			this->getComponent<TransformComponent>()->setRotation(rotation);
		}

		void Entity::setTransform(const Mat4& transform) {
			this->getComponent<TransformComponent>()->setTransform(transform);
		}

		Vec3f Entity::getPosition() {
			return this->getComponent<TransformComponent>()->getPosition();
		}

		Quat Entity::getRotation() {
			return this->getComponent<TransformComponent>()->getRotation();
		}

		const Mat4& Entity::getTransform() {
			return this->getComponent<TransformComponent>()->getTransform();
		}

	}
}