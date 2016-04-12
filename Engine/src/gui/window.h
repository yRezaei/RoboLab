#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <SDL.h>
#include "../wrapper/openGLWrapper.h"
#include "../system/input.h"

namespace robolab {
	namespace gui {

		class Window
		{
		protected:
			SDL_Window *window; /* Our window handle */
			SDL_GLContext glContext; /* Our opengl context handle */
		private:
			std::string title;
			Vec2i size;
			bool isWindowOK, isWindowResized;
			system::InputEvent inputEvent;
		private:
			void handleEvent(system::InputEvent& inputEvent);
		public:
			Window();
			~Window();
			bool initialize(const std::string& name, unsigned int Width, unsigned int Height);
			void shutdown();
			bool checkError(const std::string& location);
			SDL_Window* getPtr();
			void update();
			bool isOK();
			void setTitle(const std::string& title);
			void setBackgroundColor(float red, float green, float blue, float alpha);
			std::string getTitle() const;
			Vec2i getSize();
			int getWidth();
			int getHeight();
			void setVsync(bool value);
		};

	}
}

#endif