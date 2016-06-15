/*
* camera.h
*
* Copyright 2016 Yashar Abbasalizadeh Rezaei <yashar.a.rezaei@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*
*/
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

