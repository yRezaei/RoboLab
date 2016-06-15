#include "window.h"
#include <stdlib.h>
#include <stdio.h>
#include "../system/logging.h"


namespace robolab {
	namespace gui {

		Window::Window() {
			isWindowResized = false;
		}

		Window::~Window() {
		}

		bool Window::initialize(const std::string& Title, unsigned int Width, unsigned int Height) {
			title = Title;
			size = Vec2ui(Width, Height);
			isWindowOK = false;

			if (SDL_Init(SDL_INIT_VIDEO) < 0) {
				system::Logging::console(system::LOG_ERROR, "SDL inisialization FAILED.", LOCATION);
				shutdown();
				return false;
			}
			else {
				system::Logging::console(system::LOG_INFORMATION,  "SDL inisialization OK." );
			}

			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			
			window = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				size.x, size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			
			if (!window) {
				system::Logging::console(system::LOG_ERROR, "SDL window creation FAILED.", LOCATION);
				shutdown();
				return false;
			}
			else {		
				system::Logging::console(system::LOG_INFORMATION, "SDL window creation OK.");
			}
			if (checkError(LOCATION))
				return false;

			glContext = SDL_GL_CreateContext(window);
			if (checkError(LOCATION))
				return false;

			glewExperimental = GL_TRUE;
			unsigned int errorID = 0;
			if ((errorID = wrapper::opengl::initializeGLEW()) != 0) {
				system::Logging::console(system::LOG_ERROR, "GLEW -> " + wrapper::opengl::getGlewError(errorID), LOCATION);
				return false;
			}
			else {
				system::Logging::console(system::LOG_INFORMATION, "GLEW is initialized.");
			}
	
			setVsync(true);

			update();
			isWindowOK = true;
			return isWindowOK;
		}

		void Window::shutdown() {
			if(glContext)
				SDL_GL_DeleteContext(glContext);
			if(window)
				SDL_DestroyWindow(window);
			SDL_Quit();
		}

		bool Window::checkError(const std::string& location) {
			std::string error = SDL_GetError();
			if (!error.empty())
			{
				system::Logging::console(system::LOG_ERROR, "SDL -> " + error, location);
				SDL_ClearError();
				return true;
			}
			else
				return false;
		}


		void Window::update() {
			SDL_GL_SwapWindow(window);	
			handleEvent(inputEvent);
		}

		bool Window::isOK() {
			return isWindowOK;
		}

		void Window::setTitle(const std::string& title) {
			SDL_SetWindowTitle(window, title.c_str());
		}

		std::string Window::getTitle() const {
			return title;
		}

		void Window::setBackgroundColor(float red, float green, float blue, float alpha) {
			wrapper::opengl::setBackgroundColor(red, green, blue, alpha);
		}

		Vec2i Window::getSize() {
			SDL_GetWindowSize(window, &size[0], &size[1]);
			return size;
		}

		int Window::getWidth() {
			SDL_GetWindowSize(window, &size[0], &size[1]);
			return size.x;
		}

		int Window::getHeight() {
			SDL_GetWindowSize(window, &size[0], &size[1]);
			return size.y;
		}

		void Window::setVsync(bool value) {
			SDL_GL_SetSwapInterval(value);
		}

		SDL_Window* Window::getPtr() {
			return window;
		}

		void Window::handleEvent(system::InputEvent& inputEvent) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				switch (event.type)
				{
				case SDL_QUIT:
					isWindowOK = false;
					break;
				case SDL_WINDOWEVENT:
				{
					switch (event.window.event) 
					{
					case SDL_WINDOWEVENT_RESIZED:
						isWindowResized = true;
						size = Vec2i(event.window.data1, event.window.data2);
						break;
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						isWindowResized = true;
						size = Vec2i(event.window.data1, event.window.data2);
						break;
					case SDL_WINDOWEVENT_MINIMIZED:
						//SDL_Log("Window %d minimized", event->window.windowID);
						break;
					case SDL_WINDOWEVENT_MAXIMIZED:
						//SDL_Log("Window %d maximized", event->window.windowID);
						break;
					case SDL_WINDOWEVENT_CLOSE:
						isWindowOK = false;
						break;
					default:
						//SDL_Log("Window %d got unknown event %d", event->window.windowID, event->window.event);
						break;
					}
				}
				break;

				case SDL_MOUSEBUTTONDOWN:
				{
					switch (event.button.button)
					{
					case SDL_BUTTON(SDL_BUTTON_LEFT):
						inputEvent.mouseState[system::MOUSE_BUTTON_LEFT] = true;
						break;
					case SDL_BUTTON(SDL_BUTTON_MIDDLE):
						inputEvent.mouseState[system::MOUSE_BUTTON_MIDDLE] = true;
						break;
					case SDL_BUTTON(SDL_BUTTON_RIGHT):
						inputEvent.mouseState[system::MOUSE_BUTTON_RIGHT] = true;
						break;
					default:
						break;
					}
				}
				break;

				case SDL_MOUSEBUTTONUP:
				{
					switch (event.button.button)
					{
					case SDL_BUTTON(SDL_BUTTON_LEFT):
						inputEvent.mouseState[system::MOUSE_BUTTON_LEFT] = false;
						break;
					case SDL_BUTTON(SDL_BUTTON_MIDDLE):
						inputEvent.mouseState[system::MOUSE_BUTTON_MIDDLE] = false;
						break;
					case SDL_BUTTON(SDL_BUTTON_RIGHT):
						inputEvent.mouseState[system::MOUSE_BUTTON_RIGHT] = false;
						break;
					default:
						break;
					}
				}
				break;

				case SDL_MOUSEMOTION:
					inputEvent.isMouseMoving = true;
					inputEvent.mousePos = Vec2i(event.motion.x, event.motion.y);
					break;
				case SDL_MOUSEWHEEL:
					inputEvent.isWheelRotating = true;
					inputEvent.mouseWheel = Vec2i(event.wheel.x, event.wheel.y);
					break;
				default:
					break;
				}
			}

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			for (auto i = 0; i < 283; i++) {
				if(state[i] == 0)
					inputEvent.keyState[i] = false;
				else
					inputEvent.keyState[i] = true;
			}
			system::Input::updateInputState(inputEvent);
			inputEvent.reset();
		}

	}
}
