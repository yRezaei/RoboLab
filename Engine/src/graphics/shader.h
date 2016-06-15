/*
* shader.h
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
#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace robolab {
	namespace graphics {

		class Shader
		{
		public:
			static std::string Shader::vertexShaded;
			static std::string Shader::fragmentShaded;

			static std::string Shader::vertexShadedInstance;
			static std::string Shader::fragmentShadedInstance;

			static std::string Shader::vertexWireframe;
			static std::string Shader::fragmentWireframe;

			static std::string Shader::vertexBoundingBox;
			static std::string Shader::fragmentBoundingBox;

			static std::string Shader::vertexPicking;
			static std::string Shader::fragmentPicking;

			static std::string Shader::vertexLine;
			static std::string Shader::fragmentLine;
		};
	}
}



#endif