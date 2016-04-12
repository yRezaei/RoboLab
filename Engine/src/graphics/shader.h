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