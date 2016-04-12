#include "customErrorCallback.h"
#include "../system/logging.h"

namespace robolab {
	namespace wrapper {

		CustomErrorCallback::CustomErrorCallback() {}
		CustomErrorCallback::~CustomErrorCallback() {}

		void CustomErrorCallback::reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) {
			system::Logging::console(system::LOG_ERROR, std::string(message), std::string(file) + std::to_string(line));
		}

	}
}