/*
* window.h
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
			SDL_Window *window;
			SDL_GLContext glContext;
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