/*
* openGLWrapper.h
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
#ifndef HELPER_GL_H
#define HELPER_GL_H

#include <string>
#include <GL/glew.h>
#include "../commen/dataTypes.h"


namespace robolab {
	namespace wrapper {
		namespace opengl
		{
			using uint = unsigned int;
			using BitwiseBufferType = int;
			using BitwiseRenderingMode = int;

			enum BufferType {
				BUFFER_VERTEX_ARRAY,
				BUFFER_ATTRIBUTE,
				BUFFER_INDEX
			};

			enum DrawPrimitiveTYPE {
				DRAW_PRIMITIVE_POINT,
				DRAW_PRIMITIVE_LINE,
				DRAW_PRIMITIVE_TRIANGLE
			};

			enum PolygonPrimitiveTYPE {
				POLYGON_PRIMITIVE_POINT,
				POLYGON_PRIMITIVE_LINE,
				POLYGON_PRIMITIVE_FILL
			};

			inline uint initializeGLEW() {
				return glewInit();
			}

			inline std::string getGlewError(uint errorID) {
				return std::string(reinterpret_cast<const char*>(glewGetErrorString(errorID)));
			}

			inline void freeBuffer(uint &glBufferId) {
				glDeleteBuffers(1, &glBufferId);
			}

			inline void freeProgram(uint &glProgramId) {
				glDeleteProgram(glProgramId);
			}

			inline void setBackgroundColor(float red, float green, float blue, float alpha) {
				glClearColor(red, green, blue, alpha);
			}

			inline void clearScreen() {
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			inline void setDrawableArea(int upperX, int upperY, int width, int height) {
				glViewport(upperX, upperY, width, height);
			}

			inline uint checkError() {
				return glGetError();
			}

			inline std::string getOpenGlError(uint errorID) {
				switch (errorID)
				{
				case GL_INVALID_ENUM:
					return "GL_INVALID_ENUM";
					break;
				case GL_INVALID_VALUE:
					return "GL_INVALID_VALUE";
					break;
				case GL_INVALID_OPERATION:
					return "GL_INVALID_OPERATION";
					break;
				case GL_STACK_OVERFLOW:
					return "GL_STACK_OVERFLOW";
					break;
				case GL_STACK_UNDERFLOW:
					return "GL_STACK_UNDERFLOW";
					break;
				case GL_OUT_OF_MEMORY:
					return "GL_OUT_OF_MEMORY";
					break;
				case GL_INVALID_INDEX:
					return "GL_INVALID_INDEX";
					break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:
					return "GL_INVALID_FRAMEBUFFER_OPERATION";
					break;
				default:
					return std::to_string(errorID) + " Unkown";
					break;
				}
			}

			inline uint genBufferID(BufferType type) {
				uint bufferID = 0;
				switch (type)
				{
				case BUFFER_VERTEX_ARRAY:
					glGenVertexArrays(1, &bufferID);
					break;
				case BUFFER_ATTRIBUTE:
				case BUFFER_INDEX:
					glGenBuffers(1, &bufferID);
					break;
				}
				return bufferID;
			}

			inline void setActive(BufferType type, unsigned int bufferID) {
				switch (type)
				{
				case BUFFER_VERTEX_ARRAY:
					glBindVertexArray(bufferID);
					break;
				case BUFFER_ATTRIBUTE:
					glBindBuffer(GL_ARRAY_BUFFER, bufferID);
					break;
				case BUFFER_INDEX:
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
					break;
				}
			}

			inline void addDataToBuffer(BufferType type, const void* bufferData, unsigned long long byteSizeOfData) {
				switch (type)
				{
				case BUFFER_ATTRIBUTE:
					glBufferData(GL_ARRAY_BUFFER, byteSizeOfData, bufferData, GL_DYNAMIC_DRAW);
					break;

				case BUFFER_INDEX:
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSizeOfData, bufferData, GL_DYNAMIC_DRAW);
					break;
				}
			}

			inline void setAttributeShaderLocation(unsigned short shaderLocationID, unsigned short sizeOfAttributeElement) {
				glEnableVertexAttribArray(shaderLocationID);
				glVertexAttribPointer(shaderLocationID, sizeOfAttributeElement, GL_FLOAT, GL_FALSE, 0, 0);
			}

			inline void setInstaceAttributeShaderLocation(unsigned short shaderLocationID, unsigned short sizeOfAttributeElement, std::size_t strid , const void* pointer) {
				glVertexAttribPointer(shaderLocationID, sizeOfAttributeElement, GL_FLOAT, GL_FALSE, (GLsizei)strid, pointer);
				glEnableVertexAttribArray(shaderLocationID);
				glVertexAttribDivisor(shaderLocationID, 1);
			}


			inline void setPolygonMode(PolygonPrimitiveTYPE type, float offsetNear, float offsetFar) {
				switch (type)
				{
				case POLYGON_PRIMITIVE_POINT:
					glEnable(GL_DEPTH_TEST);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glDisable(GL_POLYGON_OFFSET_FILL);
					glDisable(GL_POLYGON_OFFSET_LINE);
					glEnable(GL_POLYGON_OFFSET_POINT);
					glPolygonOffset(offsetNear, offsetFar);
					break;
				case POLYGON_PRIMITIVE_LINE:
					glEnable(GL_DEPTH_TEST);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					glDisable(GL_POLYGON_OFFSET_FILL);
					glDisable(GL_POLYGON_OFFSET_POINT);
					glEnable(GL_POLYGON_OFFSET_LINE);
					glPolygonOffset(offsetNear, offsetFar);
					break;
				case POLYGON_PRIMITIVE_FILL:
					glEnable(GL_DEPTH_TEST);
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					glDisable(GL_POLYGON_OFFSET_LINE);
					glDisable(GL_POLYGON_OFFSET_POINT);
					glEnable(GL_POLYGON_OFFSET_FILL);
					glPolygonOffset(offsetNear, offsetFar);
					break;
				}
			}

			inline uint createShader(std::string vertexSource, std::string fragmentSource)
			{
				std::vector<char> infoLog;

				GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
				const GLchar *source[1];
				GLint sourceLength[1];
				source[0] = (const GLchar *)vertexSource.c_str();
				sourceLength[0] = (GLint)vertexSource.length();
				glShaderSource(vertexShader, 1, source, sourceLength);
				glCompileShader(vertexShader);
				GLint succeed = 0;

				glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succeed);
				if (succeed == GL_FALSE)
				{
					GLint maxLength = 0;
					glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
					infoLog.resize(maxLength);
					glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
					glDeleteShader(vertexShader);
					std::cout << "Error --> GLSL Shader\n\t" << std::string(infoLog.begin(), infoLog.end()) << std::endl;
					return 0;
				}

				GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				source[0] = (const GLchar *)fragmentSource.c_str();
				sourceLength[0] = (GLint)fragmentSource.length();
				glShaderSource(fragmentShader, 1, source, sourceLength);
				glCompileShader(fragmentShader);
				glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succeed);
				if (succeed == GL_FALSE)
				{
					GLint maxLength = 0;
					glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
					infoLog.resize(maxLength);
					glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
					glDeleteShader(fragmentShader);
					glDeleteShader(vertexShader);
					std::cout << "Error --> GLSL Shader\n\t" << std::string(infoLog.begin(), infoLog.end()) << std::endl;
					return 0;
				}

				uint glProgramId = glCreateProgram();
				glAttachShader(glProgramId, vertexShader);
				glAttachShader(glProgramId, fragmentShader);
				glLinkProgram(glProgramId);

				glGetProgramiv(glProgramId, GL_LINK_STATUS, (int *)&succeed);
				if (succeed == GL_FALSE)
				{
					GLint maxLength = 0;
					glGetProgramiv(glProgramId, GL_INFO_LOG_LENGTH, &maxLength);
					infoLog.resize(maxLength);
					glGetProgramInfoLog(glProgramId, maxLength, &maxLength, &infoLog[0]);
					glDeleteProgram(glProgramId);
					glDeleteShader(vertexShader);
					glDeleteShader(fragmentShader);
					std::cout << "Error --> GLSL Shader\n\t" << std::string(infoLog.begin(), infoLog.end()) << std::endl;
					return 0;
				}
				glDetachShader(glProgramId, vertexShader);
				glDetachShader(glProgramId, fragmentShader);
				return glProgramId;
			}

			inline void drawPrimitive(DrawPrimitiveTYPE type, std::size_t primitiveCount) {
				switch (type)
				{
				case DRAW_PRIMITIVE_POINT:
					glDrawElements(GL_POINTS, (GLsizei)primitiveCount, GL_UNSIGNED_INT, 0);
					break;
				case DRAW_PRIMITIVE_LINE:
					glDrawElements(GL_LINES, (GLsizei)primitiveCount, GL_UNSIGNED_INT, 0);
					break;
				case DRAW_PRIMITIVE_TRIANGLE:
					glDrawElements(GL_TRIANGLES, (GLsizei)primitiveCount, GL_UNSIGNED_INT, 0);
					break;
				default:
					break;
				}
			}

			inline void setShader(uint programID) {
				glUseProgram(programID);
			}

			inline int getUniformLocation(uint programID, const std::string& name) {
				return glGetUniformLocation(programID, &name[0]);
			}

			inline void setUniform1ui(unsigned short locationID, uint value) {
				glUniform1ui(locationID, value);
			}

			inline void setUniform1i(unsigned short locationID, int value) {
				glUniform1i(locationID, value);
			}

			inline void setUniform1f(unsigned short locationID, float value) {
				glUniform1f(locationID, value);
			}

			inline void setUniformVec2ui(unsigned short locationID, const uint* vec2ui) {
				glUniform2uiv(locationID, 1, vec2ui);
			}

			inline void setUniformVec3ui(unsigned short locationID, const uint* vec3ui) {
				glUniform3uiv(locationID, 1, vec3ui);
			}

			inline void setUniformVec4ui(unsigned short locationID, const uint* vec4ui) {
				glUniform4uiv(locationID, 1, vec4ui);
			}


			inline void setUniformVec2i(unsigned short locationID, const int* vec2i) {
				glUniform2iv(locationID, 1, vec2i);
			}

			inline void setUniformVec3i(unsigned short locationID, const int* vec3i) {
				glUniform3iv(locationID, 1, vec3i);
			}

			inline void setUniformVec4i(unsigned short locationID, const int* vec4i) {
				glUniform4iv(locationID, 1, vec4i);
			}

			inline void setUniformVec2f(unsigned short locationID, const float* vec2f) {
				glUniform2fv(locationID, 1, vec2f);
			}

			inline void setUniformVec3f(unsigned short locationID, const float* vec3f) {
				glUniform3fv(locationID, 1, vec3f);
			}

			inline void setUniformVec4f(unsigned short locationID, const float* vec4f) {
				glUniform4fv(locationID, 1, vec4f);
			}

			inline void setUniformMat3(unsigned short locationID, const float* mat3) {
				glUniformMatrix3fv(locationID, 1, GL_FALSE, mat3);
			}

			inline void setUniformMat4(unsigned short locationID, const float* mat4) {
				glUniformMatrix4fv(locationID, 1, GL_FALSE, mat4);
			}

			template<typename T>
			inline std::vector<T> getBufferElements(uint bufferID, uint index, uint nrOfElements) {
				std::vector<T> elements;
				glBindBuffer(GL_ARRAY_BUFFER, bufferID);
				T* element = ((T*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)) + (index);
				if (element) {
					for (auto i = 0; i < nrOfElements; i++) {
						elements.push_back(*element);
						element++;
					}
				}
				glUnmapBuffer(GL_ARRAY_BUFFER);
				return elements;
			}

			template<typename T>
			inline void setBufferElements(uint bufferID, uint index, std::vector<T>& elements) {
				glBindBuffer(GL_ARRAY_BUFFER, bufferID);
				T* element = ((T*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)) + (index);
				if (element) {
					for (auto i = 0; i < elements.size(); i++) {
						*element = elements[i];
						element++;
					}
				}
				glUnmapBuffer(GL_ARRAY_BUFFER);
			}
		};

	}
}

#endif // !RENDERER_H


