#include "input.h"

namespace robolab {
	namespace system {

		std::array<bool, 283> Input::previousKeyState = { 0 };
		std::array<bool, 283> Input::currentKeyState = { 0 };

		std::array<bool, 3> Input::previousMouseState = { 0 };
		std::array<bool, 3> Input::currentMouseState = { 0 };
	
		bool Input::mouseMovement = false;
		bool Input::wheelRotation = false;
		Vec2i Input::mousePosition = Vec2i(0, 0);
		Vec2i Input::wheelDirection = Vec2i(0, 0);

		void Input::updateInputState(InputEvent& inputEvent)
		{
			std::copy(std::begin(currentKeyState), std::end(currentKeyState), std::begin(previousKeyState));
			std::copy(std::begin(inputEvent.keyState), std::end(inputEvent.keyState), std::begin(currentKeyState));

			std::copy(std::begin(currentMouseState), std::end(currentMouseState), std::begin(previousMouseState));
			std::copy(std::begin(inputEvent.mouseState), std::end(inputEvent.mouseState), std::begin(currentMouseState));
			//currentMouseState = inputEvent.mouseState;

			mouseMovement = inputEvent.isMouseMoving;
			wheelRotation = inputEvent.isWheelRotating;
			mousePosition = inputEvent.mousePos;
			wheelDirection = inputEvent.mouseWheel;
		}

		bool Input::KeyPressed(KeyEventType keyEvent) {
			return !previousKeyState[keyEvent] && currentKeyState[keyEvent];
		}

		bool Input::KeyReleased(KeyEventType keyEvent) {
			return previousKeyState[keyEvent] && !currentKeyState[keyEvent];
		}

		bool Input::keyRepeat(KeyEventType keyEvent) {
			return previousKeyState[keyEvent] && currentKeyState[keyEvent];
		}

		bool Input::MousePressed(MouseEventType mouseEvent) {
			return !previousMouseState[mouseEvent] && currentMouseState[mouseEvent];
		}

		bool Input::MouseReleased(MouseEventType mouseEvent) {
			return previousMouseState[mouseEvent] && !currentMouseState[mouseEvent];
		}

		bool Input::MouseRepeat(MouseEventType mouseEvent) {
			return previousMouseState[mouseEvent] && currentMouseState[mouseEvent];
		}

		bool Input::IsMouseMoving() {
			return mouseMovement;
		}

		bool Input::IsMouseWheelRotating() {
			return wheelRotation;
		}


		const Vec2i& Input::MousePos() {
			return mousePosition;
		}

		const Vec2i& Input::MouseWheel() {
			return wheelDirection;
		}

		

	}
}