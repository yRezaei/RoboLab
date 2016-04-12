#ifndef BP_VALID_SURFACE_POINT_INSTANCE_H
#define BP_VALID_SURFACE_POINT_INSTANCE_H


#include "../src/engine.h"

class BP_validSurfacePointInstance : public IBlueprint
{
public:
	Vec3f rootPos;
	bool isPositionValid;
	Vec3f targetPosition;
	bool isPointValid = false;
	bool istestDone = false;
	float start;
	float surfaceRadius;
	Bounds* surfaceObjectBounds;
	std::shared_ptr<RigidObject> dropObject;
	std::shared_ptr<RigidObject> surfacePbject;
	std::string dropObjectName;
	std::string surfaceObjectName;
	bool hasTask;
	Vec3f testPoint;

	std::size_t testIndex;

	float resetTime;
	bool resultsPickedUp;
public:
	BP_validSurfacePointInstance(const Vec3f& root, const std::string& DropObjectName, const std::string& SurfaceObjectName) {
		rootPos = root;
		dropObjectName = DropObjectName;
		surfaceObjectName = SurfaceObjectName;
		hasTask = false;
		istestDone = false;
		isPointValid = false;
		testIndex = 0;
		start = 0;
	}

	~BP_validSurfacePointInstance() {
	}

	void init() override {
		if (ResourceMgr::existRenderMesh(dropObjectName)) {
			dropObject = std::make_shared<RigidObject>(dropObjectName, makeMat4(rootPos), dropObjectName, true);
		}

		if (ResourceMgr::existRenderMesh(surfaceObjectName)) {
			surfacePbject = std::make_shared<RigidObject>(surfaceObjectName, makeMat4(rootPos), surfaceObjectName, false);
			surfaceObjectBounds = &ResourceMgr::getRenderMesh(surfaceObjectName)->bounds;
		}
	}

	void setTestPoint(Vec3f& newTestPoint) {
		testPoint = newTestPoint;
		dropObject->setTransform(makeMat4(rootPos + testPoint));
		hasTask = true;
		isPointValid = false;
		resetTime = 0.0f;
	}

	Vec3f& getTestPoint() {
		return testPoint;
	}

	void update(float deltaTime) override {
		if (hasTask) {
			CollisionInfo hit;
			if (dropObject->onCollision(hit)) {
				isPointValid = true;
				istestDone = true;
				hasTask = false;
				resetTime = 0.0f;
			}

			if (resetTime > 1.5f) {
				isPointValid = false;
				istestDone = true;
				hasTask = false;
				resetTime = 0.0f;
			}
			else
				resetTime += deltaTime;
		}
	}

	void destroy() override {
	}


};

#endif // !BP_VALIDATION_INSTANCE_H

