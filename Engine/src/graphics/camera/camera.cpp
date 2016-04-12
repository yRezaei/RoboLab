#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace robolab {
	namespace graphics {

	Camera::Camera(float filedOfView, float aspectRatio, float zNear, float zFar, CameraType type) {
		_projectionView = Mat4(1.0f);
		_projection = Mat4(1.0f);
		_view = Mat4(1.0f);
		target = Vec3f(0.0f, 0.0f, 0.0f);
		position = Vec3f(0.0f);
		_upVec = Vec3f(0.0f, 0.0f, 1.0f);
		_fieldOfView = filedOfView;
		_aspectRatio = aspectRatio;
		_zNear = zNear;
		_zFar = zFar;
		_type = type;
		pitchAngle = 0;
		yawAngle = 0;
		zoomAmount = 10.0f;

		updateView();
		updateProjection();
	}

	Camera::~Camera() {

	}

	void Camera::updateView() {
		rotation = glm::rotate(Quat(), yawAngle, makeUpVec()) * glm::rotate(Quat(), pitchAngle, makeRightVec());
		position = Vec3f(makeMat3(rotation) * Vec3f(0.0f, zoomAmount, 0.0f)) + target;
		_view = glm::lookAt(position, target, makeUpVec(makeMat4(rotation)));
	}

	void Camera::updateProjection() {

		switch (_type)
		{
		case CAMERA_PERSPECTIVE:
			_projection = glm::perspective(_fieldOfView, _aspectRatio, _zNear, _zFar);
			break;
		case CAMERA_ORTHOGRAPHIC:
			_projection = glm::ortho(0,0,0,0);
			break;
		default:
			//m_projection = Transform(glm::perspective(fov, aspect, zNear, zFar));
			break;
		}
	}

	Mat4 Camera::getProjectionView() {
		return _projection * _view;
	}

	Mat4 Camera::getProjectionMat() {
		return _projection;
	}

	Mat4 Camera::getViewMat() {
		return _view;
	}

	void Camera::rotateAroundTarget(float PitchAngle, float YawAngle) {
		pitchAngle += toRadian(PitchAngle);
		yawAngle += toRadian(YawAngle);	
		updateView();
	}

	void Camera::rotateAroundPosition(float pitchAngle, float yawAngle) {
		/*position = Vec3f(makeMat3(glm::rotate(Quat(), Deg2Rad(pitchAngle), makeRightVec(_view))) * (position));
		position = Vec3f(makeMat3(glm::rotate(Quat(), Deg2Rad(yawAngle), makeUpVec())) * (position));*/
		updateView();
	}

	void Camera::translate(float offsetX, float offsetZ) {
		target += (makeRightVec(makeMat3(rotation)) * (offsetX)) + (makeUpVec() * (offsetZ)); 
		position += (makeRightVec(makeMat3(rotation)) * (offsetX)) + (makeUpVec() * (offsetZ));
		updateView();
	}

	void Camera::zoom(float amount) {
		zoomAmount *= amount;
		updateView();
	}

	void Camera::setFieldOfView(float fieldOfView) {
		_fieldOfView = fieldOfView;
		updateProjection();
	}

	void Camera::setAspectRatio(Vec2i& ScreenSize) {
		screenSize = ScreenSize;
		_aspectRatio = (float)(screenSize.x) / screenSize.y;
		updateProjection();
	}

	void Camera::setClippingPlanes(float zNear, float zFar) {
		_zNear = zNear;
		_zFar = zFar;
		updateProjection();
	}

	Vec3f Camera::getPosition() {
		return position;
	}

	Vec3f Camera::getFocus() {
		return target;
	}

	float Camera::getNear() {
		return _zNear;
	}

	float Camera::getFar() {
		return _zFar;
	}

	float Camera::getFOV() {
		return _fieldOfView;
	}

	Vec3f Camera::getMouse2WorldDirection(Vec2ui& mousePos) {
		Vec3f ray_nds = Vec3f((2.0f * mousePos.x) / screenSize.x - 1.0f,
			1.0f - (2.0f * mousePos.y) / screenSize.y, 1.0f);
		Vec4f ray_clip = Vec4f(ray_nds[0], ray_nds[1], -1.0f, 1.0f);
		Vec4f ray_eye = glm::inverse(getProjectionMat()) * ray_clip;
		return normalize(Vec3f(glm::inverse(getViewMat()) * Vec4f(ray_eye[0], ray_eye[1], -1.0f, 0.0f)));
	}


//double fov = Math3D.DegToRad(FieldOfView);
//double camDistance = (boundSphereRadius * 2.0) / Math.Tan(fov / 2.0);

	}
}