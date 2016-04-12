#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "icomponent.h"
#include "../../mathematic/math3D.h"

namespace robolab {
	using namespace math3D;

	namespace entity {
		namespace component {

			class PhysicComponent;
			class TransformComponent : public IComponent
			{
				friend class PhysicComponent;
			private:
				Mat4 transform;
			public:
				bool isChanged;
			public:
				TransformComponent(const Mat4& mat4 = Mat4(1.0f));
				TransformComponent(const Vec3f& vec3);
				TransformComponent(const Vec3f& vec3, const Quat& quat);
				TransformComponent(const Quat& quat);
				~TransformComponent();
			public:
				void init() override;
				void setTransform(const float& mat4);
				void setTransform(const Mat4& mat4);
				void setTransform(const Vec3f& vec3, const Quat& quat);
				void setPosition(const Vec3f& vec3);
				void setRotation(const Mat3& mat3);
				Vec3f getPosition();
				Quat getRotation();
				void setRotation(const Quat& quat);
				const Mat4& getTransform();
				const float& getPtr();
			private:
				void updateOtherComponent();
			};
		}
	}
}


#endif // !TRANSFORM_COMPONENT_H
