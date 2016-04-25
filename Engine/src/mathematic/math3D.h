#ifndef MATH_3D_H
#define MATH_3D_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <physx/PxPhysics.h>


namespace robolab { 
	namespace math3D {

#define Rad2Deg(angle) (angle * (180.0f / 3.141592653589793f))
#define Deg2Rad(angle) (angle * (3.141592653589793f / 180.0f))

		using Vec3uc = glm::u8vec3;

		using Vec2i = glm::ivec2;
		using Vec3i = glm::ivec3;
		using Vec4i = glm::ivec4;

		using Vec2ui = glm::u32vec2;
		using Vec3ui = glm::u32vec3;
		using Vec4ui = glm::u32vec4;

		using Vec2f = glm::vec2;
		using Vec3f = glm::vec3;
		using Vec4f = glm::vec4;

		using Vec2d = glm::dvec2;
		using Vec3d = glm::dvec3;
		using Vec4d = glm::dvec4;

		using Quat = glm::quat;

		using Mat3 = glm::mat3;
		using Mat4 = glm::mat4;

		using Vertices = std::vector<Vec3f>;
		using Normals = std::vector<Vec3f>;
		using Colors = std::vector<Vec3f>;
		using Indices = std::vector<unsigned int>;

		//#############################################################

		struct EulerAngles {
			float roll, pitch, yaw;
			EulerAngles() : roll(0.0f), pitch(0.0f), yaw(0.0f) {}
			EulerAngles(float Roll, float Pitch, float Yaw) : roll(Roll), pitch(Pitch), yaw(Yaw) {}
		};

		//#############################################################

		inline Mat4 makeMat4(const Vec3f& position) {
			return glm::translate(Mat4(1.0f), position);
		}

		inline Mat4 makeMat4(const Quat& quat) {
			return glm::mat4_cast(quat);
		}

		inline Mat4 makeMat4(const Vec3f& position, float roll, float pitch, float yaw) {
			return glm::translate(Mat4(1.0f), position) * glm::mat4_cast(Quat(Vec3f(pitch, yaw, roll)));
		}

		inline Mat4 makeMat4(const Vec3f& position, const Quat& quat) {
			return glm::translate(Mat4(1.0f), position) * glm::mat4_cast(quat);
		}

		inline Quat makeQuat(const Mat4& mat) {
			return glm::quat_cast(mat);
		}

		inline Quat makeQuat(const Mat3& mat) {
			return glm::quat_cast(mat);
		}

		inline Quat makeQuat(const EulerAngles& euler) {
			return Quat(Vec3f(euler.pitch, euler.yaw, euler.roll));
		}

		inline Mat3 makeMat3(const Quat& quat) {
			return glm::mat3_cast(quat);
		}

		inline EulerAngles makeEuler(const Quat& quat) {
			Vec3f e = glm::eulerAngles(quat);
			return EulerAngles(e.z, e.y, e.x);
		}

		inline EulerAngles makeEuler(const Mat4& mat) {
			Vec3f e = glm::eulerAngles(makeQuat(mat));
			return EulerAngles(e.z, e.y, e.x);
		}

		inline EulerAngles makeEuler(const Mat3& mat) {
			Vec3f e = glm::eulerAngles(makeQuat(mat));
			return EulerAngles(e.z, e.y, e.x);
		}

		inline Mat4 makeMat4(const EulerAngles& euler) {
			return glm::mat4_cast(makeQuat(euler));
		}

		inline Mat3 makeMat3(const EulerAngles& euler) {
			return glm::mat3_cast(makeQuat(euler));
		}

		inline void setPosition(Mat4& mat, const Vec3f& position) {
			mat[3] = Vec4f(position, 1.0f);
		}

		inline void setRotation(Mat4& mat, const Quat& quat) {
			Vec4f pos = mat[3];
			mat = makeMat4(quat);
			setPosition(mat, Vec3f(pos));
		}

		//##########################################################################

		inline float dot(const Vec3f& vec1, const Vec3f& vec2) {
			return glm::dot(vec1, vec2);
		}

		inline Vec3f cross(const Vec3f& vec1, const Vec3f& vec2) {
			return glm::cross(vec1, vec2);
		}

		inline float len(const Vec2f& vec) {
			return glm::length(vec);
		}

		inline float len(const Vec3f& vec) {
			return glm::length(vec);
		}

		inline float len(const Vec4f& vec) {
			return glm::length(vec);
		}

		inline Vec3f normalize(const Vec3f& vec) {
			return glm::normalize(vec);
		}

		inline Vec2f normalize(const Vec2f& vec) {
			return glm::normalize(vec);
		}

		inline Vec4f normalize(const Vec4f& vec) {
			return glm::normalize(vec);
		}

		//#########################################################################

		inline Vec3f makeUpVec() {
			return Vec3f(0.0f, 0.0f, 1.0f);
		}

		inline Vec3f makeUpVec(const Mat3& mat) {
			return normalize(mat * Vec3f(0.0f, 0.0f, 1.0f));
		}

		inline Vec3f makeUpVec(const Mat4& mat) {
			return normalize(Vec3f(mat * Vec4f(0.0f, 0.0f, 1.0f, 0.0f)));
		}

		inline Vec3f makeRightVec() {
			return Vec3f(1.0f, 0.0f, 0.0f);
		}

		inline Vec3f makeRightVec(const Mat3& mat) {
			return normalize(Vec3f(mat * Vec3f(1.0f, 0.0f, 0.0f)));
		}

		inline Vec3f makeRightVec(const Mat4& mat) {
			return normalize(Vec3f(mat * Vec4f(1, 0.0f, 0.0f, 0.0f)));
		}

		inline Vec3f makeForwardVec() {
			return Vec3f(0.0f, 1.0f, 0.0f);
		}

		inline Vec3f makeForwardVec(const Mat3& mat) {
			return normalize(Vec3f(mat * Vec3f(0.0f, 1.0f, 0.0f)));
		}

		inline Vec3f makeForwardVec(const Mat4& mat) {
			return normalize(Vec3f(mat * Vec4f(0.0f, 1.0f, 0.0f, 0.0f)));
		}

		inline float toRadian(float degree) {
			return glm::radians(degree);
		}

		inline float toDegree(float radian) {
			return glm::degrees(radian);
		}

		/*######################################################
						glm to physx mapper
		##################################################3###*/

		inline Vec3f makeVec3f(const physx::PxVec3& pxVec3) {
			return Vec3f(pxVec3.x, pxVec3.y, pxVec3.z);
		}

		inline Quat makeQuat(const physx::PxQuat& pxQuat) {
			return Quat(pxQuat.w, pxQuat.x, pxQuat.y, pxQuat.z);
		}

		inline Mat4 makeMat4(const physx::PxTransform& pxMat) {
			return makeMat4(makeVec3f(pxMat.p), makeQuat(pxMat.q));
		}

		inline physx::PxVec3 makePxVec3(const Vec3f& vec3f) {
			return physx::PxVec3(vec3f.x, vec3f.y, vec3f.z);
		}

		inline physx::PxQuat makePxQuat(const Quat& quat) {
			return physx::PxQuat(quat.x, quat.y, quat.z, quat.w);
		}

		inline physx::PxTransform makePxTransform(const Vec3f& vec3f, const Quat& quat) {
			return physx::PxTransform(makePxVec3(vec3f), makePxQuat(quat));
		}

		inline physx::PxTransform makePxTransform(const Mat4& mat4) {
			return physx::PxTransform(makePxVec3(Vec3f(mat4[3])), makePxQuat(makeQuat(mat4)));
		}

	}
}




#endif