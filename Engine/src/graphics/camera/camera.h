#ifndef CAMERA_H
#define CAMERA_H

#include "../../commen/dataTypes.h"
#include "../../mathematic/math3D.h"

namespace robolab {
	namespace graphics {

		enum CameraType {
			CAMERA_PERSPECTIVE,
			CAMERA_ORTHOGRAPHIC
		};

		using namespace math3D;

		class Camera // class Camera
		{
		private:
			Mat4 _projectionView;
			
			Vec3f _upVec;
			float _fieldOfView;
			float _aspectRatio;
			float _zNear;
			float _zFar;
			CameraType _type;
			Mat4 _projection;
			Mat4 _view;
			Vec2i screenSize;
			float yawAngle;
			float pitchAngle;
			Quat rotation;
			float zoomAmount;
		public:
			Vec3f position;
			Vec3f target;
			Camera(float filedOfView, float aspectRatio, float zNear, float zFar, CameraType type);
			~Camera();

		public:
			Mat4 getProjectionView();
			Mat4 getProjectionMat();
			Mat4 getViewMat();
			Vec3f getPosition();
			Vec3f getFocus();
			float getNear();
			float getFar();
			float getFOV();
			void setFieldOfView(float fieldOfView);
			void setAspectRatio(Vec2i& screenSize);
			void setClippingPlanes(float nNear, float nfar);
			void rotateAroundTarget(float PitchAngle, float YawAngle);
			void rotateAroundPosition(float PitchAngle, float YawAngle);
			void translate(float offsetX, float offsetZ);
			void zoom(float amount);
			Vec3f getMouse2WorldDirection(Vec2ui& mousePos);

		private:
			void updateView();
			void updateProjection();

		}; // end of class Camera

	}
}

#endif // !CAMERA_H

