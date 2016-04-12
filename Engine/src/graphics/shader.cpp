#include "shader.h"

#include <iostream>
#include <vector>
#include <GL/glew.h>

namespace robolab {
	namespace graphics {

		std::string Shader::vertexShaded = "#version 330\n"
			"layout(location = 0) in vec3 vertices;\n"
			"layout(location = 1) in vec3 normals;\n"
			"layout(location = 2) in vec3 colors;\n"
			"\n"
			"uniform mat4 ProjectionTransform;\n"
			"uniform mat4 ViewTransform;\n"
			"uniform mat4 ModelTransform;\n"
			"\n"
			"out vec3 mColors;\n"
			"out vec3 mNormals;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = ProjectionTransform * ViewTransform * ModelTransform * vec4(vertices, 1.0);\n"
			"	mColors = colors;\n"
			"	mNormals = normalize((ProjectionTransform * ViewTransform * ModelTransform * vec4(normals, 0.0)).xyz);\n"
			"}\n";

		std::string Shader::fragmentShaded = "#version 330\n"
			"in vec3 mColors;\n"
			"in vec3 mNormals;\n"
			"\n"
			"out vec4 fragmentColor;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	if( gl_FrontFacing ) {\n"
			"		fragmentColor =  vec4(mColors, 1) * clamp(dot(-vec3(0, 0, 1), mNormals), 0.0, 1.0);\n"
			"	} else {\n"
			"		fragmentColor =  vec4(mColors, 1) * clamp(dot(-vec3(0, 0, 1), -mNormals), 0.0, 1.0);\n"
			"	}\n"
			"}\n";

		std::string Shader::vertexShadedInstance = "#version 330\n"
			"layout(location = 0) in vec3 vertices;\n"
			"layout(location = 1) in vec3 normals;\n"
			"layout(location = 2) in vec3 colors;\n"
			"layout(location = 3) in mat4 modelInstanceTransform;\n"
			"\n"
			"uniform mat4 ProjectionTransform;\n"
			"uniform mat4 ViewTransform;\n"
			"\n"
			"out vec3 mColors;\n"
			"out vec3 mNormals;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	gl_Position = ProjectionTransform * ViewTransform * modelInstanceTransform * vec4(vertices, 1.0);\n"
			"	mColors = colors;\n"
			"	mNormals = normalize((ProjectionTransform * ViewTransform * modelInstanceTransform * vec4(normals, 0.0)).xyz);\n"
			"}\n";

		std::string Shader::fragmentShadedInstance = "#version 330\n"
			"in vec3 mColors;\n"
			"in vec3 mNormals;\n"
			"\n"
			"out vec4 fragmentColor;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	if( gl_FrontFacing ) {\n"
			"		fragmentColor =  vec4(mColors, 1) * clamp(dot(-vec3(0, 0, 1), mNormals), 0.0, 1.0);\n"
			"	} else {\n"
			"		fragmentColor =  vec4(mColors, 1) * clamp(dot(-vec3(0, 0, 1), -mNormals), 0.0, 1.0);\n"
			"	}\n"
			"}\n";

		std::string Shader::vertexWireframe = "#version 330\n"
			"layout(location = 0) in vec3 vertices;\n"
			"uniform mat4 ModelViewProjectionTransform;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = ModelViewProjectionTransform * vec4(vertices, 1.0);\n"
			"}\n";

		std::string Shader::fragmentWireframe = "#version 330\n"
			"uniform vec3 wireFrameColor;\n"
			"out vec3 fragmentColor;\n"
			"void main()\n"
			"{\n"
			"	fragmentColor =  wireFrameColor;\n"
			"}\n";

		std::string Shader::vertexBoundingBox = "#version 330\n"
			"layout(location = 0) in vec3 vertices;\n"
			"uniform mat4 ProjectionTransform;\n"
			"uniform mat4 ViewTransform;\n"
			"uniform mat4 ModelTransform;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = ProjectionTransform * ViewTransform * ModelTransform * vec4(vertices, 1.0);\n"
			"}\n";

		std::string Shader::fragmentBoundingBox = "#version 330\n"
			"out vec3 fragmentColor;\n"
			"void main()\n"
			"{\n"
			"	fragmentColor =  vec3(0.0, 1.0, 0.0);\n"
			"}\n";

		std::string Shader::vertexPicking = "#version 330\n"
			"layout(location = 0) in vec3 vertices;\n"
			"uniform mat4 ModelViewProjectionTransform; \n"
			"void main()\n"
			"{\n"
			"	gl_Position = ModelViewProjectionTransform * vec4(vertices, 1.0); \n"
			"}\n";

		std::string Shader::fragmentPicking = "#version 330\n"
			"uniform uint drawIndex; \n"
			"uniform uint objectIndex; \n"
			"out vec3 fragmentColor; \n"
			"void main()\n"
			"{\n"
			"	fragmentColor = vec3(float(objectIndex), float(drawIndex), float(gl_PrimitiveID+1)); \n"
			"}\n";

		std::string Shader::vertexLine = "#version 330\n"
			"layout(location = 0) in vec3 vertices;\n"
			"uniform mat4 ModelViewProjectionTransform;\n"
			"void main()\n"
			"{\n"
			"	gl_Position = ModelViewProjectionTransform * vec4(vertices, 1.0); \n"
			"}\n";

		std::string Shader::fragmentLine = "#version 330\n"
			"out vec3 fragmentColor;\n"
			"void main()\n"
			"{\n"
			"	fragmentColor = vec3(0.0, 1.0, 0.0); \n"
			"}\n";

	}
}
